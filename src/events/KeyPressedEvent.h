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

#ifndef GAME_KEYPRESSEDEVENT_H
#define GAME_KEYPRESSEDEVENT_H

#include <SDL_keycode.h>
#include <SDL_system.h>
#include "Event.h"
#include <vector>

namespace Events {
    class KeyPressedEvent:public Event {
    public:
       // KeyPressedEvent(int pCode, std::vector<Uint8> &&pKeys);
        KeyPressedEvent(int pCode, const std::vector<Uint8> &Keys);

        int mKeyCode;
        const std::vector<Uint8> mKeys;
    };
}


#endif //GAME_KEYPRESSEDEVENT_H
