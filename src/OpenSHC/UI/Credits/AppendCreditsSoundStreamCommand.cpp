#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

        // FUNCTION: STRONGHOLDCRUSADER 0x004DABF0
        void AppendCreditsSoundStreamCommand(int command, SHC_SoundStream soundStream)
        {
            if ((int)DAT_UnknownBinkCount::instance < 288) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = command;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = soundStream;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
