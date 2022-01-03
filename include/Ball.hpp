#ifndef BALL_HPP 
#define BALL_HPP

#include "GameObject.hpp"

class Ball : public GameObject
{

    Ball(Texture* texture, Shader* shader);

    void Draw(glm::mat4 projection) override;

};


#endif
