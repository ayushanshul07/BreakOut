#include <iostream>

#include "Game.hpp"
#include "GameLevel.hpp"
#include "SpriteRenderer.hpp"
#include "glm/fwd.hpp"

#include <memory>
#include <string>

SpriteRenderer *renderer;

Game::Game(unsigned int width, unsigned int height, unsigned int level = 0)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), Level(level),
      GameLevelPtr(new GameLevel(Level, width, height / 2)) {
  Init();
}

Game* Game::instance = nullptr;

Game* Game::getInstance()
{
    if(instance) return instance;
    instance = new Game(800,600);
    return instance;
}

Game::~Game() { delete renderer; }

void Game::Init() {
std::string shaderPath = "../assets/shaders/";
#ifdef __EMSCRIPTEN__
  shaderPath += "web/";
#endif
  std::shared_ptr<Shader> common_shader(
      new Shader(shaderPath + "BasicShader.shader"));

  std::shared_ptr<Texture> paddle_texture(
      new Texture("../assets/textures/paddle.png"));
  glm::vec2 pos = glm::vec2(Width / 2.0f - PADDLE_SIZE.x / 2.0f,
                            Height - PADDLE_SIZE.y);
  Player = std::unique_ptr<Paddle>(new Paddle(pos, PADDLE_SIZE, glm::vec3(1.0f), common_shader, paddle_texture));


glm::vec2 ballPos = pos + glm::vec2(PADDLE_SIZE.x / 2.0f - BALL_RADIUS, 
                                              -BALL_RADIUS * 2.0f);
std::shared_ptr<Texture> ball_texture(
      new Texture("../assets/textures/awesomeface.png"));
Sponge = std::unique_ptr<Ball>(new Ball(ballPos, BALL_RADIUS, glm::vec3(1.0f), INITIAL_BALL_VELOCITY, common_shader, ball_texture));

}



void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PADDLE_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f)
            {
                Player->Position.x -= velocity;
                if (Sponge->Stuck)
                    Sponge->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x)
            {
                Player->Position.x += velocity;
                if (Sponge->Stuck)
                    Sponge->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            Sponge->Stuck = false;
    }
}


void Game::Update(float dt)
{

    Sponge->Move(dt, this->Width);
}

void Game::Render() {

  glm::mat4 projection =
      glm::ortho(0.0f, static_cast<float>(this->Width),
                 static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

  GameLevelPtr->Draw(projection);
  Player->Draw(projection);
  Sponge->Draw(projection);
}
