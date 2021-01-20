#include <glwrapper/Texture.h>

#include <glm/gtc/type_ptr.hpp>

#include <utility>

namespace glwrapper {

    Texture::Texture(const GLenum target) : m_target{target} {
        glCreateTextures(target, 1, &m_id);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &m_id);
    }

    void Texture::bind() const {
        glBindTexture(m_target, m_id);
    }

    void Texture::unbind() const {
        unbind(m_target);
    }

    void Texture::unbind(GLenum target) {
        glBindTexture(target, 0);
    }

    void Texture::bindTextureUnit(GLuint unit) const {
        glBindTextureUnit(unit, m_id);
    }

    void Texture::unbindTextureUnit(GLuint unit) {
        glBindTextureUnit(unit, 0);
    }

    void Texture::setParameter(GLenum pname, GLenum value) {
        setParameter(pname, static_cast<GLint>(value));
    }

    void Texture::setParameter(GLenum pname, GLint value) {
        glTextureParameteri(m_id, pname, value);
    }

    void Texture::setParameter(GLenum pname, GLfloat value) {
        glTextureParameterf(m_id, pname, value);
    }

    void Texture::setParameter(GLenum pname, const glm::vec4& value) {
        glTextureParameterfv(m_id, pname, glm::value_ptr(value));
    }

    void Texture::subImage2D(GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format,
                             GLenum type, const GLvoid* pixels) {
        glTextureSubImage2D(m_id, level, xOffset, yOffset, width, height, format, type, pixels);
    }

    void Texture::storage1D(GLsizei levels, GLenum internalFormat, GLsizei width) {
        glTextureStorage1D(m_id, levels, internalFormat, width);
    }

    void Texture::storage2D(GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height) {
        glTextureStorage2D(m_id, levels, internalFormat, width, height);
    }

    void Texture::storage3D(GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth) {
        glTextureStorage3D(m_id, levels, internalFormat, width, height, depth);
    }

    void Texture::generateMipMap() {
        glGenerateTextureMipmap(m_id);
    }

    GLuint Texture::id() const {
        return m_id;
    }

    GLenum Texture::target() const {
        return m_target;
    }

}