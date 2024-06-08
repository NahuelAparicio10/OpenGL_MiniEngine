#include "Material.h"

Material::Material()
{
    ambient = glm::vec3(0.f, 0.f, 0.f);
    diffuse = glm::vec3(0.f, 0.f, 0.f);
    opacity = 0.f;

}

void Material::LoadMaterial(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open material file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string prefix;
        lineStream >> prefix;

        if (prefix == "Ka") {
            lineStream >> this->ambient.r >> this->ambient.g >> this->ambient.b;
        }
        else if (prefix == "Kd") {
            lineStream >> this->diffuse.r >> this->diffuse.g >> this->diffuse.b;
        }
        else if (prefix == "Ke") {
            lineStream >> this->emissive.r >> this->emissive.g >> this->emissive.b;
        }
        else if (prefix == "d") {
            lineStream >> this->opacity;
        }
    }

}
