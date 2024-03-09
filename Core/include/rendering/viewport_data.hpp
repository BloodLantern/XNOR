#pragma once

#include "core.hpp"
#include "frame_buffer.hpp"
#include "render_pass.hpp"

BEGIN_XNOR_CORE
class ViewportData
{
public:
    // Deferred Rendering
    RenderPass gbufferPass{};
    FrameBuffer* gframeBuffer = nullptr;
    Texture* positionAtttachment = nullptr;
    Texture* normalAttachement = nullptr;
    Texture* albedoAttachment = nullptr;
    
    // Forward Rendering
    RenderPass colorPass{};
    FrameBuffer* renderBuffer = nullptr;
    Texture* colorAttachment = nullptr;
    Texture* depthAtttachment = nullptr;
    Texture* meshDrawIdDrawCall = nullptr;
    
    ViewportData() = default;

    ~ViewportData() = default;  

    void Init(Vector2i windowSize);
    
    void Destroy();

private:
    void InitForward(Vector2i windowSize);

    void InitDeffered(Vector2i windowSize);

};


END_XNOR_CORE