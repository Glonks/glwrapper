#include <glwrapper/glwpch.h>
#include <glwrapper/Program.h>
#include <glwrapper/Shader.h>
#include <glwrapper/base/Log.h>
#include <glwrapper/base/Assert.h>

#include <glm/gtc/type_ptr.hpp>

namespace glw {

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
        glProgramUniform1f(m_id, getUniformLocation(name), value);
    }

    void Program::setUniform(const std::string& name, const int& value) const {
        glProgramUniform1i(m_id, getUniformLocation(name), value);
    }

    void Program::setUniform(const std::string& name, const unsigned int& value) const {
        glProgramUniform1ui(m_id, getUniformLocation(name), value);
    }

    void Program::setUniform(const std::string& name, const bool& value) const {
        glProgramUniform1i(m_id, getUniformLocation(name), value ? 1 : 0);
    }

    void Program::setUniform(const std::string& name, const glm::vec2& value) const {
        glProgramUniform2fv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::vec3& value) const {
        glProgramUniform3fv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::vec4& value) const {
        glProgramUniform4fv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::ivec2& value) const {
        glProgramUniform2iv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::ivec3& value) const {
        glProgramUniform3iv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::ivec4& value) const {
        glProgramUniform4iv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::uvec2& value) const {
        glProgramUniform2uiv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::uvec3& value) const {
        glProgramUniform3uiv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::uvec4& value) const {
        glProgramUniform4uiv(m_id, getUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat2& value) const {
        glProgramUniformMatrix2fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat3& value) const {
        glProgramUniformMatrix3fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat4& value) const {
        glProgramUniformMatrix4fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat2x3& value) const {
        glProgramUniformMatrix2x3fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat3x2& value) const {
        glProgramUniformMatrix3x2fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat2x4& value) const {
        glProgramUniformMatrix2x4fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat4x2& value) const {
        glProgramUniformMatrix4x2fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat3x4& value) const {
        glProgramUniformMatrix3x4fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Program::setUniform(const std::string& name, const glm::mat4x3& value) const {
        glProgramUniformMatrix4x3fv(m_id, getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
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