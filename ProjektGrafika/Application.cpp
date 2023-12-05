#include "Application.h"
// Including model
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/bushes.h"
#include "Models/skycube.h"

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
	delete flashlight;
	flashlight = nullptr;
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
	camera->setResolution(800, 600);
	//Binding camera into user pointer so we can use it in Callbacks
	glfwSetWindowUserPointer(window, this->camera);
	glfwSetMouseButtonCallback(window, CameraCallback::mouseButtonCallback);
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
	ShaderProgram* skyboxShader = new ShaderProgram();
	skyboxShader->add("Shaders/skybox.vert", GL_VERTEX_SHADER, 1);
	skyboxShader->add("Shaders/skybox.frag", GL_FRAGMENT_SHADER, 1);
	skyboxShader->assembleProgram();
	camera->addFollower(skyboxShader);

	this->listOfShaderPrograms.insert({ 0, skyboxShader });

	ShaderProgram* shaderNoTexture = new ShaderProgram();
	shaderNoTexture->add("Shaders/pos&normal.vert", GL_VERTEX_SHADER, 1);
	shaderNoTexture->add("Shaders/phong.frag", GL_FRAGMENT_SHADER, 1);
	shaderNoTexture->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(shaderNoTexture);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 1,shaderNoTexture });

	ShaderProgram* shaderGrass = new ShaderProgram();
	shaderGrass->add("Shaders/pos&normal&texture.vert", GL_VERTEX_SHADER, 1);
	shaderGrass->add("Shaders/phong_test_texture.frag", GL_FRAGMENT_SHADER, 1);
	shaderGrass->assembleProgram();
	//Adding ShaderProgram as follower
	camera->addFollower(shaderGrass);
	//Adding ShaderProgram into map
	this->listOfShaderPrograms.insert({ 2,shaderGrass });

	ShaderProgram* shaderHouse = new ShaderProgram();
	shaderHouse->add("Shaders/pos&normal&texture.vert", GL_VERTEX_SHADER, 1);
	shaderHouse->add("Shaders/phong_test_texture.frag", GL_FRAGMENT_SHADER, 1);
	shaderHouse->assembleProgram();
	camera->addFollower(shaderHouse);

	this->listOfShaderPrograms.insert({ 3,shaderHouse });

	ShaderProgram* shaderWall = new ShaderProgram();
	shaderWall->add("Shaders/pos&normal&texture.vert", GL_VERTEX_SHADER, 1);
	shaderWall->add("Shaders/phong_test_texture.frag", GL_FRAGMENT_SHADER, 1);
	shaderWall->assembleProgram();
	camera->addFollower(shaderWall);

	this->listOfShaderPrograms.insert({ 4,shaderWall });

	ShaderProgram* shaderTreeLeaves = new ShaderProgram();
	shaderTreeLeaves->add("Shaders/pos&normal&texture.vert", GL_VERTEX_SHADER, 1);
	shaderTreeLeaves->add("Shaders/phong_test_texture.frag", GL_FRAGMENT_SHADER, 1);
	shaderTreeLeaves->assembleProgram();
	camera->addFollower(shaderTreeLeaves);

	this->listOfShaderPrograms.insert({ 5,shaderTreeLeaves });

	ShaderProgram* shaderZombie = new ShaderProgram();
	shaderZombie->add("Shaders/pos&normal&texture.vert", GL_VERTEX_SHADER, 1);
	shaderZombie->add("Shaders/phong_test_texture.frag", GL_FRAGMENT_SHADER, 1);
	shaderZombie->assembleProgram();
	camera->addFollower(shaderZombie);

	this->listOfShaderPrograms.insert({ 6,shaderZombie });

	ShaderProgram* shaderDuck = new ShaderProgram();
	shaderDuck->add("Shaders/pos&normal&texture.vert", GL_VERTEX_SHADER, 1);
	shaderDuck->add("Shaders/phong_test_texture.frag", GL_FRAGMENT_SHADER, 1);
	shaderDuck->assembleProgram();
	camera->addFollower(shaderDuck);

	this->listOfShaderPrograms.insert({ 7,shaderDuck });

	//Set start camera for all the shaders
	camera->notifyPropertyChanged(CAMERA_VIEW);
	camera->notifyPropertyChanged(CAMERA_PERSPECTIVE);
	camera->notifyPropertyChanged(CAMERA_POSITION);
	camera->notifyPropertyChanged(CAMERA_DIRECTION);
	glGetError();
	return true;
}



