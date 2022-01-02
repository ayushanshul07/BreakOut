
#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "glm/ext/vector_float2.hpp"


class SpriteRenderer 
{
    public:
        SpriteRenderer(std::string shaderPath, std::string texturePath);
        ~SpriteRenderer();

        void Draw(glm::mat4 projection, glm::vec2 position,
                glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, 
                glm::vec3 color = glm::vec3(1.0f));

    private:
        Shader shader;
        Texture texture;
        VertexArray VAO;

        void initRenderData();
};

#endif
