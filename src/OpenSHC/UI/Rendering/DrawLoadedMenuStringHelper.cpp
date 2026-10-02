#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004DA670
    void Rendering::DrawLoadedMenuStringHelper(
        int loadedMenuStringIndex, int xPos, int yPos, int maxWidth, uint color, int fontSize, BOOLEnum isSingleLine)
    {
        if (isSingleLine == FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                DAT_ArrayOfStoredMenuStrings::instance[loadedMenuStringIndex],
                xPos + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                yPos + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight, maxWidth, color, fontSize, 0);
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            DAT_ArrayOfStoredMenuStrings::instance[loadedMenuStringIndex],
            xPos + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
            yPos + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight, OpenSHC::Text::TTA_CENTER,
            (BGR24)((int)(color)), fontSize, FALSE, 0);
    }

}
}
