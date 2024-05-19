#pragma once

#include "core.hpp"
#include "scene/component.hpp"
#include "physics/component/collider.hpp"

/// @file sphere_collider.hpp
/// @brief Defines the XnorCore::BoxCollider class

BEGIN_XNOR_CORE

/// @brief Sphere collider
class SphereCollider : public Collider
{
    REFLECTABLE_IMPL(SphereCollider)

public:
    XNOR_ENGINE SphereCollider() = default; 
    XNOR_ENGINE ~SphereCollider() override = default;
    
    DEFAULT_COPY_MOVE_OPERATIONS(SphereCollider)

    /// @brief Begin function
    XNOR_ENGINE void Begin() override;
    /// @brief Update function
    XNOR_ENGINE void Update() override;

    float_t radius = 1.f;

private:
};

END_XNOR_CORE

REFL_AUTO(type(XnorCore::SphereCollider, bases<XnorCore::Collider>),
    field(radius)
)