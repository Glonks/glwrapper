#include <glwrapper/Shader.h>
#include <glwrapper/FileSource.h>
#include <glwrapper/StringSource.h>
#include <glwrapper/base/Log.h>
#include <glwrapper/base/Assert.h>

#include <vector>

namespace glwrapper {

    Shader::Shader(const GLenum type, std::shared_ptr<Source> source) : m_type{type},
                                                                        m_id{glCreateShader(type)},
                                                                        m_source{source},
                                                                        m_compiled{false} {
        compile();
    }

    Shader::~Shader() {
        glDeleteShader(m_id);
    }

    std::shared_ptr<Shader> Shader::fromFile(const GLenum type, const std::string& filePath) {
        auto file_source = FileSource::createShared(filePath);

        if (!file_source->isValid()) {
            GLW_CORE_WARN("Error in reading file at '{0}', shader was not constructed", filePath);

            return nullptr;
        }

        return Shader::createShared(type, file_source);
    }

    std::shared_ptr<Shader> Shader::fromString(const GLenum type, const std::string& string) {
        auto string_source = StringSource::createShared(string);

        return Shader::createShared(type, string_source);
    }

    void Shader::compile() const {
        m_compiled = false;

        std::string source_str = m_source->string();
        const GLchar* source_c_str = source_str.c_str();

        glShaderSource(m_id, 1, &source_c_str, nullptr);
        glCompileShader(m_id);

        int success = 0;
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint maxLogLength = 0;
            glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLogLength);

            std::vector<GLchar> infoLog(maxLogLength);
            glGetShaderInfoLog(m_id, maxLogLength, &maxLogLength, &infoLog[0]);

            glDeleteShader(m_id);

            GLW_CORE_ERROR("{0}", infoLog.data());
            GLW_CORE_ASSERT(success == GL_TRUE, "Shader {0} ({1}) failed to compile", m_id, m_source->info());
            return;
        }

        m_compiled = true;
    }

    GLuint Shader::id() const {
        return m_id;
    }

    GLenum Shader::type() const {
        return m_type;
    }

    bool Shader::isCompiled() const {
        return m_compiled;
    }

}