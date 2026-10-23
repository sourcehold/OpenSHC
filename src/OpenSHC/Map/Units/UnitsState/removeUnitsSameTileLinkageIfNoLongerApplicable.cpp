#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F730
        void UnitsState::removeUnitsSameTileLinkageIfNoLongerApplicable()
        {
            if (DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow <= 0) {
                DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 0;
                return;
            }
            if (DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow < 100) {
                DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow
                    = DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow + 1;
                if (DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow >= 50) {
                    DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 0;
                }
                return;
            }
            DAT_GameState::instance.mapAndTime.multiplayerUnitSameTileLinkageTimeWindow = 0;
            for (int tile = 0; tile < 0x13a10; ++tile) {
                if ((short)DAT_TileMapState::instance.UnitLayer[tile] < 0
                    || (short)DAT_TileMapState::instance.UnitLayer[tile] > 2500) {
                    DAT_TileMapState::instance.UnitLayer[tile] = 0;
                    continue;
                }
                for (int unitID = (short)DAT_TileMapState::instance.UnitLayer[tile]; unitID != 0;
                    unitID = (short)this->units[unitID].nextUnitOnTheSameTile) {
                    if (this->units[unitID].tile != tile && this->units[unitID].usingTeleport == 0
                        && this->units[unitID].field303_0x413 == 0) {
                        DAT_TileMapState::instance.UnitLayer[tile] = this->units[unitID].nextUnitOnTheSameTile;
                        break;
                    }
                }
            }
        }

    }
}
}
