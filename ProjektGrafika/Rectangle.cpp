#include "Rectangle.h"
#include <cstddef>

Rectangle::Rectangle(GLuint* VBO, GLuint* VAO, int startingPosition, int count, int Flags) : Shape(startingPosition, count)
{
    this->Flags = Flags;
    setupVertexObjects(VBO, VAO);
}

bool Rectangle::setupVertexObjects(GLuint* VBO, GLuint* VAO)
{
    if (Flags == VERTICES)
    {
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBindVertexArray(*VAO); //bind the VAO
        glEnableVertexAttribArray(0); //enable vertex attributes
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
        return true;
    }
    else if (Flags == (VERTICES | COLOR))
    {
        glBindBuffer(GL_ARRAY_BUFFER, *VBO);
        glBindVertexArray(*VAO); //bind the VAO
        glEnableVertexAttribArray(0); //enable vertex attributes
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float)*8, NULL);

        //auto loc = glGetAttribLocation(idProgram, "vColor");Dobry napad, kouknout na to doma
        //glEnableVertexAttribArray(loc);
        glEnableVertexAttribArray(1); //enable vertex attributes
        /*
        stride(5 parametr) znamena rozestup mezi elementy
        Mame vertices a pak barvu, mame xyzw, w je weight a potom pro barvu rgbt, t je transparentnost, takze dohromady 8 hodnot, hodnoty jsou od sebe o 8 prvku
        */
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(4*sizeof(float)));
        return true;
    }
    else if (Flags == (VERTICES | COLOR | TEXTURE))
    {
        return true;
    }
    return false;
}

bool Rectangle::createShape()
{
    glDrawArrays(GL_QUADS, startingPosition, count);
    return true;
}

bool Rectangle::deleteShape()
{
    return false;
}

bool Rectangle::updateShape()
{
    return false;
}
