#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

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
};

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords; 
} vs_out;


void main()
{
    vec4 pos = model * vec4(aPos, 1.0);
    vs_out.FragPos = vec3(pos);
    vs_out.Normal = mat3(normalInvertMatrix) * aNormal;
    vs_out.TexCoords = aTexCoords;
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
}
