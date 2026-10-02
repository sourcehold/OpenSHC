#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Synchrony {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004660F0
    void Actions::ProcessBuildingSleepUpdate(int playerID, int buildingType)
    {
        if (buildingType >= 0x5b)
            return;

        if (DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType]) {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType] = false;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                /*
                  "this building is currently function my lord"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "other_warning7.wav");
            }
        } else {
            DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[buildingType] = true;
            if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                /*
                  work halted my lord
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "other_warning12.wav");
            }
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateAllBuildingsSnoozedState,
            DAT_BuildingsState::ptr)(playerID, buildingType);
    }

}
}
