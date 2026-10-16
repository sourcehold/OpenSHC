#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F950
        void TroopValueState::processSpottedEnemyTiles()
        {
            BOOLEnum BVar1;
            for (int i = 0; i < 101; i = i + 1) {
                int iVar2 = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile;
                if (0 < iVar2) {
                    if (80400 <= iVar2) {
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                    }
                    if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value == 100) {
                        BVar1 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::shouldLightPitchBasedOnTroopValue,
                            this)(iVar2, DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID, DAT_TroopValueState::instance.attackInfo.playerID_0x2c850);
                        if (BVar1) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::giveLightPitchInstructionToUnitClosestToPitch, this)(
                                iVar2);
                        }
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = 99;
                    } else {
                        iVar2 = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value + -1;
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = iVar2;
                        if (iVar2 <= 0) {
                            DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                        }
                    }
                }
            }
        }

    }
}
}
