#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043BBB0
    void BuildingMenus::RenderBuildingMenu_Outpost()
    {
        char* pcVar2;
        int iVar3;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        int iVar7;
        BOOLEnum BVar8;
        int blendStrength;
        iVar4 = 0;
        if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType
            == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
            iVar4 = 9;
        }
        blendStrength = 0;
        BVar8 = FALSE;
        iVar7 = 0x10;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1cf;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, iVar4), iVar3, iVar1, TVar5, BVar6, iVar7, BVar8, blendStrength);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar3 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x205;
        iVar1 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Size"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x12), iVar1, iVar4, TVar5, BVar6, iVar3, BVar8, iVar7);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar3 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x1e9;
        iVar1 = DAT_MenuHandlerState::instance.x + 0x73;
        /*
          added by script: "Small"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x13), iVar1, iVar4, TVar5, BVar6, iVar3, BVar8, iVar7);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar3 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x1e9;
        iVar1 = DAT_MenuHandlerState::instance.x + 0xcb;
        /*
          added by script: "Large"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x14), iVar1, iVar4, TVar5, BVar6, iVar3, BVar8, iVar7);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar3 = 0x12;
        BVar6 = 0;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x23f;
        iVar1 = DAT_MenuHandlerState::instance.x + 0x19;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        /*
          added by script: "Start Delay"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x15), iVar1, iVar4, TVar5, BVar6, iVar3, BVar8, iVar7);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar3 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x223;
        iVar1 = DAT_MenuHandlerState::instance.x + 0x73;
        /*
          added by script: "None"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x16), iVar1, iVar4, TVar5, BVar6, iVar3, BVar8, iVar7);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar3 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x223;
        iVar1 = DAT_MenuHandlerState::instance.x + 0xcb;
        /*
          added by script: "10 Mins"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, 0x17), iVar1, iVar4, TVar5, BVar6, iVar3, BVar8, iVar7);
    }

}
}
