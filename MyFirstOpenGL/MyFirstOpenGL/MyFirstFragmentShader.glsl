#version 440 core

uniform vec2 windowSize;
uniform sampler2D textureSampler;

in vec2 uvsFragmentShader;
in vec3 normalsFragmentShader;
in vec4 primitivePosition;

out vec4 fragColor;

uniform float opacity;
uniform vec3 ambientColor;
uniform float ambientIntensity;
uniform vec3 sunColor;
uniform vec3 moonColor;
uniform vec3 sunDirection;
uniform vec3 moonDirection;
uniform float minDiffuseLight;

struct Light {
    vec3 direction;
    vec3 color;
    float intensity;
};

void main() {
    vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
    vec4 baseColor = texture(textureSampler, adjustedTexCoord);

    vec3 normal = normalize(normalsFragmentShader);

    // Calculate the sunlight contribution
    float sunLightIntensity = max(dot(normal, sunDirection), 0.0);
    sunLightIntensity = max(sunLightIntensity, minDiffuseLight);

    // Calculate the moonlight contribution
    float moonLightIntensity = max(dot(normal, moonDirection), 0.0);
    moonLightIntensity = max(moonLightIntensity, minDiffuseLight);

    // Combine the sunlight and moonlight contributions
    vec3 lighting = (sunColor * sunLightIntensity) + (moonColor * moonLightIntensity);
    vec3 ambient = ambientColor * ambientIntensity;

    fragColor = vec4(baseColor.rgb * (ambient + lighting), opacity);
}