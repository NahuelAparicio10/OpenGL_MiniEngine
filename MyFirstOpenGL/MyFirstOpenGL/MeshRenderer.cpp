#include "MeshRenderer.h"
#include "Engine.h"
MeshRenderer::MeshRenderer(Model* model, GameObject* owner) : _owner(owner), _model(model)
{
    _transform = _owner->GetComponent<Transform>();

}

void MeshRenderer::Render(glm::mat4 view)
{
    // Verificar si _model es válido
    GLuint myProgram = ProgramManager::getInstance().compiledPrograms[_model->GetProgramID()];
    glUseProgram(myProgram);

    glm::mat4 translationMatrix = ProgramManager::getInstance().GenerateTranslationMatrix(_transform->_position + glm::vec3(0.f, 0.f, 0.f));
    glm::vec3 totalRotation = glm::radians(_transform->_rotation);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), totalRotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), totalRotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), totalRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 scaleMatrix = ProgramManager::getInstance().GenerateScaleMatrix(_transform->_scale);
    glm::mat4 projection = glm::perspective(Camera::getInstance().getfFov(), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, Camera::getInstance().getfNear(), Camera::getInstance().getfFar());

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

    glm::vec3 ambientSun = glm::vec3(1.0f, 0.9f, 0.7f);
    glm::vec3 ambientMoon = glm::vec3(0.2f, 0.2f, 0.5f);
    glm::vec3 ambientColor = glm::mix(ambientMoon, ambientSun, GetLightFactor(angleSun));

    glm::vec3 direction = CalculateLightDirection(angleSun, sunDirection, moonDirection);

    float ambientIntensity = 0.5f;

    glUniform3fv(glGetUniformLocation(myProgram, "ambientColor"), 1, glm::value_ptr(ambientColor));
    glUniform1f(glGetUniformLocation(myProgram, "ambientIntensity"), ambientIntensity);
    glUniform3fv(glGetUniformLocation(myProgram, "astroColor"), 1, glm::value_ptr(colorLight));
    glUniform3fv(glGetUniformLocation(myProgram, "astroDirection"), 1, glm::value_ptr(glm::normalize(direction)));
    glUniform1f(glGetUniformLocation(myProgram, "opacity"), material.opacity);
    glUniform1f(glGetUniformLocation(myProgram, "minDiffuseLight"), 0.15f);

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
