﻿#include "windows/header_window.hpp"

#include <ImGui/imgui.h>

#include "world.hpp"
#include "file/file_manager.hpp"
#include "resource/resource_manager.hpp"
#include "scene/scene.hpp"
#include "utils/utils.hpp"

using namespace XnorEditor;
using namespace XnorCore;

HeaderWindow::HeaderWindow(Editor* editor)
    : UiWindow(editor)
{
    m_PauseButtonPng = FileManager::Get("assets/editor/PauseButton.png");
    m_PauseButton =  ResourceManager::Load<Texture>(m_PauseButtonPng);
    
    m_PlayButtonPng = FileManager::Get("assets/editor/PlayButton.png");
    m_PlayButton = ResourceManager::Load<Texture>(m_PlayButtonPng);

    m_StopButtonPng = FileManager::Get("assets/editor/StopButton.png");
    m_StopButton = ResourceManager::Load<Texture>(m_StopButtonPng);
}

void HeaderWindow::Display()
{
    ImGui::Begin("HeaderWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);

    FetchInfo();
    
    // Value to offset the little gray image from imgui
    constexpr size_t nbrOfImages = 2;

    m_ImageSize = TileBaseSize;
    
    for (size_t i = 0; i < nbrOfImages; i++)
    {
        constexpr float_t constantOffsetValue = 1.5f;
        const float_t offSet = m_ImageSize * static_cast<float_t>(nbrOfImages - (i + 1)) * constantOffsetValue;
        const float_t x = (static_cast<float_t>(m_Size.x) - m_ImageSize) * 0.5f;
        const float_t y = (static_cast<float_t>(m_Size.y) - m_ImageSize) * 0.5f;

        m_ImagePos[i].x = x - offSet;
        m_ImagePos[i].y = y;
    }
    
    DisplayOnEditor();
    DisplayOnPlay();
 
    ImGui::End();
}

void HeaderWindow::DisplayOnEditor()
{
    const ImVec2 currentimagePos = { m_ImagePos[0].x,m_ImagePos[0].y };
    ImGui::SetCursorPos(currentimagePos);

    if (ImGui::ImageButton(Utils::IntToPointer<ImTextureID>(m_PlayButton->GetId()), { m_ImageSize, m_ImageSize }))
    {
        World::world->IsPlaying = true;
    }
}

void HeaderWindow::DisplayOnPlay()
{
    if (!World::world->IsPlaying)
        return;
    
    ImVec2 currentimagePos = { m_ImagePos[1].x, m_ImagePos[1].y };

    ImGui::SetCursorPos(currentimagePos);

    if (ImGui::ImageButton(Utils::IntToPointer<ImTextureID>(m_PauseButton->GetId()), { m_ImageSize, m_ImageSize }))
    {
        World::world->IsPlaying = false;
        return;
    }
    
    currentimagePos = { m_ImagePos[0].x, m_ImagePos[0].y };
    ImGui::SetCursorPos(currentimagePos);
    
    if (ImGui::ImageButton(Utils::IntToPointer<ImTextureID>(m_StopButton->GetId()), { m_ImageSize, m_ImageSize }))
    {
        // Reload Scene
    }
}