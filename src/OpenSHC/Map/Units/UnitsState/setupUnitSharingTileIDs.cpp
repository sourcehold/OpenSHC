#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052F440
        void UnitsState::setupUnitSharingTileIDs(int unitID, int unitCurrentTilePosition)
        {
            if (unitCurrentTilePosition == 0) {
                return;
            }
            this->units[unitID].unitOrderWhenOnSameTile = 0;
            if ((short)DAT_TileMapState::instance.UnitLayer[unitCurrentTilePosition] == unitID) {
                DAT_TileMapState::instance.UnitLayer[unitCurrentTilePosition]
                    = this->units[unitID].nextUnitOnTheSameTile;
                this->units[unitID].nextUnitOnTheSameTile = 0;
                return;
            }
            int _currentUnitID = (short)DAT_TileMapState::instance.UnitLayer[unitCurrentTilePosition];
            /* an empty tileUnk falls through and relinks unit 0 */
            int _previousUnitID = _currentUnitID;
            while (_currentUnitID != 0) {
                _previousUnitID = _currentUnitID;
                _currentUnitID = (short)this->units[_previousUnitID].nextUnitOnTheSameTile;
                if (_currentUnitID == unitID) {
                    break;
                }
                if (_currentUnitID == 0) {
                    return;
                }
            }
            this->units[_previousUnitID].nextUnitOnTheSameTile = this->units[unitID].nextUnitOnTheSameTile;
            this->units[unitID].nextUnitOnTheSameTile = 0;
        }

    }
}
}
