#define GL_SILENCE_DEPRECATION

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Game.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

Game Breakout(SCR_WIDTH, SCR_HEIGHT);
void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode) {
  // when a user presses the escape key, we set the WindowShouldClose property
  // to true, closing the application
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (key >= 0 && key < 1024) {
    if (action == GLFW_PRESS)
      Breakout.Keys[key] = true;
    else if (action == GLFW_RELEASE)
      Breakout.Keys[key] = false;
  }
}

std::function<void()> loop;
void main_loop() { loop(); }

int main(void) {

  if (!glfwInit()) {
    std::cout << "Unable to init glfw\n";
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Breakout", nullptr, nullptr);
  if (!window) {
    std::cout << "Failed to create GLFW Window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    std::cout << "Unable to init glew\n";
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Breakout.Init();

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  loop = [&] {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    Breakout.ProcessInput(deltaTime);

    Breakout.Update(deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  };

#ifdef __EMSCRIPTEN__ /* Loop until the user closes the window */
  emscripten_set_main_loop(main_loop, 0, true);
#else
  while (!glfwWindowShouldClose(window)) {
    loop();
  }
#endif

  glfwTerminate();
  return 0;
}
