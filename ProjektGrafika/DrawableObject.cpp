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
