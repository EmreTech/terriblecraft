#ifndef VAO_HPP
#define VAO_HPP

#include <glad/glad.h>

#include "buffer.hpp"

namespace gl {

struct VAO {
  unsigned int ID;

  VAO() {}

  void init() {
    glGenVertexArrays(1, &ID);
    bind();
  }

  void bind() const { glBindVertexArray(ID); }

  void attribute(Buffer vbo, GLuint index, GLint size, GLenum type,
                 GLsizei stride, size_t offset) {
    bind();
    vbo.bind(GL_ARRAY_BUFFER);

    // Since all attribute data passed in will be a floating-point number, no
    // need to use glVertexAttribIPointer.
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
  }

  void destroy() { glDeleteVertexArrays(1, &ID); }
};

} // namespace gl

#endif