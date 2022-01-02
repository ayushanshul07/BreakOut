
#include "Game.hpp"
#include "SpriteRenderer.hpp"

#include <string>

SpriteRenderer *renderer;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {}

Game::~Game() { delete renderer; }

void Game::Init() {
  std::string shaderPath = "../assets/shaders/";
#ifdef __EMSCRIPTEN__
  shaderPath += "web/";
#endif
  renderer =
      new SpriteRenderer(new Shader(shaderPath + "BasicShader.shader"),
                         new Texture("../assets/textures/awesomeface.png"));
}

void Game::ProcessInput(float dt) {}

void Game::Update(float dt) {}

void Game::Render() {
  glm::mat4 projection =
      glm::ortho(0.0f, static_cast<float>(this->Width),
                 static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

  renderer->Draw(projection, glm::vec2(200.0f, 200.0f),
                 glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
