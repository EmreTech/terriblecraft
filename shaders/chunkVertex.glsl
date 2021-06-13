#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in uint light;

uniform mat4 projView;

out vec3 TexCoord;
out float Light;

void main()
{
   gl_Position = projView * vec4(position, 1.0);

   TexCoord = texCoord;
   Light = light / 5.0f;
}