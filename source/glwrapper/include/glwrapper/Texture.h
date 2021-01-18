#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <string>

namespace glwrapper {

    class Sampler;

    class Texture : public Instantiator<Texture> {
    public:
        explicit Texture(const GLenum target);
        virtual ~Texture();

        void bind() const;
        void unbind() const;
        static void unbind(GLenum target);

        void bindTextureUnit(GLuint unit) const;
        static void unbindTextureUnit(GLuint unit);

        void subImage2D(GLint level, GLint xOffset, GLint yOffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels);

        void storage1D(GLsizei levels, GLenum internalFormat, GLsizei width);
        void storage2D(GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height);
        void storage3D(GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth);

        GLuint id() const;
        GLenum target() const;

    private:
        GLenum m_target;
        GLuint m_id;
    };

}