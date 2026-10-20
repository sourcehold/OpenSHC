#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522EF0
        void TribesState::trimTribeToSize(undefined4 tribeID, int smallerSize)
        {
            UnitLogicStateShort* pUVar1;
            UnitLogicStateShort UVar2;
            int iVar3;
            int unitSelectionIndex;
            int _currentTribeID;
            _currentTribeID = DAT_CurrentTribeID::instance;
            unitSelectionIndex = 0;
            if (this->tribes[DAT_CurrentTribeID::instance].tribeState != 0
                && (iVar3 = (int)this->tribes[DAT_CurrentTribeID::instance].size, iVar3 >= smallerSize) && 0 < iVar3) {
                do {
                    iVar3 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getUnitIDForIndexInTribe, this)(
                        _currentTribeID, unitSelectionIndex);
                    pUVar1 = &DAT_UnitsState::instance.units[iVar3].logicalState;
                    UVar2 = *pUVar1;
                    unitSelectionIndex = unitSelectionIndex + 1;
                    if ((((UVar2 == ((UnitLogicState)1)) || (UVar2 == Map::Units::ULS_NORMAL))
                            || (UVar2 == Map::Units::ULS_TRANSITIONING))
                        && smallerSize <= unitSelectionIndex) {
                        *pUVar1 = Map::Units::ULS_REMOVE;
                    }
                } while (unitSelectionIndex < this->tribes[_currentTribeID].size);
            }
        }

    }
}
}
