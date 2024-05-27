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

    glUniform1f(glGetUniformLocation(myProgram, "opacity"), material.opacity);
    glUniform3fv(glGetUniformLocation(myProgram, "ambient"), 1, glm::value_ptr(material.ambient));
    glUniform3fv(glGetUniformLocation(myProgram, "diffuse"), 1, glm::value_ptr(material.diffuse));

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


