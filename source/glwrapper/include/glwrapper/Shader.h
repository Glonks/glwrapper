#pragma once

namespace glwrapper {

    class Shader {
    public:
        virtual ~Shader() = default;

        static fromString(const std::string& string) const;
        static fromFile(const std::string& filePath) const;

        virtual void bind() = 0;
        virtual void unbind() = 0;

    protected:

    };

}