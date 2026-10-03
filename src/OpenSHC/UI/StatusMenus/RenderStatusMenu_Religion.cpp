#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b98448.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043FE10
    void StatusMenus::RenderStatusMenu_Religion()
    {
        int iVar1;
        int iVar2;
        int iVar3;
        char* pcVar4;
        int iVar5;
        TextAlignment TVar6;
        BGR24 BVar7;
        int iVar8;
        BOOLEnum BVar9;
        int iVar10;
        int iVar11;
        int blendStrength;
        int local_4;
        iVar2 = DAT_MenuHandlerState::instance.y + 0x1b0;
        iVar1 = DAT_MenuHandlerState::instance.x;
        DAT_00b98448::instance = DAT_00b98448::instance + 1;
        if (0x28 < (int)DAT_00b98448::instance) {
            DAT_00b98448::instance = 0;
        }
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
            1, DAT_MenuHandlerState::instance.x + 0xe, DAT_MenuHandlerState::instance.y + 0x1e9);
        iVar10 = 0;
        BVar9 = FALSE;
        iVar8 = 0x11;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar3 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar5 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Religion"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 8),
            iVar5, iVar3, TVar6, BVar7, iVar8, BVar9, iVar10);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(0, iVar1 + 0x78, iVar2 + 0x32);
        iVar11 = 0;
        BVar9 = FALSE;
        iVar10 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar3 = iVar1 + 0xdc;
        iVar5 = iVar3;
        iVar8 = iVar2 + 0x26;
        /*
          added by script: "Total priests"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x16),
            iVar5, iVar8, TVar6, BVar7, iVar10, BVar9, iVar11);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .priestCountUnk,
            iVar1 + 0xe2, iVar2 + 0x26, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        iVar11 = 0;
        BVar9 = FALSE;
        iVar10 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar5 = iVar3;
        iVar8 = iVar2 + 0x3c;
        /*
          added by script: "Blessed People %"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x11),
            iVar5, iVar8, TVar6, BVar7, iVar10, BVar9, iVar11);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .blessedPeoplePercentage,
            iVar1 + 0xe1, iVar2 + 0x3c, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
        iVar11 = 0;
        BVar9 = FALSE;
        iVar10 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar5 = iVar3;
        iVar8 = iVar2 + 0x52;
        /*
          added by script: "Popularity Effect:"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x12),
            iVar5, iVar8, TVar6, BVar7, iVar10, BVar9, iVar11);
        iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .blessedPeoplePercentage;
        if (iVar5 < 0x19) {
            iVar5 = 0;
        } else if (iVar5 < 0x32) {
            iVar5 = 0x32;
        } else if (iVar5 < 0x4b) {
            iVar5 = 100;
        } else {
            iVar5 = 0x5e < iVar5 ? 200 : 150;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xf0 + iVar1, iVar2 + 0x52, iVar5, TRUE);
        iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .blessedPeoplePercentage;
        if (iVar5 < 0x19) {
            local_4 = 0x19;
        LAB_00440039:
            blendStrength = 0;
            BVar9 = FALSE;
            iVar11 = 0x12;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar5 = iVar2 + 0x68;
            iVar8 = iVar3;
            iVar10 = iVar5;
            /*
              added by script: "Next level at"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1c),
                iVar8, iVar10, TVar6, BVar7, iVar11, BVar9, blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                local_4, iVar1 + 0xe1, iVar5, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            iVar11 = 0;
            BVar9 = TRUE;
            iVar10 = 0x12;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar8 = iVar1 + 0xe2;
            pcVar4 = "%";
        } else {
            if (iVar5 < 0x32) {
                local_4 = 0x32;
                goto LAB_00440039;
            }
            if (iVar5 < 0x4b) {
                local_4 = 0x4b;
                goto LAB_00440039;
            }
            if (iVar5 < 0x5f) {
                local_4 = 100;
                goto LAB_00440039;
            }
            iVar11 = 0;
            BVar9 = FALSE;
            iVar10 = 0x12;
            BVar7 = 0;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar5 = iVar2 + 0x68;
            iVar8 = iVar3;
            /*
              added by script: "Max bonus achieved."
             */
            pcVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1d);
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            pcVar4, iVar8, iVar5, TVar6, BVar7, iVar10, BVar9, iVar11);
        iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .ownsCathedralUnk;
        if (iVar5 == 0) {
        LAB_00440111:
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .ownsChurchUnk
                == 0)
                goto LAB_00440145;
            iVar5 = 0x15;
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .ownsChurchUnk
            == 0) {
            if (iVar5 == 0)
                goto LAB_00440111;
            iVar5 = 0x14;
        } else {
            iVar5 = 0x20;
        }
        iVar8 = iVar2 + 0x8c;
        iVar11 = 0;
        BVar9 = FALSE;
        iVar10 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        /*
          added by script: "Church bonus"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, iVar5),
            iVar3, iVar8, TVar6, BVar7, iVar10, BVar9, iVar11);
    LAB_00440145:
        iVar3 = 0;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ownsChurchUnk
            != 0) {
            iVar3 = 0x19;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .ownsCathedralUnk
            != 0) {
            iVar3 = iVar3 + 0x32;
        }
        if (iVar3 != 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_TextManagerObject::instance.currentXOffset_0x0 + 0xfa + iVar1, iVar2 + 0x8c, iVar3, TRUE);
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
