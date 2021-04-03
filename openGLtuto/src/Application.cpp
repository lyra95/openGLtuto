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

#include <random>
#include "Texture.h"

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
            -0.5f, -1.0f, 0.0f, 0.0f,
             0.5f, -1.0f, 1.0f, 0.0f,
             0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA));
        // indices of triangles
        unsigned int indices[] = {
                0,1,2,
                2,3,0
        };

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        IndexBuffer ib(indices, 6);
                
        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);
        
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        //shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
        
        Texture texture("res/img.png");
        texture.Bind(0);
        shader.SetUniformi("u_Texture", 0);

        std::random_device rd;

        // random_device 를 통해 난수 생성 엔진을 초기화 한다.
        std::mt19937 gen(rd());

        // 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
        std::uniform_real_distribution<float> dis(0.0, 1.0);
        // float r = 0.05f;
        //float increment = 0.05f;
        
        Renderer renderer;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            // GLCall(glClear(GL_COLOR_BUFFER_BIT));
            renderer.Clear();

            // draw
           
          
            // shader.SetUniform4f("u_Color", dis(gen), dis(gen), dis(gen), dis(gen));
            

           //GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            renderer.Draw(va,ib,shader);

            //(r > 1.0f) ? r = -0.05f : r += increment;
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