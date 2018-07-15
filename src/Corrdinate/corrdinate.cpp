#include<stdio.h>
#include<stdlib.h>

//Include GLEW
#include<GL/glew.h>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

//include GLFW
#include<GLFW/glfw3.h>
GLFWwindow* window;
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<iostream>
//#include<filesystem>

#include"shader.hpp"
float mixValue = 0.2f;
//setting
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT= 600;
int main(void)
{
    if(!glfwInit())
    {
       fprintf(stderr, "Failed to Initial glfw\n");
       getchar();
       return -1;
    }
   
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Triangle", NULL, NULL);
    if(window == NULL)
    {
       fprintf(stderr, "Failed to open GLFW window\n");
       getchar();
       return -1;
    }
    glfwMakeContextCurrent(window);
    
    //Initial GLEW
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
    {
       fprintf(stderr,"Failed initial glew\n");
       getchar();
       glfwTerminate();
       return -1;
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    /*GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);*/
    GLuint programID = LoadShaders("shader.vs", "shader.fs");
    static const GLfloat g_vertex_buffer_data[] = 
    {
       //position            //color         //texure coords
       0.5f,   0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, //top right
       0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //bottom right 
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, //top left
    };
    unsigned int indices[] ={
     0, 1, 3,  //Fist Triangle
     1, 2, 3   //second triangle
    };
    
    unsigned int VBO, VAO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(0*sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    //load and create a texure    
    unsigned int texture1,texture2;
   // unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    //unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels,0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //glGenerateMipMap(GL_TEXTURE_2D);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout<<"failed to load texure"<<std::endl;
    }
    stbi_image_free(data);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //data = stbi_load("container.jpg", &width, &height, &nrChannels,0);
    data = stbi_load("awesomeface.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      std::cout<<"Failed to load texure"<<std::endl;
    }
    stbi_image_free(data);
    glUseProgram(programID);
    glUniform1i(glGetUniformLocation(programID, "texture1"), 0);
    glUniform1i(glGetUniformLocation(programID, "texture2"), 1);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
/*  GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);
*/ 
  do{
       
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            mixValue += 0.001f;
            if(mixValue >= 1.0f)
              mixValue = 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
           mixValue -= 0.001f;
           if( mixValue <=0.0f)
             mixValue = 0.0f;
        }
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
       // glUniform1f(glGetUniformLocation(programID, "mixValue"), mixValue);
        
        //create transformations
        glm::mat4 model;
        model = glm::rotate(model,glm::radians(-55.0f), glm::vec3(1.0f, 0.f, 0.0f));
        glm::mat4 view;
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f),(float)SCR_WIDTH /(float)SCR_HEIGHT, 0.1f, 100.0f);
        glUseProgram(programID);
        unsigned int modelLoc = glGetUniformLocation(programID, "model");        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
     
        unsigned int viewLoc  = glGetUniformLocation(programID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
     
        unsigned int projectionLoc = glGetUniformLocation(programID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glBindVertexArray(VAO);
       // glDrawArrays(GL_TRIANGLES, 0, 3);
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       /* glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
             0,
             3,
             GL_FLOAT,
             GL_FALSE,
             0,
             (void *)0
        );
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);*/
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while(glfwGetKey(window,GLFW_KEY_ESCAPE)!= GLFW_PRESS && glfwWindowShouldClose(window) == 0);
    //Clean VAO
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    /*glDeleteBuffers(1, &Vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);*/
    glDeleteProgram(programID);
    glfwTerminate();
    return 0;
}

