#include "../AlliesSendAndRequestGoods.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SentOrRequestedGoodsAmount.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AD920
        void AlliesSendAndRequestGoods::MenuItemRenderFunction_AlliesSendAndRequestGoods_Main(int actionParam, ...)
        {
            // a resource's button: its picture, pressed or not, and how much of it the player has
            if (actionParam <= 20) {
                int xOffset = 0;
                if (actionParam == 6 || actionParam == 11 || actionParam == 20) {
                    xOffset = 8;
                }
                // from the button's number to the resource's: two numbers are skipped, and 14 stands for 23
                if (actionParam >= 4) {
                    ++actionParam;
                }
                if (actionParam >= 6) {
                    ++actionParam;
                }
                if (actionParam == 14) {
                    actionParam = 23;
                }
                // the call stands in each arm (one call with the picture chosen in it measures lower)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                        actionParam * 2 + 617, DAT_ButtonX::instance + xOffset, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                        actionParam * 2 + 618, DAT_ButtonX::instance + xOffset, DAT_ButtonY::instance);
                }
                if (actionParam + 1 == 8) {
                    --actionParam;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[actionParam + 1],
                    DAT_ButtonX::instance + 21, DAT_ButtonY::instance + 40, OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 19, FALSE, 0);
            } else if (actionParam == 21) {
                // the gold button
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 645, DAT_ButtonX::instance, DAT_ButtonY::instance);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 646, DAT_ButtonX::instance, DAT_ButtonY::instance);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[OpenSHC::Game::Resources::RT_GOLD],
                    DAT_ButtonX::instance + 21, DAT_ButtonY::instance + 20, OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 19, FALSE, 0);
                return;
            }
            if (actionParam == 40) {
                // the panel: a frame of 24-pixel pieces, a dark box in it, and what is being sent or asked for
                int const x = DAT_ButtonX::instance;
                int const y = DAT_ButtonY::instance;
                for (int row = 0; row < (int)DAT_ButtonH::instance; row += 24) {
                    int picture;
                    if (row == 0) {
                        picture = 1;
                    } else if (row == (int)DAT_ButtonH::instance - 24) {
                        picture = 13;
                    } else {
                        picture = 7;
                    }
                    for (int column = 0; column < 552; column += 24) {
                        // the left and right ends of every row, and all of the first and the last row
                        int piece = picture;
                        if (column != 0) {
                            if (column == 528) {
                                piece = picture + 2;
                            } else if (picture == 7) {
                                continue;
                            } else {
                                piece = picture + 1;
                            }
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, piece,
                            column + x, row + y, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, piece + 3, 0);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(x + 24, y + 24, x + 527, (int)DAT_ButtonH::instance - 25 + y, 20);
                int goods = DAT_RequestedGoodsByWhoArray::instance[0];
                if (goods == 6) {
                    goods = 7;
                } else if (goods <= 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES, 13),
                        DAT_ButtonX::instance + 36, DAT_ButtonY::instance + 36, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                    return;
                }
                // the three values both arms use are read first (read inside the arms, the match drops)
                int const goodsX = DAT_ButtonX::instance + 36;
                int const amount = DAT_SentOrRequestedGoodsAmount::instance;
                int const goodsY = DAT_ButtonY::instance;
                if (amount == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, goods * 2 + 618, goodsX, goodsY + 24);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_ALLIES, 14),
                        DAT_ButtonX::instance + 84, DAT_ButtonY::instance + 36, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(amount,
                    goodsX, goodsY + 36, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 17, FALSE,
                    0);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, goods * 2 + 618,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + 46 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 24);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_GOODS, DAT_RequestedGoodsByWhoArray::instance[0] + 1),
                    DAT_ButtonX::instance + 96, DAT_ButtonY::instance + 36, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 17, TRUE, 0);
                return;
            }
            // the amount buttons
            if (actionParam >= 100) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
                return;
            }
            if (actionParam < 50) {
                return;
            }
            MACRO_CALL(
                OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
            if (actionParam == 50) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(10,
                    DAT_ButtonX::instance + 18, DAT_ButtonY::instance + 16, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                return;
            }
            if (actionParam == 51) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(25,
                    DAT_ButtonX::instance + 15, DAT_ButtonY::instance + 16, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                return;
            }
            if (actionParam == 52) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(100,
                    DAT_ButtonX::instance + 12, DAT_ButtonY::instance + 16, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                return;
            }
            if (actionParam == 53) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(5,
                    DAT_ButtonX::instance + 21, DAT_ButtonY::instance + 16, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                return;
            }
            if (actionParam == 54) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(500,
                    DAT_ButtonX::instance + 11, DAT_ButtonY::instance + 16, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
            }
        }

    }
}
}
