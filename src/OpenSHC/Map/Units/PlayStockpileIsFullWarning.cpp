#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ee0fd8.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DWORD_00ee0fd4.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00530EB0
    uint Units::PlayStockpileIsFullWarning()
    {
        // guard of the function-local static holding the last warning time
        if ((BOOLEnum_00ee0fd8::instance & 1) == 0) {
            BOOLEnum_00ee0fd8::instance = (BOOLEnum)(BOOLEnum_00ee0fd8::instance | 1);
            DWORD_00ee0fd4::instance = timeGetTime() - 60000;
        }
        uint elapsed = timeGetTime() - DWORD_00ee0fd4::instance;
        if (elapsed > 60000) {
            // "The stockpile is full my lord"
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning11_wav_005abbf0);
            DWORD now = timeGetTime();
            // the original returns whatever is left in eax (a void function in the source)
            elapsed = SEC_RNG::instance.currentNumber2 / 5000;
            DWORD_00ee0fd4::instance = now - SEC_RNG::instance.currentNumber2 % 5000;
        }
        return elapsed;
    }

}
}
