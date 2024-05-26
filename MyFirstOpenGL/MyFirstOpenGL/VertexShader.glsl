#version 440 core

layout(location = 0) in vec3 inputVertex; 

void main() {
	// Asignar el vértice sin modificar
	gl_Position = vec4(inputVertex, 1.0);
}


