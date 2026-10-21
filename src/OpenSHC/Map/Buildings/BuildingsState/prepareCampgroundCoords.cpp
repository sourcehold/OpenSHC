#include "../BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B660
        undefined4 BuildingsState::prepareCampgroundCoords(int playerID)
        {
            int const campgroundID = DAT_GameState::instance.playerDataArray[playerID].campground.id;
            if (campgroundID <= 0) {
                return 0;
            }
            if (DAT_BuildingsState::instance.buildings[campgroundID].orientation == 4) {
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[campgroundID].x + 3;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[campgroundID].y + 5;
                return 1;
            }
            if (DAT_BuildingsState::instance.buildings[campgroundID].orientation == 2) {
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[campgroundID].x + 1;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[campgroundID].y + 3;
                return 1;
            }
            if (DAT_BuildingsState::instance.buildings[campgroundID].orientation == 6) {
                this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[campgroundID].x + 5;
                this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[campgroundID].y + 3;
                return 1;
            }
            this->DAT_TempXOffset = DAT_BuildingsState::instance.buildings[campgroundID].x + 3;
            this->DAT_TempYOffset = DAT_BuildingsState::instance.buildings[campgroundID].y + 1;
            return 1;
        }

    }
}
}
