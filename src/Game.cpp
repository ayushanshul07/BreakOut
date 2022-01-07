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
    this->DoCollisions();
    if (Sponge->Position.y >= this->Height) // did ball reach bottom edge?
    {
        this->ResetLevel();
        this->ResetPlayer();
    }
}

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
typedef std::tuple<bool, Direction, glm::vec2> Collision;

Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}    


Collision CheckCollision(Ball *one, GameObject *two) // AABB - Circle collision
{
    // get center point circle first 
    glm::vec2 center(one->Position + one->Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two->Size.x / 2.0f, two->Size.y / 2.0f);
    glm::vec2 aabb_center(
        two->Position.x + aabb_half_extents.x, 
        two->Position.y + aabb_half_extents.y
    );
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    if (glm::length(difference) <= one->Radius)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
} 


void Game::DoCollisions()
{
    int len = this->GameLevelPtr->objects.size();
    for(int i = 0; i < len; ++i)
    {
        if(!this->GameLevelPtr->objects[i]->Destroyed){
            Collision collision = CheckCollision(this->Sponge.get(), this->GameLevelPtr->objects[i].get());
            if (std::get<0>(collision)) // if collision is true
            {
                // destroy block if not solid
                if (!this->GameLevelPtr->objects[i]->isSolid)
                    this->GameLevelPtr->objects[i]->Destroyed = true;
                // collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // horizontal collision
                {
                    this->Sponge->Velocity.x = -this->Sponge->Velocity.x; // reverse horizontal velocity
                    // relocate
                    float penetration = this->Sponge->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        this->Sponge->Position.x += penetration; // move ball to right
                    else
                        this->Sponge->Position.x -= penetration; // move ball to left;
                }
                else // vertical collision
                {
                    this->Sponge->Velocity.y = -this->Sponge->Velocity.y; // reverse vertical velocity
                    // relocate
                    float penetration = this->Sponge->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        this->Sponge->Position.y -= penetration; // move ball back up
                    else
                        this->Sponge->Position.y += penetration; // move ball back down
                }
            }
        }
    }

    Collision result = CheckCollision(this->Sponge.get(), this->Player.get());
    if (!this->Sponge->Stuck && std::get<0>(result))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
        float distance = (Sponge->Position.x + Sponge->Radius) - centerBoard;
        float percentage = distance / (Player->Size.x / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        glm::vec2 oldVelocity = Sponge->Velocity;
        Sponge->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength; 
        //Sponge->Velocity.y = -Sponge->Velocity.y;
        Sponge->Velocity.y = -1.0f * abs(Sponge->Velocity.y);
        Sponge->Velocity = glm::normalize(Sponge->Velocity) * glm::length(oldVelocity);
    }
}

void Game::Render() {

  glm::mat4 projection =
      glm::ortho(0.0f, static_cast<float>(this->Width),
                 static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

  GameLevelPtr->Draw(projection);
  Player->Draw(projection);
  Sponge->Draw(projection);
}


void Game::ResetLevel()
{
    GameLevelPtr.reset(new GameLevel(Level, Width, Height/2));
}

void Game::ResetPlayer()
{

    glm::vec2 pos = glm::vec2(Width / 2.0f - PADDLE_SIZE.x / 2.0f,
                            Height - PADDLE_SIZE.y);

    Player.reset(new Paddle(pos, PADDLE_SIZE, glm::vec3(1.0f), Player->shader , Player->texture));

    glm::vec2 ballPos = pos + glm::vec2(PADDLE_SIZE.x / 2.0f - BALL_RADIUS, 
                                              -BALL_RADIUS * 2.0f);
    Sponge.reset(new Ball(ballPos, BALL_RADIUS, glm::vec3(1.0f), INITIAL_BALL_VELOCITY, Sponge->shader, Sponge->texture));
}
