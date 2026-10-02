#include "../Allies.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
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

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004AC7A0
        void Allies::MenuItemRenderFunction_Allies_Main(int param_1, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            int iVar7;
            bool bVar8;
            eTextSections textOffsetIndex;
            int xParam;
            iVar2 = DAT_ButtonY::instance;
            iVar3 = DAT_ButtonX::instance;
            if (param_1 == 100) {}
            if ((DAT_AlliesCount::instance < 1) && (param_1 != -1)) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            if ((param_1 == 0x6e) || (param_1 == 0x6f)) {
                if (((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .requestStateUnk
                         != 1)
                        || ((iVar3 = DAT_GameState::instance
                                 .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                 .playerID_askerUnk,
                            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1
                                || (iVar3
                                    != DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance]))))
                    && (DAT_GameState::instance
                            .playerDataArray
                                [DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance]]
                            .isNotNervousByEnemyTroopValue
                        == 0)) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                DAT_ButtonUnknownZero::instance = 0;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
            }
            if (param_1 == 200) {
                if (DAT_00df51f4::instance == 0) {}
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, DAT_00df51f0::instance, (int)((int)(DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance)), OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if (0x13 < (uint)param_1) {
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {}
                if (param_1 == 0x14) {
                    DAT_00df51f4::instance = 1;
                    DAT_00df51f0::instance = 5;
                }
                if (param_1 == 0x15) {
                    DAT_00df51f4::instance = 1;
                    DAT_00df51f0::instance = 6;
                }
                if (param_1 != 0x16) {}
                DAT_00df51f4::instance = 1;
                DAT_00df51f0::instance = 7;
            }
            if (6 < param_1) {
                if (param_1 != 10) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
                iVar6 = 0;
                if (0 < DAT_ButtonH::instance) {
                    do {
                        if (iVar6 == 0) {
                            iVar5 = 1;
                        } else {
                            iVar5 = (-(uint)(iVar6 != DAT_ButtonH::instance + -0x18) & 0xfffffffa) + 0xd;
                        }
                        iVar7 = 0;
                        do {
                            iVar4 = iVar5;
                            if (iVar7 == 0) {
                            LAB_004acbeb:
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    iVar4, iVar7 + iVar3, iVar2 + iVar6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    iVar4 + 3, 0);
                            } else {
                                if (iVar7 == 0x270) {
                                    iVar4 = iVar5 + 2;
                                    goto LAB_004acbeb;
                                }
                                if (iVar5 != 7) {
                                    iVar4 = iVar5 + 1;
                                    goto LAB_004acbeb;
                                }
                            }
                            iVar7 = iVar7 + 0x18;
                        } while (iVar7 < 0x288);
                        iVar6 = iVar6 + 0x18;
                    } while (iVar6 < DAT_ButtonH::instance);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    iVar3 + 0x18, iVar2 + 0x18, iVar3 + 0x26f, DAT_ButtonH::instance + -0x19 + iVar2, 0x14);
                iVar3 = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
                iVar2 = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3];
                if ((iVar2 == -1)
                    && (BVar1 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                            DAT_GameSynchronyState::ptr)(iVar3),
                        BVar1 == FALSE)) {}
                iVar7 = DAT_ButtonY::instance;
                iVar5 = DAT_ButtonX::instance;
                iVar6 = DAT_ButtonX::instance + 0x18;
                if (iVar2 == -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                        (int)((int)(DAT_GameSynchronyState::instance.aiVariationArray[iVar3] + 0x67
                            + DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 8)),
                        iVar6, (int)((int)(DAT_ButtonY::instance + 0x18)), OpenSHC::Text::TTA_LEFT,
                        (uint)((int)(DAT_RenderingDefinedData::instance
                                .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar3]])),
                        0, 0x11, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[iVar3], iVar6,
                        (int)((int)(DAT_ButtonY::instance + 0x18)), OpenSHC::Text::TTA_LEFT,
                        (uint)((int)(DAT_RenderingDefinedData::instance
                                .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar3]])),
                        0, 0x11, FALSE);
                }
                iVar2
                    = (int)DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .requestedGoodsArray1Unk[iVar3];
                if (iVar2 == 7) {
                    iVar2 = 8;
                }
                iVar4 = iVar7 + 0x38;
                bVar8 = -1 < iVar2 + -2;
                if (bVar8) {
                    /*
                      added by script: "Requests"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 0xc, iVar6, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12,
                        FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                        (int)DAT_GameState::instance
                            .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .requestedGoodsArray2Unk[iVar3],
                        iVar5 + 0x1d, iVar4, 0xccfaff, 0x12, 1);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar2 + 0x242,
                        DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + iVar6, iVar7 + 0x30,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x25b, 0);
                    xParam = iVar5 + 0x45;
                    textOffsetIndex = OpenSHC::DE::SHCDE::TEXT_GOODS;
                } else {
                    iVar2 = 1;
                    textOffsetIndex = OpenSHC::DE::SHCDE::TEXT_ALLIES;
                    xParam = iVar6;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    textOffsetIndex, iVar2, xParam, iVar4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12,
                    (BOOLEnum)((int)((uint)bVar8)));
                iVar2 = iVar7 + 0x58;
                if (DAT_GameState::instance.playerDataArray[iVar3].requestStateUnk == 0) {
                    /*
                      added by script: "No Orders"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 2, iVar6, iVar2, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12,
                        FALSE);
                } else {
                    /*
                      added by script: "Orders:"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 0x10, iVar6, iVar2, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12,
                        FALSE);
                    if (DAT_GameState::instance.playerDataArray[iVar3].requestStateUnk == 1) {
                        /*
                          added by script: "Attack"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_ALLIES, 10, iVar5 + 0x1d, iVar2, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                            0x12, TRUE);
                    }
                    if (DAT_GameState::instance.playerDataArray[iVar3].requestStateUnk == 2) {
                        /*
                          added by script: "Defend"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_ALLIES, 0x11, iVar5 + 0x1d, iVar2, OpenSHC::Text::TTA_LEFT,
                            0xccfaff, 0x12, TRUE);
                    } else {
                        iVar4 = DAT_GameState::instance.playerDataArray[iVar3].requestedAttackTargetUnk;
                        if (iVar4 == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                            /*
                              added by script: "You"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_ALLIES, 0x12, iVar5 + 0x22, iVar2, OpenSHC::Text::TTA_LEFT,
                                0xccfaff, 0x12, TRUE);
                        } else {
                            iVar2 = iVar7 + 0x4c;
                            iVar5 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + iVar6;
                            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar4] == -1) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4 + 0x2ce, iVar5, iVar2);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                    (int)((int)(DAT_GameSynchronyState::instance
                                                    .currentAIArray[DAT_GameState::instance.playerDataArray[iVar3]
                                                            .requestedAttackTargetUnk]
                                        + 700)),
                                    iVar5, iVar2);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4 + 0x2ce, iVar5, iVar2);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    DAT_GameState::instance.playerDataArray[iVar3].requestedAttackTargetUnk + 0x13,
                                    iVar5 + 2, iVar7 + 0x4e);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                                    DAT_PencilRenderCore::ptr)(iVar5, iVar2, iVar5 + 0x23, iVar7 + 0x6f,
                                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                            }
                        }
                    }
                }
                if (DAT_GameState::instance.playerDataArray[iVar3].isNotNervousByEnemyTroopValue != 0) {
                    /*
                      added by script: "Help Needed!"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 4, iVar6, iVar7 + 0x78, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                        0x12, FALSE);
                }
                iVar2 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .requestStateUnk
                    != 1) {}
                iVar5 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .playerID_askerUnk;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar5] == -1) {}
                if (iVar5 != iVar3) {}
                /*
                  added by script: "Attack"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, 10, iVar6, iVar7 + 0x78, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12,
                    FALSE);
                iVar6 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 10 + iVar6;
                iVar3 = DAT_GameState::instance.playerDataArray[iVar2].requestedAttackTargetUnk;
                iVar5 = iVar7 + 0x73;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] != -1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + 0x2ce, iVar6, iVar5);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                        DAT_TextureRenderCoreObject::ptr)(
                        DAT_GameState::instance.playerDataArray[iVar2].requestedAttackTargetUnk + 0x13, iVar6 + 2,
                        iVar7 + 0x75);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        iVar6, iVar5, iVar6 + 0x23, iVar7 + 0x96, (ushort)((int)(COL_BLACK::instance.shortValue)));
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + 0x2ce, iVar6, iVar5);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    (int)((int)(DAT_GameSynchronyState::instance.currentAIArray
                                    [DAT_GameState::instance.playerDataArray[iVar2].requestedAttackTargetUnk]
                        + 700)),
                    iVar6, iVar5);
            }
            if (param_1 == 1) {
                DAT_00df51f4::instance = 0;
            }
            iVar3 = param_1 + -1;
            if (DAT_AlliesCount::instance <= iVar3) {
                DAT_ButtonUnknownZero::instance = 0;
            }
            iVar2 = DAT_SomeTeamMemberPlayerIDArray::instance[iVar3];
            iVar6 = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar2] == -1) {
                iVar6 = DAT_GameSynchronyState::instance.currentAIArray[iVar2];
            }
            if (iVar3 == DAT_LastTeamMemberIndex::instance) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 0x222,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                if (iVar6 == 0) {
                    if (DAT_GameCore::instance.lordIcons[iVar2] == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21b,
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                    } else if (DAT_GameCore::instance.lordIcons[iVar2] == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21c,
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                    } else if (0 < DAT_TextureRenderCoreObject::instance.field69_0x98[iVar2 + 0x13]) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d,
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                            DAT_TextureRenderCoreObject::ptr)(iVar2 + 0x13, (int)((int)(DAT_ButtonX::instance + 4)),
                            (int)((int)(DAT_ButtonY::instance + 4)));
                    }
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar6 + 0x20a,
                        (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                }
            } else {
                if (iVar6 == 0) {
                    if (DAT_GameCore::instance.lordIcons[iVar2] == 0) {
                        iVar6 = 0x21b;
                    } else {
                        if (DAT_GameCore::instance.lordIcons[iVar2] != 1) {
                            if (0 < DAT_TextureRenderCoreObject::instance.field69_0x98[iVar2 + 0x13]) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                                    0x21d, (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                                    0xc);
                                MACRO_CALL_MEMBER(
                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFaceWithBlendUnk,
                                    DAT_TextureRenderCoreObject::ptr)(iVar2 + 0x13,
                                    (int)((int)(DAT_ButtonX::instance + 4)), (int)((int)(DAT_ButtonY::instance + 4)),
                                    0xc);
                            }
                            goto LAB_004aca47;
                        }
                        iVar6 = 0x21c;
                    }
                } else {
                    iVar6 = iVar6 + 0x20a;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar6,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)), 0xc);
            }
        LAB_004aca47:
            if (iVar3 == DAT_LastTeamMemberIndex::instance) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                    (int)((int)(DAT_ButtonX::instance + -6)), (int)((int)(DAT_ButtonY::instance + -6)),
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
            }
            iVar6 = 0;
            if (iVar3 != DAT_LastTeamMemberIndex::instance) {
                iVar6 = 8;
            }
            iVar3 = (int)DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .requestedGoodsArray1Unk[iVar2];
            if (iVar3 == 7) {
                iVar3 = 8;
            }
            if (-1 < iVar3 + -2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar3 + 0x242,
                    (int)((int)(DAT_ButtonX::instance + 0x3c)), (int)((int)(DAT_ButtonY::instance + -0xc)),
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x25b, iVar6);
            }
            if (DAT_GameState::instance.playerDataArray[iVar2].isNotNervousByEnemyTroopValue != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                    DAT_00df42b0::instance + 0x242, (int)((int)(DAT_ButtonX::instance + 0x3c)),
                    (int)((int)(DAT_ButtonY::instance + 0x3c)), OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x25b,
                    iVar6);
            }
            if (DAT_GameState::instance.playerDataArray[iVar2].requestStateUnk == 1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x240,
                    (int)((int)(DAT_ButtonX::instance + -0xf)), (int)((int)(DAT_ButtonY::instance + 0x39)),
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x241, iVar6);
            }
            if (DAT_GameState::instance.playerDataArray[iVar2].requestStateUnk == 2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x25c,
                    (int)((int)(DAT_ButtonX::instance + -0xf)), (int)((int)(DAT_ButtonY::instance + 0x39)),
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x25d, iVar6);
            }
        }

    }
}
}
