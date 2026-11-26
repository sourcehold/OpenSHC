#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F950
        void TroopValueState::processSpottedEnemyTiles()
        {
            for (int i = 0; i < countof(DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles); ++i) {
                int const tile = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile;
                if (tile <= 0) {
                    continue;
                }
                if (MC_MAP_TILES_COUNT <= tile) {
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                }
                if (DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value == 100) {
                    BOOLEnum const shouldLightPitch
                        = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::shouldLightPitchBasedOnTroopValue, this)(
                            tile, DAT_TroopValueState::instance.attackInfo.pitchRelatedPlayerID,
                            DAT_TroopValueState::instance.attackInfo.playerID_0x2c850);
                    if (shouldLightPitch) {
                        MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::giveLightPitchInstructionToUnitClosestToPitch, this)(
                            tile);
                    }
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = 99;
                } else {
                    int const countdown = DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value - 1;
                    DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].value = countdown;
                    if (countdown <= 0) {
                        DAT_TroopValueState::instance.attackInfo.spottedEnemyTiles[i].tile = 0;
                    }
                }
            }
        }

    }
}
}
