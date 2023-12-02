#include "DrawableObject.h"
#include "ComplexShape.h"


DrawableObject::DrawableObject(OPTION o, const float* points, GLsizeiptr size, int startingPosition, int count, int Flags, glm::vec3 objectColor)
{
	matrix = glm::mat4(1.0f);
	createVertexObjects(points, size);
	switch (o)
	{
	case MAKE_TRIANGLE:
	{
		Triangle* model = new Triangle(&this->VBO, &this->VAO, startingPosition, count, Flags);
		this->shape = model;
		break;
	}
	case MAKE_RECTANGLE:
	{
		Rectangle* model = new Rectangle(&this->VBO, &this->VAO, startingPosition, count, Flags);
		this->shape = model;
		break;
	}
	case MAKE_COMPLEX:
	{
		ComplexShape* model = new ComplexShape(&this->VBO, &this->VAO, startingPosition, count, Flags);
		this->shape = model;
	}
	default:
		break;
	}
	this->objectColor = objectColor;
}
DrawableObject::DrawableObject(const char* modelName, int Flags)
{
	this->matrix = glm::mat4(1.0f);
	int count = 0;
	vector<float> data = loadModel(modelName, count);
	createVertexObjects(&data[0], data.size() * sizeof(float));
	ComplexShape* model = new ComplexShape(&this->VBO, &this->VAO, 0, count, Flags);
	this->shape = model;
	this->objectColor = vec3(1, 1, 1);//This is obsolete, I should remove it later
}
DrawableObject::~DrawableObject()
{
	delete shape;
	shape = nullptr;
	delete material;
	material = nullptr;
}


bool DrawableObject::drawShape()
{
	program->use();
	useVAO();
	program->linkTransformation("modelMatrix", this->matrix);
	program->setObjectColor(this->objectColor);//For now its every frame, later move it to somewhere else
	shape->createShape();
	program->disable();
	return true;
}

//Ve chvili kdy mame vice objektu jinych tvaru, tak musime vytvorit novy buffer objektu a nove pole objektu 
bool DrawableObject::createVertexObjects(const float* points, GLsizeiptr size)
{
	//vertex buffer object (VBO)
	VBO = 0;//Vytvorime VBO
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Setting how data in buffer look like
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;//Vytvorime VAO
	glGenVertexArrays(1, &VAO); //generate the VAO
	return true;
}

vector<float> DrawableObject::loadModel(const char* fileName, int& count)
{
	vector<float> data;
	count = 0;
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate
		| aiProcess_OptimizeMeshes              // reduce the number of draw calls
		| aiProcess_JoinIdenticalVertices       // identifies and joins identical vertex data sets within all imported meshes
		| aiProcess_Triangulate                 // triangulates all faces of all meshes 
		| aiProcess_CalcTangentSpace;           // calculates the tangents and bitangents for the imported meshes

	const aiScene* scene = importer.ReadFile(fileName, importOptions);

	if (scene) {
		aiMesh* mesh = scene->mMeshes[0];//Only first mesh 
		printf("Triangles:%d \n", mesh->mNumFaces);
		count = mesh->mNumFaces * 3;

		aiFace* f;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < 3; j++)
			{
				int id = face.mIndices[j];

				//Vertex position
				aiVector3D pos = mesh->mVertices[id];
				data.push_back(pos.x);
				data.push_back(pos.y);
				data.push_back(pos.z);

				//Vertex normal
				aiVector3D nor = mesh->mNormals[id];
				data.push_back(nor.x);
				data.push_back(nor.y);
				data.push_back(nor.z);

				//Vertex uv
				aiVector3D uv = mesh->mTextureCoords[0][id];
				data.push_back(uv.x);
				data.push_back(uv.y);

			}
		}
	}
	else {
		std::cout << "An error occurred while loading model." << std::endl;
		exit(EXIT_FAILURE);
	};

	return data;
}

bool DrawableObject::useVAO()
{
	glBindVertexArray(VAO);
	return true;
}
void DrawableObject::runTransformation(Transformation* t)
{
	matrix = glm::mat4(1.0f);
	t->transform(&this->matrix);
}
void DrawableObject::setProgram(ShaderProgram* p)
{
	this->program = p;
}

void DrawableObject::setMaterial(Material* m)
{
	this->material = m;
	//Add shader of this material into followers
	this->material->addFollower(this->program);
	//Notify that all 4 properties have changed (we setup the material)
	this->material->notifyPropertyChanged(MATERIAL_AMBIENT);
	this->material->notifyPropertyChanged(MATERIAL_DIFFUSE);
	this->material->notifyPropertyChanged(MATERIAL_SPECULAR);
	this->material->notifyPropertyChanged(MATERIAL_SHININESS);
}

void DrawableObject::setMaterial(Material* m, Texture* t)
{
	this->material = m;
	//Add shader of this material into followers
	this->material->addFollower(this->program);
	//Notify that all 4 properties have changed (we setup the material)
	this->material->notifyPropertyChanged(MATERIAL_AMBIENT);
	this->material->notifyPropertyChanged(MATERIAL_DIFFUSE);
	this->material->notifyPropertyChanged(MATERIAL_SPECULAR);
	this->material->notifyPropertyChanged(MATERIAL_SHININESS);

	this->material->setTexture(t);
}