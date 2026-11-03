#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00eb0e40.hpp"
#include "OpenSHC/Globals/DAT_00eb1234.hpp"
#include "OpenSHC/Globals/DAT_00eb9af4.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedX.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00eb9ac4.hpp"
#include "OpenSHC/Globals/FLOAT_00eb0e2c.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/INT_00eb0e30.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"

namespace OpenSHC {

using OpenSHC::UI::Credits::CreditsRelatedStructure;

// FUNCTION: STRONGHOLDCRUSADER 0x004E12C0
void Rendering::RenderActiveCreditsElements()
{
    if (INT_00ed27a4::instance == 0) {
        MACRO_CALL(OpenSHC::UI::Helpers_Func::ColorEntireScreen)(COL_BLACK::instance.shortValue);
    }
    if (INT_00ed27a4::instance == 1) {
        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(DAT_00eb9af4::instance, 0, 0);
    }
    if (DAT_00eb0e40::instance == 5) {
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
            DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
            DAT_WindowAndDirectDraw::instance.resolutionY - 1, (int)FLOAT_00eb0e2c::instance);
        FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance - FLOAT_Between1And5::instance * 0.5;
        if (FLOAT_00eb0e2c::instance < 16.0) {
            FLOAT_00eb0e2c::instance = 16.0;
        }
    }

    for (int layer = 0; layer < 8; layer++) {
        for (int i = 0; i < 24; i++) {
            CreditsRelatedStructure& element = DAT_ARRAY_00ec0348::instance[i];
            if (element.isValid == 0 || element.field7_0x1c != layer)
                continue;

            // isValid doubles as the element type: 1 image, 2 text, 3 hover image, 4 bordered box.
            // Images fade at twice the speed of the other types.
            if (element.isValid == 1) {
                int gfxIndex = element.xSpace;
                if (element.field11_0x2c != -1
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        >= element.x
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        < element.width + element.x
                    && DAT_MouseState::instance.screenSpaceY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                        >= element.y
                    && DAT_MouseState::instance.screenSpaceY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                        < element.height + element.y) {
                    gfxIndex = element.field11_0x2c;
                }
                if (element.fadeMode == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(gfxIndex, element.x, element.y);
                } else {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderMenuGfxHelper)(
                        gfxIndex, element.x, element.y, (int)element.blendStrength);
                    if (element.fadeMode == 1) {
                        element.blendStrength = element.blendStrength - FLOAT_Between1And5::instance * 0.5 * 2.0;
                        if (element.blendStrength < 1.0)
                            element.fadeMode = 0;
                    }
                    if (element.fadeMode == 2) {
                        element.blendStrength = FLOAT_Between1And5::instance * 0.5 * 2.0 + element.blendStrength;
                        if (element.blendStrength > 31.0)
                            element.isValid = 0;
                    }
                }
            } else if (element.isValid == 4) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (element.fadeMode == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                        DAT_PencilRenderCore::ptr)(element.x + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                        element.y + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight, element.width,
                        element.height);
                } else {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithCustomBlendedBackground,
                        DAT_PencilRenderCore::ptr)(element.x + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                        element.y + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight, element.width,
                        element.height, (int)element.blendStrength);
                }
                if (element.fadeMode == 1) {
                    element.blendStrength = element.blendStrength - FLOAT_Between1And5::instance * 0.5;
                    if (element.blendStrength < 1.0)
                        element.fadeMode = 0;
                }
                if (element.fadeMode == 2) {
                    element.blendStrength = FLOAT_Between1And5::instance * 0.5 + element.blendStrength;
                    if (element.blendStrength > 31.0)
                        element.isValid = 0;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            } else if (element.isValid == 2) {
                uint color;
                switch (element.field10_0x28) {
                case 1:
                    color = 0;
                    break;
                default:
                    color = 0xccfaff;
                    break;
                }
                if (element.fadeMode == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::DrawLoadedMenuStringHelper)(element.xSpace, element.x,
                        element.y, element.width, color, element.field8_0x20, element.field9_0x24);
                } else {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::DrawLoadedMenuStringHelperWithBlending)(element.xSpace,
                        element.x, element.y, element.width, color, element.field8_0x20, element.field9_0x24,
                        (int)element.blendStrength);
                    if (element.fadeMode == 1) {
                        element.blendStrength = element.blendStrength - FLOAT_Between1And5::instance * 0.5;
                        if (element.blendStrength < 1.0)
                            element.fadeMode = 0;
                    }
                    if (element.fadeMode == 2) {
                        element.blendStrength = FLOAT_Between1And5::instance * 0.5 + element.blendStrength;
                        if (element.blendStrength > 31.0)
                            element.isValid = 0;
                    }
                }
            } else if (element.isValid == 3) {
                if (DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        >= element.x
                    && DAT_MouseState::instance.screenSpaceX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                        < element.width + element.x
                    && DAT_MouseState::instance.screenSpaceY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                        >= element.y
                    && DAT_MouseState::instance.screenSpaceY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                        < element.height + element.y) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(
                        element.xSpace + 1, element.x, element.y);
                } else {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(element.xSpace, element.x, element.y);
                }
            }
        }
    }

    if (DWORD_00eb9ac4::instance != 0) {
        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTextPageProgressBar)();
    }
    if (DAT_00eb0e40::instance == 0 || DAT_00eb0e40::instance == 5)
        return;

    // Two calls (not one with locals): the original pushes the arguments in each branch.
    if ((int)DAT_00eb0e40::instance >= 3) {
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
            DAT_RenderRelatedX::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
            DAT_RenderRelatedY::instance + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
            DAT_RenderRelatedX::instance + DAT_00eb1234::instance - 1
                + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
            INT_00eb0e30::instance + DAT_RenderRelatedY::instance - 1
                + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
            (int)FLOAT_00eb0e2c::instance);
    } else {
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
            DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX - 1,
            DAT_WindowAndDirectDraw::instance.resolutionY - 1, (int)FLOAT_00eb0e2c::instance);
    }

    if (DAT_00eb0e40::instance == 1 || DAT_00eb0e40::instance == 3) {
        FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance + FLOAT_Between1And5::instance * 0.5;
        if (DAT_00eb0e40::instance == 3) {
            FLOAT_00eb0e2c::instance = FLOAT_Between1And5::instance * 0.5 + FLOAT_00eb0e2c::instance;
        }
        if (FLOAT_00eb0e2c::instance > 31.0) {
            DAT_00eb0e40::instance = 0;
            return;
        }
    }
    if (DAT_00eb0e40::instance == 2 || DAT_00eb0e40::instance == 4) {
        FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance - FLOAT_Between1And5::instance * 0.5;
        if (DAT_00eb0e40::instance == 4) {
            FLOAT_00eb0e2c::instance = FLOAT_00eb0e2c::instance - FLOAT_Between1And5::instance * 0.5;
        }
        if (FLOAT_00eb0e2c::instance < 0.0) {
            DAT_00eb0e40::instance = 0;
            MACRO_CALL(OpenSHC::UI::Credits_Func::AppendCreditsSoundEntry)(0, 0);
            return;
        }
    }
}

}
