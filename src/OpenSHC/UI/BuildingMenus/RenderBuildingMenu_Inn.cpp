#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043AF40
    void BuildingMenus::RenderBuildingMenu_Inn()
    {
        char* pcVar2;
        int iVar3;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        int iVar7;
        BOOLEnum BVar8;
        int iVar9;
        iVar3 = DAT_BuildingsState::instance.menuSelectedBuildingID;
        iVar9 = 0;
        BVar8 = FALSE;
        iVar7 = 0x10;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        int iVar1 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x19;
        /*
          added by script: "Inn"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 0), iVar4, iVar1, TVar5, BVar6, iVar7, BVar8, iVar9);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0xa9, DAT_MenuHandlerState::instance.x + 0xb4,
            DAT_MenuHandlerState::instance.y + 0x1d1);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[iVar3].flagonsOfAleOrCheeseOrReleaseDogs / 0xa0,
            DAT_MenuHandlerState::instance.x + 200, (int)(DAT_MenuHandlerState::instance.y + 471),
            OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE, 0);
        iVar9 = 0;
        BVar8 = TRUE;
        iVar7 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x1d7;
        iVar4 = DAT_MenuHandlerState::instance.x + 0xdc;
        /*
          added by script: "Flagons of ale"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 3), iVar4, iVar1, TVar5, BVar6, iVar7, BVar8, iVar9);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            (int)DAT_BuildingsState::instance.buildings[iVar3].flagonsOfAleOrCheeseOrReleaseDogs,
            DAT_MenuHandlerState::instance.x + 0xe0, DAT_MenuHandlerState::instance.y + 0x1d7, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        iVar7 = 0;
        BVar8 = FALSE;
        iVar4 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x1e9;
        iVar1 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Working Inns"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 7), iVar1, iVar3, TVar5, BVar6, iVar4, BVar8, iVar7);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .workingInnsCount,
            DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("(",
            DAT_MenuHandlerState::instance.x + 0xc2, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].countInns,
            DAT_MenuHandlerState::instance.x + 0xc4, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(")",
            DAT_MenuHandlerState::instance.x + 0xc6, DAT_MenuHandlerState::instance.y + 0x1e9, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        iVar3 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage, DAT_GameState::ptr)(
            DAT_GameSynchronyState::instance.currentPlayerSlotID);
        iVar9 = 0;
        BVar8 = FALSE;
        iVar7 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x1fb;
        iVar4 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Population coverage"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 5), iVar4, iVar1, TVar5, BVar6, iVar7, BVar8, iVar9);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar3,
            DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 0x1fb, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 0xba, DAT_MenuHandlerState::instance.y + 0x1fb, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        if (iVar3 < 0x19) {
            iVar1 = 0;
        } else if (iVar3 < 0x32) {
            iVar1 = 0x32;
        } else if (iVar3 < 0x4b) {
            iVar1 = 100;
        } else {
            iVar1 = ((99 < iVar3) - 1 & 0xffffffce) + 200;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xd6 + DAT_MenuHandlerState::instance.x,
            DAT_MenuHandlerState::instance.y + 0x1fb, iVar1, TRUE);
        if (iVar3 < 0x19) {
            iVar3 = 0x19;
        } else if (iVar3 < 0x32) {
            iVar3 = 0x32;
        } else if (iVar3 < 0x4b) {
            iVar3 = 0x4b;
        } else {
            if (99 < iVar3) {
                iVar7 = 0;
                BVar8 = FALSE;
                iVar4 = 0x12;
                BVar6 = 0;
                TVar5 = OpenSHC::Text::TTA_LEFT;
                iVar3 = DAT_MenuHandlerState::instance.y + 0x20d;
                iVar1 = DAT_MenuHandlerState::instance.x + 0xb4;
                /*
                  added by script: "Maximum bonus achieved"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 8), iVar1, iVar3, TVar5, BVar6, iVar4, BVar8, iVar7);
            }
            iVar3 = 100;
        }
        iVar9 = 0;
        BVar8 = FALSE;
        iVar7 = 0x12;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar1 = DAT_MenuHandlerState::instance.y + 0x20d;
        iVar4 = DAT_MenuHandlerState::instance.x + 0xb4;
        /*
          added by script: "Next level at"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_INN, 6), iVar4, iVar1, TVar5, BVar6, iVar7, BVar8, iVar9);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar3,
            DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 0x20d, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("%",
            DAT_MenuHandlerState::instance.x + 0xba, DAT_MenuHandlerState::instance.y + 0x20d, OpenSHC::Text::TTA_LEFT,
            0, 0x12, TRUE, 0);
    }

}
}
