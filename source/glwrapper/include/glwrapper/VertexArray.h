#pragma once

#include <glwrapper/base/Instantiator.h>
#include <glwrapper/Buffer.h>

#include <glad/glad.h>

namespace glwrapper {

    class VertexArray : public Instantiator<VertexArray> {
    public:
        VertexArray();
        virtual ~VertexArray();

        void bind() const;
        static void unbind();

        void enable(GLuint index);
        void disable(GLuint index);

        void bindElementBuffer(const std::shared_ptr<Buffer>& buffer);
        void bindVertexBuffer(const std::shared_ptr<Buffer>& buffer);

        void drawArrays(GLenum mode, GLint first, GLsizei count) const;

        void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices = nullptr) const;

        GLuint id() const;

    private:
        GLuint m_id;
    };

}