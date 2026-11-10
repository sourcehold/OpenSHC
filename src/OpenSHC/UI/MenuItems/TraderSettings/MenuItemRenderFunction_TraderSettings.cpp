#include "../TraderSettings.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_BLUE.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004C1070
        void TraderSettings::MenuItemRenderFunction_TraderSettings(int button, ...)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            // below 0 the goods rows, below 1000 the dialog's buttons, 1100 the trader's name, else the goods list
            if (button < 0) {
                int const row = -1 - button;
                DAT_ButtonCurrentlyInteracting::instance
                    = DAT_MapPropertiesState::instance.SEC_Section1065
                          .tradeabilityArray[DAT_MissionAestheticsDefinedData::instance.field_0x345c[row]]
                    != FALSE;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                int const resource = DAT_MissionAestheticsDefinedData::instance.field_0x345c[row];
                // Two pictures per good from 141; partial pitch (157) shows the pitch picture (155)
                int icon = resource * 2 + 141;
                if (icon == 157) {
                    icon = 155;
                }
                int const imhIndex = icon + GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2] - 1;
                // y then x for the On/Off text (in the call: quick_diff 0.9570 -> 0.8865; x first: 0.9140)
                if (DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[resource]) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, icon,
                        DAT_ButtonX::instance + 10,
                        DAT_ButtonY::instance - DAT_GMImageHeaders::instance.imh[imhIndex].height / 2 + 15);
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance - 10 + DAT_ButtonX::instance;
                    // "On"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 172),
                        textX, textY, OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, icon,
                        DAT_ButtonX::instance + 10,
                        DAT_ButtonY::instance - DAT_GMImageHeaders::instance.imh[imhIndex].height / 2 + 15, 16);
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance - 10 + DAT_ButtonX::instance;
                    // "Off"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 173),
                        textX, textY, OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_7CAAAF, 18, FALSE, 0);
                }
            } else if (button < 1000) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderScenarioButtonWithText)(button);
            } else if (button == 1100) {
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        OpenSHC::UI::Enums::RBERL_SLIGHT);
                    // "Trader 1"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TRADER_NAMES, 1, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_00A2FF,
                        OpenSHC::Rendering::Colors::COL_003E66, 18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                        DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                        COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
                    // "Trader 1"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TRADER_NAMES, 1, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                        DAT_ButtonY::instance + 7, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_FFFFFF,
                        OpenSHC::Rendering::Colors::COL_000000, 18, FALSE);
                }
            } else if (!DAT_ButtonCurrentlyInteracting::instance) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdges,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    OpenSHC::UI::Enums::RBERL_SLIGHT);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBoxWithRoundedEdgesAndColor,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                    COL_BLUE::instance.shortValue, OpenSHC::UI::Enums::RBERL_SLIGHT);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
