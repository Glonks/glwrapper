#include <glwrapper/Shader.h>
#include <glwrapper/base/Log.h>

#include <vector>

namespace glwrapper {

    Shader::Shader(const GLenum type, Source* source) : m_type{type},
                                                        m_id{glCreateShader(type)},
                                                        m_source{source},
                                                        m_compiled{false} {
        compile();
    }

    Shader::~Shader() {
        glDeleteShader(m_id);
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