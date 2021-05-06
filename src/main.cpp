// Graphic libraries includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stdlib includes
#include <iostream>
#include <vector>

// Local includes
#include "gl/window.hpp"
#include "gl/shader.hpp"
#include "gl/buffer.hpp"
#include "gl/vao.hpp"
#include "gl/texture.hpp" // End of GL includes
#include "world/player/camera.hpp" // End of world includes
#include "utils/clock.hpp"
#include "utils/types.hpp" // End of utils includes

// Rewrite! Starting again with GLFW instead of SFML (like the original)
// I didn't get much done with the original write anyways...

// Macro to check if a key was pressed
#define BUTTON_PRESSED(win, key) glfwGetKey(win, key) == GLFW_PRESS

// Camera
World::Player::Camera cam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Misc
bool cursorCaptured = true;

void processInput(GLFWwindow *window)
{  
    if (BUTTON_PRESSED(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    if (BUTTON_PRESSED(window, GLFW_KEY_P))
    {
        glfwSetInputMode(window, GLFW_CURSOR, cursorCaptured ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        cursorCaptured = !cursorCaptured;
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
    gl::Window Window;
    Window.init();
    Clock c;

    glfwSetCursorPosCallback(Window.window, mouse_callback);

    // Setup OpenGL for rendering
    glEnable(GL_DEPTH_TEST);
    gl::Shader shade("shaders/vertex.glsl", "shaders/frag.glsl");

    gl::Buffer vbo;
    vbo.init(GL_ARRAY_BUFFER);
    gl::VAO vao;
    vao.init();

    vbo.bufferData(GL_ARRAY_BUFFER, sizeof(float), vertices);
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
    while (!glfwWindowShouldClose(Window.window))
    {
        // Calculate the delta time
        float currentFrame = c.elapsed();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Window.setTitle("Voxel Game - Delta: " + std::to_string(deltaTime));

        // Process any input
        processInput(Window.window);

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
        glfwSwapBuffers(Window.window);
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();

    Window.quit();
    return EXIT_SUCCESS;
}