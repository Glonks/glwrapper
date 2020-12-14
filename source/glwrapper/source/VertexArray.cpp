#include <glwrapper/VertexArray.h>

namespace glwrapper {

    VertexArray::VertexArray() {
        glCreateVertexArrays(1, &m_id);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_id);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::enable(GLuint index) {
        glEnableVertexArrayAttrib(m_id, index);
    }

    void VertexArray::disable(GLuint index) {
        glDisableVertexArrayAttrib(m_id, index);
    }

    void VertexArray::drawArrays(GLenum mode, GLint first, GLsizei count) const {
        bind();
        glDrawArrays(mode, first, count);
    }

    void VertexArray::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) const {
        bind();
        glDrawElements(mode, count, type, indices);
    }

    GLint VertexArray::id() const {
        return m_id;
    }

}