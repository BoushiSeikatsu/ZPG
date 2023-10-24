#include "Application.h"
// Including model
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"

void error_callback(int, const char* err_str)
{
	std::cout << "GLFW Error: " << err_str << std::endl;
}


Application::Application()
{
	major = 0;
	minor = 0;
	revision = 0;
	width = 0;
	height = 0;
}

Application::~Application()
{
	for (auto programPair : listOfShaderPrograms)
	{
		delete programPair.second;
		programPair.second = nullptr;
	}
	for (auto matrixPair : listOfTransformations)
	{
		delete matrixPair.second;
		matrixPair.second = nullptr;
	}
	for (auto modelPair : listOfModels)
	{
		delete modelPair.second;
		modelPair.second = nullptr;
	}
}

bool Application::initialize()
{
	glfwSetErrorCallback(error_callback);//Zatim v application, potom presunout do tridy callbacks
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
	
	 //inicializace konkretni verze
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);*/ 
	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//Adding Camera
	Camera* camera = new Camera();
	this->camera = camera;
	//Binding camera into user pointer so we can use it in Callbacks
	glfwSetWindowUserPointer(window, this->camera);
	//Locking cursor in the middle of the screen 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Binding mouse movement callback
	glfwSetCursorPosCallback(window, CameraCallback::onMouseMoved);
	//Binding key pressed callback
	glfwSetKeyCallback(window, CameraCallback::onKeyPressed);
}

