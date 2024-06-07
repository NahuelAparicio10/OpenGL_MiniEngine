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

// Spotlight properties
uniform int isEnableLantern;
uniform vec3 spotLightPos;
uniform vec3 spotLightDir;
uniform float spotLightInnerCutOff; // Inner cutoff angle
uniform float spotLightOuterCutOff; // Outer cutoff angle
uniform float spotLightMaxDist;
uniform vec3 spotLightColor;
uniform float spotLightIntensity;

void main() {

    vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
    vec4 baseColor = texture(textureSampler, adjustedTexCoord);

    vec3 normal = normalize(normalsFragmentShader);

    vec3 spotlightEffect = vec3(0.0);
    if(isEnableLantern == 1)
    {
        vec3 lightToFragment = normalize(primitivePosition.xyz - spotLightPos);

        // Angle Between light and vertex
        float theta = dot(normalize(spotLightDir), lightToFragment);
    
        // Distance between SpotLight origin and vertex
        float distanceToLight = distance(spotLightPos, primitivePosition.xyz);

        // Calculate spotlight intensity based on angle and distance
        if (theta > spotLightOuterCutOff && distanceToLight < spotLightMaxDist) {
            // Calculate intensity based on distance, adjusted within a range
            float distanceIntensity = clamp(1.0 - (distanceToLight / spotLightMaxDist), 0.0, 1.0);
            spotlightEffect = spotLightColor * distanceIntensity * spotLightIntensity;

            // Calculate the falloff within the inner and outer cutoff angles
            float falloff = smoothstep(spotLightOuterCutOff, spotLightInnerCutOff, theta);
            spotlightEffect *= falloff;
        }
    }

    // Calculate astro light intensity
    float sunLightIntensity = max(dot(normal, astroDirection), 0.0);
    sunLightIntensity = max(sunLightIntensity, minDiffuseLight);
    vec3 lighting = astroColor * sunLightIntensity;

    // Combine astro light and spotlight
    vec3 finalLighting = ambientColor * ambientIntensity + lighting + spotlightEffect;

    // Calculate final color by multiplying with base color
    vec3 finalColor = baseColor.rgb * finalLighting;

    // Assign final color to fragment
    fragColor = vec4(finalColor, opacity);
}
