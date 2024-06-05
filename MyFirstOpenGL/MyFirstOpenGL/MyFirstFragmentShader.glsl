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
uniform vec3 astroColor;
uniform vec3 astroDirection;
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
    float sunLightIntensity = max(dot(normal, astroDirection), 0.0);
    sunLightIntensity = max(sunLightIntensity, minDiffuseLight);

    // Combine the sunlight and moonlight contributions
    vec3 lighting = (astroColor * sunLightIntensity) ;
    vec3 ambient = ambientColor * ambientIntensity;

    fragColor = vec4(baseColor.rgb * (ambient + lighting), opacity);
}