bool Application::createShaders()
{
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec4 inColor;"
		"out vec4 outColor;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"void main () {"
		"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);"
		"	  outColor = inColor;"	
		"}";

	/*const char* fragment_shader =
		"#version 330\n"
		"in vec4 outColor;"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = outColor;"
		"}";*/
	const char* vertex_shader2 =
		"#version 400\n"

		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vn;"

		"out vec4 ex_worldPosition;"
		"out vec3 ex_worldNormal;"

		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"

		//"uniform mat3 normalMatrix; (M-1)T"
		"void main() {"
		"ex_worldPosition = modelMatrix * vec4(vp, 1.0);"
		"mat4 normalMatrix = transpose(inverse(modelMatrix));"
		"ex_worldNormal = vec3 ( normalMatrix * vec4 ( vn ,1.0));"
		"gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
		"}";
	const char* fragment_shader =
		"#version 400\n"
		"in vec4 ex_worldPosition;"
		"in vec3 ex_worldNormal;"
		"out vec4 out_Color;"
		"uniform vec3 cameraPosition;"
		"uniform vec3 lightPosition;"
		"uniform vec3 lightColor;"
		"void main() {"
		"vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
		"vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);"
		"out_Color = (ambient) * objectColor;"
		"}";
	const char* fragment_shader2 =
		"#version 400\n"
		"in vec4 ex_worldPosition;"
		"in vec3 ex_worldNormal;"
		"out vec4 out_Color;"
		"uniform vec3 cameraPosition;"
		"uniform vec3 lightPosition;"
		"uniform vec3 lightColor;"
		"void main() {"
		"vec3 lightVector = lightPosition - ex_worldPosition.xyz;"//ex_worldPosition/ex_worldPosition.w
		"float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);"
		"vec4 diffuse = dot_product * vec4(lightColor,1.0);"
		"vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
		"vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);"
		"out_Color = (ambient + diffuse) * objectColor;"
		"}";
	"}";
	const char* fragment_shader3 =
		"#version 400\n"
		"in vec4 ex_worldPosition;"
		"in vec3 ex_worldNormal;"
		"out vec4 out_Color;"
		"uniform vec3 cameraPosition;"
		"uniform vec3 lightPosition;"
		"uniform vec3 lightColor;"
		"void main() {"
		"vec3 lightVector = lightPosition - ex_worldPosition.xyz/ex_worldPosition.w;"//ex_worldPosition/ex_worldPosition.w
		"float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);"
		"vec4 diffuse = dot_product * vec4(lightColor, 1.0);"
		"vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
		"const float specularStrength = 0.4;"
		"vec3 viewVector = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;"
		"vec3 reflectVector = reflect(-lightVector, normalize(ex_worldNormal));"
		"float spec = pow(max(dot(normalize(viewVector), reflectVector), 0.0), 16);"
		"vec4 specular = specularStrength * spec * vec4(lightColor, 1.0);"
		"if (dot_product <= 0.0) {"
		"specular = vec4(0.0);"
		"}"
		"vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);"
		"out_Color = (ambient + diffuse + specular) * objectColor;"
		"}";
	const char* fragment_shader4 =
		"#version 400\n"
		"in vec4 ex_worldPosition;"
		"in vec3 ex_worldNormal;"
		"out vec4 out_Color;"
		"uniform vec3 cameraPosition;"
		"uniform vec3 lightPosition;"
		"uniform vec3 lightColor;"
		"void main() {"
		"vec3 lightVector = lightPosition - ex_worldPosition.xyz/ex_worldPosition.w;"//ex_worldPosition/ex_worldPosition.w
		"float dot_product = max(dot(normalize(lightVector), normalize(ex_worldNormal)), 0.0);"
		"vec4 diffuse = dot_product * vec4(lightColor, 1.0);"
		"vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);"
		"vec3 viewVector = cameraPosition - ex_worldPosition.xyz/ex_worldPosition.w;"
		"vec3 halfVector = lightVector + viewVector;"
		"const float specularStrength = 0.4;"
		"float spec = pow(max(dot(normalize(halfVector), normalize(ex_worldNormal)), 0.0), 16.0);"
		"vec4 specular = specularStrength * spec * vec4(lightColor, 1.0);"
		"if (dot_product < 0.0) {"
		"specular = vec4(0.0);"
		"}"
		"vec4 objectColor = vec4 (0.385 ,0.647 ,0.812 ,1.0);"
		"out_Color = (ambient + diffuse + specular) * objectColor;"
		"}";
	ShaderProgram* program = new ShaderProgram();
	program->add(GL_VERTEX_SHADER, 1, vertex_shader2);
	program->add(GL_FRAGMENT_SHADER, 1, fragment_shader);
	program->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(program);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 0,program });

	ShaderProgram* program2 = new ShaderProgram();
	program2->add(GL_VERTEX_SHADER, 1, vertex_shader2);
	program2->add(GL_FRAGMENT_SHADER, 1, fragment_shader4);
	program2->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(program2);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 1,program2 });

	ShaderProgram* program3 = new ShaderProgram();
	program3->add(GL_VERTEX_SHADER, 1, vertex_shader2);
	program3->add(GL_FRAGMENT_SHADER, 1, fragment_shader3);
	program3->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(program3);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 2,program3 });
	//Set start camera for all the shaders
	camera->notifyPropertyChanged(CAMERA_VIEW);
	camera->notifyPropertyChanged(CAMERA_PERSPECTIVE);
	camera->notifyPropertyChanged(CAMERA_POSITION);
	glGetError();
	return true;
}



bool Application::createModels()
{
	DrawableObject* d1 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	d1->setProgram(listOfShaderPrograms.find(0)->second);
	d1->runTransformation(listOfTransformations.find(0)->second);
	listOfModels.insert({ 0,d1 });
	DrawableObject* d2 = new DrawableObject(MAKE_COMPLEX, suziFlat, (GLsizeiptr)sizeof(sphere), 0, 2904, VERTICES | COLOR);
	d2->setProgram(listOfShaderPrograms.find(1)->second);
	d2->runTransformation(listOfTransformations.find(1)->second);
	listOfModels.insert({ 1,d2 });
	DrawableObject* d3 = new DrawableObject(MAKE_COMPLEX, suziSmooth, (GLsizeiptr)sizeof(sphere), 0, 2904, VERTICES | COLOR);
	d3->setProgram(listOfShaderPrograms.find(2)->second);
	d3->runTransformation(listOfTransformations.find(2)->second);
	listOfModels.insert({ 2,d3 });
	DrawableObject* d4 = new DrawableObject(MAKE_COMPLEX, tree, (GLsizeiptr)sizeof(sphere), 0, 92814, VERTICES | COLOR);
	d4->setProgram(listOfShaderPrograms.find(1)->second);
	d4->runTransformation(listOfTransformations.find(3)->second);
	listOfModels.insert({ 3,d4 });
	glGetError();
	return true;
}

