#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include<glad/glad.h>
#include<glm/vec3.hpp>
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<vector>
#include<cmath>
#include "shaderprogram.hpp"

std::vector<glm::vec3>      vertices;


unsigned int VBO;
unsigned int VAO;


void buildCircle(float radius,int vertexCount)
{
    float angle = 360.0f/vertexCount;

    int triangleCount = vertexCount-2;
    
    std::vector<glm::vec3>   tempVertices;

    for(int i=0;i<vertexCount;i++)
    {
        float newAngle = angle*i;  

        float x= radius*cos(glm::radians(newAngle));

        float y= radius*sin(glm::radians(newAngle));
        
        float z = 0.0f;

        tempVertices.push_back(glm::vec3(x,y,z));

    }


    for(int i=0;i<triangleCount;i++)
    {
        vertices.push_back(tempVertices[0]);
        vertices.push_back(tempVertices[i+1]);
        vertices.push_back(tempVertices[i+2]);
    }

}




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   if (key == GLFW_KEY_ESCAPE)
        glfwTerminate();   
    if(action==GLFW_PRESS)
    {
        if(key==GLFW_KEY_LEFT)  
        {
           
        }
        if(key==GLFW_KEY_RIGHT) 
        {
            
        }    
        if(key==GLFW_KEY_UP)  
        {
            
        }
        if(key==GLFW_KEY_DOWN) 
        {
            
        }                
    
        if(key==GLFW_KEY_SPACE)
        {
        }    
           
    }  
           
}

int main(int argc,char** argv)
{
    if(!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800,800,"İLk Programım",NULL,NULL);

    if(window==NULL)
    {
        std::cout<<"Pencere Olusturulamadi"<<std::endl;

        glfwTerminate();

        return -1;
    }    
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 


    buildCircle(1,4);

    ShaderProgram program;

    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    program.addUniform("uMove");
    program.addUniform("uColor");

   
    glGenVertexArrays(1, &VAO); 

    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    //dairenin vertex bilgileri vertex buffer a koplayanıyor
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    
    glEnableVertexAttribArray(0); 
    
    
   
    while(!glfwWindowShouldClose(window))
    {
        //oluşturulacak resim başlangıç rengine boyanıyor
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //çizimde kullanılacak olan program nesnesi aktif ediliyor
        program.use();
  
        //çizimde kullanılacak olan Vertex array object aktif ediliyor
        glBindVertexArray(VAO);
        //çizim komutu gönderiliyor
         ///1.Kare
        program.setVec3("uMove",glm::vec3(0.0f,0.0f,0.0f));
        program.setVec4("uColor",glm::vec4(1.0f,0.0f,0.0f,1.0f));
       
        glDrawArrays(GL_TRIANGLES, 0,vertices.size());

        std::this_thread::sleep_for (std::chrono::milliseconds(70));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

}