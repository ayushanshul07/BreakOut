
#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "GameObject.hpp"

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
        ~SpriteRenderer();

        static SpriteRenderer* getInstance();

        void Draw(GameObject* game_object, glm::mat4 projection);

    private:
        SpriteRenderer();
        VertexArray VAO;
        static SpriteRenderer* instance;
        void initRenderData();
};

#endif
