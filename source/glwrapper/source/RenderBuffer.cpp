#include <glwrapper/glwpch.h>
#include <glwrapper/RenderBuffer.h>

namespace glw {

    RenderBuffer::RenderBuffer() {
        glCreateRenderbuffers(1, &m_id);
    }

    RenderBuffer::~RenderBuffer() {
        glDeleteRenderbuffers(1, &m_id);
    }

    void RenderBuffer::bind() const {
        glBindRenderbuffer(GL_RENDERBUFFER, m_id);
    }

    void RenderBuffer::unbind() {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void RenderBuffer::storage(GLenum internalFormat, GLsizei width, GLsizei height) {
        glNamedRenderbufferStorage(m_id, internalFormat, width, height);
    }

    void RenderBuffer::storageMultisample(GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height) {
        glNamedRenderbufferStorageMultisample(m_id, samples, internalFormat, width, height);
    }

    GLuint RenderBuffer::id() const {
        return m_id;
    }

}