bool Application::createModels()
{
	Material* materialSkybox = new Material(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.2, 0.2, 0.2), glm::vec3(0.2, 0.2, 0.2), 16);
	Texture* textureSkybox = new Texture(1, "Skycube");
	//materialSkybox->setTexture(textureSkybox);

	DrawableObject* SkyBox = new DrawableObject(MAKE_COMPLEX, skycube, (GLsizeiptr)sizeof(skycube), 0, 108, VERTICES);
	SkyBox->setProgram(listOfShaderPrograms.find(0)->second);
	SkyBox->setMaterial(materialSkybox, textureSkybox);
	//SkyBox->runTransformation(listOfTransformations.find(0)->second);
	listOfModels.insert({ 200,SkyBox });

	Material* materialTrava = new Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);
	Texture* textureTrava = new Texture(0, "Textures/grass.png");

	//Test load modelu
	Texture* textureModelLoad = new Texture(2, "Textures/model.png");
	Material* material2 = new Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);

	Texture* textureZed = new Texture(3, "Textures/zed.png");
	Material* materialZed = new Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);
	
	Texture* textureTree = new Texture(4, "Textures/tree.png");
	Material* materialTree = new Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);

	Texture* textureZombie = new Texture(5, "Textures/zombie.png");
	Material* materialZombie = new Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);

	

	DrawableObject* testModelLoad = new DrawableObject("Models/model.obj", VERTICES | COLOR | TEXTURE);
	testModelLoad->setProgram(listOfShaderPrograms.find(3)->second);
	testModelLoad->setMaterial(material2, textureModelLoad);
	listOfModels.insert({ 201,testModelLoad });

	//Scene 5
	DrawableObject* scene5_1 = new DrawableObject(MAKE_COMPLEX, plain, (GLsizeiptr)sizeof(plain), 0, 6, VERTICES | COLOR | TEXTURE, glm::vec3(0.9, 0.9, 0.9));
	scene5_1->setProgram(listOfShaderPrograms.find(2)->second);
	scene5_1->setMaterial(materialTrava, textureTrava);
	scene5_1->runTransformation(listOfTransformations.find(5)->second);
	listOfModels.insert({ 9,scene5_1 });
	for (int i = 10; i < 30; i++)
	{
		int transformationChoice = rand() % 195 + 6;
		DrawableObject* tmp = nullptr;
		tmp = new DrawableObject(MAKE_COMPLEX, bushes, (GLsizeiptr)sizeof(bushes), 0, 8730, VERTICES | COLOR, glm::vec3(0, 1, 0));
		tmp->setProgram(listOfShaderPrograms.find(1)->second);
		tmp->setMaterial(materialTrava);
		tmp->runTransformation(listOfTransformations.find(transformationChoice)->second);
		listOfModels.insert({ i,tmp });
	}
	for (int i = 30; i < 80; i++)
	{
		int transformationChoice = rand() % 195 + 6;
		DrawableObject* tmp = nullptr;
		tmp = new DrawableObject(MAKE_COMPLEX, tree, (GLsizeiptr)sizeof(tree), 0, 92814, VERTICES | COLOR, glm::vec3(0, 1, 0));
		tmp->setProgram(listOfShaderPrograms.find(1)->second);
		tmp->setMaterial(materialTrava);
		tmp->runTransformation(listOfTransformations.find(transformationChoice)->second);
		listOfModels.insert({ i,tmp });
	}
	for (int i = 80; i < 90; i++)
	{
		int transformationChoice = rand() % 195 + 6;
		DrawableObject* tmp = nullptr;
		tmp = new DrawableObject("Models/tree.obj", VERTICES | COLOR | TEXTURE);
		tmp->setProgram(listOfShaderPrograms.find(5)->second);
		tmp->setMaterial(materialTree, textureTree);
		tmp->runTransformation(listOfTransformations.find(0)->second);
		tmp->runTransformation(listOfTransformations.find(transformationChoice)->second);
		listOfModels.insert({ i,tmp });
	}
	for (int i = 90; i < 100; i++)
	{
		int transformationChoice = rand() % 195 + 6;
		DrawableObject* tmp = nullptr;
		tmp = new DrawableObject("Models/zombie.obj", VERTICES | COLOR | TEXTURE);
		tmp->setProgram(listOfShaderPrograms.find(6)->second);
		tmp->setMaterial(materialZombie, textureZombie);
		Rotate* tmpRotate = new Rotate(rand() % 360, glm::vec3(0, 1, 0));
		listOfTransformations.find(transformationChoice)->second->add(tmpRotate);
		tmp->runTransformation(listOfTransformations.find(transformationChoice)->second);
		listOfModels.insert({ i,tmp });
	}
		DrawableObject* tmp = nullptr;
		tmp = new DrawableObject("Models/zombie.obj", VERTICES | COLOR | TEXTURE);
		tmp->setProgram(listOfShaderPrograms.find(6)->second);
		tmp->setMaterial(materialZombie, textureZombie);
		Rotate* tmpRotate = new Rotate(0.01, glm::vec3(0.0f, 1.0f, 0.0f));
		Translate* tmpTranslate = new Translate(glm::vec3(13, 0, 0));
		TransformationComposite* tmpComposite = new TransformationComposite();
		tmpComposite->add(tmpRotate);
		tmpComposite->add(tmpTranslate);
		tmp->runTransformation(tmpComposite);
		listOfTransformations.insert({ 201, tmpComposite });
		listOfModels.insert({ 100,tmp });
	glGetError();
	return true;
}

