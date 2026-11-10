#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ee0fe0.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DWORD_00ee0fdc.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00530F20
    void Units::PlayArmoryIsFullWarning()
    {
        // guard of the function-local static holding the last warning time
        if (!(BOOLEnum_00ee0fe0::instance & TRUE)) {
            BOOLEnum_00ee0fe0::instance |= TRUE;
            DWORD_00ee0fdc::instance = timeGetTime() - 60000;
        }
        if (timeGetTime() - DWORD_00ee0fdc::instance <= 60000) {
            return;
        }
        int const currentPlayer = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; ++buildingID) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL
                && DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_ARMORY
                && DAT_BuildingsState::instance.buildings[buildingID].owner == currentPlayer) {
                // "The armory is full my lord"
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_placement_warning12_wav_005abc08);
                DWORD_00ee0fdc::instance = timeGetTime() - SEC_RNG::instance.currentNumber2 % 5000;
                return;
            }
        }
    }

}
}
