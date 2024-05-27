#include <GL/glew.h>
#include <vector>
#include "Texture.h"
#include "Material.h"

#ifndef MODEL_H
#define MODEL_H

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 880


enum ModelType { Rock = 0, Landscape = 1 };

class Model {
public:
    Model(int IDProgram, const char* filePath, const std::string& matFilePath, const std::vector<float>& vertexs, const std::vector<float>& uvs, const std::vector<float>& normals, GLenum textureUnit, ModelType type);

    GLuint GetVAO() { return VAO; };
    GLuint GetVBO() { return VBO; };
    GLuint GetuvVBO() { return uvVBO; };
    GLuint GetNormalsVBO() { return normalsVBO; };
    ModelType GetType() { return _type; };
    unsigned int GetNumVertex() { return numVertexs; };
    int GetProgramID() { return _programID; };
    Material* GetMaterial() { return _material; };
    Texture* GetTexture() { return _texture; };


private:
    Material* _material;
    Texture* _texture;
    GLuint VAO, VBO, uvVBO, normalsVBO;
    ModelType _type;
    unsigned int numVertexs;
    int _programID;
    const char* _filePath;
};

#endif
