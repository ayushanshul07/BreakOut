#include <iostream>

#include "Paddle.hpp"
#include "SpriteRenderer.hpp"

#include "Texture.hpp"
#include <memory>

Paddle::Paddle(glm::vec2 pos, glm::vec2 size, glm::vec3 color, std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
:GameObject(texture, shader, pos, size, color, glm::vec2(PADDLE_VELOCITY, 0.0f), 0.0f)
{

}

void Paddle::Draw(glm::mat4 projection) 
{

    SpriteRenderer::getInstance()->Draw(this, projection);
}
