#version 440 core

layout(location = 0) in vec3 posicion;

void main() {
    gl_Position = vec4(posicion, 1.0);
}