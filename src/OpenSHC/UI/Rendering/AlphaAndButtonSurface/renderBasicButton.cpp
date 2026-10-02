#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00463A90
        void AlphaAndButtonSurface::renderBasicButton(int reverseOrBlendStrength, RenderTarget renderSurface)
        {
            BOOLEnum _isInGameMenu;
            uint _variation;
            int imageID;
            int _blendStrength;
            int iVar1;
            int _renderX;
            int iVar2;
            int _drawX_01;
            bool _blendStrengthMin1;
            int _buttonY;
            RenderTargetInt _drawBufferChoiceValue;
            _drawBufferChoiceValue = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
            _buttonY = DAT_ButtonY::instance;
            if (reverseOrBlendStrength == 0x20) {}
            _blendStrengthMin1 = reverseOrBlendStrength == -1;
            if (_blendStrengthMin1) {
                reverseOrBlendStrength = 0;
            }
            iVar1 = (reverseOrBlendStrength * 9 + -0x120) * 2;
            _blendStrength = ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) + 0x20;
            if (_blendStrength == 0x20) {}
            if (_blendStrengthMin1) {
                iVar1 = DAT_ButtonW::instance - (DAT_ButtonW::instance + 9) % 10;
                _renderX = DAT_ButtonX::instance + (DAT_ButtonW::instance - (iVar1 + 9)) / 2;
                if (renderSurface == OpenSHC::Rendering::Enums::RT_CONTEXT_BASED) {
                    _isInGameMenu
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                    renderSurface = (RenderTarget)(_isInGameMenu != FALSE);
                }
                /*
                  -9 if buttonH >= 31 else 0
                 */
                _variation = (DAT_ButtonH::instance < 30) - 1 & 0xfffffff7;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderSurface;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    (int)((int)(_variation + 0x7c)), _renderX, _buttonY, _blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        (int)((int)(_variation + 0x82)), _renderX + -6, _buttonY + -6,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, (int)((int)(_variation + 0x7f)),
                        reverseOrBlendStrength);
                }
                iVar2 = _renderX + 10;
                if (10 < iVar1 + -1) {
                    iVar1 = (iVar1 - 0xcU) / 10 + 1;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                            (int)((int)(_variation + 0x7d)), iVar2, _buttonY, _blendStrength);
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                (int)((int)(_variation + 0x83)), iVar2, _buttonY + -6,
                                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, (int)((int)(_variation + 0x80)),
                                reverseOrBlendStrength);
                        }
                        iVar2 = iVar2 + 10;
                        iVar1 = iVar1 + -1;
                    } while (iVar1 != 0);
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    (int)((int)(_variation + 0x7e)), iVar2, _buttonY, _blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _drawBufferChoiceValue;
                }
                iVar1 = _variation + 0x81;
                imageID = _variation + 0x84;
                goto LAB_00463e99;
            }
            /*
              if blendStrength != -1
             */
            if (DAT_ButtonW::instance == 100) {
                if (DAT_ButtonH::instance == 100) {
                    iVar1 = 0xb3;
                    iVar2 = 100;
                    goto LAB_00463cd0;
                }
            LAB_00463ca0:
                if (35 < DAT_ButtonH::instance) {
                    iVar1 = 39;
                    iVar2 = 200;
                    goto LAB_00463cd0;
                }
            } else {
                if ((DAT_ButtonW::instance < 0x1f) && (DAT_ButtonH::instance < 0x14)) {
                    iVar1 = 0x1b;
                    iVar2 = 0x14;
                    goto LAB_00463cd0;
                }
                if ((DAT_ButtonW::instance < 0x47) && (DAT_ButtonH::instance < 0x14)) {
                    iVar1 = 0x18;
                    iVar2 = 0x3c;
                    goto LAB_00463cd0;
                }
                if ((DAT_ButtonW::instance < 0x5b) && (DAT_ButtonH::instance < 0x14)) {
                    iVar1 = 0x2a;
                    iVar2 = 0x50;
                    goto LAB_00463cd0;
                }
                if (DAT_ButtonW::instance < 0xdd)
                    goto LAB_00463ca0;
            }
            if ((310 < DAT_ButtonW::instance) || (DAT_ButtonH::instance < 35)) {
                if (20 < DAT_ButtonH::instance) {
                    iVar1 = DAT_ButtonW::instance - (DAT_ButtonW::instance + 9) % 10;
                    iVar2 = DAT_ButtonX::instance + (DAT_ButtonW::instance - (iVar1 + 9)) / 2;
                    if (renderSurface == OpenSHC::Rendering::Enums::RT_CONTEXT_BASED) {
                        _isInGameMenu = MACRO_CALL_MEMBER(
                            OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                        renderSurface = (RenderTarget)(_isInGameMenu != FALSE);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderSurface;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6a, iVar2, _buttonY, _blendStrength);
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x70,
                            iVar2 + -5, _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6d,
                            reverseOrBlendStrength);
                    }
                    _drawX_01 = iVar2 + 10;
                    if (10 < iVar1 + -1) {
                        iVar1 = (iVar1 - 0xcU) / 10 + 1;
                        do {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6b,
                                _drawX_01, _buttonY, _blendStrength);
                            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    0x71, _drawX_01, _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6e,
                                    reverseOrBlendStrength);
                            }
                            _drawX_01 = _drawX_01 + 10;
                            iVar1 = iVar1 + -1;
                        } while (iVar1 != 0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6c, _drawX_01, _buttonY, _blendStrength);
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x72,
                            _drawX_01, _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6f,
                            reverseOrBlendStrength);
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _drawBufferChoiceValue;
                }
                iVar1 = DAT_ButtonW::instance - (DAT_ButtonW::instance + 9) % 10;
                iVar2 = DAT_ButtonX::instance + (DAT_ButtonW::instance - (iVar1 + 9)) / 2;
                if (renderSurface == OpenSHC::Rendering::Enums::RT_CONTEXT_BASED) {
                    _isInGameMenu
                        = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
                    renderSurface = (RenderTarget)(_isInGameMenu != FALSE);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderSurface;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xba, iVar2, _buttonY, _blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xc0,
                        iVar2 + -5, _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbd,
                        reverseOrBlendStrength);
                }
                iVar2 = iVar2 + 10;
                if (10 < iVar1 + -1) {
                    iVar1 = (iVar1 - 0xcU) / 10 + 1;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbb, iVar2, _buttonY, _blendStrength);
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xc1,
                                iVar2, _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbe,
                                reverseOrBlendStrength);
                        }
                        iVar2 = iVar2 + 10;
                        iVar1 = iVar1 + -1;
                    } while (iVar1 != 0);
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbc, iVar2, _buttonY, _blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _drawBufferChoiceValue;
                }
                iVar1 = 0xbf;
                imageID = 0xc2;
            LAB_00463e99:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, imageID, iVar2,
                    _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar1, reverseOrBlendStrength);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _drawBufferChoiceValue;
            }
            iVar1 = 0x61;
            iVar2 = 300;
        LAB_00463cd0:
            iVar2 = DAT_ButtonX::instance + (DAT_ButtonW::instance - iVar2) / 2;
            _isInGameMenu = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = (RenderTargetInt)(_isInGameMenu != FALSE);
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar1, iVar2, _buttonY, _blendStrength);
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar1 + 2,
                    iVar2 + -5, _buttonY + -6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar1 + 1,
                    reverseOrBlendStrength);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = _drawBufferChoiceValue;
        }

    }
}
}
