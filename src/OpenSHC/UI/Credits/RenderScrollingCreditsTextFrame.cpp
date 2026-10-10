#include "../Credits.func.hpp"

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
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/FLOAT_00eb9b1c.hpp"
#include "OpenSHC/Globals/FLOAT_00eb9b24.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/INT_00eb9b20.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB390
    void Credits::RenderScrollingCreditsTextFrame(float param_1)
    {
        FLOAT_00eb9b1c::instance = FLOAT_00eb9b1c::instance - FLOAT_Between1And5::instance * param_1;
        double param = (double)FLOAT_00eb9b1c::instance;
        if (param < (double)0 != (param == (double)0)) {
            INT_00eb9b20::instance = INT_00eb9b20::instance + 1;
            FLOAT_00eb9b1c::instance = (float)(param + (double)100.0);
            if ((int)FLOAT_00eb9b24::instance < INT_00eb9b20::instance) {
                DAT_00eb9b28::instance = 1;
                goto LAB_004db3f9;
            }
            param = (double)FLOAT_00eb9b1c::instance;
        }
        if (!DAT_00eb9b28::instance) {
            int yPos = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + DAT_00eb9b34::instance;
            int xPos = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + DAT_00eb9b30::instance;
            uint color = DAT_00eb9b3c::instance;
            int fontSize = DAT_00eb9b40::instance;
            int otherBlendValueUnk = (long)(param);
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderSomeSpecificTextUnk, DAT_TextManagerObject::ptr)(
                INT_00eb9b20::instance, otherBlendValueUnk, xPos, yPos, color, fontSize);
            return;
        }
    LAB_004db3f9:
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            DAT_ArrayOfStoredMenuStrings::instance[DAT_00eb9b2c::instance],
            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + DAT_00eb9b30::instance,
            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + DAT_00eb9b34::instance, DAT_00eb9b38::instance,
            DAT_00eb9b3c::instance, DAT_00eb9b40::instance, 0);
        return;
    }

}
}
