#version 410 core

in vec2 TexCoords;
out vec4 color;

uniform sampler2D diffuse;

void main() {
  color = vec4(texture(diffuse, TexCoords));
}
