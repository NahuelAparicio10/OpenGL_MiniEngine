#include "Texture.h"

//GL_TEXTURE0
void Texture::InitializeTexture(const char* filePath, GLenum _textureUnit)
{
    int width, height, nrChannels;
    unsigned char* textureInfo = stbi_load(filePath, &width, &height, &nrChannels, 0);
    
    //Definimos canal de textura activo
    glActiveTexture(_textureUnit);

    GLuint _textureID;
    glGenTextures(1, &_textureID);

    //Vinculamos texture
    glBindTexture(GL_TEXTURE_2D, _textureID);

    //Configurar textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Cargar imagen a la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureInfo);

    //Generar mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    //Liberar memoria de la imagen cargada
    stbi_image_free(textureInfo);
    textureID = _textureID;
}


