#pragma once

#include <string>

#include <glad/glad.h>

#include <glwrapper/base/Instantiator.h>
#include <glwrapper/Shader.h>

namespace glwrapper {

    class GLShader : public Shader, public Instantiator<GLShader> {
    public:
        GLShader(const std::string& filePath)

    private:

    };

}