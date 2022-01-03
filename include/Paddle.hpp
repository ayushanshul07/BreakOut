#ifndef PADDLE_HPP 
#define PADDLE_HPP

#include "GameObject.hpp"

// Initial size of the player paddle
const glm::vec2 PADDLE_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PADDLE_VELOCITY(500.0f);

class Paddle : public GameObject
{
    public:

    Paddle(glm::vec2 pos, glm::vec2 size, glm::vec3 color,
         std::shared_ptr<Shader> shader,
        std::shared_ptr<Texture> texture);

    void Draw(glm::mat4 projection) override;

};


#endif
