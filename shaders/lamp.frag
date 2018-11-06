#version 400 core

out vec4 FragColor;

in vec3 finalColor;

void main()
{
    FragColor = vec4(finalColor, 1.0f);
}