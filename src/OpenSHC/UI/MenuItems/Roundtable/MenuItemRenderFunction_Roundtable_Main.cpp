#include "../Roundtable.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df423c.hpp"
#include "OpenSHC/Globals/DAT_00df4288.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004AEF70
        void Roundtable::MenuItemRenderFunction_Roundtable_Main(int param_1, ...)
        {
            byte bVar1;
            char* textAddress;
            int iVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum BVar6;
            iVar4 = 0;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (8 < param_1) {
                if ((((param_1 < 0x13)
                         && (iVar4
                             = (int)*(char*)((int)DAT_GameSynchronyState::instance.field290_0x109e20 + param_1 + 0x1a),
                             0 < iVar4))
                        && (DAT_00df423c::instance != 0))
                    && ((
                        (DAT_ButtonCurrentlyInteracting::instance != FALSE && (param_1 + -10 != DAT_00df423c::instance))
                        && ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar4] != -1
                            || (BVar6 = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                                    DAT_GameSynchronyState::ptr)(iVar4),
                                BVar6 != FALSE)))))) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                        (int)((int)(DAT_ButtonX::instance + 0x3e)), (int)((int)(DAT_ButtonY::instance + -1)),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
                }
                if (param_1 != 0x14) {
                    if ((param_1 == 100) || (param_1 == 0x65)) {
                        DAT_ButtonUnknownZero::instance = (int)(DAT_00df423c::instance != 0);
                        if (DAT_GameSynchronyState::instance.isHost == FALSE) {
                            DAT_ButtonUnknownZero::instance = 1;
                        } else {
                            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                                DAT_00df4288::instance = 1;
                            }
                        }
                    }
                    if (((param_1 == 200) && (iVar4 = 0, DAT_00df423c::instance != 0))
                        && (DAT_GameSynchronyState::instance.isHost != FALSE)) {
                        if (DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance] == 0) {
                            DAT_00df423c::instance = 0;
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        }
                        iVar3 = (int)(char)
                                    DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[DAT_00df423c::instance];
                        if (0 < iVar3) {
                            iVar2 = DAT_MouseState::instance.screenSpaceY
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                            iVar5 = DAT_MouseState::instance.screenSpaceX
                                - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                            if (iVar2 < 4) {
                                iVar2 = 4;
                            } else if (0x16c < iVar2) {
                                iVar2 = 0x16c;
                            }
                            if (iVar5 < 4) {
                                iVar5 = 4;
                            } else if (0x2d4 < iVar5) {
                                iVar5 = 0x2d4;
                            }
                            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                                iVar4 = DAT_GameSynchronyState::instance.currentAIArray[iVar3];
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                iVar3 + 0x222, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + iVar2);
                            if (iVar4 == 0) {
                                if (DAT_GameCore::instance.lordIcons[iVar3] == 0) {
                                    iVar4 = 0x21b;
                                } else {
                                    if (DAT_GameCore::instance.lordIcons[iVar3] != 1) {
                                        if (DAT_TextureRenderCoreObject::instance.field69_0x98[iVar3 + 0x13] < 1) {
                                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                        }
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                            0x21d, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5,
                                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + iVar2);
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                                            DAT_TextureRenderCoreObject::ptr)(iVar3 + 0x13,
                                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 4 + iVar5,
                                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 4 + iVar2);
                                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                    }
                                    iVar4 = 0x21c;
                                }
                            } else {
                                iVar4 = iVar4 + 0x20a;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + iVar5,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + iVar2);
                        }
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if ((DAT_ButtonCurrentlyInteracting::instance != FALSE)
                    && (DAT_00df4288::instance = 1, DAT_00df423c::instance == 0)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                iVar4 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderCurrentButtonToScreenMenuWithBlendingUnk)(
                    ((int)(iVar4 + (iVar4 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            iVar3 = (int)(char)DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[param_1];
            if (iVar3 < 1) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            bVar1 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[iVar3];
            if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1)
                && (DAT_GameSynchronyState::instance.currentAIArray[iVar3] == 0)) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            DAT_ButtonUnknownZero::instance = (int)(DAT_GameSynchronyState::instance.isHost == FALSE);
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                iVar4 = DAT_GameSynchronyState::instance.currentAIArray[iVar3];
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar3 + 0x222,
                (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
            if (iVar4 == 0) {
                if (DAT_GameCore::instance.lordIcons[iVar3] == 0) {
                    iVar4 = 0x21b;
                } else {
                    if (DAT_GameCore::instance.lordIcons[iVar3] != 1) {
                        if (0 < DAT_TextureRenderCoreObject::instance.field69_0x98[iVar3 + 0x13]) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d,
                                (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                                DAT_TextureRenderCoreObject::ptr)(iVar3 + 0x13, (int)((int)(DAT_ButtonX::instance + 4)),
                                (int)((int)(DAT_ButtonY::instance + 4)));
                        }
                        goto LAB_004af0a8;
                    }
                    iVar4 = 0x21c;
                }
            } else {
                iVar4 = iVar4 + 0x20a;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar4,
                (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
        LAB_004af0a8:
            if (DAT_00df423c::instance == param_1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonX::instance + 0x47)), (int)((int)(DAT_ButtonY::instance + 0x47)));
            }
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                if (DAT_00df423c::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                        (int)((int)(DAT_ButtonX::instance + -6)), (int)((int)(DAT_ButtonY::instance + -6)),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    DAT_00df4288::instance = 1;
                }
            }
            if ((char)bVar1 != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    (int)((int)((char)bVar1 * 2 + 0x1ed)), (int)((int)(DAT_ButtonX::instance + -10)),
                    (int)((int)(DAT_ButtonY::instance + -8)));
            }
            iVar4 = 0;
            BVar6 = FALSE;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] == -1) {
                foregroundColor = DAT_RenderingDefinedData::instance
                                      .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar3]];
                fontSize = 0x12;
                backgroundColor = 0;
                alignment = OpenSHC::Text::TTA_CENTER;
                iVar2 = DAT_ButtonY::instance + 0x50;
                iVar5 = DAT_ButtonX::instance + 0x20;
                textAddress = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    (int)((int)(DAT_GameSynchronyState::instance.currentAIArray[iVar3] * 9 + 0xe7
                        + DAT_GameSynchronyState::instance.aiVariationArray[iVar3])));
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    textAddress, iVar5, iVar2, alignment, foregroundColor, backgroundColor, fontSize, BVar6, iVar4);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.DAT_PlayerNames[iVar3], (int)((int)(DAT_ButtonX::instance + 0x20)),
                (int)((int)(DAT_ButtonY::instance + 0x50)), OpenSHC::Text::TTA_CENTER,
                (uint)((int)(DAT_RenderingDefinedData::instance
                        .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar3]])),
                0, 0x13, FALSE, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
