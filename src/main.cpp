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
World::Player::Camera cam(glm::vec3(0.0f, 3.0f, 10.0f));
float lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Misc
bool cursorCaptured = true, wireframe = false;
Clock lastWireframeToggle, lastCursorCaptureToggle;

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

    if (BUTTON_PRESSED(window, GLFW_KEY_P) && lastCursorCaptureToggle.elapsed() > 2.0f)
    {
        glfwSetInputMode(window, GLFW_CURSOR, cursorCaptured ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        cursorCaptured = !cursorCaptured;
        lastCursorCaptureToggle.restart();
    }

    if (BUTTON_PRESSED(window, GLFW_KEY_V) && lastWireframeToggle.elapsed() > 1.0f)
    {
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
        wireframe = !wireframe;
        lastWireframeToggle.restart();
    }

    if (BUTTON_PRESSED(window, GLFW_KEY_W) && cursorCaptured) // Forward
        cam.Keyboard(0, deltaTime);
     
    if (BUTTON_PRESSED(window, GLFW_KEY_S) && cursorCaptured) // Backward
        cam.Keyboard(1, deltaTime);
     
    if (BUTTON_PRESSED(window, GLFW_KEY_A) && cursorCaptured) // Left
        cam.Keyboard(2, deltaTime);
     
    if (BUTTON_PRESSED(window, GLFW_KEY_D) && cursorCaptured) // Right
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
        
        if (y == 3) // Slight workaround to ensure the texture coordinates are being inserted properly
        {
            if (faces[i / 3] == 4) // If the face is a bottom face
                textureCoords = World::Block::GetTextureCoords(2, 0, faces[(i / 3)]);
            else if (faces[i / 3] == 5) // If the face is a top face
                textureCoords = World::Block::GetTextureCoords(0, 0, faces[(i / 3)]);
            else // Otherwise, we assume other faces
                textureCoords = World::Block::GetTextureCoords(1, 0, faces[(i / 3)]);
            
            output.push_back(textureCoords.at(x).x);
            output.push_back(textureCoords.at(x).y);

            (x != textureCoords.size() - 1 ? x++ : x = 0);
            y = 0;
        }
    }

    return output;
}

std::vector<glm::vec3> generateChunkLayer()
{
    size_t last_pos_size = 16 * 16, i = 0, y = 0;
    float x = 1.0f;
    std::vector<glm::vec3> output;

    while (i != last_pos_size)
    {
        if (y > cubePositions.size() - 1)
            y = 0;

        output.push_back(glm::vec3(cubePositions.at(y).x, cubePositions.at(y).y, cubePositions.at(y).z + x));

        if (cubePositions.at(y).x == MAX_X_CUBE_POSITION)
            x += 1.0f;

        y++;
        i++;
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
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK_RIGHT);

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

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);

    // Generating a "chunk layer"
    auto finalPositions = generateChunkLayer();

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

        // Clear the color and depth buffer every new render frame
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind textures (the texture atlas)
        tex1.bind();

        // Activate the shader and set some uniform variables
        shade.activate();
        shade.uniformMatrix4("view", cam.ViewMatrix());
        shade.uniformMatrix4("projection", projection);

        // Transform the cubes and actually render them
        glBindVertexArray(vao.ID);
        for (unsigned int i = 0; i < finalPositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, finalPositions.at(i));
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