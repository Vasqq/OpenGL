// Liam Pereira
// 40111656
// Quiz 1 COMP 371
// This quiz was done with the help of OpenGL.com and Victor Gordon's crash course on OpenGL
// https://learnopengl.com/Introduction
// https://www.youtube.com/watch?v=45MIykWJ-C4&t=4221s&ab_channel=freeCodeCamp.org


#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <string>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Sound.h"
#include"SoundManager.h"


using namespace glm;

const unsigned int width = 2048;
const unsigned int height = 1080;

using namespace std;

struct Vertex
{
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 uv;
};

void drawWorld(Shader shaderProgram, GLuint colorLoc, GLuint worldMatrixLoc, Texture tex)
{
    // Draw floor
    glm::mat4 floor = glm::mat4(1.0f);
    glm::vec3 floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
    floor = glm::translate(floor, floorPos) * glm::scale(glm::mat4(1.0), glm::vec3(100.0f, 0.01f, 100.0f));;
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floor[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // Draw axis

    glm::mat4 axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 0.1f, 0.1f));
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &axisMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 5.0f, 0.1f));
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &axisMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 5.0f));
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &axisMatrix[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void drawMuseum(Shader shaderProgram, GLuint colorLoc, GLuint worldMatrixLoc, Texture tex)
{
    // Draw floor
    glm::mat4 floor = glm::mat4(1.0f);
    glm::vec3 floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
    floor = glm::translate(floor, floorPos) * glm::scale(glm::mat4(1.0), glm::vec3(100.0f, 0.01f, 100.0f));;
    glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floor[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);



}

Vertex cubeVertexArr[] = {
    {vec3(-0.5, -0.5, -0.5), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)}, // left - red
    {vec3(-0.5, -0.5, 0.5), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 1.0f)},
    {vec3(-0.5, 0.5, 0.5), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},

    {vec3(-0.5, -0.5, -0.5), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(0.0f, 0.0f)},
    {vec3(-0.5, 0.5, 0.5), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 1.0f)},
    {vec3(-0.5, 0.5, -0.5), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec2(1.0f, 0.0f)},

    {vec3(0.5, 0.5, -0.5), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)}, // far - blue
    {vec3(-0.5, -0.5, -0.5), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
    {vec3(-0.5, 0.5, -0.5), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

    {vec3(0.5, 0.5, -0.5), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
    {vec3(0.5, -0.5, -0.5), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},
    {vec3(-0.5, -0.5, -0.5), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},

    {vec3(0.5, -0.5, 0.5), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)}, // bottom - turquoise
    {vec3(-0.5, -0.5, -0.5), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)},
    {vec3(0.5, -0.5, -0.5), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 0.0f)},

    {vec3(0.5, -0.5, 0.5), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)},
    {vec3(-0.5, -0.5, 0.5), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)},
    {vec3(-0.5, -0.5, -0.5), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 1.0f), vec2(0.0f, 0.0f)},

    {vec3(-0.5, 0.5, 0.5), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)}, // near - green
    {vec3(-0.5, -0.5, 0.5), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
    {vec3(0.5, -0.5, 0.5), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},

    {vec3(0.5, 0.5, 0.5), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
    {vec3(-0.5, 0.5, 0.5), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)},
    {vec3(0.5, -0.5, 0.5), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},

    {vec3(0.5, 0.5, 0.5), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)}, // right - purple
    {vec3(0.5, -0.5, -0.5), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
    {vec3(0.5, 0.5, -0.5), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 0.0f)},

    {vec3(0.5, -0.5, -0.5), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 0.0f)},
    {vec3(0.5, 0.5, 0.5), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), vec2(1.0f, 1.0f)},
    {vec3(0.5, -0.5, 0.5), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 1.0f), vec2(0.0f, 1.0f)},

    {vec3(0.5, 0.5, 0.5), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)}, // top - yellow
    {vec3(0.5, 0.5, -0.5), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)},
    {vec3(-0.5, 0.5, -0.5), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},

    {vec3(0.5, 0.5, 0.5), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)},
    {vec3(-0.5, 0.5, -0.5), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)},
    {vec3(-0.5, 0.5, 0.5), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)} 
};

GLfloat blockVertices[] = {
    // positions          // normals           // texture coords
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};




