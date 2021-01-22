#include <glwrapper/Buffer.h>

namespace glw {

    Buffer::Buffer() {
        glCreateBuffers(1, &m_id);
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1, &m_id);
    }

    void Buffer::bind(GLenum target) const {
        glBindBuffer(target, m_id);
    }

    void Buffer::unbind(GLenum target) {
        glBindBuffer(target, 0);
    }

    void Buffer::unbind(GLenum target, GLuint index) {
        glBindBufferBase(target, index, 0);
    }

    void Buffer::setData(GLsizeiptr size, const GLvoid* data, GLenum usage) {
        glNamedBufferData(m_id, size, data, usage);
    }

    const void* Buffer::map() const {
        return static_cast<const void*>(glMapNamedBuffer(m_id, GL_READ_ONLY));
    }

    void* Buffer::map(GLenum access) {
        return glMapNamedBuffer(m_id, access);
    }

    void Buffer::unmap() const {
        glUnmapNamedBuffer(m_id);
    }

    GLuint Buffer::id() const {
        return m_id;
    }

}