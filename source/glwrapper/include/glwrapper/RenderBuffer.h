#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>

namespace glw {

    class RenderBuffer : public Instantiator<RenderBuffer> {
    public:
        RenderBuffer();
        virtual ~RenderBuffer();

        void bind() const;
        static void unbind();

        void storage(GLenum internalFormat, GLsizei width, GLsizei height);
        void storageMultisample(GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height);

        GLuint id() const;

    private:
        GLuint m_id;
    };

}