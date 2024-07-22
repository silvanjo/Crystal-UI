#version 330 core

layout (location = 0) in vec2 aPos;

uniform mat4 model;
uniform vec4 color;

out vec4 vertexColor;

void main() {
    gl_Position = model * vec4(aPos.x, aPos.y, 0.0, 1.0);
    vertexColor = color;
}