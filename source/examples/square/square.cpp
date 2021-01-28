#include <glwrapper/glwrapper.h>

#include <GLFW/glfw3.h>

int main() {
    glw::Log::init();

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

        auto vao = glw::VertexArray::createShared();

        float vertices[] = {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                0.5f, 0.5f,
                -0.5f, 0.5f
        };

        auto vbo = glw::Buffer::createShared();
        vbo->bind(GL_ARRAY_BUFFER);
        vbo->setData(vertices, GL_STATIC_DRAW);

        vao->enable(0);

        auto binding = vao->binding(0);
        binding->bindAttribute(0);
        binding->setFormat(2, GL_FLOAT);
        binding->bindBuffer(vbo, 0, 2 * sizeof(float));

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        auto ibo = glw::Buffer::createShared();
        ibo->setData(indices, GL_STATIC_DRAW);

        vao->bindElementBuffer(ibo);

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

        auto program = glw::Program::createShared();
        program->attach(
                glw::Shader::fromString(GL_VERTEX_SHADER, vert),
                glw::Shader::fromString(GL_FRAGMENT_SHADER, frag)
        );
        program->link();
        program->setUniform("trans", 0.5f);
        program->bind();

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            vao->drawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
        }

        glfwTerminate();
    }

    return 0;
}