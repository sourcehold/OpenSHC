#include "../DisplayElements.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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

    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
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
            posY = posY + 0x41;
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX + -0xcc, posY, 0x198,
            (int)((DAT_GameSynchronyState::instance.connectionInfoExpanded * 3 + 0xc) * 0x10));
        iVar8 = 0;
        BVar7 = FALSE;
        iVar5 = 0x11;
        BVar4 = 0xc2f0eb;
        TVar3 = OpenSHC::Text::TTA_CENTER;
        iVar6 = posY + 0xf;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        iVar9 = posX;
        /*
          added by script: "Connection lost"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x31),
            iVar9, iVar6, TVar3, BVar4, iVar5, BVar7, iVar8);
        iVar9 = 0;
        BVar7 = FALSE;
        iVar6 = 0x12;
        BVar4 = 0xc2f0eb;
        TVar3 = OpenSHC::Text::TTA_CENTER;
        /*
          added by script: "Receiving game state"
         */
        if (DAT_GameSynchronyState::instance.isHost != FALSE) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x32),
                posX, posY + 0x2d, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x33),
                posX, posY + 0x2d, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            posX + -0xab, posY + 0x4a, posX + 0xab, posY + 0x5b, (ushort)(COL_WHITE::instance.shortValue));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
            posX + -0xaa, posY + 0x4b, posX + 0xaa, posY + 0x5a);
        if ((DAT_GameSynchronyState::instance.currentPacketTotalSize != 0)
            && (DAT_GameSynchronyState::instance.resyncTransferTotalSize != 0)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                posX + -0xaa, posY + 0x4b,
                ((int)(DAT_GameSynchronyState::instance.currentPacketTotalSize) * 0x154)
                        / (int)(DAT_GameSynchronyState::instance.resyncTransferTotalSize)
                    + -0xaa + posX,
                posY + 0x5a, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
        }
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes != 0) {
            if (DAT_GameSynchronyState::instance.lastAutoSaveTime == 0
                || DAT_GameSynchronyState::instance.field76_0xbe8 == 0
                || DAT_GameSynchronyState::instance.field76_0xbe8
                    <= DAT_GameSynchronyState::instance.lastAutoSaveTime) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x36),
                    posX, posY + 0x6e, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
            } else {
                iVar6 = posY + 0x6e;
                /*
                  added by script: "Auto save is on"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x36, posX + -3, iVar6, OpenSHC::Text::TTA_RIGHT,
                    0xc2f0eb, 0x12, FALSE);
                /*
                  added by script: "Last saved:"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x37, posX + 3, iVar6, OpenSHC::Text::TTA_LEFT,
                    0xc2f0eb, 0x12, FALSE);
                number = (DAT_GameSynchronyState::instance.field76_0xbe8
                             - DAT_GameSynchronyState::instance.lastAutoSaveTime)
                    / 60000;
                if (number < 1) {
                    number = 1;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    number, posX + 9, iVar6, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x12, TRUE, 0);
                /*
                  added by script: "minutes."
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x38, posX + 10, iVar6, OpenSHC::Text::TTA_LEFT,
                    0xc2f0eb, 0x12, TRUE);
            }
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x35),
                posX, posY + 0x6e, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
        }
        iVar6 = posX + -100;
        DAT_ButtonX::instance = iVar6;
        DAT_ButtonY::instance = posY + 0x96;
        DAT_ButtonW::instance = 200;
        DAT_ButtonH::instance = 0x1c;
        /*
          added by script: "Cancel game"
         */
        if (DAT_GameSynchronyState::instance.isHost != FALSE) {
            if (DAT_GameSynchronyState::instance.connectionInfoExpanded == 0) {
                BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                    (posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) + -100,
                    (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 0x96, 200, 0x1c);
                if (BVar7 != FALSE) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x34),
                        posX, posY + 0x9c, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 0);
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
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x34),
                    posX, posY + 0x9c, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x34),
                posX, posY + 0x9c, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 0);
            DAT_ButtonY::instance = posY + 0xc6;
            DAT_ButtonX::instance = posX + -0x96;
            DAT_ButtonW::instance = 100;
            DAT_ButtonH::instance = 0x1c;
            BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                (posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) + -0x96,
                (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 0xc6, 0x96, 0x1c);
            /*
              added by script: "Yes"
             */
            if (BVar7 != FALSE) {
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x16),
                    iVar6, posY + 0xcc, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 0);
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
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x16),
                    iVar6, posY + 0xcc, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
            }
            DAT_ButtonY::instance = posY + 0xc6;
            DAT_ButtonX::instance = posX + 0x32;
            DAT_ButtonW::instance = 100;
            DAT_ButtonH::instance = 0x1c;
            BVar7 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                (posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX) + 0x32,
                (posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY) + 0xc6, 0x96, 0x1c);
            /*
              added by script: "No"
             */
            if (BVar7 != FALSE) {
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x17),
                    posX + 100, posY + 0xcc, OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE, 0);
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
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x17),
                posX + 100, posY + 0xcc, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x34),
                posX, posY + 0x9c, OpenSHC::Text::TTA_CENTER, 0x7f7f7f, 0x12, FALSE, 0);
        }
    }
}
}
