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
uniform vec3 spotLightPos;
uniform vec3 spotLightDir;
uniform float spotLightCutOff; 
uniform float spotLightMaxDist;
uniform vec3 spotLightColor;
uniform float spotLightIntensity;

void main() {

    vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
    vec4 baseColor = texture(textureSampler, adjustedTexCoord);

    vec3 normal = normalize(normalsFragmentShader);
    
    vec3 lightToFragment = normalize(primitivePosition.xyz - spotLightPos);

    // Angle between lantern and fragment
    float theta = dot(spotLightDir, lightToFragment);
    
    float distanceToLight = distance(spotLightPos, primitivePosition.xyz);

    // Calcula la intensidad de la luz de la linterna basándose en el ángulo y la distancia
    vec3 spotlightEffect = vec3(0.0);
    if (theta > spotLightCutOff && distanceToLight < spotLightMaxDist) {
        float distanceIntensity = clamp(1.0 - (distanceToLight / spotLightMaxDist), 0.5, 1.0);
        spotlightEffect = spotLightColor * distanceIntensity * spotLightIntensity;
    }


    // Astro Light Calculation
    float sunLightIntensity = max(dot(normal, astroDirection), 0.0);
    sunLightIntensity = max(sunLightIntensity, minDiffuseLight);
    vec3 lighting = astroColor * sunLightIntensity;
    
    // Lantern Light + Ambient Light
    vec3 finalLighting = lighting + spotlightEffect;

    // Calcula el color final multiplicando por el color base
    vec3 finalColor = baseColor.rgb * (ambientColor * ambientIntensity + finalLighting);

    fragColor = vec4(finalColor, opacity);
}
