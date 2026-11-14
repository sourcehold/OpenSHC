#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

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

        // The 23 `((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20` below are each a signed
        // `iVar1 / 32`, and undiv.py rewrites them, but measured: raw match 40.4% -> 24.6%. The
        // opcodes are unchanged - the division frees a register, MSVC then picks ebx where the
        // original uses edi, and every instruction after it is renamed. Normalized match rises
        // 41.1% -> 48.1%, so the division is arguably the closer stream; it is kept in the shift
        // form only because the raw percentage is the gate. Retry together with whatever fixes
        // this function's register allocation.
        // FUNCTION: STRONGHOLDCRUSADER 0x00428AC0
        void General::MenuItemRenderFunction_General_AdvancedGameOptions(int param_1, ...)
        {
            int iVar1;
            uint _color;
            int iVar2;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_LOAD_MAP
                || DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_SEND_MAP_TO
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID
                == OpenSHC::UI::Enums::MMT_SKIRMISH_PLAY_OPTIONS) {
                if (param_1 != -1000 && param_1 != -10 && param_1 != -11 && param_1 != -12 && param_1 != -13
                    && param_1 != -14 && param_1 != 99 && param_1 != 100 && param_1 != 83 && param_1 != 109
                    && param_1 != 82 && param_1 != 94) {
                    return;
                }
            } else {
                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT) {
                    return;
                }
                if (DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT) {
                    return;
                }
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if (param_1 == 93) {
                    return;
                }
                if (param_1 == 31) {
                    return;
                }
            }
            if ((param_1 == 103)
                && (DAT_ButtonUnknownZero::instance = 0,
                    DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            if (!DAT_GameSynchronyState::instance.isHost) {
                if (param_1 == 103) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                if (param_1 == 93) {
                    return;
                }
            }
            if (param_1 == -1) {
                DAT_ButtonUnknownZero::instance = 1;
                return;
            }
            if (param_1 != 103) {
                if ((!DAT_ButtonCurrentlyInteracting::instance) || (!DAT_GameSynchronyState::instance.isHost)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderNonInteractingButtonBackground,
                        AlphaAndButtonSurfaceObj::ptr)(DAT_ButtonBackgroundBlendStrength::instance);
                    _color = OpenSHC::Rendering::Colors::COL_C2F0EB;
                } else {
                    _color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(
                        DAT_ButtonBackgroundBlendStrength::instance, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                }
            }
            if (param_1 == 31) {
                iVar2 = DAT_GameSynchronyState::instance.skirmishTechLevel / 2;
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                // "Tech Level"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 85, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, _color, 18, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                // "Early" "Middle" "Late"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar2 + 79,
                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
            }
            if (param_1 == 36) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                // "Win: Regicide" / "Win: 10000 Gold" / "Win: 3" / "Win: 4" / "Win: 5" / ....
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)(DAT_GameSynchronyState::instance.skirmishWinCondition + 36),
                    (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                    OpenSHC::Text::TTA_CENTER, _color, 18, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
            }
            if (param_1 == 83) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                // "Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 86, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, _color, 18, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                iVar1 = 83;
                // "Free"
                if (DAT_GameSynchronyState::instance.skirmishTroopsCostGold != 0) {
                    // "Cost Gold"
                    iVar1 = 84;
                }
                iVar2 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar1,
                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 32);
            }
            if (param_1 == 109) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                // Fog of War
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 109, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, _color, 18, FALSE,
                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                if (DAT_GameState::instance.mapAndTime.skirmishFogOfWar == 0) {
                    // OFF
                    iVar1 = 95;
                } else {
                    // Please Wait
                    iVar1 = (DAT_GameState::instance.mapAndTime.skirmishFogOfWar != 1) + 109;
                }
                iVar2 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, iVar1,
                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                    ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 32);
                return;
            }
            if (param_1 == -1000) {
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_GAME_OPTIONS, 17,
                    (int)((int)DAT_ButtonW::instance / 2 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                    OpenSHC::Text::TTA_CENTER, _color, 18, FALSE, ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
            }
            if (param_1 == 103) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }
            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
            iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32;
            if (param_1 == -10) {
                // No Cow Throwing
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 5, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, _color, 18, FALSE, iVar1);
                iVar1 = DAT_GameSynchronyState::instance.skirmishNoCowThrowing;
            LAB_00428ffd:
                if (iVar1 != 0) {
                    iVar1 = DAT_ButtonW::instance - 50 + DAT_ButtonX::instance;
                    iVar2 = 206;
                    goto LAB_00429039;
                }
            } else {
                if (param_1 == -11) {
                    // "No Dogs"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 6,
                        (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT,
                        _color, 18, FALSE, iVar1);
                    iVar1 = DAT_GameSynchronyState::instance.skirmishNoDogs;
                LAB_00429086:
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (iVar1 == 0) {
                        iVar1 = 208;
                    } else {
                        iVar1 = 206;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar1,
                        (int)(DAT_ButtonW::instance - 50 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (param_1 == -13) {
                    // "Extreme mode"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 13,
                        (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT,
                        _color, 18, FALSE, iVar1);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_GameSynchronyState::instance.skirmishExtremeMode == 0) {
                        iVar1 = 208;
                    } else {
                        iVar1 = 206;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar1,
                        (int)(DAT_ButtonW::instance - 50 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (param_1 != -14) {
                    if (param_1 != 99) {
                        if (param_1 == -12) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 7,
                                (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 7),
                                OpenSHC::Text::TTA_LEFT, _color, 18, FALSE, iVar1);
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 0) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 95,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 1) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 96,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 2) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 97,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 3) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 98,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting == 4) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 8,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishNoRushSetting != 5) {
                                return;
                            }
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                            // "1 Hour"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 9,
                                (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1,
                            (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_LEFT, _color, 18, FALSE, iVar1);
                        if (param_1 == 14) {
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2,
                                DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.skirmishStartGold,
                                (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                        }
                        if (param_1 == 15) {
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2,
                                DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.skirmishDefaultPopularity,
                                (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                        }
                        if (param_1 == 82) {
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2,
                                DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.skirmishGameSpeedLevel,
                                (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                        }
                        if (param_1 == 94) {
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 0) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 95,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 5) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 96,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes == 10) {
                                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 97,
                                    (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                    OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                    ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                            }
                            if (DAT_GameSynchronyState::instance.skirmishAutoSaveEveryMinutes != 20) {
                                return;
                            }
                            iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 98,
                                (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE,
                                ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32);
                        }
                        if (param_1 != 100) {
                            return;
                        }
                        iVar1 = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                        iVar1 = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 32;
                        // "Alliances"
                        if (DAT_GameSynchronyState::instance.skirmishAlliances == 0) {
                            // "Anytime"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 101,
                                (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance),
                                (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_RIGHT,
                                OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE, iVar1);
                        }
                        // "Start only"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 102,
                            (int)(DAT_ButtonW::instance - 20 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 7),
                            OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_B8E6F5, 0, 18, FALSE, iVar1);
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 99,
                        (int)(DAT_ButtonX::instance + 20), (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT,
                        _color, 18, FALSE, iVar1);
                    iVar1 = DAT_GameSynchronyState::instance.skirmishStrongWalls;
                    goto LAB_00429086;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MISC, 14, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 7), OpenSHC::Text::TTA_LEFT, _color, 18, FALSE, iVar1);
                iVar1 = DAT_GameSynchronyState::instance.skirmishExtremeMode;
                if (DAT_GameSynchronyState::instance.skirmishExtremeMode2 != 0)
                    goto LAB_00428ffd;
            }
            iVar2 = 208;
            iVar1 = DAT_ButtonW::instance - 50 + DAT_ButtonX::instance;
        LAB_00429039:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, iVar2, iVar1, (int)(DAT_ButtonY::instance));
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
