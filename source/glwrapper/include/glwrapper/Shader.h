#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>

#include <string>
#include <memory>

namespace glwrapper {

    class Source;

    class Shader : public Instantiator<Shader> {
    public:
        Shader(GLenum type, std::shared_ptr<Source> source);
        virtual ~Shader();

        static std::shared_ptr<Shader> fromFile(GLenum type, const std::string& filePath);
        static std::shared_ptr<Shader> fromString(GLenum type, const std::string& string);

        void compile() const;

        GLuint id() const;
        GLenum type() const;
        bool isCompiled() const;

    private:
        GLuint m_id;
        std::shared_ptr<Source> m_source;
        GLenum m_type;
        mutable bool m_compiled;
    };

}