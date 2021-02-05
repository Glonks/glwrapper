#include <glwrapper/State.h>

namespace glw {

    void setViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
        glViewport(x, y, width, height);
    }

    void enable(const GLenum cap) {
        glEnable(cap);
    }

    void enable(const std::vector<GLenum>& caps) {
        for (const GLenum& cap : caps)
            enable(cap);
    }

    void disable(const GLenum cap) {
        glDisable(cap);
    }

    void disable(const std::vector<GLenum>& caps) {
        for (const GLenum& cap : caps)
            disable(cap);
    }

    bool isEnabled(const GLenum cap) {
        return glIsEnabled(cap) == GL_TRUE;
    }

    void setBlendFunc(const GLenum sfactor, const GLenum dfactor) {
        glBlendFunc(sfactor, dfactor);
    }

    void setDepthFunc(const GLenum func) {
        glDepthFunc(func);
    }

}