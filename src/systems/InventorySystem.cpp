//
// Created by armin on 16.01.19.
//

#include "InventorySystem.h"
#include "../events/CollisionEvent.h"
#include "../managers/ComponentsManager.h"

using namespace Systems;
InventorySystem::InventorySystem(Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {
    auto collisionCallback = [system = this](const std::shared_ptr<Events::Event> &pEvent){
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());

        if(event->mType == Events::collisionTypes::keyArea2){
            auto inventory = Managers::ComponentsManager::getInventory(event->mMovingEntity);
            auto canCollect = Managers::ComponentsManager::getCanCollect(event->mMovingEntity);
            if (inventory && canCollect) {
                if(canCollect->mTypes.find(Components::Inventory::ItemTypes::keyArea2) != canCollect->mTypes.end()) {
                    inventory->addItem(Components::Inventory::ItemTypes::keyArea2);
                    Managers::ComponentsManager::removeComponentsOfEntity(event->mCollidingEntity);
                }
            }

        }
    };
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, collisionCallback);
}