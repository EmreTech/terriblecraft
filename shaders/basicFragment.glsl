#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in float light;

uniform sampler2D texture1;

void main()
{
    FragColor = light * texture(texture1, TexCoord);

    if (FragColor.a < 0.1f)
        discard;
    
}