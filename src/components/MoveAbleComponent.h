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

#ifndef GAME_MOVEABLECOMPONENT_H
#define GAME_MOVEABLECOMPONENT_H

#include <string>
#include <vector>
#include "Component.h"

namespace Components {
    class MoveAbleComponent:public Component {
    public:
        MoveAbleComponent();
        MoveAbleComponent(bool pRight, bool pDown, bool pLeft, bool pTop);

        bool canMoveLeft = false;
        bool canMoveRight = false;
        bool canMoveDown = false;
        bool canMoveUp = false;
        bool climbing = false;
        bool canDoubleJump = false;
        bool doubleJumpUsed = false;

        std::string serialize();
        bool load(std::vector<std::string> splittedStrings);

    };
}


#endif //GAME_MOVEABLECOMPONENT_H
