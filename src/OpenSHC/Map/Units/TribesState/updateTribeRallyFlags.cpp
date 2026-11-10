#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523F70
        BOOLEnum TribesState::updateTribeRallyFlags(int tribeID)
        {
            int unitSelectionIndex = 0;
            BOOLEnum _anyRallying = FALSE;
            while (unitSelectionIndex < this->tribes[tribeID].size) {
                int const _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                    tribeID, unitSelectionIndex);
                unitSelectionIndex = unitSelectionIndex + 1;
                if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                    && !DAT_UnitsState::instance.units[_unitID].dying) {
                    short const _isRallying = DAT_UnitsState::instance.units[_unitID].goToRallyPoint;
                    DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 0;
                    if (_isRallying != 0 || DAT_UnitsState::instance.units[_unitID].isSelectable_OR_matchTime == 0) {
                        _anyRallying = TRUE;
                        DAT_UnitsState::instance.units[_unitID].rallyRelatedFlag = 1;
                    }
                }
            }
            return _anyRallying;
        }

    }
}
}