int createCubeVAO(vec3 modelColor)
{
 /*   for (int i = 0; i < (sizeof(cubeVertexArr) / sizeof(cubeVertexArr[0])); i++)
    {
        cubeVertexArr[i].color = modelColor;
    };*/
    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexArr), cubeVertexArr, GL_STATIC_DRAW);

    glVertexAttribPointer(0,              // attribute 0 matches aPos in Vertex Shader
        3,              // size
        GL_FLOAT,       // type
        GL_FALSE,       // normalized?
        sizeof(Vertex), // stride - each vertex contain 2 vec3 (position, color)
        (void*)0);      // array buffer offset
   
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(sizeof(vec3)));
    glEnableVertexAttribArray(1);

     //color
    glVertexAttribPointer(2,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(2 * sizeof(vec3)));
    glEnableVertexAttribArray(2);

    // texture
    glVertexAttribPointer(3,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)(3 * sizeof(vec3)));; // uv is offseted by 2 vec3 (comes after position and color)
    
    glEnableVertexAttribArray(3);


    //// Generates Vertex Array Object and binds it
    //VAO vertexArrayObject;
    //vertexArrayObject.Bind();
    //// Generates Vertex Buffer Object and links it to vertices
    //VBO vertexBufferObject(blockVertices, sizeof(blockVertices));
    //// Links VBO attributes such as coordinates and colors to VAO
    //// Position
    //vertexArrayObject.LinkAttrib(vertexBufferObject, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    //// Normals
    //vertexArrayObject.LinkAttrib(vertexBufferObject, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    //// Textures
    //vertexArrayObject.LinkAttrib(vertexBufferObject, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    //// Unbind all to prevent accidentally modifying them
    //vertexArrayObject.Unbind();


    return vertexBufferObject;
}

void setWorldMatrix(Shader shader, mat4 worldMatrix)
{
    shader.Activate();
    GLuint worldMatrixLocation = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
}
void renderLegoCube(Shader shader, vec3 color, mat4 worldMatrix)
{
    int legoVAO = createCubeVAO(color);
    glBindVertexArray(legoVAO);
    setWorldMatrix(shader, worldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderA(Shader shader, vec3 renderColor, vec3 roomOrigin)
{
    for (int i = 0; i < 6; i++)
    {
        mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, 2.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);

        cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, -2.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);
    }
    mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, 1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, -1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, 1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, -1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, 0) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, 0) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);
}

void renderY(Shader shader, vec3 renderColor, vec3 roomOrigin)
{
    for (int i = 0; i < 4; i++)
    {
        mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, 0.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);
    }
    for (int i = 0; i < 3; i++)
    {
        mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f + (float)i, -1.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);

        cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f + (float)i, 1.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);
    }
}

void renderR(Shader shader, vec3 renderColor, vec3 roomOrigin)
{
    for (int i = 0; i < 6; i++)
    {
        mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, 2.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);
    }
    mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, 1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, -1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, 0) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 7.5f, -2.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, 1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, -1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, 0) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, -2.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 6.5f, -2.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 4.5f, 1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 3.75f, 0) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 3.25f, -1.0) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f, -2.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);
}

void renderN(Shader shader, vec3 renderColor, vec3 roomOrigin)
{
    for (int i = 0; i < 6; i++)
    {
        mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, 2.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);

        cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, -2.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);
    }

    mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 6.5f, 1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 3.5f, -1.0f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);

    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 4.5f, -0.25f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);
    cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 5.5f, 0.25f) + roomOrigin);
    renderLegoCube(shader, renderColor, cubeWorldMatrix);
}

void renderEmpty(Shader shader, vec3 renderColor, vec3 roomOrigin)
{
    for (int i = 0; i < 6; i++)
    {
        mat4 cubeWorldMatrix = translate(mat4(1.0f), vec3(0.0f, 2.5f + (float)i, 0.0f) + roomOrigin);
        renderLegoCube(shader, renderColor, cubeWorldMatrix);
    }
}

