#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043C120
    void BuildingMenus::RenderBuildingMenu_Applefarm()
    {
        char* textAddress;
        int xParam;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        BOOLEnum keepOffsetX;
        int blendStrength;
        blendStrength = 0;
        keepOffsetX = FALSE;
        fontSize = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int yParam = DAT_MenuHandlerState::instance.y + 0x1d3;
        xParam = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Apple Orchard"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_APPLEFARM, 0),
            xParam, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
    }

}
}
