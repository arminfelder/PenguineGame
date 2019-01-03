//
// Created by armin on 30.12.18.
//

#include <fstream>
#include <iostream>
#include "MapParser.h"
#include "entities/MovementReset.h"
#include "entities/LadderEnd.h"
#include "entities/LadderBegin.h"
#include "entities/HealthIndicator.h"


using namespace Entities;


int MapParser::createWorldFormMapTXT(const std::string &pMapfile, GameEngine *pEngine, SDL_Renderer *pRenderer ) {


    std::shared_ptr<SDL_Surface> imageWall(SDL_LoadBMP("./res/brick-wall.bmp"), SDL_FreeSurface) ;
    std::shared_ptr<SDL_Texture> textureWall(SDL_CreateTextureFromSurface(pRenderer, imageWall.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imagePlayer(SDL_LoadBMP("./res/hello.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> texturePlayer(SDL_CreateTextureFromSurface(pRenderer, imagePlayer.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageLadder(SDL_LoadBMP("./res/ladder.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureLadder(SDL_CreateTextureFromSurface(pRenderer, imageLadder.get()), SDL_DestroyTexture);

    std::shared_ptr<SDL_Surface> imageInvisible(SDL_LoadBMP("./res/invisible.bmp"), SDL_FreeSurface);
    std::shared_ptr<SDL_Texture> textureInvisible(SDL_CreateTextureFromSurface(pRenderer, imageInvisible.get()), SDL_DestroyTexture);


    //initial health text
    std::shared_ptr<TTF_Font> Sans(TTF_OpenFont("./res/sans.ttf", 24),TTF_CloseFont);
    SDL_Color White = {255, 255, 255, 255};
    std::shared_ptr<SDL_Surface> healthMessage(TTF_RenderText_Blended(Sans.get(), "100", White), SDL_FreeSurface);
    auto healthMessageTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, healthMessage.get()), SDL_DestroyTexture);

    //health indicator
    int id = Managers::EntityManager::createEntity<HealthIndicator>();
    Managers::ComponentsManager::createSpatialComponent(id, 20, 20);
    Managers::ComponentsManager::createVisualComponent(id,healthMessageTexture, 100,50);

    std::ifstream map;
    map.open(pMapfile);

    int line = 0;
    while(!map.eof()) {
        std::string currentLine;
        getline(map, currentLine);
        for (int i = 0; i < (int) currentLine.length(); i++) {

            int x = i*50;
            int y = line*50;
            //Defines entities given on the input from map file
            switch (currentLine[i]) {
                case '#': {
                    int id = Managers::EntityManager::createEntity<Wall>();
                    Managers::ComponentsManager::createVisualComponent(id, textureWall, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case 'p': {
                    int id = 1;
                    Managers::ComponentsManager::createVisualComponent(id, texturePlayer, 48, 48);
                    Managers::ComponentsManager::createSpatialComponent(id, x+1, y+1);
                    Managers::ComponentsManager::createMoveAbleComponent(id,true,false,true,false );
                    Managers::ComponentsManager::createHealthComponent(id,100);
                    break;
                }
                case '|': {
                    int id = Managers::EntityManager::createEntity<Ladder>();
                    Managers::ComponentsManager::createVisualComponent(id, textureLadder, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '=':{
                    int id = Managers::EntityManager::createEntity<MovementReset>();
                    Managers::ComponentsManager::createVisualComponent(id, textureInvisible, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case '-':{
                    int id = Managers::EntityManager::createEntity<LadderEnd>();
                    Managers::ComponentsManager::createVisualComponent(id, textureInvisible, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                case ':':{
                    int id = Managers::EntityManager::createEntity<LadderBegin>();
                    Managers::ComponentsManager::createVisualComponent(id, textureLadder, 50, 50);
                    Managers::ComponentsManager::createSpatialComponent(id, x, y);
                    Managers::ComponentsManager::createCollideAbleComponent(id);
                    break;
                }
                default:
                    break;
            }
        }
        line++;



    }

    return 0;
}

