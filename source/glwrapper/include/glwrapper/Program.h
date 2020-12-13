#pragma once

#include <glwrapper/base/Instantiator.h>
#include <glwrapper/Shader.h>

#include <glad/glad.h>

#include <set>

namespace glwrapper {

    class Program : public Instantiator<Program> {
    public:
        Program();
        virtual ~Program();

        void bind() const;
        static void unbind();

        void attach(std::shared_ptr<Shader> shader);
        template <typename ...Shaders>
        void attach(std::shared_ptr<Shader> shader, Shaders ... shaders);

        void detach(std::shared_ptr<Shader> shader);

        GLuint id() const;

        bool isLinked() const;

    private:
        GLuint m_id;
        std::set<std::shared_ptr<Shader>> m_shaders;
        mutable bool m_linked;
    };

    template <typename... Shaders>
    void Program::attach(std::shared_ptr<Shader> shader, Shaders ... shaders) {
        attach(shader);
        attach(std::forward<Shaders>(shaders)...);
    }

};