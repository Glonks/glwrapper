#include <glwrapper/Sampler.h>

#include <glm/gtc/type_ptr.hpp>

namespace glwrapper {

    Sampler::Sampler() {
        glCreateSamplers(1, &m_id);
    }

    Sampler::~Sampler() {
        glDeleteSamplers(1, &m_id);
    }

    void Sampler::bindTextureUnit(GLuint unit) const {
        glBindTextureUnit(unit, m_id);
    }

    void Sampler::setParameter(GLenum pname, GLenum value) {
        setParameter(pname, static_cast<GLint>(value));
    }

    void Sampler::setParameter(GLenum pname, GLint value) {
        glSamplerParameteri(m_id, pname, value);
    }

    void Sampler::setParameter(GLenum pname, GLfloat value) {
        glSamplerParameterf(m_id, pname, value);
    }

    void Sampler::setParameter(GLenum pname, const glm::vec4& value) {
        glSamplerParameterfv(m_id, pname, glm::value_ptr(value));
    }

    GLuint Sampler::id() const {
        return m_id;
    }

}