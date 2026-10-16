#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C470
        void TroopValueState::queueOilThrowForIdleArchers()
        {
            BOOLEnum BVar1;
            int iVar2;
            short* psVar3;
            int iVar4;
            iVar4 = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                psVar3 = &DAT_UnitsState::instance.units[1].owner;
                do {
                    if ((((psVar3[-5] != Map::Units::ULS_INVISIBLE)
                             && (BVar1 = MACRO_CALL_MEMBER(
                                     Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)((int)*psVar3),
                                 BVar1))
                            && (psVar3[-4] == Map::Units::UT_E_ENGINEER))
                        && ((psVar3[0x105] == 0
                            && (((UnitStateUnion*)(psVar3 + 0x115))->generic == Map::Units::States::US_SIT_DOWNUnk)))) {
                        iVar2 = 3;
                        if (0x6e < psVar3[0x12]) {
                            iVar2 = 5;
                        }
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::computeTotalUnitsWithinDistance,
                            DAT_PathFindingState::ptr)(
                            this->attackInfo.pitchRelatedPlayerID, 0, 0, (int)((int)(*(int*)(psVar3 + 0x1f))), iVar2);
                        iVar2 = DAT_PathFindingState::instance.field34_0x64;
                        if (((9 < DAT_PathFindingState::instance.ALGO_TotalTroopValue)
                                && (1 < DAT_PathFindingState::instance.ALGO_TotalTroopCount))
                            && (DAT_PathFindingState::instance.field34_0x64)) {
                            psVar3[0x183] = Map::Units::UIT_THROW_OIL;
                            psVar3[0x1a9] = DAT_UnitsState::instance.units[iVar2].x;
                            psVar3[0x1aa] = DAT_UnitsState::instance.units[iVar2].y;
                            *(int*)(psVar3 + -0x27) = 4;
                        }
                    }
                    iVar4 = iVar4 + 1;
                    psVar3 = psVar3 + 0x248;
                } while (iVar4 < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
