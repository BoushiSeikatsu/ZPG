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
	glfwSetMouseButtonCallback(window, CameraCallback::mouseButtonCallback);
	//Binding camera into user pointer so we can use it in Callbacks
	glfwSetWindowUserPointer(window, this->camera);
	//Locking cursor in the middle of the screen 
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Binding mouse movement callback
	glfwSetCursorPosCallback(window, CameraCallback::onMouseMoved);
	//Binding key pressed callback
	glfwSetKeyCallback(window, CameraCallback::onKeyPressed);
	//glfwSetKeyCallback(window, SceneCallback::onKeyPressed);//Scene switching
	glfwSetFramebufferSizeCallback(window, CameraCallback::framebufferSizeCallback);
}

bool Application::createShaders()
{
	ShaderProgram* ambientShader = new ShaderProgram();
	ambientShader->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER, 1);
	ambientShader->add("Shaders/ambient.frag", GL_FRAGMENT_SHADER, 1);
	ambientShader->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(ambientShader);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 0,ambientShader });

	ShaderProgram* lambertShader = new ShaderProgram();
	lambertShader->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER, 1);
	lambertShader->add("Shaders/lambert.frag", GL_FRAGMENT_SHADER, 1);
	lambertShader->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(lambertShader);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 1,lambertShader });

	ShaderProgram* phongShader = new ShaderProgram();
	phongShader->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER,1);
	phongShader->add("Shaders/phong.frag", GL_FRAGMENT_SHADER, 1);
	phongShader->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(phongShader);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 2,phongShader });

	ShaderProgram* blinnShader = new ShaderProgram();
	blinnShader->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER, 1);
	blinnShader->add("Shaders/blinn.frag", GL_FRAGMENT_SHADER, 1);
	blinnShader->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(blinnShader);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 3,blinnShader });

	ShaderProgram* scene2WithControl = new ShaderProgram();
	scene2WithControl->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER, 1);
	scene2WithControl->add("Shaders/phongScene3_1.frag", GL_FRAGMENT_SHADER, 1);
	scene2WithControl->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(scene2WithControl);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 4,scene2WithControl });

	ShaderProgram* scene2WithoutControl = new ShaderProgram();
	scene2WithoutControl->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER, 1);
	scene2WithoutControl->add("Shaders/phongScene3_2.frag", GL_FRAGMENT_SHADER, 1);
	scene2WithoutControl->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(scene2WithoutControl);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 5,scene2WithoutControl });

	//Set start camera for all the shaders
	camera->notifyPropertyChanged(CAMERA_VIEW);
	camera->notifyPropertyChanged(CAMERA_PERSPECTIVE);
	camera->notifyPropertyChanged(CAMERA_POSITION);
	glGetError();
	return true;
}



