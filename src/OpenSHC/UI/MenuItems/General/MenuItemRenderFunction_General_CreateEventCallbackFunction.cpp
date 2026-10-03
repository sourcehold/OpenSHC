#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BBA60
        void General::MenuItemRenderFunction_General_CreateEventCallbackFunction(int param_1, ...)
        {
            int iVar1;
            char* textAddress;
            int yParam;
            int iVar2;
            TextAlignment alignment;
            BGR24 color;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            iVar2 = 2;
            iVar1 = -1;
            switch (param_1) {
            case 0x5b:
            case 0xdd:
                iVar1 = 0;
                break;
            case 0x5c:
            case 0xde:
                iVar1 = 1;
                break;
            case 0x5d:
                iVar1 = iVar2;
                break;
            case 0x5e:
                iVar1 = 3;
                break;
            case 0x5f:
                iVar1 = 4;
                break;
            case 0x60:
                iVar1 = 5;
                break;
            case 0x61:
                iVar1 = 6;
                break;
            case 0x62:
                iVar1 = 7;
                break;
            case 99:
                iVar1 = 8;
                break;
            case 0x9d:
                iVar1 = 9;
                break;
            case 0x9e:
                iVar1 = 10;
                break;
            case 0x9f:
                iVar1 = 0xb;
                break;
            case 0xa0:
                iVar1 = 0xc;
                break;
            case 0xa1:
                iVar1 = 0xd;
                break;
            case 0xa2:
                iVar1 = 0xe;
            }
            switch (param_1) {
            case 0x94:
                param_1 = 0x92;
                iVar2 = 0;
            case 0x92:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                blendStrength = 0;
                yParam = DAT_ButtonY::instance + 6;
                keepOffsetX = FALSE;
                fontSize = 0x12;
                iVar1 = DAT_ButtonW::instance / 2 + -0xf + DAT_ButtonX::instance;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    color = 0xc2f0eb;
                } else {
                    color = 0xccfaff;
                }
                alignment = OpenSHC::Text::TTA_CENTER;
                /*
                  "Bandits"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1),
                    iVar1, yParam, alignment, color, fontSize, keepOffsetX, blendStrength);
                iVar1 = DAT_TextManagerObject::instance.currentXOffset_0x0;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    " - ",
                    (int)((int)(DAT_TextManagerObject::instance.currentXOffset_0x0 / 2 + -0xf
                        + DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2 + 0x80,
                    (int)((int)(DAT_ButtonW::instance / 2 + -9
                        + (DAT_TextManagerObject::instance.currentXOffset_0x0 + iVar1) / 2 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 3)));
                return;
            case 0xdd:
            case 0xde:
                if (DAT_MapPropertiesState::instance.invasionEventContent.crusaderArabian == iVar1) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_SCENARIO, param_1,
                        (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x12, FALSE);
                }
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
        }

    }
}
}
