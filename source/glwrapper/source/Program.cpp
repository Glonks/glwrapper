#include <glwrapper/Program.h>
#include <glwrapper/base/Log.h>
#include <glwrapper/base/Assert.h>

#include <glm/gtc/type_ptr.hpp>

namespace glwrapper {

    Program::Program() : m_id{glCreateProgram()},
                         m_linked{false} {}

    Program::~Program() {
        glDeleteProgram(m_id);
    }

    void Program::attach(std::shared_ptr<Shader> shader) {
        if (!shader->isCompiled())
            shader->compile();

        glAttachShader(m_id, shader->id());
    }

    void Program::detach(std::shared_ptr<Shader> shader) {
        if (m_shaders.find(shader) == m_shaders.end()) {
            GLW_CORE_WARN("Shader {0} isn't linked to the program it is trying to detach from", shader->id());

            return;
        }

        glDetachShader(m_id, shader->id());
    }

    void Program::link() const {
        m_linked = false;

        glLinkProgram(m_id);

        GLint success = 0;
        glGetProgramiv(m_id, GL_LINK_STATUS, &success);

        if (success == GL_FALSE) {
            GLint maxLogLength = 0;
            glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLogLength);

            std::vector<GLchar> infoLog(maxLogLength);
            glGetProgramInfoLog(m_id, maxLogLength, &maxLogLength, &infoLog[0]);

            GLW_CORE_ERROR("{0}", infoLog.data());
            GLW_CORE_ASSERT(success == GL_TRUE, "Program {0} could not be linked", m_id);

            return;
        }

        m_linked = true;
    }

    void Program::validate() const {
        glValidateProgram(m_id);
    }

    void Program::bind() const {
        if (!m_linked) {
            GLW_CORE_WARN("Program {0} isn't linked", m_id);

            return;
        }

        glUseProgram(m_id);
    }

    void Program::unbind() {
        glUseProgram(0);
    }

    void Program::dispatchCompute(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ) const {
        bind();
        glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
    }

    void Program::setUniform(const std::string& name, const float& value) const {
        glUniform1f(getUniformLocation(name), value);
    }

    void Program::setUniform(const std::string& name, const int& value) const {
        glUniform1i(getUniformLocation(name), value);
    }

    void Program::setUniform(const std::string& name, const unsigned int& value) const {
        glUniform1ui(getUniformLocation(name), value);
    }

    void Program::setUniform(const std::string& name, const bool& value) const {
        glUniform1i(getUniformLocation(name), value ? 1 : 0);
    }

    void Program::setUniform(const std::string& name, const glm::vec2& value) const {
        glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::vec3& value) const {
        glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::vec4& value) const {
        glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::ivec2& value) const {
        glUniform2iv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::ivec3& value) const {
        glUniform3iv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::ivec4& value) const {
        glUniform4iv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::uvec2& value) const {
        glUniform2uiv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::uvec3& value) const {
        glUniform3uiv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::uvec4& value) const {
        glUniform4uiv(getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat2& value) const {
        glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat3& value) const {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat4& value) const {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat2x3& value) const {
        glUniformMatrix2x3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat3x2& value) const {
        glUniformMatrix3x2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat2x4& value) const {
        glUniformMatrix2x4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat4x2& value) const {
        glUniformMatrix4x2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat3x4& value) const {
        glUniformMatrix3x4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat4x3& value) const {
        glUniformMatrix4x3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    GLuint Program::id() const {
        return m_id;
    }

    bool Program::isLinked() const {
        return m_linked;
    }

    bool Program::isValid() const {
        GLint valid = 0;
        glGetProgramiv(m_id, GL_VALIDATE_STATUS, &valid);

        return valid == 1;
    }

    const std::set<std::shared_ptr<Shader>>& Program::shaders() const {
        return m_shaders;
    }

    GLuint Program::getUniformLocation(const std::string& name) const {
        if (m_uniformLocations.find(name) != m_uniformLocations.end())
            return m_uniformLocations[name];

        int location = glGetUniformLocation(m_id, name.c_str());

        if (location == -1)
            GLW_CORE_WARN("Uniform {0} doesn't exist (might be unused in the shader)", name);

        return m_uniformLocations[name] = location;
    }

}