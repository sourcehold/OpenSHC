#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00533810
        int UnitsState::findAndDestroyAdjacentEnemyLadder(int unitID, int checkOnly)
        {
            for (int direction = 0; direction < 8; ++direction) {
                int _otherUnitID = DAT_TileMapState::instance
                                       .UnitLayer[DAT_TileMapState::instance
                                                      .directionTranslationMatrix[this->units[unitID].y][direction]
                                           + this->units[unitID].tile];
                // the original tests the head of the tile list against 0, and the following links against > 0
                if (_otherUnitID == 0) {
                    continue;
                }
                int const owner = this->units[unitID].owner;
                while (true) {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[owner]
                            != DAT_GameState::instance.mapAndTime.playerTeams[this->units[_otherUnitID].owner]
                        && owner != 0 && this->units[_otherUnitID].unitType == OpenSHC::Map::Units::UT_E_LADDER
                        && this->units[_otherUnitID].state.generic == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                        if (checkOnly != 0) {
                            return direction;
                        }
                        this->units[_otherUnitID].dying = 1;
                        this->units[_otherUnitID].animationCycleNumber = 0;
                        this->units[_otherUnitID].state.generic = OpenSHC::Map::Units::States::US_DEATH_02;
                        this->units[_otherUnitID].tunnelerFinishedDigging = 1;
                        return 1;
                    }
                    _otherUnitID = this->units[_otherUnitID].nextUnitOnTheSameTile;
                    if (_otherUnitID <= 0) {
                        break;
                    }
                }
            }
            return -1;
        }

    }
}
}
