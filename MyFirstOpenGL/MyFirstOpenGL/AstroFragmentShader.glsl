#version 440 core

uniform vec2 windowSize;
uniform sampler2D textureSampler;

in vec2 uvsFragmentShader;

out vec4 fragColor;

void main() {

    vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
    vec4 baseColor = texture(textureSampler, adjustedTexCoord);

    vec4 ambientColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec4 whiteGlow = vec4(1.0, 1.0, 1.0, 1.0);
    float glowIntensity = 0.1; // Ajusta la intensidad del brillo aquí

    // Mixes base color with ambient and glow
    vec4 finalColor = mix(baseColor * ambientColor, whiteGlow, glowIntensity);

    fragColor = finalColor;
}