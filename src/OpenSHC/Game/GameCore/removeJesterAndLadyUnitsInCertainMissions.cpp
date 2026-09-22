#include "../GameCore.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BBD0
    void GameCore::removeJesterAndLadyUnitsInCertainMissions()
    {
        if (this->missionNumber1to20 < 7) {
            DAT_GameState::instance.mapAndTime.unitJesterRelated = 0;
            int const jesterID
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .jesterIDUnk;
            if (jesterID != 0
                && DAT_UnitsState::instance.units[jesterID].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .someUnitIDSelfRef_2) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .jesterIDUnk = 0;
                DAT_UnitsState::instance.units[jesterID].logicalState = Map::Units::ULS_REMOVE;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someUnitIDSelfRef_2 = 0;
            }
        } else {
            DAT_GameState::instance.mapAndTime.unitJesterRelated = 1;
        }

        if (this->missionNumber1to20 < 11) {
            DAT_GameState::instance.mapAndTime.unitLadyRelated = 0;
            int const ladyID
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .ladyIDUnk;
            if (ladyID != 0
                && DAT_UnitsState::instance.units[ladyID].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                           .someUnitIDSelfRef) {
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .ladyIDUnk = 0;
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .someUnitIDSelfRef = 0;
                DAT_UnitsState::instance.units[ladyID].logicalState = Map::Units::ULS_REMOVE;
            }
        } else {
            DAT_GameState::instance.mapAndTime.unitLadyRelated = 1;
        }
    }

}
}
