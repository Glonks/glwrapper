#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace glw {

    class Sampler : public Instantiator<Sampler> {
    public:
        Sampler();
        virtual ~Sampler();

        void bindTextureUnit(GLuint unit) const;

        void setParameter(GLenum pname, GLenum value);
        void setParameter(GLenum pname, GLint value);
        void setParameter(GLenum pname, GLfloat value);
        void setParameter(GLenum pname, const glm::vec4& value);

        GLuint id() const;

    private:
        GLuint m_id;
    };

}