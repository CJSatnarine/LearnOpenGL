#include "VertexArrayObject.h"
#include "VertexBufferObject.h"

VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &ID); }

void VertexArrayObject::LinkVBO(VertexBufferObject &VBO, unsigned int layout) {
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VertexArrayObject::LinkAttrib(VertexBufferObject &VBO, unsigned int layout,
                                   unsigned int numComponents, GLenum type,
                                   GLsizeiptr stride, void *offset) {
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride,
                          offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VertexArrayObject::Bind() { glBindVertexArray(ID); }

void VertexArrayObject::Unbind() { glBindVertexArray(0); }

void VertexArrayObject::Delete() { glDeleteVertexArrays(1, &ID); }
