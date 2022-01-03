
#include "SpriteRenderer.hpp"
#include "Texture.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

SpriteRenderer::SpriteRenderer()
{
    this->initRenderData();
}

SpriteRenderer* SpriteRenderer::instance = nullptr;

SpriteRenderer* SpriteRenderer::getInstance()
{
    if(instance) return instance;
    instance = new SpriteRenderer();
    return instance;
}

SpriteRenderer::~SpriteRenderer()
{
    
}

void SpriteRenderer::Draw(GameObject* game_object, glm::mat4 projection)
{
    game_object->texture->Bind();
    game_object->shader->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(game_object->Position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * game_object->Size.x, 0.5 * game_object->Size.y, 0.0f) );
    model = glm::rotate(model, glm::radians(game_object->Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * game_object->Size.x, -0.5 * game_object->Size.y, 0.0f) );

    model = glm::scale(model, glm::vec3(game_object->Size, 1.0f));

    game_object->shader->SetUniformMatrix4fv("model", glm::value_ptr(model));
    game_object->shader->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
    game_object->shader->SetUniform3f("spriteColor", game_object->Color.x, game_object->Color.y, game_object->Color.z);
    

    this->VAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void SpriteRenderer::initRenderData()
{
    float vertices[] = {

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,


        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    VertexBuffer VBO(vertices, sizeof(vertices));


    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 4);

    this->VAO.AddBuffer(VBO, layout);
        
    VBO.UnBind();
    this->VAO.UnBind();

}
