#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005250B0
        BOOLEnum TribesState::anyUnitsOfTribeAreOutsideCoverageOfPathFindingAlg(int tribeID, int algTileFlag)
        {
            int _unitID;
            int iVar1 = (int)this->tribes[tribeID].size;
            int unitSelectionIndex = 0;
            if (0 < iVar1) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        tribeID, unitSelectionIndex);
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[_unitID].dying == 0
                        && DAT_TileMapState::instance.WalkLayer[DAT_UnitsState::instance.units[_unitID].tile]
                            != algTileFlag) {
                        return FALSE;
                    }
                } while (unitSelectionIndex < iVar1);
            }
            return TRUE;
        }

    }
}
}
