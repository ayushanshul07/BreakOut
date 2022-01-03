#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Texture.hpp"

#include "glm/fwd.hpp"
#include "glm/glm.hpp"

class GameObject 
{

    public:
        glm::vec2 Position, Size, Velocity;
        glm::vec3 Color;
        float Rotation;
        bool isSolid;
        bool destroyed;
        glm::mat4 model;

        std::shared_ptr<Texture> texture;
        std::shared_ptr<Shader> shader;


        GameObject(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader, glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), float Rotation = 0.0f);
   
        virtual ~GameObject(){};
        virtual void Draw(glm::mat4 projection) = 0;


};

#endif
