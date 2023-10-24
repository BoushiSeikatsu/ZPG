#include "ComplexShape.h"
#include <cstddef>

/*
Jeste je k zamysleni jestli bych mel mit setup tech Vertex objektu takhle v konstruktoru nebo to presunout jinam at trojuhlenikum zbytecne nepredavam VBO a VAO vicekrat
*/
ComplexShape::ComplexShape(GLuint* VBO, GLuint* VAO, int startingPosition, int count, int Flags) : Shape(startingPosition, count)
{
    this->Flags = Flags;
    setupVertexObjects(VBO, VAO);
}
//Pro zatim 3 moznosti, upravim potom podle potreby
bool ComplexShape::setupVertexObjects(GLuint* VBO, GLuint* VAO)
{
    if (Flags == VERTICES)
    {
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBindVertexArray(*VAO); //bind the VAO
        glEnableVertexAttribArray(0); //enable vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        return true;
    }
    else if (Flags == (VERTICES | COLOR))
    {
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBindVertexArray(*VAO); //bind the VAO
        glEnableVertexAttribArray(0); //enable vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, NULL);

        //auto loc = glGetAttribLocation(idProgram, "vColor");Dobry napad, kouknout na to doma
        //glEnableVertexAttribArray(loc);
        glEnableVertexAttribArray(1); //enable vertex attributes
        /*
        stride(5 parametr) znamena rozestup mezi elementy
        Mame vertices a pak barvu, mame xyzw, w je weight a potom pro barvu rgbt, t je transparentnost, takze dohromady 8 hodnot, hodnoty jsou od sebe o 8 prvku
        */
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
        return true;
    }
    else if (Flags == (VERTICES | COLOR | TEXTURE))
    {
        return true;
    }
    return false;
}

bool ComplexShape::createShape()
{
    glDrawArrays(GL_TRIANGLES, startingPosition, count);
    return true;
}

bool ComplexShape::deleteShape()
{
    return false;
}

bool ComplexShape::updateShape()
{
    return false;
}

