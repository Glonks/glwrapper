#include <glwrapper/glwpch.h>
#include <glwrapper/VertexBindingPoint.h>
#include <glwrapper/VertexArray.h>
#include <glwrapper/Buffer.h>

namespace glw {

    VertexBindingPoint::VertexBindingPoint(std::shared_ptr<VertexArray> vertexArray, GLuint bindingIndex)
            : m_vertexArray{std::move(vertexArray)},
              m_bindingIndex{bindingIndex},
              m_attribIndex{0},
              m_buffer{nullptr} {}

    void VertexBindingPoint::bindBuffer(const std::shared_ptr<Buffer>& buffer, GLintptr offset, GLsizei stride) {
        m_buffer = buffer;

        glVertexArrayVertexBuffer(m_vertexArray->id(), m_bindingIndex, buffer ? buffer->id() : 0, offset, stride);
    }

    void VertexBindingPoint::bindAttribute(GLuint attribIndex) {
        m_attribIndex = attribIndex;

        glVertexArrayAttribBinding(m_vertexArray->id(), m_attribIndex, m_bindingIndex);
    }

    void VertexBindingPoint::setFormat(GLint size, GLenum type, GLboolean normalized, GLuint relativeOffset) {
        glVertexArrayAttribFormat(m_vertexArray->id(), m_attribIndex, size, type, normalized, relativeOffset);
    }

    void VertexBindingPoint::setIFormat(GLint size, GLenum type, GLuint relativeOffset) {
        glVertexArrayAttribIFormat(m_vertexArray->id(), m_attribIndex, size, type, relativeOffset);
    }

    void VertexBindingPoint::setLFormat(GLint size, GLenum type, GLuint relativeOffset) {
        glVertexArrayAttribLFormat(m_vertexArray->id(), m_attribIndex, size, type, relativeOffset);
    }

    GLuint VertexBindingPoint::attributeIndex() const {
        return m_attribIndex;
    }

    GLuint VertexBindingPoint::bindingIndex() const {
        return m_bindingIndex;
    }

    std::shared_ptr<VertexArray> VertexBindingPoint::vertexArray() {
        return m_vertexArray;
    }

    std::shared_ptr<const VertexArray> VertexBindingPoint::vertexArray() const {
        return m_vertexArray;
    }

    std::shared_ptr<const Buffer> VertexBindingPoint::buffer() const {
        return m_buffer;
    }

}