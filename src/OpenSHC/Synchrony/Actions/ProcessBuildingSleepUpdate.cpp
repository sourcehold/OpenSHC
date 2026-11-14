#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x004660F0
    void Actions::ProcessBuildingSleepUpdate(int playerID, int buildingType)
    {
        if (buildingType >= 91) {
            return;
        }
        if (DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType]) {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType] = false;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_other_warning7_wav_005a58b0);
            }
        } else {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType] = true;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_WorkHaltedMyLord);
            }
        }
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateAllBuildingsSnoozedState, DAT_BuildingsState::ptr)(
            playerID, buildingType);
    }

}
}
