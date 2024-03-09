#pragma once

#include "core.hpp"
#include "rendering/frame_buffer.hpp"
#include "rendering/render_pass.hpp"
#include "resource/model.hpp"
#include "resource/shader.hpp"

/// @file tone_mapping.hpp
/// Defines the XnorCore::ToneMapping class

BEGIN_XNOR_CORE

/// @brief Encapsulates the ACES tone mapping algorithm
class ToneMapping
{
public:
    XNOR_ENGINE ToneMapping() = default;
    
    XNOR_ENGINE ~ToneMapping() = default;

    DEFAULT_COPY_MOVE_OPERATIONS(ToneMapping)

    /// @brief Initializes the shader resources
    XNOR_ENGINE void InitializeResources();
    
    /// @brief Recompiles the underlying shader
    XNOR_ENGINE void RecompileShader();
    
    /// @brief Computes the tone mapping
    /// @param imageWithoutToneMapping Initial image
    /// @param quadModel Quad model
    XNOR_ENGINE void ComputeToneMaping(const Texture& imageWithoutToneMapping, const Pointer<Model>& quadModel) const;
private:
    Pointer<Shader> m_Aces = nullptr;
};

END_XNOR_CORE