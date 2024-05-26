#version 440 core

layout(location = 0) in vec3 posicion;
uniform mat4 scale;
uniform mat4 rotation;



void main() {
    mat4 modelMatrix = mat4(1.0f);
    modelMatrix = rotation * scale * modelMatrix;
    gl_Position = modelMatrix * vec4(posicion, 1.0);
}