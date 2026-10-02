#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043D520
    void BuildingMenus::RenderBuildingMenu_Stables()
    {
        char* pcVar2;
        int iVar3;
        int xParam;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        int iVar7;
        BOOLEnum BVar8;
        int iVar9;
        iVar4 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        iVar9 = 0;
        BVar8 = FALSE;
        iVar7 = 0x10;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Stables"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, 0), iVar3, iVar1, TVar5, BVar6, iVar7, BVar8, iVar9);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)(char)DAT_BuildingsState::instance.buildings[iVar4].numberOfAnimals
                - (int)DAT_BuildingsState::instance.buildings[iVar4].randomOutpostField,
            DAT_MenuHandlerState::instance.x + 0xaf, DAT_MenuHandlerState::instance.y + 0x205, OpenSHC::Text::TTA_LEFT,
            0, 0x12, FALSE, 0);
        iVar7 = 0;
        BVar8 = TRUE;
        iVar3 = 0x12;
        BVar6 = 0;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x205;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        if ((int)(char)DAT_BuildingsState::instance.buildings[iVar4].numberOfAnimals
                - (int)DAT_BuildingsState::instance.buildings[iVar4].randomOutpostField
            == 1) {
            iVar9 = 3;
        } else {
            iVar9 = 1;
        }
        xParam = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Horse Available"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, iVar9), xParam, iVar1, TVar5, BVar6, iVar3, BVar8, iVar7);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[iVar4].randomOutpostField,
            DAT_MenuHandlerState::instance.x + 0xaf, DAT_MenuHandlerState::instance.y + 0x219, OpenSHC::Text::TTA_LEFT,
            0, 0x12, FALSE, 0);
        iVar3 = 0;
        BVar8 = TRUE;
        iVar1 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        if (DAT_BuildingsState::instance.buildings[iVar4].randomOutpostField == '\x01') {
            iVar4 = 4;
        } else {
            iVar4 = 2;
        }
        iVar9 = DAT_MenuHandlerState::instance.y + 0x219;
        iVar7 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Horse In Use"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_STABLES, iVar4), iVar7, iVar9, TVar5, BVar6, iVar1, BVar8, iVar3);
    }

}
}
