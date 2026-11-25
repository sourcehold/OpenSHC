#include "../AlliesOrder.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00df51f8.hpp"
#include "OpenSHC/Globals/DAT_00df51fc.hpp"
#include "OpenSHC/Globals/DAT_00df5200.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_EnemyArrayIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AD480
        void AlliesOrder::MenuItemRenderFunction_AlliesOrder_Main(int button, ...)
        {
            if (button == -2) {
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                return;
            }
            if (button >= 10) {
                // the dialog's other buttons; hovered, 10 and 11 set the tooltip
                if (button == 10) {
                    DAT_00df5200::instance = 0;
                }
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    if (button == 10) {
                        // "Clear Orders"
                        DAT_00df5200::instance = OpenSHC::DE::SHCDE::TEXT_ALLIES;
                        DAT_00df51fc::instance = 8;
                        return;
                    }
                    if (button == 11) {
                        // "Defend Me"
                        DAT_00df5200::instance = OpenSHC::DE::SHCDE::TEXT_ALLIES;
                        DAT_00df51fc::instance = 9;
                        return;
                    }
                }
            }
            // buttons 1 to 6 are the enemies' portraits; button turns into the row, then the player (one register)
            if (button <= 6 && button != -1) {
                --button;
                if (button >= DAT_EnemyArrayIndex::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonX::instance + 71, DAT_ButtonY::instance + 71, COL_BLACK::instance.shortValue);
                } else {
                    button = DAT_RequestedGoodsByWhoArray::instance[button + 1];
                    int ai = 0;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[button] == -1) {
                        ai = DAT_GameSynchronyState::instance.currentAIArray[button];
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, button + 546,
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                    if (ai == 0) {
                        // a human: the lord's icon, or the own face
                        if (DAT_GameCore::instance.lordIcons[button] == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 539,
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                        } else if (DAT_GameCore::instance.lordIcons[button] == 1) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 540,
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                        } else if (DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[button + 19] > 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 541,
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                                DAT_TextureRenderCoreObject::ptr)(
                                button + 19, DAT_ButtonX::instance + 4, DAT_ButtonY::instance + 4);
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, ai + 522,
                            DAT_ButtonX::instance, DAT_ButtonY::instance);
                    }
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 514,
                            DAT_ButtonX::instance - 6, DAT_ButtonY::instance - 6,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 513, 0);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 574,
                            DAT_ButtonX::instance - 10, DAT_ButtonY::instance - 8,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 575, 0);
                        // "Attack"
                        DAT_00df5200::instance = OpenSHC::DE::SHCDE::TEXT_ALLIES;
                        DAT_00df51fc::instance = 10;
                        DAT_00df51f8::instance = button;
                    }
                }
            }
            if (button != -1) {
                return;
            }
            // -1 draws the tooltip set by the hovered button, for a portrait with the player's name
            if (DAT_00df5200::instance == 0) {
                return;
            }
            int const x = DAT_ButtonX::instance;
            int const y = DAT_ButtonY::instance;
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    (OpenSHC::DE::SHCDE::eTextSections)DAT_00df5200::instance, DAT_00df51fc::instance),
                x, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
            if (DAT_00df51fc::instance == 10) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_00df51f8::instance] != -1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df51f8::instance], x + 5, y,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, TRUE, 0);
                    DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    return;
                }
                // the AI's name
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.currentAIArray[DAT_00df51f8::instance] * 8
                        + DAT_GameSynchronyState::instance.aiVariationArray[DAT_00df51f8::instance] + 103,
                    x + 5, y, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, TRUE);
            }
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }

    }
}
}
