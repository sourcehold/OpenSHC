#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

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
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00465A20
            void MenuItemRenderFunction_BuildingAndStatusMenu_BuySellMenuButtonsAndHands(int button, ...)
            {
                // 2 and 3 are the hands, shown only while some goods may be sold.
                if (button == 2 || button == 3) {
                    DAT_ButtonUnknownZero::instance = 1;
                    if (!MACRO_CALL_MEMBER(
                            Game::GameStateStructures_Func::anyGoodsAreAllowedForSale, DAT_GameState::ptr)()) {
                        return;
                    }
                    DAT_ButtonUnknownZero::instance = 0;
                    if (DAT_ButtonCurrentlyInteracting::instance && button == 2) {
                        DAT_ButtonX::instance -= 4;
                    }
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    return;
                }
                // 0 is buy and 1 is sell: the label and the price of the selected goods, centred on the button.
                // The text number stays written out as button + 5: a local for it moves the registers.
                MACRO_CALL(General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    int const width
                        = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                              MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                  DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_TRADEPOST, button + 5),
                              17)
                        + 53;
                    // y before x, as the original loads them.
                    int const labelY = DAT_ButtonY::instance + 11;
                    int const labelX = (DAT_ButtonW::instance - width) / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_TRADEPOST, button + 5),
                        labelX, labelY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 0, 17, FALSE, 0);
                    int price;
                    if (button == 0) {
                        price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getBatchBuyPrice, DAT_GameState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType);
                    } else {
                        price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalesPrice, DAT_GameState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID,
                            DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .marketSelectedResourceType);
                    }
                    // The x is written out again in both branches: labelX + 20 loses the match.
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(price,
                        (DAT_ButtonW::instance - width) / 2 + DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 10,
                        Text::TTA_LEFT, 0, 17, TRUE, 0);
                    return;
                }
                // Hovered: the same again (drawn once before the test, it loses the match), then the deal.
                int const width
                    = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                          MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                              DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_TRADEPOST, button + 5),
                          17)
                    + 53;
                // y before x, as the original loads them.
                int const labelY = DAT_ButtonY::instance + 11;
                int const labelX = (DAT_ButtonW::instance - width) / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_IN_TRADEPOST, button + 5),
                    labelX, labelY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_FFFFFF, 0, 17, FALSE, 0);
                int price;
                if (button == 0) {
                    price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getBatchBuyPrice, DAT_GameState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                } else {
                    price = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSalesPrice, DAT_GameState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                }
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(price,
                    (DAT_ButtonW::instance - width) / 2 + DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 10,
                    Text::TTA_LEFT, 0, 17, TRUE, 0);
                // Before the fail test, as in the original; amount = 5 first and the call after it loses the match.
                int amount;
                if (button == 1) {
                    amount = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::getSellResourceAmount,
                        DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .marketSelectedResourceType);
                } else {
                    amount = 5;
                }
                int const failState
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .storageMarketFailState;
                if (failState != 0) {
                    // Why the last deal failed, for a second: 9 "Not enough gold", 10 "Not enough goods", 13 to 18
                    // "No Granary built" to "No space in Armory".
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_IN_TRADEPOST, failState + 8, DAT_MenuHandlerState::instance.x + 220,
                        DAT_MenuHandlerState::instance.y + 579, Text::TTA_LEFT, 0, 18, FALSE);
                    // The call comes before the field load, as in the original.
                    DWORD const now = timeGetTime();
                    if ((int)(now
                            - DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .timeStorageMarketFailState)
                        > 1000) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .storageMarketFailState = 0;
                    }
                    return;
                }
                // "Buy" or "Sell", the amount, the goods, the price, "gold"
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_IN_TRADEPOST, button + 5, DAT_MenuHandlerState::instance.x + 220,
                    DAT_MenuHandlerState::instance.y + 579, Text::TTA_LEFT, 0, 18, FALSE);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(amount,
                    DAT_MenuHandlerState::instance.x + 222, DAT_MenuHandlerState::instance.y + 579, Text::TTA_LEFT, 0,
                    18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_GOODS,
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .marketSelectedResourceType,
                    DAT_MenuHandlerState::instance.x + 224, DAT_MenuHandlerState::instance.y + 579, Text::TTA_LEFT, 0,
                    18, TRUE);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(price,
                    DAT_MenuHandlerState::instance.x + 240, DAT_MenuHandlerState::instance.y + 579, Text::TTA_LEFT, 0,
                    18, TRUE, 0);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_IN_TRADEPOST, 12, DAT_MenuHandlerState::instance.x + 244,
                    DAT_MenuHandlerState::instance.y + 579, Text::TTA_LEFT, 0, 18, TRUE);
            }

        }
    }
}
}
