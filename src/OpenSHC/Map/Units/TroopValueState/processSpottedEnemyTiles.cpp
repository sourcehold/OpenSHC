#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F950
        void TroopValueState::processSpottedEnemyTiles()
        {
            BOOLEnum BVar1;
            int iVar2;
            AttackInfoPitchRelated* piVar3;
            piVar3 = &this->attackInfo.spottedEnemyTiles[0];
            do {
                iVar2 = piVar3->tile;
                if (0 < iVar2) {
                    if (80400 < iVar2) {
                        piVar3->tile = 0;
                    }
                    if (piVar3->value == 100) {
                        BVar1 = MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::shouldLightPitchBasedOnTroopValue, this)(
                            iVar2, this->attackInfo.pitchRelatedPlayerID, this->attackInfo.playerID_0x2c850);
                        if (BVar1) {
                            MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::
                                                  giveLightPitchInstructionToUnitClosestToPitch,
                                this)(iVar2);
                        }
                        piVar3->value = 99;
                    } else {
                        iVar2 = piVar3->value + -1;
                        piVar3->value = iVar2;
                        if (iVar2 < 1) {
                            piVar3->tile = 0;
                        }
                    }
                }
                piVar3 = piVar3 + 2;
            } while ((int)piVar3 < 0x178e8cc);
        }

    }
}
}
