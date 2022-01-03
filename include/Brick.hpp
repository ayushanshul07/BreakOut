#ifndef BRICK_HPP
#define BRICK_HPP

#include "GameObject.hpp"

class Brick : public GameObject
{
    public:
  Brick(glm::vec2 pos, glm::vec2 size, glm::vec3 color,
         std::shared_ptr<Shader> shader,
        std::shared_ptr<Texture> texture);

  void Draw(glm::mat4 projection) override;
};

#endif
