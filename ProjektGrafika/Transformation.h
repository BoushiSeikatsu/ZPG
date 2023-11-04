#pragma once
#include <glm/vec3.hpp> // glm::vec3

#include <glm/vec4.hpp> // glm::vec4

#include <glm/mat4x4.hpp> // glm::mat4

#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

/*
Bude mit v sobe matici
Bude to jednotkova matice 
potom na to az zacneme aplikovat ty transformace
Shape ma referenci na transformation 
Shape ma referenci na shaderProgram 
Shaderu se preda ta matice a rekne se shaderu at provede transformace 
*/
class Transformation
{
protected:
public:
	/*void rotate(float angle, glm::vec3 rotationAxis);
	void translate(glm::vec3 translationVector);
	void scale(glm::vec3 scalingVector);*/
	virtual void transform(glm::mat4* M) = 0;
	virtual void changeAngle(float newAngle) = 0;
};

