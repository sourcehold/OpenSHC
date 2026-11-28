#include "../../Map.func.hpp"

#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;

    // FUNCTION: STRONGHOLDCRUSADER 0x0052DF30
    void WildlifeState::updateWildlife()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
            return;
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                this->grid[x][y].field_0x34 = 0;
                this->grid[x][y].field_0x50 = 0;
                this->grid[x][y].field_0x60 = 0;
                this->grid[x][y].field_0x64 = 0;
                this->grid[x][y].field_0x70 = this->grid[x][y].field_0x70 / 100;
                if (this->grid[x][y].chimps) {
                    if (this->grid[x][y].keeps) {
                        this->grid[x][y].field_0x60 = 1;
                    }
                    if (this->grid[x][y].castlebuildings) {
                        this->grid[x][y].field_0x60 = this->grid[x][y].field_0x60 + 1;
                    }
                }
            }
        }
        for (int y = 0; y < 40; y++) {
            for (int x = 0; x < 40; x++) {
                if (this->grid[x][y].unstalkedUnitCount) {
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillField13FromCell, this)(x, y, 2);
                } else if (this->grid[x][y].buildingTiles) {
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillField13FromCell, this)(x, y, 2);
                } else if (this->grid[x][y].lionCount) {
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillField13FromCell, this)(x, y, 3);
                }
                if (this->grid[x][y].farmFieldTiles) {
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::floodFillField20FromCell, this)(x, y, 6);
                }
            }
        }
    }

}
}
