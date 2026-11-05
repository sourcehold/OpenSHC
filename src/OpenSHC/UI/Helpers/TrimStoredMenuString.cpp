#include "../Helpers.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_00eb9b28.hpp"
#include "OpenSHC/Globals/DAT_00eb9b2c.hpp"
#include "OpenSHC/Globals/DAT_00eb9b30.hpp"
#include "OpenSHC/Globals/DAT_00eb9b34.hpp"
#include "OpenSHC/Globals/DAT_00eb9b38.hpp"
#include "OpenSHC/Globals/DAT_00eb9b3c.hpp"
#include "OpenSHC/Globals/DAT_00eb9b40.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/FLOAT_00eb9b1c.hpp"
#include "OpenSHC/Globals/INT_00eb9b20.hpp"
#include "OpenSHC/Globals/INT_00eb9b24.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB300
    void Helpers::TrimStoredMenuString(int storedMenuStringIndex, undefined4 param_2, undefined4 param_3,
        int allowedWidth, undefined4 param_5, int fontSize)
    {
        FLOAT_00eb9b1c::instance = 100.0;
        INT_00eb9b20::instance = 1;
        INT_00eb9b24::instance = strlen(DAT_ArrayOfStoredMenuStrings::instance[storedMenuStringIndex]);
        // In the order of the globals' addresses, as the original stores them; other orders move the registers.
        DAT_00eb9b30::instance = param_2;
        DAT_00eb9b34::instance = param_3;
        DAT_00eb9b3c::instance = param_5;
        DAT_00eb9b28::instance = 0;
        DAT_00eb9b38::instance = allowedWidth;
        DAT_00eb9b40::instance = fontSize;
        DAT_00eb9b2c::instance = storedMenuStringIndex;
        MACRO_CALL_MEMBER(Text::TextManager_Func::trimText, DAT_TextManagerObject::ptr)(
            DAT_ArrayOfStoredMenuStrings::instance[storedMenuStringIndex], allowedWidth, fontSize);
    }

}
}
