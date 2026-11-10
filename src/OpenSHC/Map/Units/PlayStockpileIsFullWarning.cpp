#include "../Units.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ee0fd8.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DWORD_00ee0fd4.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00530EB0
    void Units::PlayStockpileIsFullWarning()
    {
        // guard of the function-local static holding the last warning time
        if (!(BOOLEnum_00ee0fd8::instance & TRUE)) {
            BOOLEnum_00ee0fd8::instance |= TRUE;
            DWORD_00ee0fd4::instance = timeGetTime() - 60000;
        }
        if (timeGetTime() - DWORD_00ee0fd4::instance <= 60000) {
            return;
        }
        // "The stockpile is full my lord"
        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
            s_placement_warning11_wav_005abbf0);
        DWORD_00ee0fd4::instance = timeGetTime() - SEC_RNG::instance.currentNumber2 % 5000;
    }

}
}
