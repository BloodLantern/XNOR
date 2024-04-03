#version 460 core
layout (location = 0) in vec3 aPos;

layout (std140, binding = 0) uniform CameraUniform
{
    mat4 view;
    mat4 projection;
    vec3 cameraPos;
};

layout (std140, binding = 1) uniform ModelUniform
{
    mat4 model;
    mat4 normalInvertMatrix;
    uint drawId;
};

out vec3 WorldPos;

void main()
{
    vec4 Pos4 =  vec4(aPos, 1.0);
    gl_Position = projection * view * model * Pos4;
    WorldPos =  (model * Pos4).xyz;
}