void drawPodium(Shader shader, vec3 renderColor, vec3 roomOrigin)
{
    int cubeAO = createCubeVAO(vec3(0.5f, 0.5f, 0.5f));
    glBindVertexArray(cubeAO);
    mat4 cubeWorldMatrix = translate(mat4(1.0f), roomOrigin) * scale(mat4(1.0f), vec3(6.0f, 3.0f, 6.0f));
    setWorldMatrix(shader, cubeWorldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    cubeWorldMatrix = translate(mat4(1.0f), roomOrigin) * scale(mat4(1.0f), vec3(5.0f, 4.0f, 5.0f));
    setWorldMatrix(shader, cubeWorldMatrix);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES      /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f,		    0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 10.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		10.0f, 10.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		10.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

GLfloat cubeVertices[] = {
    // positions          // normals           // texture coords
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  20.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  20.0f, 20.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  20.0f, 20.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 20.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   20.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   20.0f, 20.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   20.0f, 20.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 20.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  20.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  20.0f, 20.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 20.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 20.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  20.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  20.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  20.0f, 20.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 20.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 20.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  20.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 20.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  20.0f, 20.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  20.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  20.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 20.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 20.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  20.0f, 20.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  20.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  20.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 20.0f
};

//GLfloat blockVertices[] = {
//    // positions          // normals           // texture coords
//       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//};

GLfloat pyVertices[] =
{ //     COORDINATES     /    /    TexCoord   /        NORMALS       //
    -0.5f, 0.0f,  0.5f,      	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
    -0.5f, 0.0f, -0.5f,    	     0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f, -0.5f,     	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
     0.5f, 0.0f,  0.5f,     	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

    -0.5f, 0.0f,  0.5f,     	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
    -0.5f, 0.0f, -0.5f,     	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
     0.0f, 0.8f,  0.0f,     	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

    -0.5f, 0.0f, -0.5f,     	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
     0.5f, 0.0f, -0.5f,     	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
     0.0f, 0.8f,  0.0f,     	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

     0.5f, 0.0f, -0.5f,          0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
     0.5f, 0.0f,  0.5f,          5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
     0.0f, 0.8f,  0.0f,          2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

     0.5f, 0.0f,  0.5f,          5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
    -0.5f, 0.0f,  0.5f,          0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
     0.0f, 0.8f,  0.0f,    	     2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint pyIndices[] =
{
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};


int main()

{
    SoundManager soundManager;
    soundManager.Initialize();
    soundManager.LoadSound();

    // Initial world position, scale and rotation of snowman
    glm::vec3 redCubePos = vec3(10.5f, 0.5f, -14.5f);
    glm::vec3 blueCubePos = vec3(13.5f, 0.5f, -10.5f);
    glm::vec3 greenCubePos = vec3(16.5f, 0.5f, -7.5f);
    glm::vec3 trophieCubePos = vec3(23.5f, -2.5f, -10.5f);


    glm::vec3 redPlatePos = vec3(13.5f, 0.0f, -14.5f);
    glm::vec3 bluePlatePos = vec3(17.5f, 0.0f, -10.5f);
    glm::vec3 greenPlatePos = vec3(11.5f, 0.0f, -6.5f);


    glm::vec3 redPlatePosInitial = redPlatePos;
    glm::vec3 bluePlatePosInitial = bluePlatePos;
    glm::vec3 greenPlatePosInitial = greenPlatePos;

    glm::vec3 position = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0, 0.3, 1.0);
    glm::mat4 rotation = glm::mat4(1.0f);

    glm::vec3 positionInitial = position;
    glm::vec3 scaleInitial = scale;
    glm::mat4 rotationInitial = rotation;

    bool redPlateOn = false;
    bool bluePlateOn = false;
    bool greenPlateOn = false;

    string letterState = "empty";
    int textureState = 1;
    vec3 roomOrigin = vec3(-18.5f, 0.5f, -10.5f);
    vec3 renderColor = vec3(0.0f, 0.0f, 0.0f);

    mat4 rotationMat = mat4(1.0f);
    mat4 lightBox = mat4(1.0f);


	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
    Shader colorShader("color.vert", "color.frag");

	// Generates Vertex Array Object and binds it
	VAO cubeVAO;
	cubeVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO cubeVBO(cubeVertices, sizeof(cubeVertices));
	// Generates Element Buffer Object and links it to indices
	//EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	// 
	// Co ords
    cubeVAO.LinkAttrib(cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// Colors
	//VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	// Textures
    cubeVAO.LinkAttrib(cubeVBO, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Normals
    cubeVAO.LinkAttrib(cubeVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
    cubeVAO.Unbind();
    cubeVBO.Unbind();


    // Generates Vertex Array Object and binds it
    VAO cubeSpaceRoomVAO;
    cubeSpaceRoomVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO cubeSpaceRoomVBO(blockVertices, sizeof(blockVertices));
    // Generates Element Buffer Object and links it to indices
    //EBO EBO1(indices, sizeof(indices));
    // Links VBO attributes such as coordinates and colors to VAO
    // 
    // Co ords
    cubeSpaceRoomVAO.LinkAttrib(cubeSpaceRoomVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // Colors
    //VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    // Textures
    cubeSpaceRoomVAO.LinkAttrib(cubeSpaceRoomVBO, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    // Normals
    cubeSpaceRoomVAO.LinkAttrib(cubeSpaceRoomVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    cubeSpaceRoomVAO.Unbind();
    



    // MUSEUM FLOOR VERTICES
    // -----------------------------------------------------------------------------------------------------

    VAO VAOmuseumFloor;
    VAOmuseumFloor.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO VBOmuseumFloor(vertices, sizeof(vertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBOmuseumFloor(indices, sizeof(indices));
    // Links VBO attributes such as coordinates and colors to VAO
    // Position
    VAOmuseumFloor.LinkAttrib(VBOmuseumFloor, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // Texture
    VAOmuseumFloor.LinkAttrib(VBOmuseumFloor, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Normals
    VAOmuseumFloor.LinkAttrib(VBOmuseumFloor, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAOmuseumFloor.Unbind();
    VBOmuseumFloor.Unbind();
    EBOmuseumFloor.Unbind();

    VAO pyVAO;
    pyVAO.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO pyVBO(pyVertices, sizeof(pyVertices));
    // Generates Element Buffer Object and links it to indices
    EBO pyEBO(pyIndices, sizeof(pyIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    // Positions
    pyVAO.LinkAttrib(pyVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // Tex co-ords
    pyVAO.LinkAttrib(pyVBO, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Normals
    pyVAO.LinkAttrib(pyVBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    pyVAO.Unbind();
    pyVBO.Unbind();
    pyEBO.Unbind();





	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(cubeVertices, sizeof(cubeVertices));
	// Generates Element Buffer Object and links it to indices
	//EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	//lightEBO.Unbind();



    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(15.0f, 1.0f, 10.0f);
    glm::vec3 lightPos2 = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 lightPos3 = glm::vec3(5.0f, 0.0f, 0.0f); // red cube
    glm::vec3 lightPos4 = glm::vec3(-5.0f, 0.0f, 0.0f); // green cube
    glm::vec3 lightPos5 = glm::vec3(0.0f, 0.0f, 5.0f); // blue cube



    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = translate(lightModel, lightPos) * rotationMat;
    //lightModel = glm::translate(lightModel, lightPos) * glm::scale(glm::mat4(1.0), glm::vec3(10.0f));

    //mat4 lightModel2 = lightModel * translate(mat4(1.0f), lightPos2) * rotationMat* glm::scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));



    // Setup lighting for shaders

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Initialize textures

    Texture snowTex("snow.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    snowTex.texUnit(shaderProgram, "tex4", 0);
    Texture skyTex("sky.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    skyTex.texUnit(shaderProgram, "tex4", 0);
    
    Texture containerTex("container.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    containerTex.texUnit(shaderProgram, "tex0", 0);
    Texture planksTex("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    planksTex.texUnit(shaderProgram, "tex0", 0);
    Texture planksSpec("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    planksSpec.texUnit(shaderProgram, "tex1", 1);

    Texture grassTex("grass.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    grassTex.texUnit(shaderProgram, "tex3", 0);

    Texture goldTex("gold.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    goldTex.texUnit(shaderProgram, "tex2", 1);
    Texture diamondTex("diamond.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    diamondTex.texUnit(shaderProgram, "tex3", 1);
    Texture obsidianTex("obsidian.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    obsidianTex.texUnit(shaderProgram, "tex3", 1);

    Texture trophyTex("trophy.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    trophyTex.texUnit(shaderProgram, "tex4", 0);


    Texture brick("stoneArt.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    brick.texUnit(shaderProgram, "tex4", 0);
    Texture popCat("pop_cat.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "tex1", 0);
    Texture concrete("concrete.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    concrete.texUnit(shaderProgram, "tex3", 0);
    Texture legoYellowTex("legoYellow.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    legoYellowTex.texUnit(shaderProgram, "tex0", 0);
    Texture legoBlueTex("legoBlueTex.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    legoBlueTex.texUnit(shaderProgram, "tex0", 0);
    Texture legoRedTex("legoRed.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    legoYellowTex.texUnit(shaderProgram, "tex0", 0);
    Texture legoGreenTex("legoGreen.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    legoBlueTex.texUnit(shaderProgram, "tex0", 0);

    Texture guitarTex("guitar.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    guitarTex.texUnit(shaderProgram, "tex0", 0);
    Texture harpTex("harp.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    harpTex.texUnit(shaderProgram, "tex0", 0);
    Texture pianoTex("piano.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    pianoTex.texUnit(shaderProgram, "tex0", 0);
    Texture saxTex("sax.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    saxTex.texUnit(shaderProgram, "tex0", 0);
    Texture musicTex("music.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    musicTex.texUnit(shaderProgram, "tex0", 0);




    // Get addresses of uniforms
    GLuint colorLoc = glGetUniformLocation(shaderProgram.ID, "lightColor");
    GLuint worldMatrixLoc = glGetUniformLocation(shaderProgram.ID, "model");

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 1.0f, 2.0f));
    //float rotationVal = 0.0f;
    double previousTime = glfwGetTime();

	// Main while loope
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double crntTime = glfwGetTime();
        if (crntTime - previousTime >= 1 / 60) {
            rotationMat *= rotate(glm::mat4(1.0f), glm::radians(0.01f), glm::vec3(0.0, 1.0, 0.0));
            previousTime = crntTime;
        }

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 300.0f);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);


		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Exports the camera Position to the Fragment Shader for specular lighting
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(colorShader, "camMatrix");

        cubeVAO.Bind();
        // Original code from the tutorial
		// Binds textures so that they appear in the rendering
	

        // SETUP WORLD
        // ----------------------------------------------------------------------
        // Draw world floor
        snowTex.Bind();

        glm::mat4 floor = glm::mat4(1.0f);
        glm::vec3 floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
        floor = glm::translate(floor, floorPos) * glm::scale(glm::mat4(1.0), glm::vec3(100.0f, 0.01f, 100.0f));;
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floor[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        skyTex.Bind();
         // Draw skybox
        glm::mat4 skybox = glm::mat4(1.0f);
        glm::vec3 skyboxPos = glm::vec3(0.0f, 0.0f, 0.0f);
        skybox = glm::translate(skybox, skyboxPos) * glm::scale(glm::mat4(1.0), glm::vec3(100.0f, 100.0f, 100.0f));;
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &skybox[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);



        // Draw Museum
        // ---------------------------------------------------------------------------------------------------------
        //

        brick.Bind();

        glm::mat4 mainBodyMatrix = glm::mat4(1.0f);

        glm::vec3 wallPos[] = { vec3(-25.0f, 0.0f,  10.0f),
                                vec3(-25.0f, 0.0f, -10.0f),
                                vec3(25.0f, 0.0f,   10.0f) ,
                                vec3(25.0f, 0.0f,  -10.f),
                                vec3(12.5f, 0.0f,  -20.0f),
                                vec3(-12.5f, 0.0f, -20.0f),
                                vec3(12.5f, 0.0f,   20.0f),
                                vec3(-12.5f, 0.0f,  20.0f),
                                vec3(5.0f, 0.0f,  -15.0f),
                                vec3(15.0f, 0.0f,  0.0f),
                                vec3(5.0f, 0.0f,  15.0f),
                                vec3(-5.0f, 0.0f,  -15.0f),
                                vec3(-15.0f, 0.0f,  0.0f),
                                vec3(-5.0f, 0.0f,  15.0f),
                                vec3(5.0f, 0.0f,  -7.5f) };

        mat4 wallScaleShort = glm::scale(glm::mat4(1.0), glm::vec3(0.01f, 20.0f, 20.0f));
        mat4 wallScaleLong = glm::scale(glm::mat4(1.0), glm::vec3(0.01f, 20.0f, 25.0f));
        mat4 wallScaleInterior = glm::scale(glm::mat4(1.0), glm::vec3(0.01f, 20.0f, 10.0f));
        mat4 seperatorScaleInterior = glm::scale(glm::mat4(1.0), glm::vec3(20.0f, 20.0f, 1.0f));


        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        {
            if ((camera.Position.x >= 4.0f && camera.Position.x <= 6.0f) && camera.Position.z <= -5.5f && camera.Position.z >= -9.5f)
            {
                rotation = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
            }
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            break;
        }


        cubeSpaceRoomVAO.Bind();


        glm::mat4 wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[0]) * wallScaleShort;
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[1])
            * wallScaleShort;
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[2])
            * wallScaleShort;
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[3])
            * wallScaleShort;
        glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[4])
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * wallScaleLong;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[5])
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * wallScaleLong;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[6])
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * wallScaleLong;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[7])
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * wallScaleLong;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[8])
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[9])
          * seperatorScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[10])
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[11])
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[12])
          * seperatorScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[13])
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      containerTex.Bind();

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[11] + vec3(0.02f,0.0f,0.0f))
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

    wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[10] + vec3(-0.02f, 0.0f, 0.0f))
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[8] + vec3(-0.02f, 0.0f, 0.0f))
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

  wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), wallPos[13] + vec3(0.02f, 0.0f, 0.0f))
          * wallScaleInterior;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      

      // Draw roof
      pyVAO.Bind();
      glm::vec3 roofPos = glm::vec3(0.0f, 10.0f, 0.0f);
      glm::mat4 roofModel = glm::mat4(1.0f);
      roofModel = glm::translate(roofModel, roofPos) * glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 10.0f, 40.0f));
      shaderProgram.setMat4("model", roofModel);
      glDrawElements(GL_TRIANGLES, sizeof(pyIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
      
      // Draw museum floor
      VAOmuseumFloor.Bind();
      planksTex.Bind();
      planksSpec.Bind();
      glm::mat4 museumFloor = glm::mat4(1.0f);
      glm::vec3 museumFloorPos = glm::vec3(0.0f, 0.01f, 0.0f);
      floor = glm::translate(museumFloor, museumFloorPos) * glm::scale(glm::mat4(1.0), glm::vec3(25.0f, 0.01f, 20.0f));;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &floor[0][0]);
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

      // DRAW SPACE ROOM
      // ------------------------------------------------------------------------
      // Floor
      //cubeVAO.Bind();
      grassTex.Bind();
      VAOmuseumFloor.Bind();
      glm::mat4 roomFloor = glm::mat4(1.0f);
      glm::vec3 roomFloorPos = glm::vec3(15.0f, 0.04f, -10.0f);
      roomFloor = glm::translate(roomFloor, roomFloorPos) * glm::scale(glm::mat4(1.0), glm::vec3(5.0f));;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &roomFloor[0][0]);
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

      cubeVAO.Bind();

      obsidianTex.Bind();

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), vec3(15.0f,0.0f,-15.0f))
          * glm::scale(glm::mat4(1.0), glm::vec3(10.0f, 0.1f, 0.1f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), vec3(20.0f, 0.0f, -10.0f))
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * glm::scale(glm::mat4(1.0), glm::vec3(10.0f, 0.1f, 0.1f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), vec3(15.0f, 0.0f, -5.0f))
          * glm::scale(glm::mat4(1.0), glm::vec3(10.0f, 0.1f, 0.1f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      wall = mainBodyMatrix * glm::translate(glm::mat4(1.0), vec3(10.0f, 0.0f, -10.0f))
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * glm::scale(glm::mat4(1.0), glm::vec3(10.0f, 0.1f, 0.1f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &wall[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);


      // MOVABLE BLOCKS
      // --------------------------------------------------------------------------------------
      // check if player is near cube

      if ((camera.Position.x >= redCubePos.x + -1.0f && camera.Position.x <= redCubePos.x + 1.0f)
          && (camera.Position.z <= redCubePos.z + 1.0f && camera.Position.z >= redCubePos.z - 1.0f))
      {
          if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
          {
              redCubePos += glm::vec3(0.1f, 0.0f, 0.0f);
          }

          if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
          {
              redCubePos += glm::vec3(-0.1f, 0.0f, 0.0f);
          }

          if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
          {
              redCubePos += glm::vec3(0.0f, 0.0f, -0.1f);
          }

          if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
          {
              redCubePos += glm::vec3(0.0f, 0.0f, 0.1f);
          }
  
      }

      else if ((camera.Position.x >= blueCubePos.x + -1.0f && camera.Position.x <= blueCubePos.x + 1.0f)
          && (camera.Position.z <= blueCubePos.z + 1.0f && camera.Position.z >= blueCubePos.z - 1.0f))
          {

              if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
              {
                  blueCubePos += glm::vec3(0.1f, 0.0f, 0.0f);
              }

              if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
              {
                  blueCubePos += glm::vec3(-0.1f, 0.0f, 0.0f);
              }

              if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
              {
                  blueCubePos += glm::vec3(0.0f, 0.0f, -0.1f);
              }

              if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
              {
                  blueCubePos += glm::vec3(0.0f, 0.0f, 0.1f);
              }
          }

      else if ((camera.Position.x >= greenCubePos.x + -1.0f && camera.Position.x <= greenCubePos.x + 1.0f)
          && (camera.Position.z <= greenCubePos.z + 1.0f && camera.Position.z >= greenCubePos.z - 1.0f))
          {

              if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
              {
                  greenCubePos += glm::vec3(0.1f, 0.0f, 0.0f);
              }

              if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
              {
                  greenCubePos += glm::vec3(-0.1f, 0.0f, 0.0f);
              }

              if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
              {
                  greenCubePos += glm::vec3(0.0f, 0.0f, -0.1f);
              }

              if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
              {
                  greenCubePos += glm::vec3(0.0f, 0.0f, 0.1f);
              }
          }
     
      // CUBE ON PLATE LOGIC
      // ---------------------------------------------------------------------------------
      // check if red cube is on plate
      if ((redCubePos.x >= redPlatePos.x + -0.5f && redCubePos.x <= redPlatePos.x + 0.5f)
          && (redCubePos.z <= redPlatePos.z + 0.5f && redCubePos.z >= redPlatePos.z - 0.5f))
      {
          redPlatePos += (float)glfwGetTime() * vec3(0.0f, -0.0001f, 0.0f);
          redPlateOn = true;
      }
      else
      {
          redPlatePos = redPlatePosInitial;
          redPlateOn = false;
      }

      // check if blue cube is on plate
      if ((blueCubePos.x >= bluePlatePos.x + -0.5f && blueCubePos.x <= bluePlatePos.x + 0.5f)
          && (blueCubePos.z <= bluePlatePos.z + 0.5f && blueCubePos.z >= bluePlatePos.z - 0.5f))
      {
          bluePlatePos += (float)glfwGetTime() * vec3(0.0f, -0.0001f, 0.0f);
          bluePlateOn = true;
      }
      else
      {
          bluePlatePos = bluePlatePosInitial;
          bluePlateOn = false;
      }

      // check if green cube is on plate
      if ((greenCubePos.x >= greenPlatePos.x + -0.5f && greenCubePos.x <= greenPlatePos.x + 0.5f)
          && (greenCubePos.z <= greenPlatePos.z + 0.5f && greenCubePos.z >= greenPlatePos.z - 0.5f))
      {
          greenPlatePos += (float)glfwGetTime() * vec3(0.0f, -0.0001f, 0.0f);
          greenPlateOn = true;
      }
      else
      {
          greenPlatePos = greenPlatePosInitial;
          greenPlateOn = false;
      }

      cubeSpaceRoomVAO.Bind();
      goldTex.Bind();

      // DRAW PRESURE PLATES
      // red pressure plate
      mat4 plateRed = mainBodyMatrix * glm::translate(glm::mat4(1.0), redPlatePos)
          * glm::scale(glm::mat4(1.0), scale);
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &plateRed[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      diamondTex.Bind();

      // blue pressure plate
      mat4 plateBlue = mainBodyMatrix * glm::translate(glm::mat4(1.0), bluePlatePos)
          * glm::scale(glm::mat4(1.0), scale);
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &plateBlue[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      obsidianTex.Bind();
      // green pressure plate
      mat4 plateGreen = mainBodyMatrix * glm::translate(glm::mat4(1.0), greenPlatePos)
          * glm::scale(glm::mat4(1.0), scale);
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &plateGreen[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);


      
      goldTex.Bind();

      mat4 redBlock = mainBodyMatrix * glm::translate(glm::mat4(1.0), redCubePos)
          * glm::scale(glm::mat4(1.0), vec3(0.8f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &redBlock[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);
   
      diamondTex.Bind();

      mat4 blueBlock = mainBodyMatrix * glm::translate(glm::mat4(1.0), blueCubePos)
          * glm::scale(glm::mat4(1.0), vec3(0.8f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &blueBlock[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      obsidianTex.Bind();

      mat4 greenBlock = mainBodyMatrix * glm::translate(glm::mat4(1.0), greenCubePos)
          * glm::scale(glm::mat4(1.0), vec3(0.8f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &greenBlock[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      trophyTex.Bind();

      mat4 trophieBlock = mainBodyMatrix * glm::translate(glm::mat4(1.0), trophieCubePos)
          * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0))
          * glm::scale(glm::mat4(1.0), vec3(1.0f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &trophieBlock[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);


      if ((redPlateOn == true) && (bluePlateOn == true) && (greenPlateOn = true))
      {
          if (trophieCubePos.y <= 0.5f)
          {
              trophieCubePos += (float)glfwGetTime() * vec3(0.0f, 0.0007f, 0.0f);
          }
      }



      // SHAPE ROOM
      //-------------------------------------------------------------------------
        // draw legos

      if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
      {
          textureState = 2;
      }

      if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
      {
          textureState = 3;
      }

      if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
      {
          textureState = 4;
      }

      // Default texture
      if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
      {
          textureState = 1;
      }


   

      if (textureState == 1)
      {
          legoYellowTex.Bind();
      }

      else if (textureState == 2)
      {
          legoBlueTex.Bind();
      }

      else if (textureState == 3)
      {
          legoRedTex.Bind();

      }

      else if (textureState == 4)
      {
          legoGreenTex.Bind();

      }



 

      if (letterState == "empty")
      {
          renderEmpty(shaderProgram, renderColor, roomOrigin);
      }
      if (letterState == "A")
      {
          renderA(shaderProgram, renderColor, roomOrigin);
      }
      if (letterState == "Y")
      {
          renderY(shaderProgram, renderColor, roomOrigin);
      }
      if (letterState == "R")
      {
          renderR(shaderProgram, renderColor, roomOrigin);
      }
      if (letterState == "N")
      {
          renderN(shaderProgram, renderColor, roomOrigin);
      }

      concrete.Bind();
      drawPodium(shaderProgram, vec3(0.0f, 0.0f, 0.0f), roomOrigin);


      if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
      {
          letterState = "A";
      }

      if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
      {
          letterState = "Y";
      }

      if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
      {
          letterState = "R";
      }

      if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
      {
          letterState = "N";
      }

   
      // SOUND ROOM
      // -----------------------------------------------------------


      if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) // switch sound
      {
          soundManager.Play(0);
      }
      if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) // switch sound
      {
          soundManager.Play(1);
      }
      if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) // switch sound
      {
          soundManager.Play(2);
      }
      if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) // switch sound
      {
          soundManager.Play(3);
      }
      //if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS) // switch sound
      //{
      //    soundManager.Play(4);
      //}

      concrete.Bind();

      mat4 base1 = translate(mat4(1.0f), vec3(-23.5f, 0.1f, 19.f)) * glm::scale(mat4(1.0f), vec3(2.0f, 0.2f, 1.0f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &base1[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      mat4 op1 = translate(mat4(1.0f), vec3(-23.5f, 1.0f, 19.f)) * glm::scale(mat4(1.0f), vec3(1.0f, 1.6f, 0.7f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &op1[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      guitarTex.Bind();

      mat4 st1 = translate(mat4(1.0f), vec3(-23.5f, 2.2f, 19.f)) * glm::scale(mat4(1.0f), vec3(0.6f, 0.8f, 0.2f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &st1[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      concrete.Bind();

      mat4 base2 = translate(mat4(1.0f), vec3(-6.5f, 0.1f, 19.f)) * glm::scale(mat4(1.0f), vec3(2.0f, 0.2f, 1.0f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &base2[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);


      mat4 op2 = translate(mat4(1.0f), vec3(-6.5f, 1.0f, 19.f)) * glm::scale(mat4(1.0f), vec3(1.0f, 1.6f, 0.7f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &op2[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      harpTex.Bind();

      mat4 st2 = translate(mat4(1.0f), vec3(-6.5f, 2.2f, 19.f)) * glm::scale(mat4(1.0f), vec3(0.6f, 0.8f, 0.2f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &st2[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      concrete.Bind();

      mat4 base3 = translate(mat4(1.0f), vec3(-6.5f, 0.1f, 2.f)) * glm::scale(mat4(1.0f), vec3(2.0f, 0.2f, 1.0f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &base3[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);


      mat4 op3 = translate(mat4(1.0f), vec3(-6.5f, 1.0f, 2.f)) * glm::scale(mat4(1.0f), vec3(1.0f, 1.6f, 0.7f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &op3[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      pianoTex.Bind();
      mat4 st3 = translate(mat4(1.0f), vec3(-6.5f, 2.2f, 2.f)) * glm::scale(mat4(1.0f), vec3(0.6f, 0.8f, 0.2f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &st3[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      concrete.Bind();

      mat4 base4 = translate(mat4(1.0f), vec3(-23.5f, 0.1f, 2.f)) * glm::scale(mat4(1.0f), vec3(2.0f, 0.2f, 1.0f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &base4[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);


      mat4 op4 = translate(mat4(1.0f), vec3(-23.5f, 1.0f, 2.f)) * glm::scale(mat4(1.0f), vec3(1.0f, 1.6f, 0.7f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &op4[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      saxTex.Bind();
      mat4 st4 = translate(mat4(1.0f), vec3(-23.5f, 2.2f, 2.f)) * glm::scale(mat4(1.0f), vec3(0.6f, 0.8f, 0.2f));
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &st4[0][0]);
      glDrawArrays(GL_TRIANGLES, 0, 36);

     musicTex.Bind();
      VAOmuseumFloor.Bind();
      glm::mat4 roomMusicFloor = glm::mat4(1.0f);
      glm::vec3 roomMusicFloorPos = glm::vec3(-15.0f, 0.04f, 10.0f);
      roomMusicFloor = glm::translate(roomMusicFloor, roomMusicFloorPos) * glm::scale(glm::mat4(1.0), glm::vec3(10.0f));;
      glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &roomMusicFloor[0][0]);
      glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

      // Tells OpenGL which Shader Program we want to use
      lightShader.Activate();
      // Export the camMatrix to the Vertex Shader of the light cube
      camera.Matrix(lightShader, "camMatrix");
      // Bind the VAO so OpenGL knows to use it
      lightVAO.Bind();   

      glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    
          if ( (camera.Position.x >= lightPos.x + -2.0f && camera.Position.x <= lightPos.x + 2.0f) && (camera.Position.z >= lightPos.z + -2.0f && camera.Position.z <= lightPos.z + 2.0f))
          {


              vec4 lightColor2 = vec4(static_cast<float>(sin(glfwGetTime() * 2.0)), static_cast<float>(sin(glfwGetTime() * 0.7)), static_cast<float>(sin(glfwGetTime() * 1.3)), 1.0f);
              lightBox = lightModel * translate(mat4(1.0f), lightPos)
                  * glm::scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
              lightShader.Activate();
              glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightBox));
              glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w);
              shaderProgram.Activate();
              glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &lightBox[0][0]);
              glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w);
              glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
              glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

              

              if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
              {

                  vec4 lightColor3 = vec4(1.0f, 0.0f, 0.0f, 1.0f);
                  lightBox = lightModel * translate(mat4(1.0f), lightPos3)
                      * glm::scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                  lightShader.Activate();
                  glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightBox));
                  glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor3.x, lightColor3.y, lightColor3.z, lightColor3.w);
                  shaderProgram.Activate();
                  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor3.x, lightColor3.y, lightColor3.z, lightColor3.w);
                  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos3.x, lightPos3.y, lightPos3.z);
                  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

              }

              if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
              {
                  vec4 lightColor4 = vec4(0.0f, 1.0f, 0.0f, 1.0f);
                  lightBox = lightModel * translate(mat4(1.0f), lightPos4)
                      * glm::scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                  lightShader.Activate();
                  glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightBox));
                  glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor4.x, lightColor4.y, lightColor4.z, lightColor4.w);
                  shaderProgram.Activate();
                  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor4.x, lightColor4.y, lightColor4.z, lightColor4.w);
                  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos4.x, lightPos4.y, lightPos4.z);
                  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

              }

              if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
              {

                  vec4 lightColor5 = vec4(0.0f, 0.0f, 1.0f, 1.0f);
                  lightBox = lightModel * translate(mat4(1.0f), lightPos5)
                      * glm::scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
                  lightShader.Activate();
                  glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightBox));
                  glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor5.x, lightColor5.y, lightColor5.z, lightColor5.w);
                  shaderProgram.Activate();
                  glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor5.x, lightColor5.y, lightColor5.z, lightColor5.w);
                  glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos5.x, lightPos5.y, lightPos5.z);
                  glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
              }

              


          }

          else {

              vec4 lightColor6 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
              lightBox = translate(mat4(1.0f), lightPos)
                  * glm::scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
              lightShader.Activate();
              glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, value_ptr(lightBox));
              glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor6.x, lightColor6.y, lightColor6.z, lightColor6.w);
              shaderProgram.Activate();
              glUniformMatrix4fv(worldMatrixLoc, 1, GL_FALSE, &lightBox[0][0]);
              glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor6.x, lightColor6.y, lightColor6.z, lightColor6.w);
              glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
              glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

          }


          /*glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
          glm::vec3 lightPos2 = glm::vec3(10.0f, 5.0f, 15.0f);
          glm::vec3 lightPos3 = glm::vec3(2.0f, 1.0f, 3.0f)*/;
      
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
    cubeVAO.Delete();
    cubeVBO.Delete();
    pyVAO.Delete();
    pyVBO.Delete();
    pyEBO.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
	shaderProgram.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}