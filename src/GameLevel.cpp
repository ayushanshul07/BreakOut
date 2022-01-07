#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>

#include "GameLevel.hpp"
#include "Texture.hpp"
#include "Brick.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"

#include "glm/ext/vector_float2.hpp"
#include "glm/fwd.hpp"

GameLevel::GameLevel(unsigned int level, unsigned int width, unsigned int height)
{
    std::string levelPath("../assets/levels/level0.txt");
    Load(levelPath.c_str(), width, height);
}

void GameLevel::Load(const char *file, unsigned int level_width, unsigned int level_height)
{
    this->objects.clear();
    unsigned int tileCode;
    
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->Init(tileData, level_width, level_height);
    }
}


void GameLevel::Init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size();
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / static_cast<float>(height); 
    // initialize level tiles based on tileData	
    std::string shaderPath = "../assets/shaders/";
#ifdef __EMSCRIPTEN__
  shaderPath += "web/";
#endif

    std::shared_ptr<Shader> common_shader(new Shader(shaderPath + "BasicShader.shader"));

    std::shared_ptr<Texture> solid_brick(new Texture("../assets/textures/brick_solid.png"));
    std::shared_ptr<Texture> breakable_brick(new Texture("../assets/textures/brick.png"));
    
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // solid
            {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                
                std::unique_ptr<Brick> brickp(new Brick(pos, size,glm::vec3(0.8f,0.8f,0.7f), common_shader,solid_brick));
                brickp->isSolid = true;
                (this->objects).push_back(std::move(brickp));
            }
            else if (tileData[y][x] > 1)	// non-solid; now determine its color based on level data
            {
                glm::vec3 color = glm::vec3(1.0f); // original: white
                if (tileData[y][x] == 2)
                    color = glm::vec3(0.2f, 0.6f, 1.0f);
                else if (tileData[y][x] == 3)
                    color = glm::vec3(0.0f, 0.7f, 0.0f);
                else if (tileData[y][x] == 4)
                    color = glm::vec3(0.8f, 0.8f, 0.4f);
                else if (tileData[y][x] == 5)
                    color = glm::vec3(1.0f, 0.5f, 0.0f);

                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                std::unique_ptr<Brick> brickp(new Brick(pos, size, color, common_shader, breakable_brick));
                brickp->isSolid = false;
                this->objects.push_back(std::move(brickp));
            }
        }
    }

    std::shared_ptr<Texture> paddle_texture(new Texture("../assets/textures/paddle.png"));
    glm::vec2 pos =  glm::vec2(levelWidth / 2.0f - PADDLE_SIZE.x / 2.0f, 2 * levelHeight - PADDLE_SIZE.y);
    std::unique_ptr<Paddle> paddlep(new Paddle(pos, PADDLE_SIZE, glm::vec3(1.0f), common_shader, paddle_texture));

}

void GameLevel::Draw(glm::mat4 projection)
{

    for(int i = 0; i < objects.size(); ++i){
        if(!objects[i]->Destroyed) objects[i]->Draw(projection);
    }

}
