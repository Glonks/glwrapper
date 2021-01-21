#pragma once

#include <glwrapper/base/Instantiator.h>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <map>
#include <vector>
#include <array>

namespace glwrapper {

    class Texture;
    class RenderBuffer;

    class FrameBuffer : public Instantiator<FrameBuffer> {
    public:
        FrameBuffer();
        virtual ~FrameBuffer();

        void bind() const;
        void bind(GLenum target) const;
        static void unbind();
        static void unbind(GLenum target);

        void attachTexture(GLenum attachment, const std::shared_ptr<Texture>& texture, GLint level = 0);
        void attachRenderBuffer(GLenum attachment, const std::shared_ptr<RenderBuffer>& renderBuffer);

        void detach(GLenum attachment);

        void setDrawBuffer(GLenum buf);
        void setDrawBuffers(const std::vector<GLenum>& bufs);
        void setDrawBuffers(GLsizei count, const GLenum* bufs);
        template <std::size_t Count>
        void setDrawBuffers(const std::array<GLenum, Count>& bufs);

        void clear(GLbitfield mask);
        static void clearColor(const glm::vec4& color);
        static void clearDepth(GLdouble depth);

        void blit(std::array<GLint, 4> srcCoords, const std::shared_ptr<FrameBuffer>& drawFrameBuffer,
                  std::array<GLint, 4> dstCoords, GLbitfield mask, GLenum filter) const;

        GLuint id() const;
        GLenum status() const;
        std::map<GLenum, std::shared_ptr<Texture>> attachedTextures() const;
        std::map<GLenum, std::shared_ptr<RenderBuffer>> attachedRenderBuffers() const;

    private:
        GLuint m_id;
        std::map<GLenum, std::shared_ptr<Texture>> m_attachedTextures;
        std::map<GLenum, std::shared_ptr<RenderBuffer>> m_attachedRenderBuffers;
    };

    template <std::size_t Count>
    void FrameBuffer::setDrawBuffers(const std::array<GLenum, Count>& bufs) {
        setDrawBuffers(static_cast<GLsizei>(Count), bufs.data());
    }

}