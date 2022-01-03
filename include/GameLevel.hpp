#ifndef GAMELEVEL_HPP
#define GAMELEVEL_HPP

#include "GameObject.hpp"
#include "SpriteRenderer.hpp"

#include <memory>
#include <vector>
class GameLevel {

public:
  std::vector<std::unique_ptr<GameObject>> objects;

  GameLevel(unsigned int level, unsigned int width, unsigned int height);


  bool IsComplete();
  void Draw(glm::mat4 projection);

private:
  void Init(std::vector<std::vector<unsigned int>> tileData,
            unsigned int level_width, unsigned int level_height);
  void Load(const char *file, unsigned int level_width,
            unsigned int level_height);
};

#endif
