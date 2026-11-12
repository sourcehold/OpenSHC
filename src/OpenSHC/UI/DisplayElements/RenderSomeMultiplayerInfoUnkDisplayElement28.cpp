#include "../DisplayElements.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
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
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B2530
        void RenderSomeMultiplayerInfoUnkDisplayElement28(int posX, int posY, DWORD elementState)
        {
            DWORD const currentTime = timeGetTime();
            if (DAT_GameCore::instance.mapU4Int0 != 0) {
                posY += 65;
            }
            // Nested, not early returns (early returns: quick_diff 0.9395 -> 0.6573)
            if (DAT_GameSynchronyState::instance.DAT_SomeTime == 0) {
                if (DAT_GameSynchronyState::instance.isHost) {
                    if (DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.laggingPlayerIDUnk]
                        == -1) {
                        DAT_GameSynchronyState::instance.DAT_SomeTime = currentTime;
                        // "Timed Out"
                        DAT_GameSynchronyState::instance.lagNotificationCode = 65;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_99);
                    } else if (currentTime
                            - DAT_GameSynchronyState::instance
                                .connectionLagInfoArray[DAT_GameSynchronyState::instance.laggingPlayerIDUnk]
                                .time
                        <= 10000) {
                        DAT_GameSynchronyState::instance.DAT_SomeTime = currentTime;
                        // "Back in the Game!"
                        DAT_GameSynchronyState::instance.lagNotificationCode = 67;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_99);
                    }
                }
            } else if (currentTime - DAT_GameSynchronyState::instance.DAT_SomeTime > 2000) {
                DAT_GameSynchronyState::instance.DAT_SomeTime = 0;
                DAT_GameSynchronyState::instance.laggingPlayerIDUnk = 0;
                MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                    OpenSHC::UI::Enums::DEID_SOME_MULTIPLAYER_INFO_Unk_28, 0);
                return;
            }
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(posX - 204, posY, 408, 96);
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            int const textY = posY + 20;
            int const textX = posX - 190;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.finalResults
                    .names[DAT_GameSynchronyState::instance.laggingPlayerIDUnk],
                textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
            // ": Not Responding", after the name
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 64),
                textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
            if (DAT_GameSynchronyState::instance.DAT_SomeTime == 0) {
                DAT_ButtonX::instance = posX;
                DAT_ButtonY::instance = posY + 52;
                DAT_ButtonW::instance = 180;
                DAT_ButtonH::instance = 28;
                if (DAT_GameSynchronyState::instance.isHost) {
                    // Seconds until the player is dropped (60 s after their last message), shown as 50 at most
                    int secondsLeft = 60
                        - (currentTime
                              - DAT_GameSynchronyState::instance
                                  .connectionLagInfoArray[DAT_GameSynchronyState::instance.laggingPlayerIDUnk]
                                  .time)
                            / 1000;
                    if (secondsLeft > 50) {
                        secondsLeft = 50;
                    } else if (secondsLeft < 0) {
                        secondsLeft = 0;
                    }
                    int const buttonTextY = posY + 58;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(secondsLeft, posX - 102, buttonTextY, OpenSHC::Text::TTA_CENTER,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                    if (MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                            posX - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX,
                            posY - DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY + 52, 180,
                            28)) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        // "Eject", highlighted
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 91),
                            posX + 90, buttonTextY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                            18, FALSE, 0);
                        if (!DAT_MouseState::instance.leftClickStart) {
                            return;
                        }
                        DAT_GameSynchronyState::instance.DAT_SomeTime = timeGetTime();
                        // "Ejected"
                        DAT_GameSynchronyState::instance.lagNotificationCode = 66;
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_UNKNOWN_99);
                        return;
                    }
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    // "Eject"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 91),
                        posX + 90, buttonTextY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                        FALSE, 0);
                    return;
                }
                // "Eject", greyed out: only the host can eject
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 91),
                    posX + 90, posY + 58, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F, 18, FALSE,
                    0);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION,
                    DAT_GameSynchronyState::instance.lagNotificationCode),
                posX, posY + 58, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
        }

    }
}
}
