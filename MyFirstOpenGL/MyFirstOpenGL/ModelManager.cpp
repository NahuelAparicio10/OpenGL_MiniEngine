#include "ModelManager.h"

ModelManager::ModelManager()
{
	GenerateModels();
}

ModelManager::~ModelManager()
{
	for (Model* model : models)
	{
		delete model;
	}
}

// -- Generates Model with texture, material and ProgramID

void ModelManager::GenerateModels()
{
	models.push_back(LoadOBJModel(0, "Assets/Models/landscape.obj", "Assets/Textures/landscape/landscape.jpeg", "Assets/Materials/landscape.mtl", GL_TEXTURE0, ModelType::Terrain));
	models.push_back(LoadOBJModel(0, "Assets/Models/rock.obj", "Assets/Textures/rock/rock.jpeg", "Assets/Materials/rock.mtl", GL_TEXTURE1, ModelType::Rock));
	models.push_back(LoadOBJModel(0, "Assets/Models/bush.obj", "Assets/Textures/bush/bush.png", "Assets/Materials/bush.mtl", GL_TEXTURE2, ModelType::Bush));
	models.push_back(LoadOBJModel(0, "Assets/Models/trunk.obj", "Assets/Textures/tronc.jpeg", "Assets/Materials/trunk.mtl", GL_TEXTURE3, ModelType::Tree));
	models.push_back(LoadOBJModel(1, "Assets/Models/sun.obj", "Assets/Textures/sun.jpeg", "Assets/Materials/sun.mtl", GL_TEXTURE4, ModelType::Sun));
	models.push_back(LoadOBJModel(1, "Assets/Models/sun.obj", "Assets/Textures/moon.jpeg", "Assets/Materials/sun.mtl", GL_TEXTURE5, ModelType::Moon));
}

Model* ModelManager::GetModelByType(ModelType type)
{
	if (!models.empty())
	{
		for (Model* model : models)
		{
			if (model->GetType() == type) {
				return model;
			}
		}
	}
	return nullptr;
}

Model* ModelManager::LoadOBJModel(int IDProgram, const std::string& filePath, const char* texturefilePath, const std::string& matFilePath, GLenum textureUnit, ModelType type)
{
	//Verifico archivo y si no puedo abrirlo cierro aplicativo
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "No se ha podido abrir el archivo: " << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//Variables lectura fichero
	std::string line;
	std::stringstream ss;
	std::string prefix;
	glm::vec3 tmpVec3;
	glm::vec2 tmpVec2;

	//Variables elemento modelo
	std::vector<float> vertexs;
	std::vector<float> vertexNormal;
	std::vector<float> textureCoordinates;

	//Variables temporales para algoritmos de sort
	std::vector<float> tmpVertexs;
	std::vector<float> tmpNormals;
	std::vector<float> tmpTextureCoordinates;

	//Recorremos archivo linea por linea
	while (std::getline(file, line)) {

		//Por cada linea reviso el prefijo del archivo que me indica que estoy analizando
		ss.clear();
		ss.str(line);
		ss >> prefix;

		//Estoy leyendo un vertice
		if (prefix == "v") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector de vertices los valores
			tmpVertexs.push_back(tmpVec3.x);
			tmpVertexs.push_back(tmpVec3.y);
			tmpVertexs.push_back(tmpVec3.z);
		}

		//Estoy leyendo una UV (texture coordinate)
		else if (prefix == "vt") {

			//Las UVs son siempre imagenes 2D asi que uso el tmpvec2 para almacenarlas
			ss >> tmpVec2.x >> tmpVec2.y;

			//Almaceno en mi vector temporal las UVs
			tmpTextureCoordinates.push_back(tmpVec2.x);
			tmpTextureCoordinates.push_back(tmpVec2.y);

		}

		//Estoy leyendo una normal
		else if (prefix == "vn") {

			//Asumo que solo trabajo 3D así que almaceno XYZ de forma consecutiva
			ss >> tmpVec3.x >> tmpVec3.y >> tmpVec3.z;

			//Almaceno en mi vector temporal de normales las normales
			tmpNormals.push_back(tmpVec3.x);
			tmpNormals.push_back(tmpVec3.y);
			tmpNormals.push_back(tmpVec3.z);

		}

		//Estoy leyendo una cara
		else if (prefix == "f") {

			int vertexData;
			short counter = 0;

			//Obtengo todos los valores hasta un espacio
			while (ss >> vertexData) {

				//En orden cada numero sigue el patron de vertice/uv/normal
				switch (counter) {
				case 0:
					//Si es un vertice lo almaceno - 1 por el offset y almaceno dos seguidos al ser un vec3, salto 1 / y aumento el contador en 1
					vertexs.push_back(tmpVertexs[(vertexData - 1) * 3]);
					vertexs.push_back(tmpVertexs[((vertexData - 1) * 3) + 1]);
					vertexs.push_back(tmpVertexs[((vertexData - 1) * 3) + 2]);
					ss.ignore(1, '/');
					counter++;
					break;
				case 1:
					//Si es un uv lo almaceno - 1 por el offset y almaceno dos seguidos al ser un vec2, salto 1 / y aumento el contador en 1
					textureCoordinates.push_back(tmpTextureCoordinates[(vertexData - 1) * 2]);
					textureCoordinates.push_back(tmpTextureCoordinates[((vertexData - 1) * 2) + 1]);
					ss.ignore(1, '/');
					counter++;
					break;
				case 2:
					//Si es una normal la almaceno - 1 por el offset y almaceno tres seguidos al ser un vec3, salto 1 / y reinicio
					vertexNormal.push_back(tmpNormals[(vertexData - 1) * 3]);
					vertexNormal.push_back(tmpNormals[((vertexData - 1) * 3) + 1]);
					vertexNormal.push_back(tmpNormals[((vertexData - 1) * 3) + 2]);
					counter = 0;
					break;
				}
			}
		}
	}

	return new Model(IDProgram, texturefilePath, matFilePath, vertexs, textureCoordinates, vertexNormal, textureUnit, type);
}