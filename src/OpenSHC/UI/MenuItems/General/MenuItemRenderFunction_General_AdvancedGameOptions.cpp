#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00428AC0
        void General::MenuItemRenderFunction_General_AdvancedGameOptions(int param_1, ...)
        {
            int iVar1;
            uint _color;
            int iVar2;
            if (((DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_LOAD_MAP)
                    || (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_SEND_MAP_TO))
                || (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM)) {}
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == OpenSHC::UI::Enums::MMT_SKIRMISH_PLAY_OPTIONS) {
                if ((((param_1 != -1000) && (param_1 != -10))
                        && ((param_1 != -0xb && ((param_1 != -0xc && (param_1 != -0xd))))))
                    && ((param_1 != -0xe
                        && (((((param_1 != 99 && (param_1 != 100)) && (param_1 != 0x53))
                                 && ((param_1 != 0x6d && (param_1 != 0x52))))
                            && (param_1 != 0x5e)))))) {}
            } else {
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {}
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT) {}
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {}
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (param_1 == 0x5d) {}
                if (param_1 == 0x1f) {}
            }
            if ((param_1 == 0x67)
                && (DAT_ButtonUnknownZero::instance = 0,
                    DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                if (param_1 == 0x67) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 0x5d) {}
            }
            if (param_1 == -1) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            if (param_1 != 0x67) {
                if ((DAT_ButtonCurrentlyInteracting::instance == FALSE)
                    || (DAT_GameSynchronyState::instance.isHost == FALSE)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                        AlphaAndButtonSurfaceObj::ptr)(DAT_ButtonBackgroundBlendStrength::instance);
                    _color = 0xc2f0eb;
                } else {
                    _color = 0xccfaff;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                }
            }
            if (param_1 == 0x1f) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                iVar2 = DAT_GameSynchronyState::instance.skirmishTechLevel / 2;
                /*
                  "Tech Level"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x55, (int)((int)(DAT_ButtonX::instance + 0x14)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                /*
                  "Early" "Middle" "Late"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar2 + 0x4f,
                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 == 0x24) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                /*
                  "Win: Regicide" / "Win: 10000 Gold" / "Win: 3" / "Win: 4" / "Win: 5" / ....
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)((int)(DAT_GameSynchronyState::instance.skirmishWinCondition + 0x24)),
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, _color, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 == 0x53) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                /*
                  "Troops"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x56, (int)((int)(DAT_ButtonX::instance + 0x14)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                iVar1 = 0x53;
                /*
                  "Free"
                 */
                if (DAT_GameSynchronyState::instance.skirmishTroopsCostGold != 0) {
                    /*
                      "Cost Gold"
                     */
                    iVar1 = 0x54;
                }
                iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar1,
                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                    ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 == 0x6d) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                /*
                  Fog of War
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x6d, (int)((int)(DAT_ButtonX::instance + 0x14)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                if (DAT_GameState::instance.mapAndTime.skirmishFogOfWar == 0) {
                    /*
                      OFF
                     */
                    iVar1 = 0x5f;
                } else {
                    /*
                      Please Wait
                     */
                    iVar1 = (DAT_GameState::instance.mapAndTime.skirmishFogOfWar != 1) + 0x6d;
                }
                iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar1,
                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                    ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 == -1000) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 0x11,
                    (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_CENTER, _color, 0x12, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
            }
            if (param_1 == 0x67) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
            iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20;
            if (param_1 == -10) {
                /*
                  No Cow Throwing
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 5, (int)((int)(DAT_ButtonX::instance + 0x14)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                iVar1 = DAT_GameSynchronyState::instance.skirmishNoCowThrowing;
            LAB_00428ffd:
                if (iVar1 != 0) {
                    iVar1 = DAT_ButtonW::instance + -0x32 + DAT_ButtonX::instance;
                    iVar2 = 0xce;
                    goto LAB_00429039;
                }
            } else {
                if (param_1 == -0xb) {
                    /*
                      "No Dogs"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 6,
                        (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 7)),
                        OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                    iVar1 = DAT_GameSynchronyState::instance.skirmishNoDogs;
                LAB_00429086:
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (iVar1 == 0) {
                        iVar1 = 0xd0;
                    } else {
                        iVar1 = 0xce;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar1,
                        (int)((int)(DAT_ButtonW::instance + -0x32 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance)));
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (param_1 == -0xd) {
                    /*
                      "Extreme mode"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 0xd,
                        (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 7)),
                        OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_GameSynchronyState::instance.skirmishExtremeMode == 0) {
                        iVar1 = 0xd0;
                    } else {
                        iVar1 = 0xce;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar1,
                        (int)((int)(DAT_ButtonW::instance + -0x32 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance)));
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (param_1 != -0xe) {
                    if (param_1 != 99) {
                        if (param_1 == -0xc) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7,
                                (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 7)),
                                OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 0) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 1) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x60,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 2) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x61,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 3) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x62,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 4) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 8,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting != 5) {}
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            /*
                              "1 Hour"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 9,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12,
                                FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                            (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 7)),
                            OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                        if (param_1 == 0xe) {
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2,
                                DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.skirmishStartGold,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12,
                                FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        if (param_1 == 0xf) {
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2,
                                DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.skirmishDefaultPopularity,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12,
                                FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        if (param_1 == 0x52) {
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2,
                                DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.skirmishGameSpeedLevel,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12,
                                FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        if (param_1 == 0x5e) {
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 0) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x5f,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x60,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x61,
                                    (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0,
                                    0x12, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes != 0x14) {}
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x62,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12,
                                FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        }
                        if (param_1 != 100) {}
                        iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                        /*
                          "Alliances"
                         */
                        if (DAT_GameSynchronyState::instance.skirmishAlliances == 0) {
                            /*
                              "Anytime"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x65,
                                (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                                (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12,
                                FALSE, iVar1);
                        }
                        /*
                          "Start only"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x66,
                            (int)((int)(DAT_ButtonW::instance + -0x14 + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_RIGHT, 0xb8e6f5, 0, 0x12, FALSE,
                            iVar1);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 99,
                        (int)((int)(DAT_ButtonX::instance + 0x14)), (int)((int)(DAT_ButtonY::instance + 7)),
                        OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                    iVar1 = DAT_GameSynchronyState::instance.skirmishStrongWalls;
                    goto LAB_00429086;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 0xe, (int)((int)(DAT_ButtonX::instance + 0x14)),
                    (int)((int)(DAT_ButtonY::instance + 7)), OpenSHC::Text::TTA_LEFT, _color, 0x12, FALSE, iVar1);
                iVar1 = DAT_GameSynchronyState::instance.skirmishExtremeMode;
                if (DAT_GameSynchronyState::instance.skirmishExtremeMode2 != 0)
                    goto LAB_00428ffd;
            }
            iVar1 = DAT_ButtonW::instance + -0x32 + DAT_ButtonX::instance;
            iVar2 = 0xd0;
        LAB_00429039:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar2, iVar1, (int)((int)(DAT_ButtonY::instance)));
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