bool Application::createTransformation()
{
	Scale* smallTree = new Scale(glm::vec3(0.5, 0.5, 0.5));
	TransformationComposite* smallTreeComposite = new TransformationComposite();
	smallTreeComposite->add(smallTree);
	listOfTransformations.insert({ 0,smallTreeComposite });
	//Scene 5
	Scale* scene_5Plain = new Scale(glm::vec3(20.0f, 1.0f, 20.0f));
	Translate* scene_5Plain2 = new Translate(glm::vec3(-0.1f, 0.f, -0.1f));
	TransformationComposite* compositeScene5Plain = new TransformationComposite();
	compositeScene5Plain->add(scene_5Plain);
	compositeScene5Plain->add(scene_5Plain2);
	listOfTransformations.insert({ 5,compositeScene5Plain });
	for (int i = 6; i < 200; i++)
	{
		int xMod = rand() % 2;
		int zMod = rand() % 2;
		if (xMod == 0)
		{
			xMod = -1;
		}
		if (zMod == 0)
		{
			zMod = -1;
		}
		int xTranslate = (rand() % 20 + 4) * xMod;
		//int yTranslate = rand() % 2 + 1;
		int zTranslate = (rand() % 18) * zMod;
		int randomAngle = rand() % 360;
		Translate* tmp1 = new Translate(glm::vec3(xTranslate, 0, zTranslate));
		Rotate* tmp2 = new Rotate(randomAngle, glm::vec3(0, 1, 0));
		TransformationComposite* tmp3 = new TransformationComposite();
		tmp3->add(tmp1);
		//tmp3->add(tmp2);
		listOfTransformations.insert({ i,tmp3 });
	}
	return true;
}

