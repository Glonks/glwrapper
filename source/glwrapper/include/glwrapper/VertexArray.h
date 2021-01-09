#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>

#include <map>
#include <vector>

namespace glwrapper {

    class Buffer;
    class VertexBindingPoint;

    class VertexArray : public Instantiator<VertexArray> {
    public:
        VertexArray();
        virtual ~VertexArray();

        void bind() const;
        static void unbind();

        void enable(GLuint index);
        void disable(GLuint index);

        std::shared_ptr<VertexBindingPoint> binding(GLuint bindingIndex);
        std::shared_ptr<const VertexBindingPoint> binding(GLuint bindingIndex) const;

        void bindElementBuffer(const std::shared_ptr<Buffer>& buffer);

        void drawArrays(GLenum mode, GLint first, GLsizei count) const;

        void drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices = nullptr) const;

        GLuint id() const;
        std::vector<std::shared_ptr<VertexBindingPoint>> bindings();
        std::vector<std::shared_ptr<const VertexBindingPoint>> bindings() const;

    private:
        GLuint m_id;
        std::map<GLuint, std::shared_ptr<VertexBindingPoint>> m_vertexBindingPoints;
    };

}