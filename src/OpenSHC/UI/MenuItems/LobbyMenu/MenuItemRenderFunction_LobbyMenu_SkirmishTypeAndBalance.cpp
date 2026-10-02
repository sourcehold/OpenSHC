#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::Game::TrailType;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Rendering::Colors::BGR24;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042A480
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_SkirmishTypeAndBalance(int param_1, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            char* textAddress;
            int iVar3;
            int xParam;
            int _goldMultiplier;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            if (BVar1 == FALSE) {
                _goldMultiplier = 1;
                if (((((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_ROUNDTABLE)
                          && (DAT_MenuModalComposition1::instance.activeModalDialogID
                              != OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT))
                         && (DAT_MenuModalComposition1::instance.activeModalDialogID
                             != OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT))
                        || (DAT_ButtonUnknownZero::instance = 1, DAT_GameSynchronyState::instance.isHost == FALSE))
                    && (DAT_ButtonUnknownZero::instance = 0, DAT_GameSynchronyState::instance.isHost == FALSE)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if ((0x13 < param_1) || (param_1 < 10)) {
                    if (param_1 == 4) {
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x2a2,
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                            ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            (int)((int)(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance + 0x2a2)),
                            (int)((int)(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance * 0x46 + -0x32
                                + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance)), ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    if (param_1 == 0x14) {
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        iVar2 = ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                        BVar1 = FALSE;
                        fontSize = 0x11;
                        color = 0xccfaff;
                        alignment = OpenSHC::Text::TTA_CENTER;
                        iVar3 = DAT_ButtonY::instance + 1;
                        xParam = DAT_ButtonX::instance + 0xb4;
                        MACRO_CALL_MEMBER( OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_TYPE, DAT_GameSynchronyState::instance.skirmishGameIntensityType + -1), xParam, iVar3, alignment, color, fontSize, BVar1, iVar2);
                        if (DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance < 3) {
                            iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_TYPE, 3,
                                (int)((int)(DAT_ButtonX::instance + 0xb4)), (int)((int)(DAT_ButtonY::instance + 0x1a)),
                                OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x13, FALSE,
                                ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        if (3 < DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance) {
                            iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAME_TYPE, 4,
                                (int)((int)(DAT_ButtonX::instance + 0xb4)), (int)((int)(DAT_ButtonY::instance + 0x1a)),
                                OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x13, FALSE,
                                ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            (int)((int)(730)), (int)((int)(DAT_ButtonX::instance + 0xa5)),
                            (int)((int)(DAT_ButtonY::instance + 0x29)),
                            ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        if (((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER)
                                && (DAT_GameCore::instance.isSkirmishTrail == TRUE))
                            && (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME)) {
                            _goldMultiplier = 3;
                        }
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_RenderingDefinedData::instance
                                    .field451_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                                          + DAT_GameSynchronyState::instance.skirmishGameIntensityType
                                                              * 5)
                                            * 2
                                        + 0xc]
                                * _goldMultiplier,
                            (int)((int)(DAT_ButtonX::instance + 110)), (int)((int)(DAT_ButtonY::instance + 0x30)),
                            OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE,
                            ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_RenderingDefinedData::instance
                                    .field451_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                                          + DAT_GameSynchronyState::instance.skirmishGameIntensityType
                                                              * 5)
                                            * 2
                                        + 0xd]
                                * _goldMultiplier,
                            (int)((int)(DAT_ButtonX::instance + 250)), (int)((int)(DAT_ButtonY::instance + 0x30)),
                            OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE,
                            ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                    } else if (param_1 < 4) {
                        if (param_1 == DAT_GameSynchronyState::instance.skirmishGameIntensityType) {
                            iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            iVar3 = DAT_UIButtonDefinedData::instance
                                        .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                        .pictureInGm_0x4
                                + 1;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)((OpenSHC::IO::Graphics::GmID)(DAT_UIButtonDefinedData::instance
                                    .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                    .gmId_0x0),
                                iVar3, (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                                ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                            DAT_CurrentButtonPictureInGm::instance = iVar3;
                            if (param_1 == DAT_GameSynchronyState::instance.skirmishGameIntensityType) {
                                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                    = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                return;
                            }
                        }
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                            ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        return;
                    }
                }
            }
            return;
        }

    }
}
}
