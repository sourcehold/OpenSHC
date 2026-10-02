#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043BFA0
    void BuildingMenus::RenderBuildingMenu_Apothecary()
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
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar3 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Apothecary"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_HEALERS, 0), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
        iVar8 = 0;
        BVar7 = FALSE;
        iVar6 = 0x12;
        BVar5 = 0;
        TVar4 = OpenSHC::Text::TTA_LEFT;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x203;
        iVar3 = DAT_MenuHandlerState::instance.x + 0xb1;
        /*
          added by script: "Immunity From Disease"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_HEALERS, 3), iVar3, iVar1, TVar4, BVar5, iVar6, BVar7, iVar8);
        iVar1
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].healerCount;
        if (2 < iVar1) {
            iVar1 = 3;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            iVar1 * 0x14, DAT_MenuHandlerState::instance.x + 0xb7, DAT_MenuHandlerState::instance.y + 0x203,
            OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 0xb7, DAT_MenuHandlerState::instance.y + 0x203, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
    }

}
}
