#ifndef VERTEX_BUFFER_OBJECT
#define VERTEX_BUFFER_OBJECT

#include "../glad/glad.h"

class VertexBufferObject {
  public:
    // Reference ID of the Vertex Buffer Object.
    unsigned int ID;

    // Constructor that generates a Vertex Buffer Object and links it to
    // vertices.
    VertexBufferObject(GLfloat *vertices, GLsizeiptr size);

    // Binds the VBO.
    void Bind();

    // Unbinds the VBO.
    void Unbind();

    // Deletes the VBO.
    void Delete();
};

#endif
