#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "vendor/stb_image.h"
#include "Texture.h"


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    // GLFW error callback
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glEnable(GL_DEBUG_OUTPUT);
    glfwSetErrorCallback(GLFWErrorCallback);
    glDebugMessageCallback(GLDebugCallback, nullptr);

    {
        float positions[16] =
                //coords      //text cords
        { /*0*/-0.5f, -0.5f,   0.0f, 0.0f,
          /*1*/0.5f, -0.5f,    1.0f, 0.0f,
          /*2*/0.5f, 0.5f,     1.0f, 1.0f, 
          /*3*/-0.5f, 0.5f,    0.0f, 1.0f };

        unsigned int indices[] = { 0, 1, 2,
                                   2, 3, 0 };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexArray va = VertexArray();
        //(was 4*2 before texture)
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/Basic.shader");
        shader.bind();
        shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/fish.jpg");
        texture.bind();
        shader.setUniform1i("u_texture", 0);

        va.unbind(); vb.unbind(); ib.unbind(); shader.unbind();
 
        float r = 0.0f;
        float increment = 0.05f;

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            renderer.clear();
            
            shader.bind();
            shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

            renderer.draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}


