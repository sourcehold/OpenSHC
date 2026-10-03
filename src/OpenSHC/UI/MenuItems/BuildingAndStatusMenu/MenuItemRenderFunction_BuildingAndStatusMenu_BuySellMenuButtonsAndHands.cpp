#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeInt.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::Resources::ResourceTypeInt;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00465A20
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(
            int param_1, ...)
        {
            ResourceTypeInt RVar1;
            char* pcVar2;
            int iVar3;
            int iVar4;
            DWORD _now;
            int iVar5;
            TextAlignment TVar6;
            uint uVar7;
            uint uVar8;
            int iVar9;
            BOOLEnum BVar10;
            int iVar11;
            int iVar12;
            if ((param_1 == 2) || (param_1 == 3)) {
                DAT_ButtonUnknownZero::instance = 1;
                BVar10 = MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::anyGoodsAreAllowedForSale, DAT_GameState::ptr)();
                if (BVar10 != FALSE) {
                    DAT_ButtonUnknownZero::instance = 0;
                    if ((DAT_ButtonCurrentlyInteracting::instance != FALSE) && (param_1 == 2)) {
                        DAT_ButtonX::instance = DAT_ButtonX::instance + -4;
                    }
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                }
            } else {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                iVar4 = param_1 + 5;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    iVar11 = 0x11;
                    iVar11 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, iVar4),
                        iVar11);
                    iVar12 = 0;
                    BVar10 = FALSE;
                    iVar9 = 0x11;
                    uVar8 = 0;
                    uVar7 = 0xffffff;
                    TVar6 = OpenSHC::Text::TTA_LEFT;
                    iVar5 = DAT_ButtonY::instance + 0xb;
                    iVar3 = (DAT_ButtonW::instance - (iVar11 + 0x35)) / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, iVar4),
                        iVar3, iVar5, TVar6, uVar7, uVar8, iVar9, BVar10, iVar12);
                    RVar1
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .marketSelectedResourceType;
                    if (param_1 == 0) {
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBatchBuyPrice,
                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)(RVar1));
                    } else {
                        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalesPrice,
                            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)(RVar1));
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(iVar4,
                        (int)((DAT_ButtonW::instance - (iVar11 + 0x35)) / 2 + 0x14 + DAT_ButtonX::instance),
                        (int)(DAT_ButtonY::instance + 10), OpenSHC::Text::TTA_LEFT, 0, 0x11, TRUE, 0);
                }
                iVar11 = 0x11;
                iVar11
                    = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, iVar4),
                        iVar11);
                iVar12 = 0;
                BVar10 = FALSE;
                iVar9 = 0x11;
                uVar8 = 0;
                uVar7 = 0xffffff;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar5 = DAT_ButtonY::instance + 0xb;
                iVar3 = (DAT_ButtonW::instance - (iVar11 + 0x35)) / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, iVar4),
                    iVar3, iVar5, TVar6, uVar7, uVar8, iVar9, BVar10, iVar12);
                RVar1 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType;
                if (param_1 == 0) {
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getBatchBuyPrice,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)(RVar1));
                } else {
                    iVar3 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSalesPrice,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)(RVar1));
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    iVar3, (int)((DAT_ButtonW::instance - (iVar11 + 0x35)) / 2 + 0x14 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 10), OpenSHC::Text::TTA_LEFT, 0, 0x11, TRUE, 0);
                if (param_1 == 1) {
                    iVar11 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getSellResourceAmount,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        (int)(DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType));
                } else {
                    iVar11 = 5;
                }
                iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState;
                if (iVar5 == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, iVar4, DAT_MenuHandlerState::instance.x + 0xdc,
                        DAT_MenuHandlerState::instance.y + 0x243, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(iVar11, DAT_MenuHandlerState::instance.x + 0xde,
                        DAT_MenuHandlerState::instance.y + 0x243, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_GOODS,
                        (int)(DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType),
                        DAT_MenuHandlerState::instance.x + 0xe0, DAT_MenuHandlerState::instance.y + 0x243,
                        OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(iVar3, DAT_MenuHandlerState::instance.x + 0xf0,
                        DAT_MenuHandlerState::instance.y + 0x243, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
                    /*
                      added by script: "gold"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, 0xc, DAT_MenuHandlerState::instance.x + 0xf4,
                        DAT_MenuHandlerState::instance.y + 0x243, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_IN_TRADEPOST, iVar5 + 8, DAT_MenuHandlerState::instance.x + 0xdc,
                    DAT_MenuHandlerState::instance.y + 0x243, OpenSHC::Text::TTA_LEFT, 0, 0x12, FALSE);
                _now = timeGetTime();
                if (1000 < (int)(_now
                        - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .timeStorageMarketFailState)) {
                    /*
                      Resets the market fail state after 1 second
                     */
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .storageMarketFailState = 0;
                }
            }
        }

    }
}
}