bool Application::createLighting()
{
	//Scene 2
	Lighting* moonlight = new Lighting(glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.1, 0.1, 0.1), false);
	moonlight->addFollower(this->listOfShaderPrograms.find(1)->second);
	moonlight->addFollower(this->listOfShaderPrograms.find(2)->second);
	moonlight->addFollower(this->listOfShaderPrograms.find(3)->second);
	moonlight->addFollower(this->listOfShaderPrograms.find(4)->second);
	moonlight->addFollower(this->listOfShaderPrograms.find(5)->second);
	moonlight->addFollower(this->listOfShaderPrograms.find(6)->second);
	moonlight->addFollower(this->listOfShaderPrograms.find(7)->second);
	moonlight->notifyPropertyChanged(LIGHT_POSITION);
	moonlight->notifyPropertyChanged(LIGHT_COLOR);
	moonlight->notifyPropertyChanged(LIGHT_DIRECTION);
	moonlight->notifyPropertyChanged(LIGHT_CUTOFF);
	this->listOfLights.insert({ 1,moonlight });

	this->flashlight = new Flashlight(glm::vec3(0.5, 0.5, 0.5), glm::cos(glm::radians(15.0f)), glm::cos(glm::radians(20.0f)));
	this->flashlight->addFollower(this->listOfShaderPrograms.find(1)->second);
	this->flashlight->addFollower(this->listOfShaderPrograms.find(2)->second);
	this->flashlight->addFollower(this->listOfShaderPrograms.find(3)->second);
	this->flashlight->addFollower(this->listOfShaderPrograms.find(4)->second);
	this->flashlight->addFollower(this->listOfShaderPrograms.find(5)->second);
	this->flashlight->addFollower(this->listOfShaderPrograms.find(6)->second);
	this->flashlight->addFollower(this->listOfShaderPrograms.find(7)->second);
	this->flashlight->notifyPropertyChanged(LIGHT_COLOR);
	this->flashlight->notifyPropertyChanged(LIGHT_CUTOFF);
	this->flashlight->notifyPropertyChanged(LIGHT_CUTOFF_OUT);
	this->flashlight->use();
	return true;

}

void Application::run()
{
	//glClearColor(1.0, 0.0, 0.0, 1.0);
	printf("Size of sphere: %d\n", sizeof(sphere));
	SceneCallback::setSceneLimit(1);//Set number of scenes we will use
	map<int, DrawableObject*> deletedObjects;
	map<int, DrawableObject*> createdObjects;
	Texture* textureDuck = new Texture(6, "Textures/zed.png");
	Material* materialDuck = new Material(glm::vec3(0.05, 0.05, 0.05), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 16);
	bool makingDuck = false;
	int modelCount = 101;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, 200, 0xFF);
		listOfModels.find(200)->second->drawShape();
		glClear(GL_DEPTH_BUFFER_BIT);
		switch (SceneCallback::getSceneIndex())
		{
		case 0:
		{
			listOfModels.find(201)->second->drawShape();
			if (PlayerActionCallback::indexSelectedModel == 9 && !makingDuck)//Index for plane
			{
				DrawableObject* duck = new DrawableObject("Models/rubberDuck.obj", VERTICES | COLOR | TEXTURE);
				duck->setProgram(listOfShaderPrograms.find(7)->second);
				duck->setMaterial(materialDuck, textureDuck);
				Translate* tmp = new Translate(PlayerActionCallback::positionSelectedModel);
				Scale* tmpScale = new Scale(glm::vec3(0.1, 0.1, 0.1));
				TransformationComposite* tmpComposite = new TransformationComposite();
				tmpComposite->add(tmp);
				tmpComposite->add(tmpScale);
				duck->runTransformation(tmpComposite);
				createdObjects.insert({ modelCount + createdObjects.size(),duck});
				makingDuck = true;
			}
			else if(PlayerActionCallback::indexSelectedModel != 9)
			{
				makingDuck = false;
			}
			for (int i = 9; i < modelCount; i++)
			{
				glStencilFunc(GL_ALWAYS, i, 0xFF);
				if (i == PlayerActionCallback::indexSelectedModel)
				{
					if (i >= 90 && i <= 100)
					{
						deletedObjects.insert({ i, listOfModels.find(i)->second });
					}
				}
				if (deletedObjects.count(i) != 1)
				{
					listOfModels.find(i)->second->drawShape();
					if (i == 100)
					{
						listOfTransformations.find(201)->second->changeAngle(-0.005);
						listOfModels.find(100)->second->runTransformation(listOfTransformations.find(201)->second);
					}	
				}
			}
			for (auto pair : createdObjects)
			{
				glStencilFunc(GL_ALWAYS, pair.first, 0xFF);
				pair.second->drawShape();
			}

		}
		}





		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
		glGetError();
	}
	for (auto pair : createdObjects)
	{
		delete pair.second;
		pair.second = nullptr;
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