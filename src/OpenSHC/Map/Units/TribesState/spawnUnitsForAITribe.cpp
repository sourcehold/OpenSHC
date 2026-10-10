#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00522F70
        void TribesState::spawnUnitsForAITribe(
            undefined4 param_1, int param_2, int param_3, int param_4, UnitType param_5, int param_6, int param_7)
        {
            int microXPosition;
            UnitTypeShort UVar1;
            int unitID;
            int aiUnitBehaviourType;
            if (((0 < param_2) || (0 < param_3)) && 0 < param_6) {
                microXPosition = param_2 * 8;
                param_2 = param_6;
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        param_4, param_4, microXPosition, param_3 * 8, 8, param_5);
                    if (unitID) {
                        DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex = param_7;
                        UVar1 = DAT_UnitsState::instance.units[unitID].unitType;
                        if (UVar1 == Map::Units::UT_E_ARCHER || UVar1 == Map::Units::UT_E_XBOW
                            || UVar1 == Map::Units::UT_A_ARCHER || UVar1 == Map::Units::UT_A_SLINGER
                            || UVar1 == Map::Units::UT_A_HARCHER || UVar1 == Map::Units::UT_A_FIRETHROWER) {
                            aiUnitBehaviourType = 0x11;
                        } else {
                            aiUnitBehaviourType = 0x14;
                        }
                        MACRO_CALL_MEMBER(AI::AICState_Func::addUnitToItsTribe, DAT_AICState::ptr)(
                            unitID, aiUnitBehaviourType);
                    }
                    param_2 = param_2 + -1;
                } while (param_2);
            }
        }

    }
}
}
