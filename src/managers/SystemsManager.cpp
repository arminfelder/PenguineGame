//
// Created by armin on 20.12.18.
//

#include "SystemsManager.h"

using namespace Managers;
using namespace Systems;

SystemsManager::SystemsManager(SDL_Window *pWindow, SDL_Renderer *pPrenderer, EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    mHealthSystem = new HealthSystem(pEventsManager);
    mPositionSystem = new PositionSystem(pEventsManager);
    mInputSystem = new InputSystem(pEventsManager);
    mCollisionSystem = new CollisionSystem(pEventsManager);

    mRenderSystem = new RenderSystem(pWindow,pPrenderer,pEventsManager);
}

void SystemsManager::sendEvent() {

}

HealthSystem *SystemsManager::getMHealthSystem() const {
    return mHealthSystem;
}

RenderSystem *SystemsManager::getMRenderSystem() const {
    return mRenderSystem;
}

void SystemsManager::update(float pTimeDiff) {
    mInputSystem->update();
    mEventsManager->dispatch();
    mRenderSystem->update(pTimeDiff);
}