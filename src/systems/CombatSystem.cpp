/******************************************************************************
* Copyright (C) Mario Löscher, Armin Felder
* This file is part of PenguinGame <https://git.felder-edv.at/uibkcpp18/game>.
*
* PenguinGame is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* PenguinGame is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PenguinGame. If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/


#include <iostream>
#include "CombatSystem.h"
#include "../events/KeyDownEvent.h"
#include "../managers/ComponentsManager.h"
#include "../managers/EntityManager.h"
#include "../entities/Projectile.h"
#include "../events/CollisionEvent.h"
#include "../events/HealthEvent.h"
#include "../events/EntityCanSee.h"

Systems::CombatSystem::CombatSystem(SDL_Renderer *pRenderer,Managers::EventsManager *pEventsManager):mEventsManager(pEventsManager) {

    auto attackCallback = [system=this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::KeyDownEvent*>(pEvent.get());
        if(event->mKeyCode.sym == SDLK_LCTRL){
            auto playerSpatial = Managers::ComponentsManager::getSpatialComponent(1);
            auto playerVisual = Managers::ComponentsManager::getVisualComponent(1);
            int moveX = 200;
            if(playerVisual->mFlip){
                moveX *= -1;
            }
            int test = (playerVisual->mImageRect.w)+1;
            test = test*playerVisual->mFlip?-1:1;
            int x = playerSpatial->mPositionX+(((playerVisual->mImageRect.w)+1)*(playerVisual->mFlip?-1:1));
            int y = playerSpatial->mPositionY+(playerVisual->mImageRect.h/2);

            int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
            Managers::ComponentsManager::createVisualComponent(bulletId,system->mBlueBullet, 10,5);
            Managers::ComponentsManager::createSpatialComponent(bulletId,x,y);
            Managers::ComponentsManager::createPathComponent(bulletId,{SDL_Point{moveX,0}},15);
            Managers::ComponentsManager::createDamageComponent(bulletId,10);
            Managers::ComponentsManager::createTimeToLive(bulletId, 500);
        }
    };

    auto bulletCollisionCallback = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::CollisionEvent*>(pEvent.get());
        if(event->mType == Events::collisionTypes::npc||event->mType == Events::collisionTypes::player){
            auto damage = Managers::ComponentsManager::getDamage(event->mMovingEntity);
            if(damage) {
                system->mEventsManager->addEvent(std::make_shared<Events::HealthEvent>(event->mCollidingEntity,-damage->mDamage));
                Managers::ComponentsManager::removeComponentsOfEntity(event->mMovingEntity);
                std::cout << "bullet coll" << std::endl;
            }
        }

    };

    auto canSeeEnemy = [system = this](const std::shared_ptr<Events::Event> &pEvent)->void{
        auto event = static_cast<Events::EntityCanSee*>(pEvent.get());
        auto path = Managers::ComponentsManager::getPaths(event->mSeeingEntity);
        path->mPaused = true;

        auto enemySpatial = Managers::ComponentsManager::getSpatialComponent(event->mSeenEntity);

        auto entitySpatial = Managers::ComponentsManager::getSpatialComponent(event->mSeeingEntity);
        auto entityVisual = Managers::ComponentsManager::getVisualComponent(event->mSeeingEntity);
        int moveX = 200;
        bool flip = false;
        if(enemySpatial->mPositionX < entitySpatial->mPositionX){
            moveX *= -1;
            flip = true;
        }
        int x = entitySpatial->mPositionX+(((entityVisual->mImageRect.w)+1)*(flip?-1:1));
        int y = entitySpatial->mPositionY+(entityVisual->mImageRect.h/2);

        int bulletId = Managers::EntityManager::createEntity<Entities::Projectile>();
        Managers::ComponentsManager::createVisualComponent(bulletId,system->mBlueBullet, 10,5);
        Managers::ComponentsManager::createSpatialComponent(bulletId,x,y);
        Managers::ComponentsManager::createPathComponent(bulletId,{SDL_Point{moveX,0}},15);
        Managers::ComponentsManager::createDamageComponent(bulletId,10);
        Managers::ComponentsManager::createTimeToLive(bulletId, 500);
    };

    mEventsManager->regsiterEventHandler(Events::EventTypes::KePressed ,attackCallback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::Collision, bulletCollisionCallback);
    mEventsManager->regsiterEventHandler(Events::EventTypes::EntityCanSee, canSeeEnemy);
    std::shared_ptr<SDL_Surface> imageBlueBullet(SDL_LoadBMP("./res/new_bullet.bmp"), SDL_FreeSurface);
    mBlueBullet = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(pRenderer, imageBlueBullet.get()), SDL_DestroyTexture);

}