#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include "VertexBufferObject.h"
#include "glad/glad.h"

class VertexArrayObject {
  public:
    // ID reference for the VAO.
    unsigned int ID;

    // Constructor that generates VAO ID.
    VertexArrayObject();

    // Links a VBO to the VAO using a certain layout.
    void LinkVBO(VertexBufferObject &VBO, unsigned int layout);

    // Bind the VAO.
    void Bind();

    // Unbinds the VAO.
    void Unbind();

    // Deletes the VAO.
    void Delete();
};

#endif
