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

        // FUNCTION: STRONGHOLDCRUSADER 0x00463A90
        void AlphaAndButtonSurface::renderBasicButton(int reverseOrBlendStrength, RenderTarget renderSurface)
        {
            int x = DAT_ButtonX::instance;
            int const y = DAT_ButtonY::instance;
            // -1 asks for a plain button of any width, tiled from 10 pixel wide images.
            BOOL plainTiled = FALSE;
            if (reverseOrBlendStrength == 32) {
                return;
            }
            if (reverseOrBlendStrength == -1) {
                reverseOrBlendStrength = 0;
                plainTiled = TRUE;
            }
            RenderTargetInt savedRenderTarget;
            int const blendStrength = (reverseOrBlendStrength * 9 - 288) * 2 / 32 + 32;
            if (blendStrength == 32) {
                return;
            }
            if (plainTiled) {
                int width = (int)DAT_ButtonW::instance + 9 - ((int)DAT_ButtonW::instance + 9) % 10;
                x += ((int)DAT_ButtonW::instance - width) / 2;
                savedRenderTarget = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
                if (renderSurface == OpenSHC::Rendering::Enums::RT_CONTEXT_BASED) {
                    renderSurface
                        = (RenderTarget)(MACRO_CALL_MEMBER(
                                             OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                            != FALSE);
                }
                // Buttons taller than 30 pixels use the tall variant, 9 images earlier.
                int image = (int)DAT_ButtonH::instance > 30 ? 0x73 : 0x7c;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderSurface;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image, x, y, blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 6,
                        x - 6, y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 3, reverseOrBlendStrength);
                }
                width -= 10;
                x += 10;
                image += 1;
                for (; width > 10; width -= 10) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image, x, y, blendStrength);
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 6,
                            x, y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 3, reverseOrBlendStrength);
                    }
                    x += 10;
                }
                image += 1;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image, x, y, blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 6, x,
                        y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 3, reverseOrBlendStrength);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = savedRenderTarget;
                return;
            }
            // Buttons with a size of their own use one image; any other size is tiled, short or tall.
            int image;
            int imageWidth;
            if ((int)DAT_ButtonW::instance == 100 && (int)DAT_ButtonH::instance == 100) {
                image = 0xb3;
                imageWidth = 100;
            } else if ((int)DAT_ButtonW::instance <= 30 && (int)DAT_ButtonH::instance < 20) {
                image = 0x1b;
                imageWidth = 20;
            } else if ((int)DAT_ButtonW::instance <= 70 && (int)DAT_ButtonH::instance < 20) {
                image = 0x18;
                imageWidth = 60;
            } else if ((int)DAT_ButtonW::instance <= 90 && (int)DAT_ButtonH::instance < 20) {
                image = 0x2a;
                imageWidth = 80;
            } else if ((int)DAT_ButtonW::instance <= 220 && (int)DAT_ButtonH::instance > 35) {
                image = 0x27;
                imageWidth = 200;
            } else if ((int)DAT_ButtonW::instance <= 310 && (int)DAT_ButtonH::instance >= 35) {
                image = 0x61;
                imageWidth = 300;
            } else if ((int)DAT_ButtonH::instance < 20) {
                int width = (int)DAT_ButtonW::instance + 9 - ((int)DAT_ButtonW::instance + 9) % 10;
                x += ((int)DAT_ButtonW::instance - width) / 2;
                savedRenderTarget = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
                if (renderSurface == OpenSHC::Rendering::Enums::RT_CONTEXT_BASED) {
                    renderSurface
                        = (RenderTarget)(MACRO_CALL_MEMBER(
                                             OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                            != FALSE);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderSurface;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xba, x, y, blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xc0, x - 5,
                        y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbd, reverseOrBlendStrength);
                }
                width -= 10;
                x += 10;
                for (; width > 10; width -= 10) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbb, x, y, blendStrength);
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xc1, x,
                            y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbe, reverseOrBlendStrength);
                    }
                    x += 10;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbc, x, y, blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xc2, x, y - 6,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xbf, reverseOrBlendStrength);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = savedRenderTarget;
                return;
            } else {
                int width = (int)DAT_ButtonW::instance + 9 - ((int)DAT_ButtonW::instance + 9) % 10;
                x += ((int)DAT_ButtonW::instance - width) / 2;
                savedRenderTarget = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
                if (renderSurface == OpenSHC::Rendering::Enums::RT_CONTEXT_BASED) {
                    renderSurface
                        = (RenderTarget)(MACRO_CALL_MEMBER(
                                             OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
                            != FALSE);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = renderSurface;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6a, x, y, blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x70, x - 5,
                        y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6d, reverseOrBlendStrength);
                }
                width -= 10;
                x += 10;
                for (; width > 10; width -= 10) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6b, x, y, blendStrength);
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x71, x,
                            y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6e, reverseOrBlendStrength);
                    }
                    x += 10;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6c, x, y, blendStrength);
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x72, x, y - 6,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0x6f, reverseOrBlendStrength);
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = savedRenderTarget;
                return;
            }
            x += ((int)DAT_ButtonW::instance - imageWidth) / 2;
            savedRenderTarget = DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)() != FALSE;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)(
                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image, x, y, blendStrength);
            if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 2, x - 5,
                    y - 6, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, image + 1, reverseOrBlendStrength);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = savedRenderTarget;
        }

    }
}
}
