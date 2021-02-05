#include <glwrapper/glwpch.h>
#include <glwrapper/VertexArray.h>
#include <glwrapper/Buffer.h>
#include <glwrapper/VertexBindingPoint.h>

#include <memory>

namespace glw {

    VertexArray::VertexArray() {
        glCreateVertexArrays(1, &m_id);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_id);
    }

    void VertexArray::unbind() {
        glBindVertexArray(0);
    }

    void VertexArray::enable(GLuint index) {
        glEnableVertexArrayAttrib(m_id, index);
    }

    void VertexArray::disable(GLuint index) {
        glDisableVertexArrayAttrib(m_id, index);
    }

    std::shared_ptr<VertexBindingPoint> VertexArray::binding(GLuint bindingIndex) {
        const auto i_binding = m_vertexBindingPoints.find(bindingIndex);

        if (i_binding == m_vertexBindingPoints.end()) {
            const auto it_binding = m_vertexBindingPoints.emplace(bindingIndex, VertexBindingPoint::createShared(
                    std::shared_ptr<VertexArray>(this), bindingIndex));

            return it_binding.first->second;
        }

        return i_binding->second;
    }

    std::shared_ptr<const VertexBindingPoint> VertexArray::binding(GLuint index) const {
        const auto i_binding = m_vertexBindingPoints.find(index);

        if (i_binding == m_vertexBindingPoints.end())
            return nullptr;

        return i_binding->second;
    }

    void VertexArray::bindElementBuffer(const std::shared_ptr<Buffer>& buffer) {
        glVertexArrayElementBuffer(m_id, buffer ? buffer->id() : 0);
    }

    void VertexArray::drawArrays(GLenum mode, GLint first, GLsizei count) const {
        bind();
        glDrawArrays(mode, first, count);
    }

    void VertexArray::drawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) const {
        bind();
        glDrawElements(mode, count, type, indices);
    }

    GLuint VertexArray::id() const {
        return m_id;
    }

    std::vector<std::shared_ptr<VertexBindingPoint>> VertexArray::bindings() {
        std::vector<std::shared_ptr<VertexBindingPoint>> v_bindings;
        v_bindings.reserve(m_vertexBindingPoints.size());

        for (const auto& t_binding : m_vertexBindingPoints)
            v_bindings.push_back(t_binding.second);

        return v_bindings;
    }

    std::vector<std::shared_ptr<const VertexBindingPoint>> VertexArray::bindings() const {
        std::vector<std::shared_ptr<const VertexBindingPoint>> v_bindings;
        v_bindings.reserve(m_vertexBindingPoints.size());

        for (const auto& t_binding : m_vertexBindingPoints)
            v_bindings.push_back(t_binding.second);

        return v_bindings;
    }

}