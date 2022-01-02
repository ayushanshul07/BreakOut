
#include "SpriteRenderer.hpp"
#include "glm/gtc/type_ptr.hpp"

SpriteRenderer::SpriteRenderer(Shader* shader, Texture* texture)
{
    this->shader = shader;
    this->texture = texture;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    
}

void SpriteRenderer::Draw(glm::mat4 projection, glm::vec2 position,
        glm::vec2 size, float rotate, glm::vec3 color)
{
    this->shader->Bind();
    this->texture->Bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5* size.y, 0.0f) );
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader->SetUniformMatrix4fv("model", glm::value_ptr(model));
    this->shader->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
    this->shader->SetUniform3f("spriteColor", color.x, color.y, color.z);
    

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
