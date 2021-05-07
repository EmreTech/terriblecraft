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
#include "world/player/camera.hpp" 
#include "world/block/blockatlas.hpp" // End of world includes
#include "utils/clock.hpp"
#include "utils/types.hpp" // End of utils includes

// Rewrite! Starting again with GLFW instead of SFML (like the original)
// I didn't get much done with the original write anyways...

// Macro to check if a key was pressed
#define BUTTON_PRESSED(win, key) glfwGetKey(win, key) == GLFW_PRESS

// Camera
World::Player::Camera cam(glm::vec3(0.0f, 0.0f, 10.0f));
float lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Misc
bool cursorCaptured = true;

struct FPSCounter
{
    float fps = 0;

    FPSCounter(){}

    void update()
    {
        frameCount++;

        if (delayTimer.elapsed() > 0.5)
        {
            fps = frameCount / fpsTimer.restart();
            frameCount = 0;
            delayTimer.restart();
        }
    }

    private:
    int frameCount = 0;
    Clock delayTimer;
    Clock fpsTimer; 
};

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

std::vector<float> test()
{
    std::vector<float> output;
    std::array<glm::vec2, 6> textureCoords;

    int x, y = 0;

    for (size_t i{0}; i < vertices.size(); i++)
    {
        output.push_back(vertices.at(i));
        y++;
        
        if (y == 3)
        {
            if (faces[i / 3] == 4) // If the face is a bottom face
            {
                textureCoords = World::Block::GetTextureCoords(2, 0, faces[(i / 3)]);
            }
            else if (faces[i / 3] == 5) // If the face is a top face
            {
                textureCoords = World::Block::GetTextureCoords(0, 0, faces[(i / 3)]);
            }
            else // Otherwise, we assume side faces
            {
                textureCoords = World::Block::GetTextureCoords(1, 0, faces[(i / 3)]);
            }

            float tex_first  = textureCoords.at(x).x;
            float tex_second = textureCoords.at(x).y;
            
            output.push_back(tex_first);
            output.push_back(tex_second);

            (x != textureCoords.size() - 1 ? x++ : x = 0);
            y = 0;
        }
    }

    return output;
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

    auto newVertices = test(); // Testing out the texture atlas
    vbo.bufferData(GL_ARRAY_BUFFER, sizeof(float), newVertices);
    vao.attribute(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao.attribute(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    gl::Texture tex1("res/blocks.png", GL_RGBA, STBI_rgb_alpha);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
    (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

    // Generating a "chunk layer"
    size_t last_pos_size = 4 * 5, i = 0;
    float x = 1;
    while (i != last_pos_size)
    {
        glm::vec3 insert = glm::vec3(cubePositions.at(i).x, cubePositions.at(i).y, cubePositions.at(i).z + x);
        cubePositions.push_back(insert);

        if (cubePositions.at(i).x == 3.0f)
        {
            x += 0.5f;
            x -= 0.5f;
        }

        i++;
    }

    FPSCounter fpsCount;
    // Game loop!
    while (!glfwWindowShouldClose(Window.window))
    {
        // Calculate the delta time
        float currentFrame = c.elapsed();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process any input
        processInput(Window.window);

        // Update the FPS count (not related to delta time calculation at all)
        fpsCount.update();
        Window.setTitle("Voxel Game - FPS: " + std::to_string(fpsCount.fps));

        // Render
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, tex1.ID);

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

    // Cleanup GL resources
    vao.destroy();
    vbo.destroy();

    Window.quit();
    return EXIT_SUCCESS;
}