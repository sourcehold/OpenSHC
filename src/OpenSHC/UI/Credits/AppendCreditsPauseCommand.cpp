#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_CreditsScriptCommandCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA840
        void AppendCreditsPauseCommand()
        {
            if ((int)DAT_CreditsScriptCommandCount::instance < 288) {
                DAT_ARRAY_00eb9b68::instance[DAT_CreditsScriptCommandCount::instance].commandType = 0x1c;
                DAT_CreditsScriptCommandCount::instance += 1;
            }
        }

    }
}
}
