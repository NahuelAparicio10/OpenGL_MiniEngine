#include "MeshRenderer.h"

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

    float time = glfwGetTime(); // Obtener el tiempo actual
    float cycleTime = 20.0f; // Ciclo de 20 segundos
    float dayPhase = fmod(time, cycleTime) / cycleTime; // Normalizar el tiempo en un rango [0, 1]

    // Calculate the positions of the sun and moon
    float angle = dayPhase * 2.0f * 3.14f;
    glm::vec3 sunDirection = glm::vec3(cos(angle), sin(angle), -3.0f);
    glm::vec3 moonDirection = glm::vec3(cos(angle + 3.14f), sin(angle + 3.14f), -3.0f);

    // Ambient light color change
    glm::vec3 ambientColor = glm::vec3(0.2f, 0.2f, 0.5f) * (1.0f - abs(cos(angle))) + glm::vec3(1.0f, 0.9f, 0.7f) * abs(cos(angle));
    float ambientIntensity = 0.5f;

    // Sun and moon light colors
    glm::vec3 sunColor = glm::vec3(1.0f, 0.9f, 0.7f);
    glm::vec3 moonColor = glm::vec3(0.2f, 0.2f, 0.5f);

    glUniform1f(glGetUniformLocation(myProgram, "opacity"), material.opacity);
    glUniform3fv(glGetUniformLocation(myProgram, "ambientColor"), 1, glm::value_ptr(ambientColor));
    glUniform1f(glGetUniformLocation(myProgram, "ambientIntensity"), ambientIntensity);
    glUniform3fv(glGetUniformLocation(myProgram, "sunColor"), 1, glm::value_ptr(sunColor));
    glUniform3fv(glGetUniformLocation(myProgram, "moonColor"), 1, glm::value_ptr(moonColor));
    glUniform3fv(glGetUniformLocation(myProgram, "sunDirection"), 1, glm::value_ptr(glm::normalize(sunDirection)));
    glUniform3fv(glGetUniformLocation(myProgram, "moonDirection"), 1, glm::value_ptr(glm::normalize(moonDirection)));
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


