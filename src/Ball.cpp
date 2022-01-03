#include <iostream>

#include "Ball.hpp"
#include "SpriteRenderer.hpp"

#include "Texture.hpp"
#include "glm/fwd.hpp"
#include <memory>

Ball::Ball(glm::vec2 pos, float radius, glm::vec3 color, glm::vec2 velocity, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
:GameObject(texture, shader, pos, glm::vec2(2*BALL_RADIUS,2*BALL_RADIUS), color, velocity, 0.0f), Stuck(true), Radius(BALL_RADIUS)
{

}

void Ball::Draw(glm::mat4 projection) 
{

    SpriteRenderer::getInstance()->Draw(this, projection);
}

glm::vec2 Ball::Move(float dt, unsigned int window_width)
{
    // if not stuck to player board
    if (!this->Stuck)
    {
        // move the ball
        this->Position += this->Velocity * dt;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
    return this->Position;
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void Ball::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}