bool Application::createModels()
{
	//Scene 1 
	Material* material = new Material(glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);
	DrawableObject* scene1_1 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene1_1->setProgram(listOfShaderPrograms.find(2)->second);
	scene1_1->setMaterial(material);
	scene1_1->runTransformation(listOfTransformations.find(0)->second);
	listOfModels.insert({ 0,scene1_1 });
	DrawableObject* scene1_2 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene1_2->setProgram(listOfShaderPrograms.find(2)->second);
	scene1_2->setMaterial(material);
	scene1_2->runTransformation(listOfTransformations.find(1)->second);
	listOfModels.insert({ 1,scene1_2 });
	DrawableObject* scene1_3 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene1_3->setProgram(listOfShaderPrograms.find(2)->second);
	scene1_3->setMaterial(material);
	scene1_3->runTransformation(listOfTransformations.find(2)->second);
	listOfModels.insert({ 2,scene1_3 });
	DrawableObject* scene1_4 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene1_4->setProgram(listOfShaderPrograms.find(2)->second);
	scene1_4->setMaterial(material);
	scene1_4->runTransformation(listOfTransformations.find(3)->second);
	listOfModels.insert({ 3,scene1_4 });

	//Scene 3
	DrawableObject* scene2_1 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene2_1->setProgram(listOfShaderPrograms.find(4)->second);//Change shader to 5 for shader without control of angle from dot product
	scene2_1->setMaterial(material);
	scene2_1->runTransformation(listOfTransformations.find(4)->second);
	listOfModels.insert({ 4,scene2_1 });

	//Scene 4
	DrawableObject* scene4_1 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene4_1->setProgram(listOfShaderPrograms.find(2)->second);
	scene4_1->setMaterial(material);
	scene4_1->runTransformation(listOfTransformations.find(0)->second);
	listOfModels.insert({ 5,scene4_1 });
	DrawableObject* scene4_2 = new DrawableObject(MAKE_COMPLEX, suziFlat, (GLsizeiptr)sizeof(suziFlat), 0, 2904, VERTICES | COLOR);
	scene4_2->setProgram(listOfShaderPrograms.find(2)->second);
	scene4_2->setMaterial(material);
	scene4_2->runTransformation(listOfTransformations.find(1)->second);
	listOfModels.insert({ 6,scene4_2 });
	DrawableObject* scene4_3 = new DrawableObject(MAKE_COMPLEX, suziSmooth, (GLsizeiptr)sizeof(suziSmooth), 0, 2904, VERTICES | COLOR);
	scene4_3->setProgram(listOfShaderPrograms.find(2)->second);
	scene4_3->setMaterial(material);
	scene4_3->runTransformation(listOfTransformations.find(2)->second);
	listOfModels.insert({ 7,scene4_3 });
	DrawableObject* scene4_4 = new DrawableObject(MAKE_COMPLEX, sphere, (GLsizeiptr)sizeof(sphere), 0, 2880, VERTICES | COLOR);
	scene4_4->setProgram(listOfShaderPrograms.find(2)->second);
	scene4_4->setMaterial(material);
	scene4_4->runTransformation(listOfTransformations.find(3)->second);
	listOfModels.insert({ 8,scene4_4 });

	glGetError();
	return true;
}

bool Application::createTransformation()
{
	

	//Scene 1
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

	Translate* t4 = new Translate(glm::vec3(0.0f, -3.f, 0.f));
	TransformationComposite* compositeMoveDown = new TransformationComposite();
	compositeMoveDown->add(t4);
	listOfTransformations.insert({ 3,compositeMoveDown });

	//Scene 2
	Translate* scene2_1 = new Translate(glm::vec3(0.f, 0.0f, 3.f));
	TransformationComposite* compositeScene2 = new TransformationComposite();
	compositeScene2->add(scene2_1);
	listOfTransformations.insert({ 4,compositeScene2 });

	return true;
}

bool Application::createLighting()
{
	//Scene 1
	Lighting* light = new Lighting(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5, 0.5, 0.5));
	light->addFollower(this->listOfShaderPrograms.find(0)->second);
	light->addFollower(this->listOfShaderPrograms.find(1)->second);
	light->addFollower(this->listOfShaderPrograms.find(2)->second);
	light->addFollower(this->listOfShaderPrograms.find(3)->second);
	//Initialize light to starting values
	light->notifyPropertyChanged(LIGHT_POSITION);
	light->notifyPropertyChanged(LIGHT_COLOR);

	this->listOfLights.insert({ 0,light });

	//Scene 2
	Lighting* light2 = new Lighting(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.5, 0.5, 0.5));
	light2->addFollower(this->listOfShaderPrograms.find(4)->second);
	light2->addFollower(this->listOfShaderPrograms.find(5)->second);
	light2->notifyPropertyChanged(LIGHT_POSITION);
	light2->notifyPropertyChanged(LIGHT_COLOR);
	this->listOfLights.insert({ 1,light2 });
	return true;
}

void Application::run()
{
	//glClearColor(1.0, 0.0, 0.0, 1.0);
	printf("Size of sphere: %d\n", sizeof(sphere));
	SceneCallback::setSceneLimit(4);//Set number of scenes we will use
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		switch (SceneCallback::getSceneIndex())
		{
			case 0:
			{
				listOfModels.find(0)->second->drawShape();
				listOfModels.find(1)->second->drawShape();
				listOfModels.find(2)->second->drawShape();
				listOfModels.find(3)->second->drawShape();
				break;
			}
			case 1:
			{
				
				break;
			}
			case 2:
			{
				listOfModels.find(4)->second->drawShape();
				break;
			}
			case 3:
			{
				listOfModels.find(5)->second->drawShape();
				listOfModels.find(6)->second->drawShape();
				listOfModels.find(7)->second->drawShape();
				listOfModels.find(8)->second->drawShape();
				break;
			}
		}
		
		

		
		
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