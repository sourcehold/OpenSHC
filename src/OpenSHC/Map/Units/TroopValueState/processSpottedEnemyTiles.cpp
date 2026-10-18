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
            BOOLEnum shouldLightPitch;
            for (int i = 0; i < 100; i = i + 1) {
                int tileOrCountdown = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile;
                if (0 < tileOrCountdown) {
                    if (80400 <= tileOrCountdown) {
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                    }
                    if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value == 100) {
                        shouldLightPitch
                            = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::shouldLightPitchBasedOnTroopValue,
                                this)(tileOrCountdown, DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID,
                                DAT_TroopValueState::instance.attackInfo.playerID_0x2c850);
                        if (shouldLightPitch) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::giveLightPitchInstructionToUnitClosestToPitch, this)(
                                tileOrCountdown);
                        }
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = 99;
                    } else {
                        tileOrCountdown = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value + -1;
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = tileOrCountdown;
                        if (tileOrCountdown <= 0) {
                            DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                        }
                    }
                }
            }
        }

    }
}
}
