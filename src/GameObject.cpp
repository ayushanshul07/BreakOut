
#include "GameObject.hpp"


GameObject::GameObject(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader, glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity, float rotation):
    texture(std::move(texture)), shader(std::move(shader)) ,Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(rotation), Destroyed(false)
{


}
