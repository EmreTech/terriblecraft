// Libraries includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// stdlib includes
#include <iostream>
#include <vector>
#include <utility>
#include <random>

// Local includes
#include "utils/clock.hpp"
#include "utils/types.hpp"
#include "utils/glm_include.hpp"
#include "utils/perlin_noise.hpp"
#include "utils/ray.hpp" // End of utils includes
#include "world/chunk/chunk.hpp"
#include "world/chunk/chunkMeshBuilder.hpp"
#include "world/player/camera.hpp" // End of world includes
#include "renderer/cubeRenderer.hpp"
#include "renderer/chunkRenderer.hpp"
#include "renderer/skyboxRenderer.hpp"

// Rewrite! Starting again with GLFW instead of SFML (like the original)
// I didn't get much done with the original write anyways...

using CompressedBlocks = std::vector<std::pair<uint16_t, uint32_t>>;

// Macro to check if a key was pressed
#define BUTTON_PRESSED(win, key) glfwGetKey(win, key) == GLFW_PRESS

// Camera
//World::Player::Camera cam(glm::vec3(8.0f, 17.0f, 8.0f));
World::Player::Camera cam(glm::vec3(0.0f, 2.0f, 0.0f));
float lastX = WINDOW_WIDTH / 2.0f, lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Misc
bool cursorCaptured = true, wireframe = false;
Clock lastWireframeToggle, lastCursorCaptureToggle;
World::Chunk::Chunk sec({0.0f, 0.0f});

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

void resize_window_event(GLFWwindow *win, int width, int height) {
  glViewport(0, 0, width, height);
}

int heightAt(int x, int z, int chunkX, int chunkZ)
{
  float xCoord = (x + (chunkX * CHUNK_SIZE)) * 0.1f;
  float zCoord = (z + (chunkZ * CHUNK_SIZE)) * 0.1f;

  auto generatedNoiseOne = PerlinNoise::getInstance().generateNoise( xCoord * 1.5f, zCoord * 1.5f, 0 ) * 10.0f;
  auto generatedNoiseTwo = PerlinNoise::getInstance().generateNoise( xCoord, zCoord, 0) * 5.0f;
  return generatedNoiseOne + generatedNoiseTwo;
}

CompressedBlocks compressChunk(World::Chunk::Chunk& chunk)
{
  CompressedBlocks output;
  World::Block::Block currentBlock = chunk.getBlock(0, 0, 0);
  uint32_t blockCount = 1;

  for (uint32_t i = 1; i < (CHUNK_VOLUME * chunk.getAmountOfSections()); i++)
  {
    int x = i % CHUNK_SIZE;
    int y = i / CHUNK_AREA;
    int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

    auto block = chunk.getBlock(x, y, z);

    if (block == currentBlock)
      blockCount++;

    else
    {
      output.emplace_back(currentBlock.id, blockCount);
      currentBlock = block;
      blockCount = 1;
    }
  }

  output.emplace_back(currentBlock.id, blockCount);
  return output;
}

World::Chunk::Chunk decompressChunk(const CompressedBlocks& blocks, const glm::vec2& pos)
{
  World::Chunk::Chunk output(pos);
  int blockPointer = 0;

  for (auto& block : blocks)
  {
    auto blockType = block.first;
    auto count = block.second;

    for (uint32_t i = 0; i < count; i++)
    {
      int x = blockPointer % CHUNK_SIZE;
      int y = blockPointer / CHUNK_AREA;
      int z = (blockPointer / CHUNK_SIZE) % CHUNK_SIZE;

      output.setBlock(x, y, z, blockType);
      blockPointer++;
    }
  }

  return output;
}

glm::vec3 toBlockPos(const glm::vec3& vec)
{
  auto x = static_cast<int>(floor(vec.x));
  auto y = static_cast<int>(floor(vec.y));
  auto z = static_cast<int>(floor(vec.z));
  return {x, y, z};
}

int main() {
  //float r = 9.0f, g = 139.0f, b = 244.0f;
  float r = 0.1f, g = 0.1f, b = 0.1f;

  // Init GLFW

  glfwInit();
  Clock c;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TerribleCraft", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to create window. You might not have the right OpenGL version installed." << '\n';
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize Glad (OpenGL)" << '\n';
    glfwTerminate();
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, resize_window_event);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(window, mouse_callback);

  // Setup OpenGL for rendering
  glEnable(GL_DEPTH_TEST);

  Renderer::SkyboxRenderer skybox;
  Renderer::ChunkRenderer chunkTest;

  for (int i = 0; i < CHUNK_VOLUME * 2; i++)
  {
    int x = i % CHUNK_SIZE;
    int y = i / CHUNK_AREA;
    int z = (i / CHUNK_SIZE) % CHUNK_SIZE;

    if (y <= (CHUNK_SIZE - 1))
    {
        sec.setBlock(x, y, z, World::Block::BlockType::DIRT);
    }

    if (y > (CHUNK_SIZE - 1))
    {
        int newY = heightAt(x, z, sec.getPosition().x, sec.getPosition().y);
        float baseLandHeight = CHUNK_SIZE + 2.0f + newY;

        World::Block::Block b;
        if (y <= baseLandHeight)
        {
            b = World::Block::BlockType::DIRT;

            if (y > baseLandHeight - 1)
                b = World::Block::BlockType::GRASS;
        }

        sec.setBlock(x, y, z, b);
    }
  }

  FPSCounter fpsCount;

  sec.makeMesh();
  Clock mDelay;

  // Game loop!
  while (!glfwWindowShouldClose(window)) {
    // Calculate the delta time
    float currentFrame = c.elapsed();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Process any input
    processInput(window);

    bool leftMouse  = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    bool rightMouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    Ray ray(cam.Position, cam.Front);
    for (; ray.getLength() < 8; ray.step())
    {
      auto rayBlockPos = toBlockPos(ray.getEnd());

      if (true)
      {
        if (mDelay.elapsed() > 0.1f)
        {
          mDelay.restart();
          if (leftMouse)
          {
            sec.setBlock(rayBlockPos.x, rayBlockPos.y, rayBlockPos.z, World::Block::BlockType::AIR);
          }

          if (rightMouse)
          {
            rayBlockPos = toBlockPos(ray.getLast());
            sec.setBlock(rayBlockPos.x, rayBlockPos.y, rayBlockPos.z, World::Block::BlockType::STONE);
          }
        }
      }
    }

    // Update the FPS count (not related to delta time calculation at all)
    fpsCount.update();
    glfwSetWindowTitle(window, ("TerribleCraft - FPS: " + std::to_string(fpsCount.fps)).c_str());

    // BUG: Remaking meshes takes up a lot of memory
    sec.deleteMeshes();
    sec.makeMesh();
    sec.draw(chunkTest);

    // Render

    // Clear the color and depth buffer every new render frame
    glClearColor(r / 255, g / 255, b / 255, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    chunkTest.render(cam);

    glDepthFunc(GL_LEQUAL);
    skybox.render(cam);
    glDepthFunc(GL_LESS);

    // GLFW: Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}