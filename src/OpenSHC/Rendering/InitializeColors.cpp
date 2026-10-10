#include "../Rendering.func.hpp"

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

using Rendering::ColorMode;

// FUNCTION: STRONGHOLDCRUSADER 0x00467890
void Rendering::InitializeColors()
{
    COL_BLUE::instance.shortValue = 0x1f;
    COL_BLACK::instance.shortValue = 0;
    if (DAT_WindowAndDirectDraw::instance.colorBitMode == Rendering::RGB_555) {
        /*
          Does not care about "alpha" bit?
         */
        COL_RED::instance.shortValue = -0x400;
        COL_LIME::instance.shortValue = 0x3e0;
        COL_DARK_GREEN::instance.shortValue = 0x1e0;
        COL_WHITE::instance.shortValue = 0x7fff;
        COL_BRIGHT_YELLOW::instance.shortValue = 0x7307;
        COL_MODERATE_GREEN::instance.shortValue = 0x3307;
        COL_DARK_CYAN_GREY::instance.shortValue = 0x35ef;
        COL_VERY_DARK_GREY::instance.shortValue = 0x1ce7;
        COL_MAGENTA::instance.shortValue = 0x7c1f;
        COL_VIVID_BLUE::instance.shortValue = 0x125f;
        COL_VERY_SOFT_YELLOW::instance.shortValue = 0x77b7;
    } else {
        COL_RED::instance.shortValue = -0x800;
        COL_LIME::instance.shortValue = 0x7c0;
        COL_DARK_GREEN::instance.shortValue = 0x3c0;
        COL_WHITE::instance.shortValue = -1;
        COL_BRIGHT_YELLOW::instance.shortValue = -0x39f9;
        COL_MODERATE_GREEN::instance.shortValue = 0x4607;
        COL_DARK_CYAN_GREY::instance.shortValue = 0x7bcf;
        COL_VERY_DARK_GREY::instance.shortValue = 0x39c7;
        COL_MAGENTA::instance.shortValue = -0x7e1;
        COL_VIVID_BLUE::instance.shortValue = 0x24bf;
        COL_VERY_SOFT_YELLOW::instance.shortValue = -0x1089;
    }
    uint _int16bit = MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(0xc0, 0xc0, 0xc0);
    COL_LIGHT_GREY::instance.shortValue = (short)_int16bit;
    _int16bit = MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(0xd7, 0xd2, 0xa4);
    COL_GREYISH_YELLOW::instance.shortValue = (short)_int16bit;
    _int16bit = MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(0x29, 0x75, 0x20);
    COL_DARK_LIME::instance.shortValue = (short)_int16bit;
    _int16bit = MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(0x68, 0x74, 0x58);
    COL_DARK_GRAYISH_GREEN::instance.shortValue = (short)_int16bit;
    _int16bit = MACRO_CALL(UI::Rendering_Func::TransformToCurrentModeColor)(0x8c, 0, 0);
    COL_DARK_RED::instance.shortValue = (short)_int16bit;
}

}
