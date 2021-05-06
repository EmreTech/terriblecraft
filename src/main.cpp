// graphic libraries includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stdlib includes
#include <iostream>
#include <vector>

// local includes
#include "gl/shader.hpp"
#include "gl/buffer.hpp"
#include "gl/vao.hpp"
#include "gl/texture.hpp"

#include "world/player/camera.hpp"

#include "utils/clock.hpp"
#include "utils/types.hpp"

// Rewrite! Starting again with GLFW instead of SFML (like the original)
// I didn't get much done with the original write anyways...

// Macro to check if a key was pressed
#define BUTTON_PRESSED(win, key) glfwGetKey(win, key) == GLFW_PRESS

// Window size
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Camera
World::Player::Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool cursorCaptured = true;

void resize_window_event(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// TODO: Move keyboard and mouse processing input functions to a seperate file
void processInput(GLFWwindow *window)
{  
    if (BUTTON_PRESSED(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (BUTTON_PRESSED(window, GLFW_KEY_P))
    {
        if (cursorCaptured)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursorCaptured = false;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorCaptured = true;
        }
    }

    if (BUTTON_PRESSED(window, GLFW_KEY_W)) // Forward
        cam.Keyboard(0, deltaTime);
     
    if (BUTTON_PRESSED(window, GLFW_KEY_S)) // Backward
        cam.Keyboard(1, deltaTime);
     
    if (BUTTON_PRESSED(window, GLFW_KEY_A)) // Left
        cam.Keyboard(2, deltaTime);
     
    if (BUTTON_PRESSED(window, GLFW_KEY_D)) // Right
        cam.Keyboard(3, deltaTime);
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse || !cursorCaptured)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    cam.Mouse(xoffset, yoffset);
}

int main()
{
    // Init GLFW
    glfwInit();
    Clock c;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
#endif

    // Open a window
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxel Game", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window with GLFW. You might not have the required OpenGL version" << '\n';
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    // Init Glad (for OpenGL functions)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize Glad (OpenGL)" << '\n';
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(window, resize_window_event);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Setup OpenGL for rendering
    glEnable(GL_DEPTH_TEST);
    gl::Shader shade("shaders/vertex.glsl", "shaders/frag.glsl");

    std::vector<float> vertices {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Top
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Left
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Front
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    std::vector<glm::vec3> cubePositions {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    gl::Buffer vbo;
    vbo.init(GL_ARRAY_BUFFER);
    gl::VAO vao;
    vao.init();

    vbo.bufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front());
    vao.attribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao.attribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    gl::Texture tex1("res/container.jpg", GL_RGB);
    gl::Texture tex2("res/awesomeface.png", GL_RGBA, true);

    shade.activate();
    shade.uniformInt("texture1", 0);
    shade.uniformInt("texture2", 1);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
    (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

    // Game loop!
    while (!glfwWindowShouldClose(window))
    {
        // Calculate the delta time
        float currentFrame = c.elapsed();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwSetWindowTitle(window, ("Voxel Game - Delta: " + std::to_string(deltaTime)).c_str());

        // Process any input
        processInput(window);

        // Render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1.ID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, tex2.ID);

        shade.activate();

        glm::mat4 view = cam.ViewMatrix();

        shade.uniformMatrix4("view", view);
        shade.uniformMatrix4("projection", projection);

        glBindVertexArray(vao.ID);
        for (unsigned int i = 0; i < cubePositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            shade.uniformMatrix4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // GLFW: Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();

    glfwTerminate();
    return EXIT_SUCCESS;
}