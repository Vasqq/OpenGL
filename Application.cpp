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

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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
  
    // Draw ground
    // Z - axis

    for (float i = -50.0f; i <= 50.0f; i++)
    {
        glm::mat4 floorWorldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, i)) * glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 0.02f, 0.02f));
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floorWorldMatrix[0][0]);
        glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(0.53f, 0.81f, 0.92f)));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // X - axis

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

    // Identity matrix
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
    /*-0.5f, -0.5f, -0.5f,  0.583f,  0.771f,  0.014f,
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
    -0.5f,  0.5f, -0.5f,  0.583f,  0.771f,  0.014f*/

        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f

};


// Initial world position, scale and rotation of snowman

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
    //---------------------------------------------------
    // Position attrib
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    // Texture attrib
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));


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

    // Texture
    Texture popCat("snow.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex0", 0);


    // Main while loop
    //Rendering commands here...
    // ------------------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        


        shaderProgram.Activate();

        //popCat.Bind();


        //Handles camera inputs to move around
        camera.Inputs(window);

        // Set projection and view matrix
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");



        // Set up the world to draw the snowman

        drawWorld(shaderProgram, colorLoc, worldMatrixLoc);

        // Reposition snowman randomly in the world

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            position = getRandomPosition();

        }

        // Scale up the snowman

        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        {
            scale *= glm::vec3(1.01f);

        }

        // Scale down the snowman

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        {
            scale *= glm::vec3(0.99f);

        }

        // Rotate snowman clockwise

        if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        {
            rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(5.0f), glm::vec3(0.0, 1.0, 0.0));

        }

        // Rotate snowman counter-clockwise


        if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        {
            rotation *= glm::rotate(glm::mat4(1.0f), glm::radians(-25.0f), glm::vec3(0.0, 1.0, 0.0));

        }


        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {
       
            // Move snowman left

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                position += glm::vec3(-0.5f, 0.0f, 0.0f);

            }

            // Move snowman right


            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                position += glm::vec3(0.5f, 0.0f, 0.0f);

            }

            // Move snowman forward


            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                position += glm::vec3(0.0f, 0.0f, 0.5f);

            }

            // Move snowman back


            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                position += glm::vec3(0.0f, 0.0f, -0.5f);

            }

        }

        // Reset snowman to initial position

        if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
        {
            position = positionInitial;
            rotation = rotationInitial;
            scale = scaleInitial;

        }

        // Set rendering mode to lines

        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        }


        // Set rendering mode to points

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

        }

        // Set rendering mode to triangles

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        }
        
        // Draw snowman based on position, scale and rotation
        
        drawSnowman(shaderProgram, colorLoc, position, scale, rotation);

       // glm::mat4 mainBodyMatrix = glm::mat4(1.0f);
       // mainBodyMatrix = glm::translate(mainBodyMatrix, position) * rotation;
       // mainBodyMatrix = glm::scale(mainBodyMatrix, scale);
       // shaderProgram.setMat4("model", mainBodyMatrix);
       //// glUniform3fv(colorLoc, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
       // glDrawArrays(GL_TRIANGLES, 0, 36);


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

//// Vertices coordinates
// Vertices coordinates
//GLfloat vertices[] =
//{ //     COORDINATES      TexCoord  //
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//};
//
//// Indices for vertices order
//GLuint indices[] =
//{
//	0, 2, 1, // Upper triangle
//	0, 3, 2 // Lower triangle
//};
//
//
//
//int main()
//{
//	// Initialize GLFW
//	glfwInit();
//
//	// Tell GLFW what version of OpenGL we are using 
//	// In this case we are using OpenGL 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// Tell GLFW we are using the CORE profile
//	// So that means we only have the modern functions
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
//	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
//	// Error check if the window fails to create
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	// Introduce the window into the current context
//	glfwMakeContextCurrent(window);
//
//	//Load GLAD so it configures OpenGL
//	gladLoadGL();
//	// Specify the viewport of OpenGL in the Window
//	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
//	glViewport(0, 0, 800, 800);
//
//
//
//	// Generates Shader object using shaders default.vert and default.frag
//	Shader shaderProgram("default.vert", "default.frag");
//
//
//
//	// Generates Vertex Array Object and binds it
//	VAO VAO1;
//	VAO1.Bind();
//
//	// Generates Vertex Buffer Object and links it to vertices
//	VBO VBO1(vertices, sizeof(vertices));
//	// Generates Element Buffer Object and links it to indices
//	EBO EBO1(indices, sizeof(indices));
//
//	// Links VBO attributes such as coordinates and colors to VAO
//	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
//	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	// Unbind all to prevent accidentally modifying them
//	VAO1.Unbind();
//	VBO1.Unbind();
//	EBO1.Unbind();
//
//	// Gets ID of uniform called "scale"
//	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
//
//
//	// Original code from the tutorial
//	Texture popCat("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
//	popCat.texUnit(shaderProgram, "tex0", 0);
//
//	Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
//
//	// Main while loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// Specify the color of the background
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
//		// Clean the back buffer and assign the new color to it
//		glClear(GL_COLOR_BUFFER_BIT);
//		// Tell OpenGL which Shader Program we want to use
//		shaderProgram.Activate();
//
//		camera.Inputs(window);
//		// Updates and exports the camera matrix to the Vertex Shader
//		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
//		// Binds texture so that is appears in rendering
//		popCat.Bind();
//		// Bind the VAO so OpenGL knows to use it
//		VAO1.Bind();
//		// Draw primitives, number of indices, datatype of indices, index of indices
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		// Swap the back buffer with the front buffer
//		glfwSwapBuffers(window);
//		// Take care of all GLFW events
//		glfwPollEvents();
//	}
//
//
//
//	// Delete all the objects we've created
//	VAO1.Delete();
//	VBO1.Delete();
//	EBO1.Delete();
//	popCat.Delete();
//	shaderProgram.Delete();
//	// Delete window before ending the program
//	glfwDestroyWindow(window);
//	// Terminate GLFW before ending the program
//	glfwTerminate();
//	return 0;
//}