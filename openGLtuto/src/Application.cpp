#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

int main(void)
{   
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    {
        GLFWwindow* window;

        

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);


        // Initialize glew. print ERROR if it fails
        if (glewInit() != GLEW_OK)
            std::cout << "ERROR" << std::endl;
        
        // print openGL version
        std::cout << glGetString(GL_VERSION) << std::endl;


        glfwSwapInterval(10);


        // triangle positions
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f, 0.5f,
            -0.5f, 0.5f
        };

        // indices of triangles
        unsigned int indices[] = {
                0,1,2,
                2,3,0
        };

        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        IndexBuffer ib(indices, 6);

        //GLCall(glEnableVertexAttribArray(0));
        //GLCall(glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,8,0));

        
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        
        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));

            // draw
           
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            
            //GLCall(glBindVertexArray(0));
            va.Bind();
            ib.Bind();

           GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            (r > 1.0f) ? r = -0.05f : r += increment;
            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

        shader.Unbind();
    }
    glfwTerminate();
    return 0;
}