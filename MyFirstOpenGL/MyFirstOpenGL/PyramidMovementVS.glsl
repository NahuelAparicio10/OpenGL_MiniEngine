#version 440 core

layout(location = 0) in vec3 posicion;
uniform mat4 translation;
uniform mat4 rotation;
 

void main() {
    mat4 modelMatrix = mat4(1.0f);
    modelMatrix = rotation * modelMatrix;
    modelMatrix = translation * modelMatrix;
    gl_Position = modelMatrix * vec4(posicion, 1.0);
}