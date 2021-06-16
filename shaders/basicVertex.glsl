#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in float Inputlight;

out vec2 TexCoord;
out float light;

uniform mat4 model;
uniform mat4 projView;

void main()
{
    gl_Position = projView * model * vec4(pos, 1.0);
    TexCoord = texCoord;
    light = Inputlight;
}