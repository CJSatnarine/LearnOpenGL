#ifndef ELEMENT_BUFFER_OBJECT_H
#define ELEMENT_BUFFER_OBJECT_H

#include "../glad/glad.h"

class ElementBufferObject {
  public:
    // ID reference of the Elements Buffer Object.
    unsigned int ID;

    // Constructor that generates EBO and links it to indices.
    ElementBufferObject(unsigned int *indices, GLsizeiptr size);

    // Binds the EBO.
    void Bind();

    // Unbinds the EBO.
    void Unbind();

    // Deletes the EBO.
    void Delete();
};

#endif
