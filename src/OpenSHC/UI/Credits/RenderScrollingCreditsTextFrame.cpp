#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"

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
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/INT_00eb9b20.hpp"
#include "OpenSHC/Globals/INT_00eb9b24.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DB390
        void RenderScrollingCreditsTextFrame(float frameTime)
        {
            FLOAT_00eb9b1c::instance -= FLOAT_Between1And5::instance * frameTime;
            if (FLOAT_00eb9b1c::instance <= 0.0f) {
                FLOAT_00eb9b1c::instance += 100.0;
                INT_00eb9b20::instance += 1;
                if (INT_00eb9b20::instance > INT_00eb9b24::instance) {
                    DAT_00eb9b28::instance = 1;
                }
            }
            if (DAT_00eb9b28::instance != 0) {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_ArrayOfStoredMenuStrings::instance[DAT_00eb9b2c::instance],
                    DAT_00eb9b30::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                    DAT_00eb9b34::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                    DAT_00eb9b38::instance, DAT_00eb9b3c::instance, DAT_00eb9b40::instance, 0);
            } else {
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderSomeSpecificTextUnk, DAT_TextManagerObject::ptr)(
                    INT_00eb9b20::instance, (int)FLOAT_00eb9b1c::instance,
                    DAT_00eb9b30::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                    DAT_00eb9b34::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                    DAT_00eb9b3c::instance, DAT_00eb9b40::instance);
            }
        }

    }
}
}
