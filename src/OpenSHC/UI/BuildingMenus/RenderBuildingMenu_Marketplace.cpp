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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043CDB0
    void BuildingMenus::RenderBuildingMenu_Marketplace()
    {
        char* pcVar2;
        int iVar3;
        TextAlignment TVar4;
        BGR24 BVar5;
        int iVar6;
        BOOLEnum BVar7;
        int iVar8;
        iVar8 = 0;
        BVar7 = FALSE;
        iVar6 = 0x10;
        BVar5 = 0;
        TVar4 = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d4;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "The Marketplace"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 0),
            iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
        iVar8 = 0;
        BVar7 = FALSE;
        iVar6 = 0x12;
        BVar5 = 0;
        TVar4 = OpenSHC::Text::TTA_CENTER;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x23c;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x10b;
        /*
          added by script: "Choose a goods type to trade"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 0x13),
            iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
    }

}
}
