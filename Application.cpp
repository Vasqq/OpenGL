// Liam Pereira
// 40111656
// Assignment 1 COMP 371
// Completed with the help of learnOpenGL.com :)



#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,

    -0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,

    -0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,

     0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,

    -0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,

    -0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
     0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f,  0.5f,  0.5f,  0.583f,  0.771f,  0.014f,
    -0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f
};

// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.75f,  0.0f),
    glm::vec3(0.0f,  0.75f, 0.0f),
    glm::vec3(0.0f,  0.75f, 0.0f),
    glm::vec3(0.0f,  -1.0f,  0.0f),
    glm::vec3(-2.0f,  -5.0f,  0.0f)

};



int main()
{
    // glfw: initialize and configures
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_WIDTH, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, SCR_HEIGHT, SCR_WIDTH);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, sizeof(vertices));

    // Links VBO attributes such as coordinates and colors to VAO
    
    // Position attrib
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // Color attrib
    //VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Texture attrib
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));


    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();


    glEnable(GL_DEPTH_TEST);

    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        
        //Rendering commands here...
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();
        //Handles camera inputs

        camera.Inputs(window);

        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");



        //// Draw ground
        //glm::mat4 groundWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.01f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1000.0f, 0.02f, 1000.0f));
        //GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram.ID, "model");
        //glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &groundWorldMatrix[0][0]);

        //glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices, starting at index 0

        GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram.ID, "model");

        for (float i = -50.0f; i <= 50.0f; i++)
        {
            glm::mat4 floorWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, i)) * glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 0.02f, 0.02f));
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &floorWorldMatrix[0][0]);
            glUniform3fv(worldMatrixLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        for (float i = -50.0f; i <= 50.0f; i++)
        {
            glm::mat4 floorWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.02f, 0.02f, 100.0f));
            glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &floorWorldMatrix[0][0]);
            glUniform3fv(worldMatrixLocation, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.0f)));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        glm::mat4 model = glm::mat4(1.0f);


        model = glm::translate(model, cubePositions[0]);
        model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
        shaderProgram.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        model = glm::translate(model, cubePositions[1]);
        model = glm::scale(model, glm::vec3(0.75, 0.75, 0.75));
        shaderProgram.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

       
        model = glm::translate(model, cubePositions[2]);
        model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
        shaderProgram.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::translate(model, cubePositions[3]);
        model = glm::scale(model, glm::vec3(6.0, 0.25, 0.25));
        shaderProgram.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::translate(glm::mat4(1.0f), cubePositions[4]);
        model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 1.0));
        shaderProgram.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::translate(glm::mat4(1.0f), cubePositions[4]);
        model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 1.0));
        shaderProgram.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

       

        // Updates and exports the camera matrix to the vertex shader
        VAO1.Bind();

        //glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Check and call events and swap buffers.
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}