#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042A480
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance(int buttonID, ...)
        {
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            // DAT_ButtonUnknownZero is set for the host while one of three AI setup dialogs is open, and for a guest
            BOOLEnum const aiSetupOpen
                = DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT;
            if (aiSetupOpen) {
                DAT_ButtonUnknownZero::instance = TRUE;
            }
            if (!aiSetupOpen || !DAT_GameSynchronyState::instance.isHost) {
                DAT_ButtonUnknownZero::instance = FALSE;
                if (!DAT_GameSynchronyState::instance.isHost) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_ButtonUnknownZero::instance = TRUE;
                }
            }
            // the balance buttons (10 on) draw nothing; button 4 draws the bar
            if (buttonID < 20 && buttonID >= 10) {
                return;
            }
            // the fade is written the long way round, as the original computes it; it comes back to the blend strength
            // 4: the balance bar and its marker
            if (buttonID == 4) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 674,
                    DAT_ButtonX::instance, DAT_ButtonY::instance,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                    DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance + 674,
                    DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance * 70 - 50 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            // 20: the game type, who the balance favours, and each side's starting gold
            if (buttonID == 20) {
                // the arguments in locals, in the order they are pushed (written into the call, the match is lost)
                int const blend = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32;
                int const y = DAT_ButtonY::instance + 1;
                int const x = DAT_ButtonX::instance + 180;
                int const index = DAT_GameSynchronyState::instance.skirmishGameIntensityType - 1;
                // "Normal Game", "Crusader Game" or "Deathmatch Game"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_TYPE, index),
                    x, y, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, blend);
                if ((int)DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance < 3) {
                    // "Human Advantage"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_TYPE, 3, DAT_ButtonX::instance + 180,
                        DAT_ButtonY::instance + 26, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                        19, FALSE, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                if ((int)DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance > 3) {
                    // "Computer Advantage"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_TYPE, 4, DAT_ButtonX::instance + 180,
                        DAT_ButtonY::instance + 26, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF,
                        19, FALSE, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 730,
                    DAT_ButtonX::instance + 165, DAT_ButtonY::instance + 41,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                // the extreme trail's skirmishes start with three times the gold; the original compares the flag with 1
                int goldMultiplier = 1;
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER
                    && DAT_GameCore::instance.isSkirmishTrail == TRUE
                    && DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    goldMultiplier = 3;
                }
                // the human side's starting gold, then the computer side's
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_RenderingDefinedData::instance
                            .StartGoldPerFairnessLevel[DAT_GameSynchronyState::instance.skirmishGameIntensityType
                                - 1][DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance - 1][0]
                        * goldMultiplier,
                    DAT_ButtonX::instance + 110, DAT_ButtonY::instance + 48, OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_RenderingDefinedData::instance
                            .StartGoldPerFairnessLevel[DAT_GameSynchronyState::instance.skirmishGameIntensityType
                                - 1][DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance - 1][1]
                        * goldMultiplier,
                    DAT_ButtonX::instance + 250, DAT_ButtonY::instance + 48, OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            if (buttonID > 3) {
                return;
            }
            // 1 to 3: the game types, the chosen one drawn pressed
            if (buttonID == DAT_GameSynchronyState::instance.skirmishGameIntensityType) {
                int const picture
                    = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                          .pictureInGm_0x4
                    + 1;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::IO::Graphics::GmID)DAT_UIButtonDefinedData::instance
                                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                          .gmId_0x0,
                    picture, DAT_ButtonX::instance, DAT_ButtonY::instance,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                DAT_CurrentButtonPictureInGm::instance = picture;
                // the original reads the type again behind the draw. The draw target goes back in both arms: set back
                // once, in front of this test, the match is lost
                if (buttonID == DAT_GameSynchronyState::instance.skirmishGameIntensityType) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            // not the chosen type, or no longer after the draw: the plain button
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
        }

    }
}
}
