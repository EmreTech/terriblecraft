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
#include "gl/window.hpp" // End of GL includes
#include "utils/clock.hpp"
#include "utils/types.hpp" // End of utils includes
#include "world/block/blockdata.hpp"
#include "world/chunk/layer.hpp"
#include "world/chunk/chunkMeshBuilder.hpp"
#include "world/player/camera.hpp" // End of world includes
#include "renderer/cubeRenderer.hpp"
#include "renderer/chunkRenderer.hpp"

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

struct FPSCounter {
  float fps = 0;

  FPSCounter() {}

  void update() {
    frameCount++;

    if (delayTimer.elapsed() > 0.5) {
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

void processInput(GLFWwindow *window) {
  if (BUTTON_PRESSED(window, GLFW_KEY_ESCAPE))
    glfwSetWindowShouldClose(window, true);

  if (BUTTON_PRESSED(window, GLFW_KEY_P) &&
      lastCursorCaptureToggle.elapsed() > 1.0f) {
    glfwSetInputMode(window, GLFW_CURSOR,
                     cursorCaptured ? GLFW_CURSOR_NORMAL
                                    : GLFW_CURSOR_DISABLED);
    cursorCaptured = !cursorCaptured;
    lastCursorCaptureToggle.restart();
  }

  if (BUTTON_PRESSED(window, GLFW_KEY_V) &&
      lastWireframeToggle.elapsed() > 1.0f) {
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

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse || !cursorCaptured) {
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

std::vector<glm::vec3> generateChunkLayer() {
  size_t last_pos_size = 16 * 16, i = 0, y = 0;
  float x = 1.0f;
  std::vector<glm::vec3> output;

  while (i != last_pos_size) {
    if (y > cubePositions.size() - 1)
      y = 0;

    output.push_back(glm::vec3(cubePositions.at(y).x, cubePositions.at(y).y,
                               cubePositions.at(y).z + x));

    if (cubePositions.at(y).x == MAX_X_CUBE_POSITION)
      x += 1.0f;

    y++;
    i++;
  }

  return output;
}

int main() {
  // Init GLFW
  gl::Window Window;
  Window.init();
  Clock c;

  glfwSetCursorPosCallback(Window.window, mouse_callback);

  // Setup OpenGL for rendering
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);

  Renderer::CubeRenderer test;
  Renderer::ChunkRenderer chunkTest;

  // Generating a "chunk layer"
  //auto finalPositions = generateChunkLayer();

  //for (const auto& i : finalPositions)
  //  test.add(i);
  test.add({3, 1, 0});

  std::cout << "Generate chunk!" << '\n';
  World::Chunk::Layer testLayer;

  for (int x = 0; x < 16; x++)
  for (int z = 0; z < 16; z++)
  {
    //std::cout << "X: " << x << " Z: " << z << '\n';
    testLayer.setBlock(x, z, World::Block::BlockType::GRASS);
  }
  
  World::Chunk::ChunkMeshBuilder builder(testLayer);
  builder.buildMesh(testLayer.mesh);
  testLayer.mesh.buffer();

  chunkTest.add(testLayer.mesh);
  std::cout << "End of generate chunk!" << '\n';

  FPSCounter fpsCount;
  // Game loop!
  while (!glfwWindowShouldClose(Window.window)) {
    // Calculate the delta time
    float currentFrame = c.elapsed();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process any input
    processInput(Window.window);

    // Update the FPS count (not related to delta time calculation at all)
    fpsCount.update();
    Window.setTitle("TerribleCraft - FPS: " + std::to_string(fpsCount.fps));

    // Render

    // Clear the color and depth buffer every new render frame
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    test.render(cam);
    chunkTest.render(cam);

    // GLFW: Swap buffers and poll events
    glfwSwapBuffers(Window.window);
    glfwPollEvents();
  }

  Window.quit();
  return EXIT_SUCCESS;
}