bool Application::createTransformation()
{
	//First scene
	/*Translate* t1 = new Translate(glm::vec3(0.f, 0.0f, 3.f));
	TransformationComposite* compositeMoveLeft = new TransformationComposite();
	compositeMoveLeft->add(t1);
	listOfTransformations.insert({ 0,compositeMoveLeft });*/

	//Second scene
	Translate* t1 = new Translate(glm::vec3(3.f, 0.0f, 0.0f));
	TransformationComposite* compositeMoveLeft = new TransformationComposite();
	compositeMoveLeft->add(t1);
	listOfTransformations.insert({ 0,compositeMoveLeft });

	Translate* t2 = new Translate(glm::vec3(-3.f, 0.0f, 0.0f));
	TransformationComposite* compositeMoveRight = new TransformationComposite();
	compositeMoveRight->add(t2);
	listOfTransformations.insert({ 1,compositeMoveRight });

	Translate* t3 = new Translate(glm::vec3(0.0f, 3.f, 0.0f));
	TransformationComposite* compositeMoveUp = new TransformationComposite();
	compositeMoveUp->add(t3);
	listOfTransformations.insert({ 2,compositeMoveUp });

	Translate* t4 = new Translate(glm::vec3(0.0f, -7.f, -1.f));
	TransformationComposite* compositeMoveDown = new TransformationComposite();
	compositeMoveDown->add(t4);
	listOfTransformations.insert({ 3,compositeMoveDown });

	return true;
}

bool Application::createLighting()
{
	Lighting* light = new Lighting(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5, 0.5, 0.5));
	light->addFollower(this->listOfShaderPrograms.find(0)->second);
	light->addFollower(this->listOfShaderPrograms.find(1)->second);
	light->addFollower(this->listOfShaderPrograms.find(2)->second);
	//Initialize light to starting values
	light->notifyPropertyChanged(LIGHT_POSITION);
	light->notifyPropertyChanged(LIGHT_COLOR);

	this->listOfLights.insert({ 0,light });
	return true;
}

void Application::run()
{
	//glClearColor(1.0, 0.0, 0.0, 1.0);
	printf("Size of sphere: %d\n", sizeof(sphere));
	float bounds = 0.5;
	bool movingRight = true;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		listOfModels.find(0)->second->drawShape();
		listOfModels.find(1)->second->drawShape();
		listOfModels.find(2)->second->drawShape();
		listOfModels.find(3)->second->drawShape();

		
		
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
		glGetError();
	}
	glfwDestroyWindow(window);
	printf("Outside\n");
	glfwTerminate();
}


/*Rotating 2D object
Rotate r = Rotate(0.01, glm::vec3(0.0f, 0.0f, 1.0f));
		listOfModels.find(0)->second->runTransformation(&r);
*/

/*Moving object from edge of screen to other edge
listOfModels.find(1)->second->drawShape();
		if (movingRight)
		{
			Translate t = Translate(glm::vec3(0.002f, 0.0f, 0.0f));
			listOfModels.find(1)->second->runTransformation(&t);
			bounds += 0.002;
		}
		else
		{
			Translate t = Translate(glm::vec3(-0.002f, 0.0f, 0.0f));
			listOfModels.find(1)->second->runTransformation(&t);
			bounds -= 0.002;
		}


		if (bounds > 1)
		{
			movingRight = false;
		}
		else if (bounds < -1)
		{
			movingRight = true;
		}

*/