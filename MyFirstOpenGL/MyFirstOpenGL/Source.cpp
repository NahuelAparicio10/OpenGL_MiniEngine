#include "ProgramManager.h"
#include "Texture.h"
#include "Engine.h"
#include "Source.h"
#include "Camera.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


std::vector<Model*> models;
Texture* _texture;
void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {


	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
	glUniform2f(glGetUniformLocation(ProgramManager::getInstance().compiledPrograms[0], "windowSize"), iFrameBufferWidth, iFrameBufferHeight);
}




void main() {	
	
	//Definir semillas del rand según el tiempo
	srand(static_cast<unsigned int>(time(NULL)));

	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Configuramos la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_BACK);

	//Indicamos lado del culling

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	
	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {
		Engine::getInstance().Init();
	
		//Cargo Modelos
		GenerateLandscape();
		//GenerateTroll();
		//GenerateRocks();
		//GenerateClouds();
		GenerateDesertRocks();
	

		//Definimos color para limpiar el buffer de color
		glClearColor(5.0f, 186.f, 152.f, 1.0f);

		//Definimos modo de dibujo para cada cara
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();
			
			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			// Updates time, inputs and camera
			Engine::getInstance().Update(window);

			//Render models
			for (Model *model : models)
			{
				model->Render(Camera::getInstance().getViewMatrix());
			}
			
			//Cambiamos buffers
			glFlush();
			glfwSwapBuffers(window);
		}
		glUseProgram(0);

		//We delete programs to avoid overloaded info
		for (int i = 0; i < 4; i++) {
			glDeleteProgram(ProgramManager::getInstance().compiledPrograms[i]);
		}

	}
	else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}

	//Terminate GLFW
	glfwTerminate();





}

void GenerateDesertRocks()
{
	Model* rock1; 
	rock1 = Engine::getInstance().LoadOBJModel(0, "Assets/Models/rock.obj", "Assets/Textures/rock/rock_bc.png", "Assets/Materials/rock.mtl",GL_TEXTURE0, ModelType::Rock);
	rock1->_position = glm::vec3{ 0.f,0.f,0.f };
	rock1->_rotation = glm::vec3{ 0.f,0.f,0.f };
	rock1->_scale = glm::vec3{ 1.f,1.f,1.f };

	models.push_back(rock1);
}





//Generating models logic
void GenerateLandscape()
{
	//Floor with orange texture using porgram 0
	Model* landscape;
	landscape = Engine::getInstance().LoadOBJModel(0, "Assets/Models/landscape.obj", "Assets/Textures/landscape/sand_albedo.jpeg","Assets/Materials/landscape.mtl", GL_TEXTURE1, ModelType::Landscape);
	landscape->_position = glm::vec3{ 0.f,0.f,5.f };
	landscape->_rotation = glm::vec3{ 0.f,0.f,0.f };
	landscape->_scale = glm::vec3{ 1.f,1.f,1.f };
	
	models.push_back(landscape);

}











