#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>

#include <set>

namespace glw {

    void setViewport(GLint x, GLint y, GLsizei width, GLsizei height);

    void enable(GLenum cap);
    void enable(const std::vector<GLenum>& caps);

    void disable(GLenum cap);
    void disable(const std::vector<GLenum>& caps);

    bool isEnabled(GLenum cap);

    void setBlendFunc(GLenum sfactor, GLenum dfactor);
    void setDepthFunc(GLenum func);

}