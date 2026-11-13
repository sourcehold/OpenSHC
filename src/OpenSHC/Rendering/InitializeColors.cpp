#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Rendering/ColorMode.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/COL_BRIGHT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_DARK_CYAN_GREY.hpp"
#include "OpenSHC/Globals/COL_DARK_GRAYISH_GREEN.hpp"
#include "OpenSHC/Globals/COL_DARK_GREEN.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/COL_DARK_RED.hpp"
#include "OpenSHC/Globals/COL_GREYISH_YELLOW.hpp"
#include "OpenSHC/Globals/COL_LIGHT_GREY.hpp"
#include "OpenSHC/Globals/COL_LIME.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/COL_MODERATE_GREEN.hpp"
#include "OpenSHC/Globals/COL_RED.hpp"
#include "OpenSHC/Globals/COL_VERY_DARK_GREY.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_VIVID_BLUE.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x00467890
    void InitializeColors()
    {
        COL_BLUE::instance.shortValue = 31;
        COL_BLACK::instance.shortValue = 0;
        if (DAT_WindowAndDirectDraw::instance.colorBitMode == RGB_555) {
            COL_RED::instance.shortValue = (short)64512;
            COL_LIME::instance.shortValue = (short)992;
            COL_DARK_GREEN::instance.shortValue = (short)480;
            COL_WHITE::instance.shortValue = (short)32767;
            COL_BRIGHT_YELLOW::instance.shortValue = (short)29447;
            COL_MODERATE_GREEN::instance.shortValue = (short)13063;
            COL_DARK_CYAN_GREY::instance.shortValue = (short)13807;
            COL_VERY_DARK_GREY::instance.shortValue = (short)7399;
            COL_MAGENTA::instance.shortValue = (short)31775;
            COL_VIVID_BLUE::instance.shortValue = (short)4703;
            COL_VERY_SOFT_YELLOW::instance.shortValue = (short)30647;
        } else {
            COL_RED::instance.shortValue = (short)63488;
            COL_LIME::instance.shortValue = (short)1984;
            COL_DARK_GREEN::instance.shortValue = (short)960;
            COL_WHITE::instance.shortValue = (short)65535;
            COL_BRIGHT_YELLOW::instance.shortValue = (short)50695;
            COL_MODERATE_GREEN::instance.shortValue = (short)17927;
            COL_DARK_CYAN_GREY::instance.shortValue = (short)31695;
            COL_VERY_DARK_GREY::instance.shortValue = (short)14791;
            COL_MAGENTA::instance.shortValue = (short)63519;
            COL_VIVID_BLUE::instance.shortValue = (short)9407;
            COL_VERY_SOFT_YELLOW::instance.shortValue = (short)61303;
        }
        COL_LIGHT_GREY::instance.shortValue
            = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(192, 192, 192);
        COL_GREYISH_YELLOW::instance.shortValue
            = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(215, 210, 164);
        COL_DARK_LIME::instance.shortValue
            = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(41, 117, 32);
        COL_DARK_GRAYISH_GREEN::instance.shortValue
            = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(104, 116, 88);
        COL_DARK_RED::instance.shortValue
            = (short)MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(140, 0, 0);
    }

}
}
