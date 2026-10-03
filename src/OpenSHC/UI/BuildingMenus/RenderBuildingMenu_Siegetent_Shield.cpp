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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043E280
    void BuildingMenus::RenderBuildingMenu_Siegetent_Shield()
    {
        char* pcVar2;
        int iVar3;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        int iVar7;
        BOOLEnum BVar8;
        int blendStrength;
        iVar3 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        blendStrength = 0;
        BVar8 = FALSE;
        iVar7 = 0x11;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1eb;
        iVar4 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Portable Shield"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_SIEGE_TENT, 5),
            iVar4, iVar1, TVar5, BVar6, iVar7, BVar8, blendStrength);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (DAT_BuildingsState::instance.buildings[iVar3].buildingProgress * 100) / 0x78,
            DAT_MenuHandlerState::instance.x + 0xb4, DAT_MenuHandlerState::instance.y + 0x209, OpenSHC::Text::TTA_LEFT,
            0, 0x11, FALSE, 0);
        iVar7 = 0;
        BVar8 = TRUE;
        iVar4 = 0x11;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x209;
        iVar1 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "% Complete"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_SIEGE_TENT, 6),
            iVar1, iVar3, TVar5, BVar6, iVar4, BVar8, iVar7);
    }

}
}
