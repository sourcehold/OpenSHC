#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DWORD_00df5568.hpp"
#include "OpenSHC/Globals/INT_00df5564.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BC770
        void SetTutorialHintActiveWithTimestamp()
        {
            INT_00df5564::instance = 1;
            DWORD_00df5568::instance = timeGetTime();
        }

    }
}
}
