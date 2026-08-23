#include "OpenSHC/UI.func.hpp"

#include "OpenSHC/Globals/DAT_00df5564.hpp"
#include "OpenSHC/Globals/DWORD_00df5568.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004BC770
void UI::SetTutorialHintActiveWithTimestamp()
{
    DAT_00df5564::instance = 1;
    DWORD_00df5568::instance = timeGetTime();
}

}
