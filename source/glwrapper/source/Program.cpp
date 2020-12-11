#include <glwrapper/Program.h>

namespace glwrapper {

    Program::Program() : m_id{0} {}

    void Program::bind() const {
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