#include <glwrapper/Program.h>
#include <glwrapper/base/Log.h>

namespace glwrapper {

    Program::Program() : m_id{glCreateProgram()},
                         m_linked{false} {}

    Program::~Program() {
        glDeleteProgram(m_id);
    }

    void Program::attach(std::shared_ptr<Shader> shader) {
        glAttachShader(m_id, shader->id());
    }

    void Program::detach(std::shared_ptr<Shader> shader) {
        if (m_shaders.find(shader) == m_shaders.end()) {
            GLW_CORE_WARN("Shader {0} isn't linked to the program it is trying to detach from", shader->id());

            return;
        }

        glDetachShader(m_id, shader->id());
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

    GLuint Program::id() const {
        return m_id;
    }

    bool Program::isLinked() const {
        return m_linked;
    }

}