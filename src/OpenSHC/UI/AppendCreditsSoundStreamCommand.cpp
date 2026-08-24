#include "../UI.func.hpp"

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {

using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

/*
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */

// FUNCTION: STRONGHOLDCRUSADER 0x004DABF0
void UI::AppendCreditsSoundStreamCommand(int param_1, SHC_SoundStream param_2)
{
    if (DAT_UnknownBinkCount::instance < 0x120) {
        DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = param_1;
        DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = param_2;
        DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
    }
    return;
}

}
