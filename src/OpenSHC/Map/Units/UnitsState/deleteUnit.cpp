#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053E790
        void UnitsState::deleteUnit(uint unitID)
        {
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::deselectUnit, DAT_UnitsState::ptr)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearOrDeselectUnitFromSelection, this)(
                DAT_UnitsState::instance.units[unitID].owner, unitID, 0);
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->units[unitID].owner] == -1
                && this->units[unitID].isStalked == 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updateUnitDeathHeatmapIn3SpacesAroundTile,
                    DAT_PathFindingState::ptr)(this->units[unitID].x, this->units[unitID].y);
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setupUnitSharingCurrentTilePosition, this)(unitID);
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x490, '\0', &this->units[unitID]);
        }

    }
}
}
