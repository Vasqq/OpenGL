// Liam Pereira
// 40111656
// Quiz 1 COMP 371
// This quiz was done with the help of OpenGL.com and Victor Gordon's crash course on OpenGL
// https://learnopengl.com/Introduction
// https://www.youtube.com/watch?v=45MIykWJ-C4&t=4221s&ab_channel=freeCodeCamp.org



#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "time.h"
#include "Texture.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

// Constants for screen and viewport size

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

void drawWorld(Shader shaderProgram, GLuint colorLoc, GLuint worldMatrixLoc)
{

    // Draw axis

    glm::mat4 axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 0.1f, 0.1f));
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &axisMatrix[0][0]);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.0f, 0.0f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 5.0f, 0.1f));
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &axisMatrix[0][0]);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 5.0f));
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &axisMatrix[0][0]);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 1.0f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw skybox

    //glm::mat4 skyBoxMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) 
    //    * glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 100.0f));
    //shaderProgram.setMat4("model", skyBoxMatrix);
    //glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.4f, 0.5f, 0.95f)));
    //glDrawArrays(GL_TRIANGLES, 0, 36);

    // Draw ground

    for (float i = -50.0f; i <= 50.0f; i++)
    {
        glm::mat4 floorWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, i)) * glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 0.02f, 0.02f));
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floorWorldMatrix[0][0]);
        glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.53f, 0.81f, 0.92f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    for (float i = -50.0f; i <= 50.0f; i++)
    {
        glm::mat4 floorWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.02f, 0.02f, 100.0f));
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floorWorldMatrix[0][0]);
        glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.53f, 0.81f, 0.92f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}

void drawSnowman(Shader shaderProgram,GLuint colorLoc, glm::vec3 position, glm::vec3 scale, glm::mat4 rotation)
{

    // Main cube
    //-------------------------------------------------------------------------------------------------

    glm::mat4 mainBodyMatrix = glm::mat4(1.0f);
    mainBodyMatrix = glm::translate(mainBodyMatrix, position) * rotation;
    mainBodyMatrix = glm::scale(mainBodyMatrix, scale);
    shaderProgram.setMat4("model", mainBodyMatrix);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Torso

    glm::mat4 middleBody = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.85f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.8f, 0.8f, 0.8f));
    shaderProgram.setMat4("model", middleBody);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    // Head

    glm::mat4 head = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 1.5f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.6f, 0.6f, 0.6f));
    shaderProgram.setMat4("model", head);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Arms

    glm::mat4 arms = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(3.0f, 0.2f, 0.2f));
    shaderProgram.setMat4("model", arms);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Legs

    glm::mat4 legs = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.20f, -0.5f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.3f, 1.0f, 0.2f));
    shaderProgram.setMat4("model", legs);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    legs = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.20f, -0.5f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.3f, 1.0f, 0.2f));
    shaderProgram.setMat4("model", legs);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Nose

    glm::mat4 nose = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 1.55f, 0.35f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.5f)));
    shaderProgram.setMat4("model", nose);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Eyes

    glm::mat4 eyes = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.17f, 1.65f, 0.28f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
    shaderProgram.setMat4("model", eyes);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    eyes = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.17f, 1.65f, 0.28f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.1f, 0.1f, 0.1f));
    shaderProgram.setMat4("model", eyes);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // Mouth
    glm::mat4 mouth = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 1.40f, 0.28f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.3f, 0.07f, 0.07f));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
    shaderProgram.setMat4("model", mouth);
    glDrawArrays(GL_TRIANGLES, 0, 36);



    // Hair
    //----------------


    glm::mat4 hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.02f, 2.0f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.5f, 0.0f, 0.2f)));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 2.0f, 0.2f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.05f, 2.0f, -0.2f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.24f, 2.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), (float)(60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.17f, 2.0f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), (float)(60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.18f, 2.0f, -0.2f))
        * glm::rotate(glm::mat4(1.0f), (float)(60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.21f, 2.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), (float)(-60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.23f, 2.0f, 0.2f))
        * glm::rotate(glm::mat4(1.0f), (float)(-60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hair = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.18f, 2.0f, -0.2f))
        * glm::rotate(glm::mat4(1.0f), (float)(-60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.02f, 0.6f, 0.02f));
    shaderProgram.setMat4("model", hair);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Hands
    // ----------------------------------------

    glm::mat4 hand = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(1.5f, 1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.3f, 0.3f, 0.3f));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f,1.0f, 1.0f)));
    shaderProgram.setMat4("model", hand);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    hand = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-1.5f, 1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.3f, 0.3f, 0.3f));
    shaderProgram.setMat4("model", hand);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // Fingers
    // -----------------------------------------

    glm::mat4 fingers = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(1.8f, 1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.03f, 0.03f));
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.58f, 0.29f, 0.0f)));
    shaderProgram.setMat4("model", fingers);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    fingers = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(1.8f, 0.87f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), (float)(-60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.03f, 0.03f));
    shaderProgram.setMat4("model", fingers);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    fingers = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(1.8f, 1.13f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), (float)(60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.03f, 0.03f));
    shaderProgram.setMat4("model", fingers);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    fingers = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-1.8f, 1.0f, 0.0f))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.03f, 0.03f));
    shaderProgram.setMat4("model", fingers);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    fingers = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-1.8f, 0.87f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), (float)(60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.03f, 0.03f));
    shaderProgram.setMat4("model", fingers);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    fingers = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-1.8f, 1.13f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), (float)(-60), glm::vec3(0.0, 0.0, 1.0))
        * glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.03f, 0.03f));
    shaderProgram.setMat4("model", fingers);
    glDrawArrays(GL_TRIANGLES, 0, 36);


}


