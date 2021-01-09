#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <set>
#include <unordered_map>

namespace glwrapper {

    class Shader;

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

        void link() const;
        void validate() const;

        void dispatchCompute(GLuint numGroupsX, GLuint numGroupsY, GLuint numGroupsZ) const;

        void setUniform(const std::string& name, const float& value) const;
        void setUniform(const std::string& name, const int& value) const;
        void setUniform(const std::string& name, const unsigned int& value) const;
        void setUniform(const std::string& name, const bool& value) const;

        void setUniform(const std::string& name, const glm::vec2& value) const;
        void setUniform(const std::string& name, const glm::vec3& value) const;
        void setUniform(const std::string& name, const glm::vec4& value) const;

        void setUniform(const std::string& name, const glm::ivec2& value) const;
        void setUniform(const std::string& name, const glm::ivec3& value) const;
        void setUniform(const std::string& name, const glm::ivec4& value) const;

        void setUniform(const std::string& name, const glm::uvec2& value) const;
        void setUniform(const std::string& name, const glm::uvec3& value) const;
        void setUniform(const std::string& name, const glm::uvec4& value) const;

        void setUniform(const std::string& name, const glm::mat2& value) const;
        void setUniform(const std::string& name, const glm::mat3& value) const;
        void setUniform(const std::string& name, const glm::mat4& value) const;

        void setUniform(const std::string& name, const glm::mat2x3& value) const;
        void setUniform(const std::string& name, const glm::mat3x2& value) const;

        void setUniform(const std::string& name, const glm::mat2x4& value) const;
        void setUniform(const std::string& name, const glm::mat4x2& value) const;

        void setUniform(const std::string& name, const glm::mat3x4& value) const;
        void setUniform(const std::string& name, const glm::mat4x3& value) const;

        GLuint id() const;
        bool isLinked() const;
        bool isValid() const;
        const std::set<std::shared_ptr<Shader>>& shaders() const;

    private:
        GLuint m_id;
        std::set<std::shared_ptr<Shader>> m_shaders;
        mutable std::unordered_map<std::string, GLint> m_uniformLocations;
        mutable bool m_linked;

        GLuint getUniformLocation(const std::string& name) const;
    };

    template <typename... Shaders>
    void Program::attach(std::shared_ptr<Shader> shader, Shaders ... shaders) {
        attach(shader);
        attach(std::forward<Shaders>(shaders)...);
    }

}