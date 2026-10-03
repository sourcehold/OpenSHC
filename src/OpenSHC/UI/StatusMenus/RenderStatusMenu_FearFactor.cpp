#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
    using OpenSHC::Text::GameLanguage;
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
    // FUNCTION: STRONGHOLDCRUSADER 0x0043F2F0
    void StatusMenus::RenderStatusMenu_FearFactor()
    {
        int iVar1;
        int iVar2;
        char* pcVar3;
        int iVar4;
        int iVar5;
        TextAlignment TVar6;
        BGR24 BVar7;
        int iVar8;
        uint uVar9;
        BOOLEnum BVar10;
        int iVar11;
        int iVar12;
        int iVar13;
        int local_4;
        int _fearFactorLevel;
        iVar2 = DAT_MenuHandlerState::instance.y + 0x1bf;
        iVar1 = DAT_MenuHandlerState::instance.x;
        local_4 = 0;
        if ((DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_ENGLISH)
            && (DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_AMERICAN)) {
            local_4 = -0x14;
        }
        iVar11 = 0;
        BVar10 = FALSE;
        iVar8 = 0x11;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar5 = iVar2 + 0x14;
        iVar4 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Fear Factor"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 2),
            iVar4, iVar5, TVar6, BVar7, iVar8, BVar10, iVar11);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(0, iVar1 + 100, iVar2 + 0x32);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .goodStuffCount,
            iVar1 + 0x80, iVar2 + 0x76, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
            DAT_TextureRenderCoreObject::ptr)(1, iVar1 + 0xb4, iVar2 + 0x32);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].badStuffCount,
            iVar1 + 0xd0, iVar2 + 0x76, OpenSHC::Text::TTA_LEFT, 0, 0x11, FALSE, 0);
        iVar12 = 0;
        BVar10 = FALSE;
        iVar11 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar5 = local_4 + 0x118 + iVar1;
        iVar4 = iVar5;
        iVar8 = iVar2 + 0x19;
        /*
          added by script: "Popularity Effect:"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x12),
            iVar4, iVar8, TVar6, BVar7, iVar11, BVar10, iVar12);
        _fearFactorLevel = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .fearFactorLevel;
        if (_fearFactorLevel <= 0) {
            if ((uint)_fearFactorLevel < 0x80000000) {
                /*
                  > -1 ?
                 */
                iVar4 = 0;
            } else {
                iVar4 = _fearFactorLevel * 0x19;
            }
        } else {
            iVar4 = _fearFactorLevel * 0x19;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + local_4 + 300 + iVar1, iVar2 + 0x19, iVar4, FALSE);
        iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .fearFactorLevel;
        if (iVar4 < 5) {
            if (-5 < iVar4) {
                iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .goodStuffCount;
                iVar8 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .badStuffCount;
                if (iVar8 < iVar4) {
                    iVar12 = 0;
                    BVar10 = FALSE;
                    iVar11 = 0x12;
                    BVar7 = 0;
                    TVar6 = OpenSHC::Text::TTA_LEFT;
                    iVar4 = iVar2 + 0x2d;
                    iVar8 = iVar5;
                    /*
                      added by script: "Good things for next level:"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1b),
                        iVar8, iVar4, TVar6, BVar7, iVar11, BVar10, iVar12);
                    iVar4
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .objectsLeftUntilNextLevel;
                } else {
                    if (iVar8 <= iVar4)
                        goto LAB_0043f56c;
                    /*
                      added by script: "Bad things for next level:"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x1a, iVar5, iVar2 + 0x2d, OpenSHC::Text::TTA_LEFT, 0,
                        0x12, FALSE);
                    iVar4
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .objectsLeftUntilNextLevel;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    iVar4, local_4 + 0x11d + iVar1, iVar2 + 0x2d, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0, 0x12, TRUE, 0);
                goto LAB_0043f56c;
            }
            iVar4 = 0x18;
        } else {
            iVar4 = 0x19;
        }
        iVar11 = iVar2 + 0x2d;
        iVar13 = 0;
        BVar10 = FALSE;
        iVar12 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar8 = iVar5;
        /*
          added by script: "Maximum cruelty achieved."
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, iVar4),
            iVar8, iVar11, TVar6, BVar7, iVar12, BVar10, iVar13);
    LAB_0043f56c:
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            == 0) {
            iVar13 = 0;
            iVar12 = 0x12;
            uVar9 = 0;
            iVar11 = 0xfa;
            iVar4 = iVar2 + 0x4b;
            iVar8 = iVar5;
            /*
              added by script: "No effect on population."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 10),
                iVar8, iVar4, iVar11, uVar9, iVar12, iVar13);
        }
        if (0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel) {
            iVar13 = 0;
            iVar12 = 0x12;
            uVar9 = 0;
            iVar11 = 0xfa;
            iVar4 = iVar2 + 0x4b;
            iVar8 = iVar5;
            /*
              added by script: "People are happier, but idler."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0xb),
                iVar8, iVar4, iVar11, uVar9, iVar12, iVar13);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorLevel
            < 0) {
            iVar13 = 0;
            iVar12 = 0x12;
            uVar9 = 0;
            iVar11 = 0xfa;
            iVar4 = iVar2 + 0x4b;
            iVar8 = iVar5;
            /*
              added by script: "People are less happy, but more efficient."
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0xc),
                iVar8, iVar4, iVar11, uVar9, iVar12, iVar13);
        }
        iVar11 = 0;
        BVar10 = FALSE;
        iVar8 = 0x12;
        BVar7 = 0;
        TVar6 = OpenSHC::Text::TTA_LEFT;
        iVar4 = iVar2 + 0x7d;
        /*
          added by script: "Efficiency %:"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0x13),
            iVar5, iVar4, TVar6, BVar7, iVar8, BVar10, iVar11);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .fearFactorProductivityUnk,
            local_4 + 0x11d + iVar1, iVar2 + 0x7e, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0, 0x12, TRUE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
