#include "../DisplayElements.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AFE10
    void DisplayElements::RenderSomeMultiplayerInfoUnkDisplayElement19(int posX, int posY, DWORD elementState)
    {
        uint number;
        TextAlignment TVar3;
        BGR24 BVar4;
        int iVar5;
        int iVar6;
        BOOLEnum BVar7;
        int iVar8;
        int iVar9;
        if (DAT_GameCore::instance.mapU4Int0 != 0) {
            posY += 65;
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(
            posX - 204, posY, 408, (int)((DAT_GameSynchronyState::instance.connectionInfoExpanded * 3 + 12) * 16));
        iVar8 = 0;
        BVar7 = FALSE;
        iVar5 = 17;
        BVar4 = 0xc2f0eb;
        TVar3 = OpenSHC::Text::TTA_CENTER;
        iVar6 = posY + 0xf;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        iVar9 = posX;
        // "Connection lost"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 49),
            iVar9, iVar6, TVar3, BVar4, iVar5, BVar7, iVar8);
        iVar9 = 0;
        BVar7 = FALSE;
        iVar6 = 18;
        BVar4 = 0xc2f0eb;
        TVar3 = OpenSHC::Text::TTA_CENTER;
        // "Receiving game state"
        if (DAT_GameSynchronyState::instance.isHost) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 50),
                posX, posY + 45, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 51),
                posX, posY + 45, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            posX - 171, posY + 74, posX + 171, posY + 91, (ushort)(COL_WHITE::instance.shortValue));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
            posX - 170, posY + 75, posX + 170, posY + 90);
        if ((DAT_GameSynchronyState::instance.currentPacketTotalSize != 0)
            && (DAT_GameSynchronyState::instance.resyncTransferTotalSize != 0)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                posX - 170, posY + 75,
                ((int)(DAT_GameSynchronyState::instance.currentPacketTotalSize) * 340)
                        / (int)(DAT_GameSynchronyState::instance.resyncTransferTotalSize)
                    - 170 + posX,
                posY + 90, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes != 0) {
            if (DAT_GameSynchronyState::instance.lastAutoSaveTime == 0
                || DAT_GameSynchronyState::instance.field_0xbe8 == 0
                || DAT_GameSynchronyState::instance.field_0xbe8 <= DAT_GameSynchronyState::instance.lastAutoSaveTime) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 54),
                    posX, posY + 110, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
            } else {
                iVar6 = posY + 110;
                // "Auto save is on"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 54, posX - 3, iVar6, OpenSHC::Text::TTA_RIGHT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                // "Last saved:"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 55, posX + 3, iVar6, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                number
                    = (DAT_GameSynchronyState::instance.field_0xbe8 - DAT_GameSynchronyState::instance.lastAutoSaveTime)
                    / 60000;
                if (number < 1) {
                    number = 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    number, posX + 9, iVar6, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE,
                    0);
                // "minutes."
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 56, posX + 10, iVar6, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE);
            }
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 53),
                posX, posY + 110, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
        }
        iVar6 = posX - 100;
        DAT_ButtonX::instance = iVar6;
        DAT_ButtonY::instance = posY + 150;
        DAT_ButtonW::instance = 200;
        DAT_ButtonH::instance = 28;
        // "Cancel game"
        if (DAT_GameSynchronyState::instance.isHost) {
            if (DAT_GameSynchronyState::instance.connectionInfoExpanded == 0) {
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    (posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) - 100,
                    (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 150, 200, 28);
                if (BVar7) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 52),
                        posX, posY + 156, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                        0);
                    if (DAT_MouseState::instance.leftClickStart == 0) {
                        return;
                    }
                    DAT_GameSynchronyState::instance.connectionInfoExpanded = 1;
                    return;
                }
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 52),
                    posX, posY + 156, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 52),
                posX, posY + 156, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
            DAT_ButtonY::instance = posY + 198;
            DAT_ButtonX::instance = posX - 150;
            DAT_ButtonW::instance = 100;
            DAT_ButtonH::instance = 28;
            BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                (posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) - 150,
                (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 198, 150, 28);
            // "Yes"
            if (BVar7) {
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 22),
                    iVar6, posY + 204, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE, 0);
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_KILL_GAME);
                }
            } else {
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 22),
                    iVar6, posY + 204, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
            }
            DAT_ButtonY::instance = posY + 198;
            DAT_ButtonX::instance = posX + 50;
            DAT_ButtonW::instance = 100;
            DAT_ButtonH::instance = 28;
            BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                (posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) + 50,
                (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 198, 150, 28);
            // "No"
            if (BVar7) {
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 23),
                    posX + 100, posY + 204, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                    FALSE, 0);
                if (DAT_MouseState::instance.leftClickStart == 0) {
                    return;
                }
                DAT_GameSynchronyState::instance.connectionInfoExpanded = 0;
                return;
            }
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 23),
                posX + 100, posY + 204, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 52),
                posX, posY + 156, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F, 18, FALSE, 0);
        }
    }
}
}
