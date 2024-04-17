﻿#include "resource/skeleton.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "assimp/cimport.h"
#include "utils/logger.hpp"

using namespace XnorCore;

bool_t Skeleton::Load(const uint8_t* const buffer, const int64_t length)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFileFromMemory(buffer, length, aiProcess_Triangulate | aiProcess_PopulateArmatureData);

    if (!scene)
    {
        Logger::LogError("An error occured while loading model: {}. Assimp error: {}", m_Name, importer.GetErrorString());
        return false;
    }

    if (scene->mNumMeshes >= 1 && scene->mMeshes[0]->HasBones())
    {
        return Load(*scene->mMeshes[0]);
    }

    if (!scene->hasSkeletons())
    {
        Logger::LogError("Invalid skeleton format, should contain a skeleton: {}", m_Name);
        return false;
    }

    if (scene->mNumSkeletons > 1)
    {
        Logger::LogError("Invalid skeleton format, should only contain a single skeleton: {}", m_Name);
        return false;
    }

    return Load(*scene->mSkeletons[0]);
}

bool_t Skeleton::Load(const aiSkeleton& loadedData)
{
    m_Bones.Resize(loadedData.mNumBones);
    
    for (size_t i = 0; i < loadedData.mNumBones; i++)
    {
        const aiSkeletonBone* const bone = loadedData.mBones[i];

        const Matrix* const local = reinterpret_cast<const Matrix*>(&bone->mLocalMatrix);
        const Matrix* const globalInv = reinterpret_cast<const Matrix*>(&bone->mOffsetMatrix);

        m_Bones[i].Create(*local, *globalInv);
        m_Bones[i].parentId = bone->mParent;
    }

    ComputeGlobalMatrices();
    
    return true;
}

inline bool_t Skeleton::Load(const aiMesh& loadedData)
{
    const size_t numBones = loadedData.mNumBones;
    
    m_Bones.Resize(numBones);

    List<const aiNode*> boneInfo(numBones);

    for (size_t i = 0; i < numBones; i++)
    {
        const aiBone* const bone = loadedData.mBones[i];

        const Matrix* const local = reinterpret_cast<const Matrix*>(&bone->mOffsetMatrix);
        const Matrix* const globalInv = reinterpret_cast<const Matrix*>(&bone->mOffsetMatrix);

        Bone* b = &m_Bones[i];
        b->name = std::string(bone->mName.data);
        b->Create(*local, *globalInv);
    
        boneInfo[i] = bone->mNode;
    }

    for (size_t i = 0; i < numBones; i++)
    {
        const aiBone* const bone = loadedData.mBones[i];

        for (int32_t j = 0; j < static_cast<int32_t>(numBones); j++)
        {
            if (bone->mNode->mParent == boneInfo[j])
            {
                m_Bones[i].parentId = j;
                m_Bones[j].children.Add(static_cast<int32_t>(i));
                break;
            }
        }
    }

    ComputeGlobalMatrices();

    // PrintBones();
    
    return true;
}

const List<Bone>& Skeleton::GetBones() const
{
    return m_Bones;
}

void Skeleton::ComputeGlobalMatrices()
{
    for (size_t i = 0; i < m_Bones.GetSize(); i++)
    {
        Bone& bone = m_Bones[i];
        const int32_t parentId = bone.parentId;

        if (parentId != -1)
        {
            bone.local = m_Bones[parentId].global.Inverted() * bone.local;

            bone.position = static_cast<Vector3>(bone.local * Vector4(0.f, 0.f, 0.f, 1.f));

            Vector3 position;
            Vector3 scale;
            Vector3 skew;
            Vector4 perspective;
            bone.local.Decompose(&position, &bone.rotation, &scale, &skew, &perspective);
        }
    }
}

void Skeleton::PrintBones() const
{
    for (size_t i = 0; i < m_Bones.GetSize(); i++)
    {
        const Bone& bone = m_Bones[i];
        Logger::LogInfo("{} ; {} ; {}\n{}\n{}\n{}", bone.name, bone.position, Quaternion::ToEuler(bone.rotation) * Calc::Rad2Deg, bone.local, bone.global, bone.globalInverse);
    }
}