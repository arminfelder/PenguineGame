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

#ifndef GAME_SPATIALCOMPONENT_H
#define GAME_SPATIALCOMPONENT_H

#include <iosfwd>
#include <vector>

namespace Components {
    class SpatialComponent {
    public:
        SpatialComponent(int pPositionX, int pPositionY,bool pMoveWithMap = true);
        int mPositionX;
        int mPositionY;

        int mPrevPositionX = 0;
        int mPrevPositionY = 0;

        bool moveWithMap = true;
        std::string serialize();
        bool load(std::vector<std::string> splittedStrings);

    };
}


#endif //GAME_SPATIALCOMPONENT_H
