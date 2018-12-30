//
// Created by armin on 29.12.18.
//

#include "PositionSystem.h"
#include "../events/KeyPressedEvent.h"
#include "../events/EntityMoved.h"
#include "../managers/ComponentsManager.h"
#include "../events/CollisionEvent.h"

Systems::PositionSystem::PositionSystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    std::function<void(const std::shared_ptr<Events::Event>&)> callback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::KeyUpEvent*>(pEvent.get());
        auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
        auto moveable = Managers::ComponentsManager::getMoveableComponent(1);

        switch (event->mKeyCode.sym){
            case SDLK_UP:
                if(moveable->canMoveUp) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionY -= 10;
                    system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1));
                }
                break;
            case SDLK_RIGHT:
                if(moveable->canMoveRight) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionX += 10;
                    system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1));
                }
                break;
            case SDLK_DOWN:
                if(moveable->canMoveDown) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionY += 10;
                    system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1));
                }
                break;
            case SDLK_LEFT:
                if(moveable->canMoveLeft) {
                    playerSpatial->mPrevPositionX = playerSpatial->mPositionX;
                    playerSpatial->mPrevPositionY = playerSpatial->mPositionY;
                    playerSpatial->mPositionX -= 10;
                    system->mEventsManager->addEvent(std::make_shared<Events::EntityMoved>(1));
                }
                break;
            default:
                break;
        }

    };

    std::function<void(const std::shared_ptr<Events::Event>&)> callbackCollision = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void {
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());
        if(event->mType == Events::collisionTypes::regular){
            int entity = event->mMovingEntity;
            auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(entity);
            playerSpatial->mPositionX = playerSpatial->mPrevPositionX;
            playerSpatial->mPositionY = playerSpatial->mPrevPositionY;
        }
    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::Input, callback );
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, callbackCollision);
}