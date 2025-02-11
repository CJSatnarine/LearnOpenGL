#include "ElementBufferObject.h"

ElementBufferObject::ElementBufferObject(unsigned int *indices,
                                         GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ElementBufferObject::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); }

void ElementBufferObject::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

void ElementBufferObject::Delete() { glDeleteBuffers(1, &ID); }
