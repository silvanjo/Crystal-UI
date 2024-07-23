#version 330 core

in vec4 vertexColor;

out vec4 FragColor;

uniform float cornerRadius;

void main() {
    FragColor = vertexColor;
}