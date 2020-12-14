#include <glwrapper/glwrapper.h>

#include <GLFW/glfw3.h>

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
    const int HEIGHT = 540;

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

        float vertices[] = {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                0.5f, 0.5f,
                -0.5f, 0.5f
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        auto vao = glwrapper::VertexArray::createUnique();
        vao->bind();

        auto vbo = glwrapper::Buffer::createUnique();
        vbo->bind(GL_ARRAY_BUFFER);
        vbo->setData(vertices, GL_STATIC_DRAW);

        vao->enable(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<const void*>(0)); // Replace with VertexArray func

        auto ibo = glwrapper::Buffer::createUnique();
        ibo->bind(GL_ELEMENT_ARRAY_BUFFER);
        ibo->setData(indices, GL_STATIC_DRAW);

        glwrapper::Buffer::unbind(GL_ARRAY_BUFFER);
        glwrapper::VertexArray::unbind();

        std::string vert = R"(
            #version 460 core

            layout (location = 0) in vec4 position;

            out vec3 c_pos;

            void main() {
                c_pos = vec3(position.x, position.y, position.z);
                gl_Position = position;
            }
        )";

        std::string frag = R"(
            #version 460 core

            in vec3 c_pos;
            uniform float trans;
            out vec4 color;

            void main() {
                color = vec4(c_pos * 0.5 + trans, 1.0f);
            }
        )";

        auto program = glwrapper::Program::createUnique();
        program->attach(
                glwrapper::Shader::fromString(GL_VERTEX_SHADER, vert),
                glwrapper::Shader::fromString(GL_FRAGMENT_SHADER, frag)
        );
        program->link();

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            program->bind();
            program->setUniform("trans", 0.5f);

            vao->bind();
            vao->drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
    }

    return 0;
}