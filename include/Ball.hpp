#ifndef BALL_HPP 
#define BALL_HPP

#include "GameObject.hpp"

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;

class Ball : public GameObject
{
    public:

    bool Stuck;
    float Radius;


    Ball( glm::vec2 pos, float radius, glm::vec3 color, glm::vec2 velocity, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);

    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(float dt, unsigned int window_width);
    // resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);

    void Draw(glm::mat4 projection) override;
};


#endif
