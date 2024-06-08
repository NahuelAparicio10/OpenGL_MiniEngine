#version 440 core

layout(location = 0) in vec3 posicion;
layout(location = 1) in vec2 uvsVertexShader;
layout(location = 2) in vec3 normalsVertexShader;

out vec2 uvsGeometryShader;
out vec3 normalsGeometryShader;


void main() {

    uvsGeometryShader = uvsVertexShader;
    normalsGeometryShader = normalsVertexShader;

    gl_Position = vec4(posicion, 1.0);
  

}