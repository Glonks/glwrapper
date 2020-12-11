#pragma once

#include <glwrapper/base/Source.h>

#include <glad/glad.h>

#include <string>
#include <memory>

namespace glwrapper {

    class Shader {
    public:
        Shader(const GLenum shaderType, Source* source);
        virtual ~Shader();

        void compile() const;

        GLuint id() const;
        GLenum type() const;
        bool isCompiled() const;

    private:
        GLuint m_id;
        Source* m_source;
        GLenum m_type;
        mutable bool m_compiled;
    };

}