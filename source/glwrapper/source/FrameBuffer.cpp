#include <glwrapper/glwpch.h>
#include <glwrapper/FrameBuffer.h>
#include <glwrapper/Texture.h>
#include <glwrapper/RenderBuffer.h>
#include <glwrapper/base/Log.h>
#include <glwrapper/base/Assert.h>

#include <set>

namespace glw {

    FrameBuffer::FrameBuffer() {
        glCreateFramebuffers(1, &m_id);
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &m_id);
    }

    FrameBuffer::FrameBuffer(GLuint id) : m_id{id} {}

    std::unique_ptr<FrameBuffer> FrameBuffer::defaultFrameBuffer() {
        return FrameBuffer::createUnique(0);
    }

    void FrameBuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    }

    void FrameBuffer::bind(GLenum target) const {
        glBindFramebuffer(target, m_id);
    }

    void FrameBuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FrameBuffer::unbind(GLenum target) {
        glBindFramebuffer(target, 0);
    }

    void FrameBuffer::attachTexture(const GLenum attachment, const std::shared_ptr<Texture>& texture, GLint level) {
        m_attachedTextures[attachment] = texture;

        glNamedFramebufferTexture(m_id, attachment, texture->id(), level);
    }

    void FrameBuffer::attachRenderBuffer(const GLenum attachment, const std::shared_ptr<RenderBuffer>& renderBuffer) {
        m_attachedRenderBuffers[attachment] = renderBuffer;

        glNamedFramebufferRenderbuffer(m_id, attachment, GL_RENDERBUFFER, renderBuffer ? renderBuffer->id() : 0);
    }

    void FrameBuffer::detach(const GLenum attachment) {
        auto it_t = m_attachedTextures.find(attachment);
        auto it_rb = m_attachedRenderBuffers.find(attachment);

        if (it_t != m_attachedTextures.end())
            m_attachedTextures.erase(it_t);

        else if (it_rb != m_attachedRenderBuffers.end())
            m_attachedRenderBuffers.erase(it_rb);

        else
            GLW_CORE_WARN("{0} is not currently attached", attachment);
    }

    void FrameBuffer::setDrawBuffer(GLenum buf) {
        glNamedFramebufferDrawBuffer(m_id, buf);
    }

    void FrameBuffer::setDrawBuffers(const std::vector<GLenum>& bufs) {
        setDrawBuffers(bufs.size(), bufs.data());
    }

    void FrameBuffer::setDrawBuffers(const GLsizei count, const GLenum* bufs) {
        GLW_CORE_ASSERT(bufs != nullptr || count != 0, "No draw buffers passed");

        glNamedFramebufferDrawBuffers(m_id, count, bufs);
    }

    void FrameBuffer::clear(const GLbitfield mask) {
        bind(GL_DRAW_FRAMEBUFFER);

        glClear(mask);
    }

    void FrameBuffer::clearColor(const glm::vec4& color) {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void FrameBuffer::clearDepth(const GLdouble depth) {
        glClearDepth(depth);
    }

    void FrameBuffer::blit(std::array<GLint, 4> srcCoords, const std::shared_ptr<FrameBuffer>& drawFrameBuffer,
                           std::array<GLint, 4> dstCoords, GLbitfield mask, GLenum filter) const {
        bind(GL_READ_FRAMEBUFFER);
        drawFrameBuffer->bind(GL_DRAW_FRAMEBUFFER);

        glBlitNamedFramebuffer(m_id, drawFrameBuffer->id(), srcCoords[0], srcCoords[1], srcCoords[2], srcCoords[3],
                               dstCoords[0], dstCoords[1], dstCoords[2], dstCoords[3], mask, filter);
    }

    GLuint FrameBuffer::id() const {
        return m_id;
    }

    GLenum FrameBuffer::status() const {
        return glCheckNamedFramebufferStatus(m_id, GL_FRAMEBUFFER);
    }

    std::map<GLenum, std::shared_ptr<Texture>> FrameBuffer::attachedTextures() const {
        return m_attachedTextures;
    }

    std::map<GLenum, std::shared_ptr<RenderBuffer>> FrameBuffer::attachedRenderBuffers() const {
        return m_attachedRenderBuffers;
    }

}