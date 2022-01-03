

#ifndef Game_hpp
#define Game_hpp

#include <memory>

#include "GameLevel.hpp"
#include "Paddle.hpp"
#include "Brick.hpp"
#include "Ball.hpp"

#include <GLFW/glfw3.h>

enum GameState{
  GAME_ACTIVE,
  GAME_MENU,
  GAME_WIN
};

class Game
{

    private:
        Game(unsigned int width, unsigned int height, unsigned int level);
        static Game* instance;
    public:
        GameState State;
        bool Keys[1024];
        static Game* getInstance();
        unsigned int Level;
        unsigned int Width, Height;
        std::unique_ptr<GameLevel> GameLevelPtr;
        std::unique_ptr<Paddle> Player;
        std::unique_ptr<Ball> Sponge;

        ~Game();

        void Init();

        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};



#endif
