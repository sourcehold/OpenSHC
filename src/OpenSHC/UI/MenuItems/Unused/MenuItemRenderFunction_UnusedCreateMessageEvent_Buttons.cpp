#include "../Unused.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
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
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BA980
        void Unused::MenuItemRenderFunction_UnusedCreateMessageEvent_Buttons(int param_1, ...)
        {
            int textNumInGroup;
            uint color;
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_MapPropertiesState::instance.field69_0x13590 == 4) {
                if (param_1 == 9) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 10) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 0xb) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 0xc) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
            } else {
                if (param_1 == 0x3f1) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 0x3f2) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 0x3f3) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
                if (param_1 == 0x3f4) {
                    DAT_ButtonUnknownZero::instance = 1;
                }
            }
            if ((param_1 < 9) && (param_1 + -4 == DAT_MapPropertiesState::instance.field69_0x13590)) {
                if (DAT_MapPropertiesState::instance.field69_0x13590 == 3) {
                LAB_004baa3d:
                    if (8 < param_1) {
                        if (param_1 == 9) {
                            param_1 = 0x18;
                        } else {
                            if (param_1 != 10) {
                                DAT_ButtonUnknownZero::instance = 1;
                            }
                            param_1 = 0x19;
                        }
                    }
                }
            LAB_004baa59:
                DAT_ButtonCurrentlyInteracting::instance = TRUE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                textNumInGroup = param_1;
                if ((DAT_MapPropertiesState::instance.field69_0x13590 == 4)
                    && (((param_1 == 0x3f1 || (param_1 == 0x3f2)) || ((param_1 == 0x3f3 || (param_1 == 0x3f4)))))) {
                    textNumInGroup = param_1 + -1000;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ENEMY_FACES, param_1 + -0x3f0,
                        (int)((int)(DAT_ButtonW::instance / 2 + -0x20 + DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 7)));
                    DAT_ButtonY::instance = DAT_ButtonY::instance + 0x48;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                color = 0xccfaff;
                goto LAB_004babe5;
            }
            if (DAT_MapPropertiesState::instance.field69_0x13590 == 4) {
                if ((((param_1 < 0xd) || (1000 < param_1))
                        && (param_1 + -0x3f1 == (*(int*)&DAT_MapPropertiesState::instance.padding_0x13594[0])))
                    || (param_1 + -0xd == (*(int*)&DAT_MapPropertiesState::instance.padding_0x13594[4])))
                    goto LAB_004baa59;
            } else {
                if (DAT_MapPropertiesState::instance.field69_0x13590 == 3) {
                    if ((param_1 < 0xd) && (param_1 + -8 == (*(int*)&DAT_MapPropertiesState::instance.padding_0x13594[0])))
                        goto LAB_004baa3d;
                LAB_004bab10:
                    if (0xc < param_1) {
                        DAT_ButtonUnknownZero::instance = 0;
                    }
                } else {
                    if ((DAT_MapPropertiesState::instance.field69_0x13590 < 3) && (8 < param_1)) {
                        DAT_ButtonUnknownZero::instance = 0;
                    }
                    if (DAT_MapPropertiesState::instance.field69_0x13590 < 4)
                        goto LAB_004bab10;
                }
                if ((DAT_MapPropertiesState::instance.field69_0x13590 == 3) && (8 < param_1)) {
                    if (param_1 == 9) {
                        param_1 = 0x18;
                    } else {
                        if (param_1 != 10) {
                            DAT_ButtonUnknownZero::instance = 1;
                        }
                        param_1 = 0x19;
                    }
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            textNumInGroup = param_1;
            if ((DAT_MapPropertiesState::instance.field69_0x13590 == 4)
                && (((param_1 == 0x3f1 || (param_1 == 0x3f2)) || ((param_1 == 0x3f3 || (param_1 == 0x3f4)))))) {
                textNumInGroup = param_1 + -1000;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ENEMY_FACES, param_1 + -0x3f0,
                    (int)((int)(DAT_ButtonW::instance / 2 + -0x20 + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance + 7)));
                DAT_ButtonY::instance = DAT_ButtonY::instance + 0x48;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                color = 0xc2f0eb;
            } else {
                color = 0xccfaff;
            }
        LAB_004babe5:
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                OpenSHC::DE::SHCDE::TEXT_SCENARIO, textNumInGroup,
                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, color, 0x12, FALSE);
        }

    }
}
}
