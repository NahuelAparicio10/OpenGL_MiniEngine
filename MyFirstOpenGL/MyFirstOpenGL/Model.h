#ifndef MODEL_H
#define MODEL_H
#include "Texture.h"
#include "Material.h"
#include "ProgramManager.h"
#include "Camera.h"
#include "GameObject.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 880


enum ModelType { Rock = 0, Landscape = 1 };
class Model : public GameObject {
public:
    Model(int IDProgram, const char* filePath,const std::string& matFilePath,const std::vector<float>& vertexs, const std::vector<float>& uvs, const std::vector<float>& normals, GLenum textureUnit, ModelType type);
    void Render(glm::mat4 view);
    


private:
    Texture* _texture;
    Material* _material;
    GLuint VAO, VBO, uvVBO, normalsVBO;
    ModelType _type;
    unsigned int numVertexs;
    int _programID;
    const char* _filePath;
};

#endif
