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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043BD60
    void BuildingMenus::RenderBuildingMenu_House()
    {
        char* pcVar2;
        int iVar3;
        TextAlignment alignment;
        BGR24 color;
        int iVar4;
        uint color_00;
        BOOLEnum keepOffsetX;
        int iVar5;
        int blendStrength;
        iVar5 = 0;
        keepOffsetX = FALSE;
        iVar4 = 0x10;
        color = 0;
        alignment = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Hovel"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_HOUSE, 0), iVar3, iVar1, alignment, color, iVar4, keepOffsetX, iVar5);
        blendStrength = 0;
        iVar5 = 0x12;
        color_00 = 0;
        iVar4 = 0x136;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x1fb;
        iVar3 = DAT_MenuHandlerState::instance.x + 0xaf;
        /*
          added by script: "Provides space for 8 peasants."
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_HOUSE, 1), iVar3, iVar1, iVar4, color_00, iVar5, blendStrength);
    }

}
}
