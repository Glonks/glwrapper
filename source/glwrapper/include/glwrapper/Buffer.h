#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>

#include <vector>
#include <array>

namespace glwrapper {

    class Buffer : public Instantiator<Buffer> {
    public:
        Buffer();
        virtual ~Buffer();

        void bind(GLenum target) const;
        static void unbind(GLenum target);
        static void unbind(GLenum target, GLuint index);

        void setData(GLsizeiptr size, const GLvoid* data, GLenum usage);

        template <typename T>
        void setData(const T& data, GLenum usage);

        template <typename T>
        void setData(const std::vector<T>& data, GLenum usage);

        template <typename T, std::size_t Count>
        void setData(const std::array<T, Count>& data, GLenum usage);

        const void* map() const;
        void* map(GLenum access);

        void unmap() const;

        GLuint id() const;

    private:
        GLuint m_id;
    };

    template <typename T>
    void Buffer::setData(const T& data, GLenum usage) {
        setData(static_cast<GLsizeiptr>(sizeof(T)), &data, usage);
    }

    template <typename T>
    void Buffer::setData(const std::vector<T>& data, GLenum usage) {
        setData(static_cast<GLsizeiptr>(data.size() * sizeof(T)), data.data(), usage);
    }

    template <typename T, std::size_t Count>
    void Buffer::setData(const std::array<T, Count>& data, GLenum usage) {
        setData(static_cast<GLsizeiptr>(Count * sizeof(T)), data.data(), usage);
    }

}