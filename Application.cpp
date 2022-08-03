// Liam Pereira
// 40111656
// Quiz 2 COMP 371
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

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

using namespace glm;

const unsigned int width = 800;
const unsigned int height = 800;


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


// Floor
// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		    0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 50.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		50.0f, 50.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		50.0f, 0.0f,		0.0f, 1.0f, 0.0f
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


int main()

{
    // Initial world position, scale and rotation of snowman



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
    VAO VAOfloor;
    VAOfloor.Bind();

    VBO VBOfloor(vertices, sizeof(vertices));
    EBO EBOfloor(indices, sizeof(indices));

    // Co ords
    VAOfloor.LinkAttrib(VBOfloor, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    // Colors
    VAOfloor.LinkAttrib(VBOfloor, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    // Textures
    VAOfloor.LinkAttrib(VBOfloor, 3, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    // Normals
    VAOfloor.LinkAttrib(VBOfloor, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    // Unbind all to prevent accidentally modifying them
    VAOfloor.Unbind();
    VBOfloor.Unbind();
    EBOfloor.Unbind();



    // Cube vertices
    // ---------------------------------------------------------------------------------------------------
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(cubeVertices, sizeof(cubeVertices));

	// Links VBO attributes such as coordinates and colors to VAO
	// Position
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	// Textures
	VAO1.LinkAttrib(VBO1, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Normals
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();


    VAO VAO2;
    VAO2.Bind();
    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO2(pyVertices, sizeof(pyVertices));
    // Generates Element Buffer Object and links it to indices
    EBO EBO2(pyIndices, sizeof(pyIndices));
    // Links VBO attributes such as coordinates and colors to VAO
    // Positions
    VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // Tex co-ords
    VAO2.LinkAttrib(VBO2, 3, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Normals
    VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    VAO2.Unbind();
    VBO2.Unbind();
    EBO2.Unbind();


    // Light vertices
    // ---------------------------------------------------------------------------------------------------

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();


    // light  model definition
    // ---------------------------------------------------------------------------------------------------


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 0.1f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 5.0f, 30.0f);
    lightModel = glm::translate(lightModel, lightPos) * glm::scale(glm::mat4(1.0), glm::vec3(10.0f, 10.0f, 10.0f));

    // Giving the shaders necessary light values to process light 

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Texture declarations

    Texture tex0("lava.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture tex1("red.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture tex2("sky.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture tex3("dirt.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture tex4("lapis.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture tex5("metal.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture tex6("black_gloss.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture tex7("gold.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture tex8("water.jpg", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
    Texture tex9("iron.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture tex10("obsidian.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);







	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    glm::vec3 position = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 scale = glm::vec3(2.0, 2.0, 2.0);
    glm::mat4 rotation = glm::mat4(1.0f);

    glm::vec3 positionInitial = position;
    glm::vec3 scaleInitial = scale;
    glm::mat4 rotationInitial = rotation;

    glm::vec3 cameraFrontPosition = glm::vec3(0.0f, 0.2f, -1.5f) + positionInitial;
    glm::vec3 cameraBackPosition = glm::vec3(0.0f, 0.2f, 1.5f) + positionInitial;


    int cameraNum = 3;

	// Creates camera object

    Camera cameraMain(width, height, vec3(0.0f, 5.0f, 25.0f));
    Camera cameraFront(width, height, cameraFrontPosition);
    Camera cameraBack(width, height, cameraBackPosition);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        {

            // Move skateboard left

            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                position += glm::vec3(-0.1f, 0.0f, 0.0f);

            }

            // Move skateboard right


            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                position += glm::vec3(0.1f, 0.0f, 0.0f);

            }

            // Move skateboard forward


            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                position += glm::vec3(0.0f, 0.0f, -0.1f);

            }


            // Move skateboard back


            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                position += glm::vec3(0.0f, 0.0f, 0.1f);

            }
        }

        // Assign a number to decide which camera to use

        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            cameraNum = 1;

        }
        else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        {

            cameraNum = 2;


        }

        else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            cameraNum = 3;


        }

		// Handles camera inputs
		// Updates and exports the camera matrix to the Vertex Shader

        if (cameraNum == 1)
        {
            cameraFront.updateMatrix(45.0f, 0.1f, 300.0f);
            cameraFront.Inputs(window);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), cameraFront.Position.x, cameraFront.Position.y, cameraFront.Position.z);

        }

        if (cameraNum == 2)
        {
            cameraBack.updateMatrix(45.0f, 0.1f, 300.0f);
            cameraBack.Inputs(window);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), cameraBack.Position.x, cameraBack.Position.y, cameraBack.Position.z);

        }

        else if (cameraNum == 3)
        {
            cameraMain.updateMatrix(45.0f, 0.1f, 300.0f);
            cameraMain.Inputs(window);
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), cameraMain.Position.x, cameraMain.Position.y, cameraMain.Position.z);

        }


		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Exports the camera Position to the Fragment Shader 

        if (cameraNum == 1)
        {
            cameraFront.Matrix(colorShader, "camMatrix");


        }

        if (cameraNum == 2)
        {
            cameraBack.Matrix(colorShader, "camMatrix");


        }

        else if (cameraNum == 3)
        {
            cameraMain.Matrix(colorShader, "camMatrix");


        }



       


        tex0.texUnit(shaderProgram, "tex0", 0);
		// Binds textures so that they appear in the rendering
		tex0.Bind();


        // Draw floor
        // ------------------------------------------------------------------------------------------------------------
        glm::mat4 floor = glm::mat4(1.0f);
        glm::vec3 floorPos = glm::vec3(0.0f, 0.0f, 0.0f);
        floor = glm::translate(floor, floorPos) * glm::scale(glm::mat4(1.0), glm::vec3(50.0f, 1.0f, 50.0f));;
        shaderProgram.setMat4("model", floor);

        VAOfloor.Bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        tex4.texUnit(shaderProgram, "tex0", 0);
        tex4.Bind();

        VAO1.Bind();


        // Draw skybox
        // ------------------------------------------------------------------------------------------------------------

        glm::mat4 skybox = glm::mat4(1.0f);
        glm::vec3 skyboxPos = glm::vec3(0.0f, 0.0f, 0.0f);
        skybox = glm::translate(skybox, skyboxPos) * glm::scale(glm::mat4(1.0), glm::vec3(100.0f, 100.0f, 100.0f));;
        shaderProgram.setMat4("model", skybox);

        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Draw axis
        // ------------------------------------------------------------------------------------------------------------

        tex1.texUnit(shaderProgram, "tex0", 0);
        tex1.Bind();

        glm::mat4 axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(2.5f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 0.1f, 0.1f));
        shaderProgram.setMat4("model", axisMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        VAO2.Bind();
      
        glm::vec3 objectPosY = glm::vec3(5.0f, 0.0f, 0.0f);
        glm::mat4 objectModelY = glm::mat4(1.0f);
        objectModelY = glm::translate(objectModelY, objectPosY) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0, 0.0, 1.0));
        shaderProgram.setMat4("model", objectModelY);
        glDrawElements(GL_TRIANGLES, sizeof(pyIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        VAO1.Bind();


        tex2.texUnit(shaderProgram, "tex0", 0);
        tex2.Bind();

        axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.5f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 5.0f, 0.1f));
        shaderProgram.setMat4("model", axisMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        VAO2.Bind();

        glm::vec3 objectPosX = glm::vec3(0.0f, 5.0f, 0.0f);
        glm::mat4 objectModelX = glm::mat4(1.0f);
        objectModelX = glm::translate(objectModelX, objectPosX) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));
        shaderProgram.setMat4("model", objectModelX);
        glDrawElements(GL_TRIANGLES, sizeof(pyIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        VAO1.Bind();

        tex3.texUnit(shaderProgram, "tex0", 0);
        tex3.Bind();

        axisMatrix = glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), 5.0f * 0, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.5f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 5.0f));
        shaderProgram.setMat4("model", axisMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        VAO2.Bind();

        glm::vec3 objectPosZ = glm::vec3(0.0f, 0.0f, 5.0f);
        glm::mat4 objectModelZ = glm::mat4(1.0f);
        objectModelZ = glm::translate(objectModelZ, objectPosZ) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
        shaderProgram.setMat4("model", objectModelZ);
        glDrawElements(GL_TRIANGLES, sizeof(pyIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        VAO1.Bind();





        // Turn spotlight on/off

        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        {
            glUniform1i(glGetUniformLocation(shaderProgram.ID, "spotOff"), false);

        }

        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        {
            glUniform1i(glGetUniformLocation(shaderProgram.ID, "spotOff"), true);

        }

        // Original code from the tutorial
        tex5.texUnit(shaderProgram, "tex0", 0);
        //// Binds textures so that they appear in the rendering
        tex5.Bind();


        // Drawing skateboard
        //------------------------------------------------------------------------------------------------

        glm::mat4 mainBodyMatrix = glm::mat4(1.0f);
        mainBodyMatrix = glm::translate(mainBodyMatrix, position)
                 
                        * glm::scale(mainBodyMatrix, glm::vec3(16.0, 0.25, 4.0));
        shaderProgram.setMat4("model", mainBodyMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Drawing all the wheels
        //-------------------------------------------------------------------------------------------------

        // Original code from the tutorial
        tex6.texUnit(shaderProgram, "tex0", 0);
        //// Binds textures so that they appear in the rendering
        tex6.Bind();


        // Draw wheel relative to mainBodyMatrix
        glm::mat4 wheel = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.35f, -1.7f, 0.35f))
            * glm::scale(glm::mat4(1.0), glm::vec3(0.0625f, 4.0f, 0.25f));
        shaderProgram.setMat4("model", wheel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 2nd wheel
        wheel = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(0.35f, -1.7f, -0.35f))
            * glm::scale(glm::mat4(1.0), glm::vec3(0.0625f, 4.0f, 0.25f));
        shaderProgram.setMat4("model", wheel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 3rd wheel
        wheel = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.35f, -1.7f, 0.35f))
            * glm::scale(glm::mat4(1.0), glm::vec3(0.0625f, 4.0f, 0.25f));
        shaderProgram.setMat4("model", wheel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 4th wheel
        wheel = mainBodyMatrix * glm::translate(glm::mat4(1.0), glm::vec3(-0.35f, -1.7f, -0.35f))
            * glm::scale(glm::mat4(1.0), glm::vec3(0.0625f, 4.0f, 0.25f));
        shaderProgram.setMat4("model", wheel);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Drawing letter L
        // --------------------------------------------------------------------------------------------------------

           // Original code from the tutorial
        tex7.texUnit(shaderProgram, "tex0", 0);
        //// Binds textures so that they appear in the rendering
        tex7.Bind();

        vec3 letterLPos = position + vec3(-6.0f, 0.5f, 0.0f);
        // Create 1st part of letter
        mainBodyMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(letterLPos))
            * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(glfwGetTime() * 30.0)), glm::vec3(0.0, 1.0, 0.0))
            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
        shaderProgram.setMat4("model", mainBodyMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);;
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);;
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);;
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);;
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
        shaderProgram.setMat4("model", block);;
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);;
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // Drawing letter I
        // --------------------------------------------------------------------------------------------------------

         // Original code from the tutorial
        tex8.texUnit(shaderProgram, "tex0", 0);
        //// Binds textures so that they appear in the rendering
        tex8.Bind();

        vec3 letterIPos = position + vec3(-2.0f, 0.5f, 0.0f);
        // Create 1st part of letter
        mainBodyMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(letterIPos))
            * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(glfwGetTime() * 30.0)), glm::vec3(0.0, 1.0, 0.0))
            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
        shaderProgram.setMat4("model", mainBodyMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Drawing digit 5
        // --------------------------------------------------------------------------------------------------------

         // Original code from the tutorial
        tex9.texUnit(shaderProgram, "tex0", 0);
        //// Binds textures so that they appear in the rendering
        tex9.Bind();

        vec3 digit5Pos = position + vec3(0.0f, 0.5f, 0.0f);
        // Create 1st part of letter
        mainBodyMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(digit5Pos))
            * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(glfwGetTime() * 30.0)), glm::vec3(0.0, 1.0, 0.0))
            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
        shaderProgram.setMat4("model", mainBodyMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Drawing digit 6
        // --------------------------------------------------------------------------------------------------------

         // Original code from the tutorial
        tex10.texUnit(shaderProgram, "tex0", 0);
        //// Binds textures so that they appear in the rendering
        tex10.Bind();

        vec3 digit6Pos = position + vec3(4.0f, 0.5f, 0.0f);
        // Create 1st part of letter
        mainBodyMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(digit6Pos))
            * glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(glfwGetTime() * 30.0)), glm::vec3(0.0, 1.0, 0.0))
            * glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
        shaderProgram.setMat4("model", mainBodyMatrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 4.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        block = mainBodyMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shaderProgram.setMat4("model", block);
        glDrawArrays(GL_TRIANGLES, 0, 36);

		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube

        if (cameraNum == 1)
        {
            cameraFront.Matrix(lightShader, "camMatrix");


        }

        if (cameraNum == 2)
        {
            cameraBack.Matrix(lightShader, "camMatrix");


        }

        else if (cameraNum == 3)
        {
            cameraMain.Matrix(lightShader, "camMatrix");


        }

		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
    VAOfloor.Delete();
	VBO1.Delete();
    VBOfloor.Delete();
	EBOfloor.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}