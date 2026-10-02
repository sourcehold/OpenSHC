#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BB0D0
        void BuildingAvailability::MenuItemRenderFunction_BuildingAvailability_Buttons(int param_1, ...)
        {
            short sVar1;
            int xParam;
            char* textAddress;
            int yParam;
            TextAlignment alignment;
            BGR24 BVar2;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 < 1000) {
                if (param_1 < 2000)
                    goto LAB_004bb22b;
            } else if (param_1 < 2000) {
                sVar1 = DAT_MapPropertiesState::instance.buildingAvailability[DAT_MissionAestheticsDefinedData::instance
                        .field1234_0x312c[DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                            + param_1]];
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                blendStrength = 0;
                xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance + 6;
                keepOffsetX = FALSE;
                fontSize = 0x13;
                if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                    BVar2 = 0xc2f0eb;
                } else {
                    BVar2 = 0xccfaff;
                }
                alignment = OpenSHC::Text::TTA_CENTER;
                textAddress = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_SCENARIO, (int)((int)(0xad - (uint)(sVar1 != 0))));
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    textAddress, xParam, yParam, alignment, BVar2, fontSize, keepOffsetX, blendStrength);
            }
            if (param_1 < 3000) {
                switch (DAT_MissionAestheticsDefinedData::instance
                        .BuildingNameRelatedStructArray[DAT_MissionAestheticsDefinedData::instance.field1224_0x218c
                                [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + param_1]]
                        .field1_0x4[0]
                        .identifier1) {
                case 0x32:
                case 0x52:
                case 0x53:
                case 0x56:
                case 0x57:
                    goto switchD_004bb1b8_caseD_32;
                default:
                    DAT_ButtonUnknownZero::instance = 1;
                }
            }
        LAB_004bb22b:
            if (param_1 == -2) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(1, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            if (param_1 == -1) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(param_1);
            return;
        switchD_004bb1b8_caseD_32:
            DAT_ButtonUnknownZero::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                BVar2 = 0xc2f0eb;
            } else {
                BVar2 = 0xccfaff;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("!",
                (int)((int)(DAT_ButtonW::instance / 2 + DAT_ButtonX::instance)),
                (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_CENTER, BVar2, 0x13, FALSE, 0);
        }

    }
}
}
