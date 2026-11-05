#include "../Allies.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00df42b0.hpp"
#include "OpenSHC/Globals/DAT_00df51f0.hpp"
#include "OpenSHC/Globals/DAT_00df51f4.hpp"
#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC7A0
        void Allies::MenuItemRenderFunction_Allies_Main(int param_1, ...)
        {
            BOOLEnum BVar1;
            int iVar4;
            int iVar5;
            int iVar6;
            int iVar7;
            eTextSections textOffsetIndex;
            int xParam;
            int iVar2;
            int iVar3;
            if (param_1 == 100) {
                return;
            }
            if (DAT_AlliesCount::instance < 1 && param_1 != -1) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            if ((param_1 == 110) || (param_1 == 111)) {
                if (((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .requestStateUnk
                         != 1)
                        || ((iVar3 = DAT_GameState::instance
                                 .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                 .playerID_askerUnk,
                            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1
                                || (iVar3
                                    != DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance]))))
                    && DAT_GameState::instance
                            .playerDataArray
                                [DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance]]
                            .isNotNervousByEnemyTroopValue
                        == 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 0;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
            }
            if (param_1 == 200) {
                if (DAT_00df51f4::instance == 0) {
                    return;
                }
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, DAT_00df51f0::instance, (int)(DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance), OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0,
                    18, FALSE);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if (19 < (uint)param_1) {
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    return;
                }
                if (param_1 == 20) {
                    DAT_00df51f4::instance = 1;
                    DAT_00df51f0::instance = 5;
                }
                if (param_1 == 21) {
                    DAT_00df51f4::instance = 1;
                    DAT_00df51f0::instance = 6;
                }
                if (param_1 != 22) {
                    return;
                }
                DAT_00df51f4::instance = 1;
                DAT_00df51f0::instance = 7;
            }
            if (6 >= param_1) {
                if (param_1 == 1) {
                    DAT_00df51f4::instance = 0;
                }
                iVar3 = param_1 - 1;
                if (DAT_AlliesCount::instance <= iVar3) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
                iVar6 = 0;
                iVar2 = DAT_SomeTeamMemberPlayerIDArray::instance[iVar3];
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar2] == -1) {
                    iVar6 = DAT_GameSynchronyState::instance.currentAIArray[iVar2];
                }
                if (iVar3 == DAT_LastTeamMemberIndex::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 546,
                        (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                    if (iVar6 == 0) {
                        if (DAT_GameCore::instance.lordIcons[iVar2] == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 539,
                                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                        } else if (DAT_GameCore::instance.lordIcons[iVar2] == 1) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 540,
                                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                        } else if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[iVar2 + 19]) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 541,
                                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                                DAT_TextureRenderCoreObject::ptr)(
                                iVar2 + 19, (int)(DAT_ButtonX::instance + 4), (int)(DAT_ButtonY::instance + 4));
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar6 + 522,
                            (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                    }
                } else {
                    if (iVar6 == 0) {
                        if (DAT_GameCore::instance.lordIcons[iVar2] == 0) {
                            iVar6 = 539;
                        } else {
                            if (DAT_GameCore::instance.lordIcons[iVar2] != 1) {
                                if (0 < DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[iVar2 + 19]) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                                        541, (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance), 12);
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFaceWithBlendUnk,
                                        DAT_TextureRenderCoreObject::ptr)(iVar2 + 19, (int)(DAT_ButtonX::instance + 4),
                                        (int)(DAT_ButtonY::instance + 4), 12);
                                }
                                goto LAB_004aca47;
                            }
                            iVar6 = 540;
                        }
                    } else {
                        iVar6 += 522;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar6,
                        (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance), 12);
                    return;
                }
            LAB_004aca47:
                if (iVar3 == DAT_LastTeamMemberIndex::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 514,
                        (int)(DAT_ButtonX::instance - 6), (int)(DAT_ButtonY::instance - 6),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 513, 0);
                    return;
                }
                iVar6 = 0;
                if (iVar3 != DAT_LastTeamMemberIndex::instance) {
                    iVar6 = 8;
                }
                iVar3
                    = (int)DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .requestedGoodsArray1Unk[iVar2];
                if (iVar3 == 7) {
                    iVar3 = 8;
                }
                if (-1 < iVar3 - 2) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar3 + 578,
                        (int)(DAT_ButtonX::instance + 60), (int)(DAT_ButtonY::instance - 12),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 603, iVar6);
                }
                if (DAT_GameState::instance.playerDataArray[iVar2].isNotNervousByEnemyTroopValue != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                        DAT_00df42b0::instance + 578, (int)(DAT_ButtonX::instance + 60),
                        (int)(DAT_ButtonY::instance + 60), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 603, iVar6);
                }
                if (DAT_GameState::instance.playerDataArray[iVar2].requestStateUnk == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 576,
                        (int)(DAT_ButtonX::instance - 15), (int)(DAT_ButtonY::instance + 57),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 577, iVar6);
                }
                if (DAT_GameState::instance.playerDataArray[iVar2].requestStateUnk == 2) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 604,
                        (int)(DAT_ButtonX::instance - 15), (int)(DAT_ButtonY::instance + 57),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 605, iVar6);
                }
                return;
            }
            if (param_1 != 10) {
                DAT_ButtonUnknownZero::instance = 0;
            }
            iVar3 = DAT_ButtonX::instance;
            iVar2 = DAT_ButtonY::instance;
            iVar6 = 0;
            if (0 < (int)DAT_ButtonH::instance) {
                do {
                    if (iVar6 == 0) {
                        iVar5 = 1;
                    } else {
                        if (iVar6 == DAT_ButtonH::instance - 24) {
                            iVar5 = 13;
                        } else {
                            iVar5 = 7;
                        }
                    }
                    iVar7 = 0;
                    do {
                        iVar4 = iVar5;
                        if (iVar7 == 0) {
                        LAB_004acbeb:
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar4,
                                iVar7 + iVar3, iVar2 + iVar6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar4 + 3,
                                0);
                        } else {
                            if (iVar7 == 624) {
                                iVar4 = iVar5 + 2;
                                goto LAB_004acbeb;
                                return;
                            }
                            if (iVar5 != 7) {
                                iVar4 = iVar5 + 1;
                                goto LAB_004acbeb;
                            }
                        }
                        iVar7 += 24;
                    } while (iVar7 < 648);
                    iVar6 += 24;
                } while (iVar6 < (int)DAT_ButtonH::instance);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(iVar3 + 24, iVar2 + 24, iVar3 + 623, DAT_ButtonH::instance - 25 + iVar2, 20);
            iVar3 = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
            iVar2 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3];
            if ((iVar2 == -1)
                && (BVar1 = MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(iVar3),
                    !BVar1)) {
                return;
            }
            iVar7 = DAT_ButtonY::instance;
            iVar5 = DAT_ButtonX::instance;
            iVar6 = DAT_ButtonX::instance + 24;
            if (iVar2 == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)(DAT_GameSynchronyState::instance.aiVariationArray[iVar3] + 103
                        + DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 8),
                    iVar6, (int)(DAT_ButtonY::instance + 24), OpenSHC::Text::TTA_LEFT,
                    (uint)(DAT_RenderingDefinedData::instance
                            .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar3]]),
                    0, 17, FALSE);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.DAT_PlayerNames[iVar3], iVar6, (int)(DAT_ButtonY::instance + 24),
                    OpenSHC::Text::TTA_LEFT,
                    (uint)(DAT_RenderingDefinedData::instance
                            .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar3]]),
                    0, 17, FALSE);
            }
            iVar2 = (int)DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .requestedGoodsArray1Unk[iVar3];
            if (iVar2 == 7) {
                iVar2 = 8;
            }
            iVar4 = iVar7 + 56;
            int bVar8 = -1 < iVar2 - 2;
            if (bVar8) {
                // added by script: "Requests"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, 12, iVar6, iVar4, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                    (int)DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .requestedGoodsArray2Unk[iVar3],
                    iVar5 + 29, iVar4, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, 1);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar2 + 578,
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + iVar6, iVar7 + 48,
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 603, 0);
                xParam = iVar5 + 69;
                textOffsetIndex = OpenSHC::DE::SHCDE::TEXT_GOODS;
            } else {
                iVar2 = 1;
                xParam = iVar6;
                textOffsetIndex = OpenSHC::DE::SHCDE::TEXT_ALLIES;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(textOffsetIndex,
                iVar2, xParam, iVar4, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18,
                (BOOLEnum)bVar8);
            iVar2 = iVar7 + 88;
            if (DAT_GameState::instance.playerDataArray[iVar3].requestStateUnk == 0) {
                // added by script: "No Orders"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, 2, iVar6, iVar2, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
            } else {
                // added by script: "Orders:"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, 16, iVar6, iVar2, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                if (DAT_GameState::instance.playerDataArray[iVar3].requestStateUnk == 1) {
                    // added by script: "Attack"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 10, iVar5 + 29, iVar2, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                }
                if (DAT_GameState::instance.playerDataArray[iVar3].requestStateUnk == 2) {
                    // added by script: "Defend"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 17, iVar5 + 29, iVar2, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                } else {
                    iVar4 = DAT_GameState::instance.playerDataArray[iVar3].requestedAttackTargetUnk;
                    if (iVar4 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        // added by script: "You"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_ALLIES, 18, iVar5 + 34, iVar2, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                    } else {
                        iVar2 = iVar7 + 76;
                        iVar5 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + iVar6;
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar4] == -1) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4 + 718, iVar5, iVar2);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                (int)(DAT_GameSynchronyState::instance.currentAIArray
                                          [DAT_GameState::instance.playerDataArray[iVar3].requestedAttackTargetUnk]
                                    + 700),
                                iVar5, iVar2);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4 + 718, iVar5, iVar2);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                                DAT_TextureRenderCoreObject::ptr)(
                                DAT_GameState::instance.playerDataArray[iVar3].requestedAttackTargetUnk + 19, iVar5 + 2,
                                iVar7 + 78);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                                DAT_PencilRenderCore::ptr)(
                                iVar5, iVar2, iVar5 + 35, iVar7 + 111, (ushort)(COL_BLACK::instance.shortValue));
                        }
                    }
                }
            }
            if (DAT_GameState::instance.playerDataArray[iVar3].isNotNervousByEnemyTroopValue != 0) {
                // added by script: "Help Needed!"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, 4, iVar6, iVar7 + 120, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
            }
            iVar2 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .requestStateUnk
                != 1) {
                return;
            }
            iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .playerID_askerUnk;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar5] == -1) {
                return;
            }
            if (iVar5 != iVar3) {
                return;
            }
            // added by script: "Attack"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_ALLIES, 10, iVar6, iVar7 + 120, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
            iVar6 += DAT_TextManagerObject::instance.currentXOffset_0x0 + 10;
            iVar3 = DAT_GameState::instance.playerDataArray[iVar2].requestedAttackTargetUnk;
            iVar5 = iVar7 + 115;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + 718, iVar6, iVar5);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                    DAT_TextureRenderCoreObject::ptr)(
                    DAT_GameState::instance.playerDataArray[iVar2].requestedAttackTargetUnk + 19, iVar6 + 2,
                    iVar7 + 117);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                    iVar6, iVar5, iVar6 + 35, iVar7 + 150, (ushort)(COL_BLACK::instance.shortValue));
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + 718, iVar6, iVar5);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                (int)(DAT_GameSynchronyState::instance
                          .currentAIArray[DAT_GameState::instance.playerDataArray[iVar2].requestedAttackTargetUnk]
                    + 700),
                iVar6, iVar5);
        }

    }
}
}
