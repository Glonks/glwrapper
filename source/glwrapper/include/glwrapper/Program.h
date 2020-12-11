#pragma once

#include <glwrapper/base/Instantiator.h>
#include <glwrapper/Shader.h>

#include <set>

namespace glwrapper {

    class Program : public Instantiator<Program> {
    public:
        Program();
        virtual ~Program();

        void bind() const;
        static void unbind();

        GLuint id() const;
        bool isLinked() const;

    private:
        GLuint m_id;
        std::set<Shader> m_shaders;
        mutable bool m_linked;
    };

};