void drawLetterP(GLFWwindow* window, Shader shaderProgram, GLuint colorLoc, glm::vec3 position)
{

    // LETTER P

    // Place letter on skateboard
    position = position + glm::vec3(0.0f, 2.0f, 0.0f);

    glm::mat4 rotMatrix = glm::mat4(1.0f);


    // Select letter P by pressing 1

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        // Rotate letter counter-clockwise

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        {

            rotMatrix = rotMatrix * glm::rotate(glm::mat4(1.0f), (float)(glfwGetTime()), glm::vec3(0.0, 1.0, 0.0));

        }

          // Rotate letter clockwise

        if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        {

            rotMatrix = rotMatrix * glm::rotate(glm::mat4(1.0f), (float)(-glfwGetTime()), glm::vec3(0.0, 1.0, 0.0));

        }
    }
    

    // Create 1st part of letter
    glm::mat4 mainBodyMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position))
        * rotMatrix
        * glm::scale(glm::mat4(1.0f), glm::vec3(0.4, 4.0, 0.1));
    shaderProgram.setMat4("model", mainBodyMatrix);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.25f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Create 2nd part of later
    glm::mat4 line = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.5f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(6.0, 0.1, 1.0));
    shaderProgram.setMat4("model", line);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.25f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Create 3rd part of later
   line = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.25f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 0.5, 1.0));
    shaderProgram.setMat4("model", line);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.25f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Create 4th part of letter
    line = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.5f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(6.0, 0.1, 1.0));
    shaderProgram.setMat4("model", line);
    glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.25f)));
    glDrawArrays(GL_TRIANGLES, 0, 36);

    


}

glm::vec3 getRandomPosition()
{
    GLfloat x,y,z;
    y = 3.0f;
    srand(time(0));

    x = (rand() % (50 - (-50) + 1)) - 50;
    z = (rand() % (50 - (-50) + 1)) - 50;

        return glm::vec3(x, y, z);
}

   


    // set up vertex data and configure vertex attributes
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


// world positions of the skateboards

glm::vec3 position = glm::vec3(0.0f, 3.0f, -3.0f);
glm::vec3 scale = glm::vec3(3.0, 3.0, 3.0);
glm::mat4 rotation = glm::mat4(1.0f);

glm::vec3 positionInitial = position;
glm::vec3 scaleInitial = scale;
glm::mat4 rotationInitial = rotation;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

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
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));


    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();

    // Set depth test for 3d objects in the world
    glEnable(GL_DEPTH_TEST);

    // Initialize the camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    // Initialize and define view and projection matrices
    glm::mat4 view = glm::mat4(1.0f); 
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));

    // Get address for the unifroms from the shader
    GLuint colorLoc = glGetUniformLocation(shaderProgram.ID, "color");
    GLuint worldMatrixLoc = glGetUniformLocation(shaderProgram.ID, "model");


    // Main while loop
    //Rendering commands here...
    // ------------------------------------------------------------------


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        //Handles camera inputs to move around
        camera.Inputs(window);

        // Set projection and view matrix
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        drawWorld(shaderProgram, colorLoc, worldMatrixLoc);

        // Draw main body cube
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position = getRandomPosition();

        }

        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        {
            scale *= glm::vec3(1.01f);

        }

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        {
            scale *= glm::vec3(0.99f);

        }
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));

        }
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        {
            rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(-5.0f), glm::vec3(0.0, 1.0, 0.0));

        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                position += glm::vec3(-0.5f, 0.0f, 0.0f);

            }

            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                position += glm::vec3(0.5f, 0.0f, 0.0f);

            }

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                position += glm::vec3(0.0f, 0.0f, 0.5f);

            }

            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                position += glm::vec3(0.0f, 0.0f, -0.5f);

            }

        }

        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        {
            position = positionInitial;
            rotation = rotationInitial;
            scale = scaleInitial;

        }
        

    
        drawSnowman(shaderProgram, colorLoc, position, scale, rotation);


        // Updates and exports the camera matrix to the vertex shader
        VAO1.Bind();

        //glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Check and call events and swap buffers.
        glfwPollEvents();
    }


    // Clean up memory

    VAO1.Delete();
    VBO1.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}