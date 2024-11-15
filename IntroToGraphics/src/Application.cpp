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

        unsigned int indices[] = { 0, 1, 2,                 //start and end points of lines to be drawn, this draws a square.
                                   2, 3, 0 };

        glEnable(GL_BLEND);                                     //enables the use of transparency
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexArray va = VertexArray();                     //creates a new vertex array that stores vertex buffers
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));      //create vertex buffer to store our vertex positions  (was 4*2 before texture)

        VertexBufferLayout layout;   //create a new layout for our vertex buffer
        layout.push<float>(2);      //push two floats as one element in the layout
        layout.push<float>(2);      //do it again

        va.addBuffer(vb, layout);   //add our vertex buffer to our vertex array with the set layout

        IndexBuffer ib(indices, 6);     //make a new index buffer with our indicies and an int representing the indices count

        Shader shader("res/shaders/Basic.shader");
        shader.bind();                                              //create a new shader from a filepath and attach it
        shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/fish.jpg");
        texture.bind();                                                 //create a new texture from a filepath and attach it

        shader.setUniform1i("u_texture", 0);

        va.unbind(); vb.unbind(); ib.unbind(); shader.unbind();                 //unbind our array, buffers, and shader as we are done passing their data.

 
        Renderer renderer;

        float r = 0.0f;                         //used to shift the red color of the texture
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();               //clears the screen    -      alt:glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

            shader.bind();                      //readies the program 
            shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);      //sets the tint of the displayed texture

            renderer.draw(va, ib, shader);                  //runs shaders

            if (r > 1.0f)
                increment = -0.05f;          //reverses the red color value incrementation of the shader
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;            //increments the red color value of the shader

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}


