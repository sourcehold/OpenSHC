#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA6E0
    void Rendering::DrawLoadedMenuStringHelperWithBlending(int loadedMenuStringIndex, int xPos, int yPos, int maxWidth,
        uint color, int fontSize, BOOLEnum isSingleLine, int blendStrength)
    {
        xPos += DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
        yPos += DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
        if (!isSingleLine) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                DAT_ArrayOfStoredMenuStrings::instance[loadedMenuStringIndex], xPos, yPos, maxWidth, color, fontSize,
                blendStrength);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                DAT_ArrayOfStoredMenuStrings::instance[loadedMenuStringIndex], xPos, yPos, OpenSHC::Text::TTA_CENTER,
                color, fontSize, FALSE, blendStrength);
        }
    }

}
}
