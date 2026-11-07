#include "../EditScenario.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include <stdlib.h>

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BF1D0
        void EditScenario::MenuItemRenderFunction_EditScenario_TextBoxLike(int box, ...)
        {
            if (box == 7
                && DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0) {
                return;
            }
            int const cursorOffset = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            // each case renders its own text (one call after the switch: quick_diff 0.9606 -> 0.9356)
            switch (box) {
            // boxes 0 to 7 show a text slot, with the cursor while it is typed into
            case 0: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_UNKNOWN_15) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 4 + cursorOffset, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 5 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                }
                // y, x and the text first (in the call: quick_diff 0.9606 -> 0.8724; the text in it: 0.8459)
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_15);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            case 1: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_UNKNOWN_10) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 8 + cursorOffset, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 9 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 10;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_10);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            case 2: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_UNKNOWN_11) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 8 + cursorOffset, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 9 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 10;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_11);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            case 3: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_UNKNOWN_12) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 9 + cursorOffset, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 10 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                    // the typed value goes to the starting good, unit or popularity being edited
                    if (DAT_MapPropertiesState::instance.indexStored < 20) {
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[DAT_MissionAestheticsDefinedData::instance
                                    .field_0x345c[DAT_MapPropertiesState::instance.indexStored]]
                            = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12));
                    } else if (DAT_MapPropertiesState::instance.indexStored < 30) {
                        DAT_MapPropertiesState::instance
                            .SEC_SiegeInformation[DAT_MapPropertiesState::instance.indexStored - 20]
                            = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12));
                        int const unitPoints = MACRO_CALL_MEMBER(
                            OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                        // the starting units may cost 500 points at most
                        if (unitPoints > 500) {
                            DAT_MapPropertiesState::instance
                                .SEC_SiegeInformation[DAT_MapPropertiesState::instance.indexStored - 20]
                                += 500 - unitPoints;
                        }
                    } else if (DAT_MapPropertiesState::instance.indexStored == 30) {
                        DAT_MapPropertiesState::instance.SEC_StartingPopularity
                            = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12));
                    }
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 11;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            case 6: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_UNKNOWN_14) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 4 + cursorOffset, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 5 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_14);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            case 7: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_UNKNOWN_12) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 9 + cursorOffset, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 10 + cursorOffset, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                    // the typed value, in the condition's unit
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .data.scenario.conditions[DAT_MapPropertiesState::instance.invasionTroopIndex]
                        .value = atol(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                                     DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12))
                        / DAT_MissionAestheticsDefinedData::instance
                              .EventConditionValueScale[DAT_MapPropertiesState::instance.invasionTroopIndex];
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 11;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_UNKNOWN_12);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            // 100 to 102 show a total under a "Total Troops" label
            case 100: {
                // "Total Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 16, DAT_ButtonW::instance / 2 - 20 + DAT_ButtonX::instance,
                    DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18,
                    FALSE);
                int const unitPoints = MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    unitPoints, DAT_ButtonW::instance / 2 - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, TRUE, 0);
                break;
            }
            case 101: {
                // "Total Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 16, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                int const unitCount = MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::sumUnitCounts, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    unitCount, DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            case 102: {
                // "Total Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 16, DAT_ButtonX::instance + 20, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE);
                int const invasionUnitCount = MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::sumInvasionEventUnitCount, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    invasionUnitCount, DAT_ButtonW::instance - 10 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_RIGHT, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE, 0);
                break;
            }
            }
        }

    }
}
}
