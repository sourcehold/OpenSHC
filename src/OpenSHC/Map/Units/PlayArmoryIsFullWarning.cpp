#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ee0fe0.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DWORD_00ee0fdc.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530F20
    void Units::PlayArmoryIsFullWarning()
    {
        // guard of the function-local static holding the last warning time
        if ((BOOLEnum_00ee0fe0::instance & 1) == 0) {
            BOOLEnum_00ee0fe0::instance = (BOOLEnum)(BOOLEnum_00ee0fe0::instance | 1);
            DWORD_00ee0fdc::instance = timeGetTime() - 60000;
        }
        if (timeGetTime() - DWORD_00ee0fdc::instance <= 60000) {
            return;
        }
        for (int i = 1; i < DAT_BuildingsState::instance.maxBuildingsCount; ++i) {
            if (DAT_BuildingsState::instance.buildings[i].logicalState == OpenSHC::Map::Buildings::BLS_NORMAL
                && DAT_BuildingsState::instance.buildings[i].buildingType == OpenSHC::Map::Buildings::BT_ARMORY
                && DAT_BuildingsState::instance.buildings[i].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
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
