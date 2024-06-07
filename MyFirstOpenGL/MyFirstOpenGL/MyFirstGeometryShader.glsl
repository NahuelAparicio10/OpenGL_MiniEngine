#version 440 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 uvsGeometryShader[];
in vec3 normalsGeometryShader[];

out vec2 uvsFragmentShader;
out vec3 normalsFragmentShader;
out vec4 primitivePosition;
out vec3 camPositionWorld;
out vec3 camDirectionWorld;

uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform mat4 scaleMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;

void main() {
    mat4 model = translationMatrix * rotationMatrix * scaleMatrix;

    vec3 camPosition = (inverse(view) * vec4(cameraPosition, 1.0)).xyz;
    vec3 camDirection = (inverse(view) * vec4(0.0, 0.0, -1.0, 0.0)).xyz;

    for (int i = 0; i < gl_in.length(); i++) {
        gl_Position = projection * view * model * gl_in[i].gl_Position;
        uvsFragmentShader = uvsGeometryShader[i];
        normalsFragmentShader = mat3(rotationMatrix) * normalsGeometryShader[i];
        primitivePosition = model * gl_in[i].gl_Position;

        camPositionWorld = camPosition;
        camDirectionWorld = camDirection;

        EmitVertex();
    }

    EndPrimitive();
}