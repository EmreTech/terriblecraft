#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in uint Inputlight;

out vec2 TexCoord;
out float light;

uniform mat4 projView;

void main()
{
   gl_Position = projView * vec4(position, 1.0);

   TexCoord = texCoord;
   light = float(Inputlight / 5.0f);
}