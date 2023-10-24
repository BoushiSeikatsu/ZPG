#include "DrawableObject.h"
#include "ComplexShape.h"


DrawableObject::DrawableObject(OPTION o, const float* points, GLsizeiptr size, int startingPosition, int count, int Flags)
{
	matrix = glm::mat4(1.0f);
	createVertexObjects(points, size);
	switch (o)
	{
	case 0:
	{
		Triangle* model = new Triangle(&this->VBO, &this->VAO, startingPosition, count, Flags);
		this->shape = model;
		break;
	}
	case 1:
	{
		Rectangle* model = new Rectangle(&this->VBO, &this->VAO, startingPosition, count, Flags);
		this->shape = model;
		break;
	}
	case 2:
	{
		ComplexShape* model = new ComplexShape(&this->VBO, &this->VAO, startingPosition, count, Flags);
		this->shape = model;
	}
	default:
		break;
	}
}
DrawableObject::~DrawableObject()
{
	delete shape;
	shape = nullptr;
}


bool DrawableObject::drawShape()
{
	program->use();
	useVAO();
	program->linkTransformation("modelMatrix", this->matrix);
	shape->createShape();
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
	t->transform(&this->matrix);
}
void DrawableObject::setProgram(ShaderProgram* p)
{
	this->program = p;
}