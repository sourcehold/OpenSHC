#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040B660
        undefined4 BuildingsState::prepareCampgroundCoords(int playerID)
        {
            int campground = DAT_GameState::instance.playerDataArray[playerID].campground.id;
            if (campground <= 0) {
                return 0;
            }
            if (DAT_BuildingsState::instance.buildings[campground].orientation == 4) {
                this->DAT_TempXOffset = (short)DAT_BuildingsState::instance.buildings[campground].x + 3;
                this->DAT_TempYOffset = (short)DAT_BuildingsState::instance.buildings[campground].y + 5;
                return 1;
            }
            if (DAT_BuildingsState::instance.buildings[campground].orientation == 2) {
                this->DAT_TempXOffset = (short)DAT_BuildingsState::instance.buildings[campground].x + 1;
                this->DAT_TempYOffset = (short)DAT_BuildingsState::instance.buildings[campground].y + 3;
                return 1;
            }
            if (DAT_BuildingsState::instance.buildings[campground].orientation == 6) {
                this->DAT_TempXOffset = (short)DAT_BuildingsState::instance.buildings[campground].x + 5;
                this->DAT_TempYOffset = (short)DAT_BuildingsState::instance.buildings[campground].y + 3;
                return 1;
            }
            this->DAT_TempXOffset = (short)DAT_BuildingsState::instance.buildings[campground].x + 3;
            this->DAT_TempYOffset = (short)DAT_BuildingsState::instance.buildings[campground].y + 1;
            return 1;
        }

    }
}
}
