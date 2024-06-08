#include "MeshRenderer.h"
#include "Engine.h"
MeshRenderer::MeshRenderer(Model* model, GameObject* owner) : _owner(owner), _model(model)
{
    _transform = _owner->GetComponent<Transform>();
    _ambientIntensity = 0.5f;
    _ambientMoon = { 1.0f, 0.9f, 0.7f };
    _ambientSun = { 0.2f, 0.2f, 0.5f };
}

void MeshRenderer::Render(glm::mat4 view)
{
    Camera* _camera = Engine::GetInstance().GetObjectsManager()->GetCamera();
    GLuint myProgram = ProgramManager::GetInstance().compiledPrograms[_model->GetProgramID()];
    glUseProgram(myProgram);

    glm::mat4 translationMatrix = ProgramManager::GetInstance().GenerateTranslationMatrix(_transform->_position + glm::vec3(0.f, 0.f, 0.f));
    glm::vec3 totalRotation = glm::radians(_transform->_rotation);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), totalRotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), totalRotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), totalRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = ProgramManager::GetInstance().GenerateScaleMatrix(_transform->_scale);
    glm::mat4 projection = glm::perspective(_camera->GetfFov(), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, _camera->GetfNear(), _camera->GetfFar());

    glUniform2f(glGetUniformLocation(myProgram, "windowSize"), WINDOW_WIDTH, WINDOW_HEIGHT);
    glUniform1i(glGetUniformLocation(myProgram, "textureSampler"), (int)_model->GetType());
    glUniformMatrix4fv(glGetUniformLocation(myProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(myProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
    glUniformMatrix4fv(glGetUniformLocation(myProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
    glUniformMatrix4fv(glGetUniformLocation(myProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(myProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    const Material& material = *_model->GetMaterial();

    glm::vec3 sunPos = glm::vec3(0, 0, 0) - Engine::GetInstance().GetObjectsManager()->GetSun()->GetComponent<Transform>()->_position;
    glm::vec3 moonPos = glm::vec3(0, 0, 0) - Engine::GetInstance().GetObjectsManager()->GetMoon()->GetComponent<Transform>()->_position;
    glm::vec3 sunDirection = glm::normalize(sunPos); 
    glm::vec3 moonDirection = glm::normalize(moonPos);
        
    float angleSun = glm::degrees(glm::atan(sunDirection.y, sunDirection.x));
    if (angleSun < 0) 
    {
        angleSun += 360.0f; // Normalize 0-360 degrree
    }

    float timeOfDay = Engine::GetInstance().GetTimeManager()->CalculateTimeOfDay();

    glm::vec3 colorLight = Engine::GetInstance().GetMapManager()->GetInterpolatedColor(timeOfDay);

    glm::vec3 ambientColor = glm::mix(_ambientMoon, _ambientSun, GetLightFactor(angleSun));

    glm::vec3 direction = CalculateLightDirection(angleSun, sunDirection, moonDirection);

    // Sends astro (moon, sun) values to shader
    glUniform3fv(glGetUniformLocation(myProgram, "ambientColor"), 1, glm::value_ptr(ambientColor));
    glUniform1f(glGetUniformLocation(myProgram, "ambientIntensity"), _ambientIntensity);
    glUniform3fv(glGetUniformLocation(myProgram, "astroColor"), 1, glm::value_ptr(colorLight));
    glUniform3fv(glGetUniformLocation(myProgram, "astroDirection"), 1, glm::value_ptr(glm::normalize(direction)));
    glUniform1f(glGetUniformLocation(myProgram, "opacity"), material.opacity);
    glUniform1f(glGetUniformLocation(myProgram, "minDiffuseLight"), 0.15f);

    glm::vec3 cameraFront = _camera->GetVectorFront();
    Lantern* lantern = Engine::GetInstance().GetObjectsManager()->GetLantern();
    SpotLight* lanternLight = lantern->GetSpotLight();

    //Sends Lantern & Spotlight values to shader
    glUniform1i(glGetUniformLocation(myProgram, "isEnableLantern"), lantern->IsLanternEnabled());
    glUniform3fv(glGetUniformLocation(myProgram, "spotLightDir"), 1, glm::value_ptr(glm::normalize(lantern->GetTransform()->_vectorFront)));
    glUniform3fv(glGetUniformLocation(myProgram, "spotLightPos"), 1, glm::value_ptr(lantern->GetTransform()->_position));
    glUniform1f(glGetUniformLocation(myProgram, "spotLightInnerCutOff"), glm::cos(glm::radians(lanternLight->GetInnerCutOff())));
    glUniform1f(glGetUniformLocation(myProgram, "spotLightOuterCutOff"), glm::cos(glm::radians(lanternLight->GetOutterCutOff())));
    glUniform1f(glGetUniformLocation(myProgram, "spotLightMaxDist"), lanternLight->GetMaxDistance());
    glUniform3fv(glGetUniformLocation(myProgram, "spotLightColor"), 1, glm::value_ptr(lanternLight->GetLightColor()));
    glUniform1f(glGetUniformLocation(myProgram, "spotLightIntensity"), lanternLight->GetLightIntensity());

    //Vinculo su VAO para ser usado
    glBindVertexArray(_model->GetVAO());

    // Dibujamos
    glDrawArrays(GL_TRIANGLES, 0, _model->GetNumVertex());

    //Desvinculamos VAO
    glBindVertexArray(0);
}

const std::type_index MeshRenderer::GetType()
{
    return typeid(MeshRenderer);
}

// -- Interpolates beetwween sun direction and moon direction
// Tried to interpolate the direction so we could have a smooth change between day/night but it's not working idk why

glm::vec3 MeshRenderer::CalculateLightDirection(float angleSun, glm::vec3 sunDirection, glm::vec3 moonDirection)
{
    float transitionAngle = 180.0f;
    float smoothTransitionAngle = 25.f;

    float startAngle = transitionAngle - smoothTransitionAngle;
    float endAngle = transitionAngle + smoothTransitionAngle;

    float t;
    if (angleSun < startAngle) {
        t = 0.0f;
    }
    else if (angleSun > endAngle) {
        t = 1.0f;
    }
    else {
        t = (angleSun - startAngle) / (2 * smoothTransitionAngle);
    }

    return glm::normalize(glm::mix(sunDirection, moonDirection, t));
}

// Makes realistic fade between day night cycle
// Get Light Fator depending the angle of the sun
// where 90 degrees means full light
// 180 degrees means moderate light
// 270 degrees means no light
// 360 degrees means full light again

float MeshRenderer::GetLightFactor(float angleSun)
{
    float lightFactor;
    if (angleSun >= 90.0f && angleSun <= 270.0f) {
        lightFactor = (angleSun - 90.0f) / 180.0f;
    }
    else {
        if (angleSun < 90.0f) {
            lightFactor = (360.0f - 270.0f + angleSun) / 180.0f;
        }
        else {
            lightFactor = (angleSun - 270.0f) / 180.0f;
        }
        lightFactor = 1.0f - lightFactor;
    }
    return lightFactor;
}
