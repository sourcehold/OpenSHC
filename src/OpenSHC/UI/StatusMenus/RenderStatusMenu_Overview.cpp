#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b96120.hpp"

namespace OpenSHC {
namespace UI {

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
    // FUNCTION: STRONGHOLDCRUSADER 0x00447DC0
    void StatusMenus::RenderStatusMenu_Overview()
    {
        char* pcVar1;
        int iVar2;
        int iVar3;
        int iVar4;
        TextAlignment TVar5;
        BGR24 BVar6;
        BOOLEnum BVar7;
        int iVar8;
        int blendStrength;
        int iVar9;
        INT_00b96120::instance = 0x47;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
            0, DAT_MenuHandlerState::instance.x + 0x12, DAT_MenuHandlerState::instance.y + 0x1c7);
        iVar3 = DAT_MenuHandlerState::instance.y + 0x1cf;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x8d;
        pcVar1 = MACRO_CALL_MEMBER(
            OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar1, iVar4, iVar3, OpenSHC::Text::TTA_CENTER, 0, 0x13, FALSE, 0);
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            == 0) {
            iVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeGoldRelatedComputation)();
        } else {
            iVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeFearFactorComputation)();
        }
        iVar4 = 0x13;
        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PLAYER_DESC, iVar3),
            iVar4);
        iVar3 = 0x13;
        /*
          added by script: "and"
         */
        iVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PLAYER_DESC, 0x28),
            iVar3);
        iVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::SomePopularityRelatedComputation)();
        iVar8 = 0x13;
        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PLAYER_DESC, iVar3),
            iVar8);
        iVar3 = DAT_MenuHandlerState::instance.y;
        iVar2 = DAT_MenuHandlerState::instance.x - (iVar4 + iVar2 + 0xc + iVar8) / 2;
        iVar4 = iVar2 + 0x8d;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            == 0) {
            iVar8 = MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeGoldRelatedComputation)();
        } else {
            iVar8 = MACRO_CALL(OpenSHC::UI::Helpers_Func::SomeFearFactorComputation)();
        }
        iVar3 = iVar3 + 0x242;
        blendStrength = 0;
        BVar7 = FALSE;
        iVar9 = 0x13;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PLAYER_DESC, iVar8),
            iVar4, iVar3, TVar5, BVar6, iVar9, BVar7, blendStrength);
        iVar9 = 0;
        BVar7 = TRUE;
        iVar8 = 0x13;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar4 = DAT_MenuHandlerState::instance.y + 0x242;
        iVar3 = iVar2 + 0x93;
        /*
          added by script: "and"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PLAYER_DESC, 0x28),
            iVar3, iVar4, TVar5, BVar6, iVar8, BVar7, iVar9);
        iVar4 = DAT_MenuHandlerState::instance.y + 0x242;
        iVar3 = MACRO_CALL(OpenSHC::UI::Helpers_Func::SomePopularityRelatedComputation)();
        iVar9 = 0;
        BVar7 = TRUE;
        iVar8 = 0x13;
        BVar6 = 0;
        TVar5 = OpenSHC::Text::TTA_LEFT;
        iVar2 = iVar2 + 0x99;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_PLAYER_DESC, iVar3),
            iVar2, iVar4, TVar5, BVar6, iVar8, BVar7, iVar9);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
