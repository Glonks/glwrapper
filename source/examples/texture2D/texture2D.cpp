#include <glwrapper/glwrapper.h>

#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

int main() {
    glwrapper::Log::init();

    int init_success = glfwInit();

    if (!init_success) {
        GLW_ERROR("Failed to init GLFW");

        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int WIDTH = 960;
    const int HEIGHT = 960;

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Test", nullptr, nullptr);

    if (window == nullptr) {
        GLW_ERROR("Couldn't create a window");
        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* _window, int _width, int _height) {
        glViewport(0, 0, _width, _height);
    });

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        GLW_ERROR("Failed to init GLAD");

        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::string vert = R"(
            #version 460 core

            layout (location = 0) in vec4 position;
            layout (location = 1) in vec2 tex_coord;

            out vec2 v_tex_coord;

            void main() {
                v_tex_coord = tex_coord;
                gl_Position = position;
            }
        )";

        std::string frag = R"(
            #version 460 core

            in vec2 v_tex_coord;
            uniform sampler2D u_texture;

            out vec4 color;

            void main() {
                color = texture(u_texture, v_tex_coord);
            }
        )";

        auto program = glwrapper::Program::createShared();
        program->attach(
                glwrapper::Shader::fromString(GL_VERTEX_SHADER, vert),
                glwrapper::Shader::fromString(GL_FRAGMENT_SHADER, frag)
        );
        program->link();
        program->bind();

        auto vao = glwrapper::VertexArray::createShared();
        vao->bind();

        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.0f, 1.0f
        };

        auto vbo = glwrapper::Buffer::createShared();
        vbo->bind(GL_ARRAY_BUFFER);
        vbo->setData(vertices, GL_STATIC_DRAW);

        vao->enable(0);

        auto binding_1 = vao->binding(0);
        binding_1->bindAttribute(0);
        binding_1->setFormat(2, GL_FLOAT);
        binding_1->bindBuffer(vbo, 0, 4 * sizeof(float));

        vao->enable(1);

        auto binding_2 = vao->binding(0);
        binding_2->bindAttribute(1);
        binding_2->setFormat(2, GL_FLOAT, GL_FALSE, 2 * sizeof(float));

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        auto ibo = glwrapper::Buffer::createShared();
        ibo->setData(indices, GL_STATIC_DRAW);

        vao->bindElementBuffer(ibo);

        auto sampler = glwrapper::Sampler::createShared();
        sampler->setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        sampler->setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        sampler->setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        sampler->setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        sampler->bindTextureUnit(0);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* pixels = stbi_load("assets/cat.png", &width, &height, &channels, 0);
        GLW_INFO(channels);

        auto texture = glwrapper::Texture::createShared(GL_TEXTURE_2D);
        texture->storage2D(1, GL_RGBA8, width, height);
        texture->subImage2D(0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, reinterpret_cast<const GLvoid*>(pixels));
        texture->bindTextureUnit(0);

        stbi_image_free(pixels);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            vao->drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }

    return 0;
}