#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>

namespace glwrapper {

    class VertexArray;
    class Buffer;

    class VertexBindingPoint : public Instantiator<VertexBindingPoint> {
    public:
        VertexBindingPoint(std::shared_ptr<VertexArray> vertexArray, GLuint bindingIndex);
        virtual ~VertexBindingPoint() = default;

        void bindBuffer(const std::shared_ptr<Buffer>& buffer, GLintptr offset, GLsizei stride);
        void bindAttribute(GLuint attribIndex);

        void setFormat(GLint size, GLenum type, GLboolean normalized = GL_FALSE, GLuint relativeOffset = 0);
        void setIFormat(GLint size, GLenum type, GLuint relativeOffset = 0);
        void setLFormat(GLint size, GLenum type, GLuint relativeOffset = 0);

        GLuint attributeIndex() const;
        GLuint bindingIndex() const;

        std::shared_ptr<VertexArray> vertexArray();
        std::shared_ptr<const VertexArray> vertexArray() const;

        std::shared_ptr<const Buffer> buffer() const;

    private:
        GLuint m_attribIndex;
        GLuint m_bindingIndex;
        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<Buffer> m_buffer;
    };

}