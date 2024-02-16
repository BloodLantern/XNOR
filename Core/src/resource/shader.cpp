#include "resource/shader.hpp"

#include <fstream>
#include <glad/glad.h>

#include "rendering/rhi.hpp"
#include "utils/logger.hpp"

using namespace XnorCore;

void Shader::Load([[maybe_unused]] const uint8_t* buffer, [[maybe_unused]] const int64_t length) 
{
}

void Shader::Load(const File& vertexShader, const File& fragmentShader)
{
    std::string vertexCode;
    GetShaderCode(vertexShader.GetFilepath().generic_string().c_str(), &vertexCode);

    std::string fragmentCode;
    GetShaderCode(fragmentShader.GetFilepath().generic_string().c_str(), &fragmentCode);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Move to rhi
    const uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    RHI::CheckCompilationError(vertex, "VERTEX");

    // Move to rhi
    const uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    RHI::CheckCompilationError(fragment, "FRAGMENT");

    // Move to rhi
    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertex);
    glAttachShader(m_Id, fragment);
    glLinkProgram(m_Id);
    RHI::CheckCompilationError(m_Id, "PROGRAM");
}

XNOR_ENGINE void Shader::Recompile(const File& vertexShader, const File& fragmentShader)
{
    RHI::DestroyShader(m_Id);

    Load(vertexShader, fragmentShader);
}

void Shader::Unload()
{
    return void();
}

uint32_t Shader::GetId() const
{
    return  m_Id;
}


void Shader::GetShaderCode(const char* shaderPath, std::string* shaderCode)
{
    if (!shaderCode || !shaderPath)
        throw std::runtime_error("Shader Path or Shader are nullptr");

    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(shaderPath);
        std::stringstream stream;
        stream << shaderFile.rdbuf();
        shaderFile.close();
        *shaderCode = stream.str();
    }
    catch (std::ifstream::failure& e)
    {
        const std::string what = e.what();
        std::string message = "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:";
        message += what;
        message += '\n';
        Logger::LogError("%s", message.c_str());
    }
}

