#include "../EditScenario.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
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

#include "stdlib.h"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BF1D0
        void EditScenario::MenuItemRenderFunction_EditScenario_TextBoxLike(int param_1, ...)
        {
            int iVar1;
            char* pcVar2;
            long lVar3;
            int number;
            int xParam;
            int iVar4;
            if ((param_1 == 7)
                && (DAT_MissionAestheticsDefinedData::instance
                        .EventConditionMaxValue[DAT_MapPropertiesState::instance.invasionTroopIndex]
                    == 0)) {
                return;
            }
            iVar1 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            switch (param_1) {
            case 0:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    == (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_SEVEN__NUMERIC_ONLY)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 4 + iVar1, (int)(DAT_ButtonY::instance + 2),
                        DAT_ButtonX::instance + 5 + iVar1, (int)(DAT_ButtonH::instance - 4 + DAT_ButtonY::instance),
                        (ushort)(COL_DARK_LIME::instance.shortValue));
                }
                iVar1 = DAT_ButtonY::instance + 6;
                xParam = DAT_ButtonX::instance + 6;
                iVar4 = 15;
                break;
            case 1:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    == (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_TWO__FILTER_A)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 8 + iVar1, (int)(DAT_ButtonY::instance + 2),
                        DAT_ButtonX::instance + 9 + iVar1, (int)(DAT_ButtonH::instance - 4 + DAT_ButtonY::instance),
                        (ushort)(COL_DARK_LIME::instance.shortValue));
                }
                iVar1 = DAT_ButtonY::instance + 6;
                xParam = DAT_ButtonX::instance + 10;
                iVar4 = 10;
                break;
            case 2:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    == (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_THREE__FILTER_A)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 8 + iVar1, (int)(DAT_ButtonY::instance + 2),
                        DAT_ButtonX::instance + 9 + iVar1, (int)(DAT_ButtonH::instance - 4 + DAT_ButtonY::instance),
                        (ushort)(COL_DARK_LIME::instance.shortValue));
                }
                iVar1 = DAT_ButtonY::instance + 6;
                xParam = DAT_ButtonX::instance + 10;
                iVar4 = 11;
                break;
            case 3:
                if (DAT_UserTextHandlerState::instance.textArrayIndex == 12) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 9 + iVar1, (int)(DAT_ButtonY::instance + 2),
                        DAT_ButtonX::instance + 10 + iVar1, (int)(DAT_ButtonH::instance - 4 + DAT_ButtonY::instance),
                        (ushort)(COL_DARK_LIME::instance.shortValue));
                    if (DAT_MapPropertiesState::instance.indexStored < 20) {
                        pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                            DAT_UserTextHandlerState::ptr)(12);
                        lVar3 = atol(pcVar2);
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[DAT_MissionAestheticsDefinedData::instance
                                    .field_0x345c[DAT_MapPropertiesState::instance.indexStored]] = lVar3;
                    } else if (DAT_MapPropertiesState::instance.indexStored < 30) {
                        pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                            DAT_UserTextHandlerState::ptr)(12);
                        lVar3 = atol(pcVar2);
                        DAT_MapPropertiesState::instance
                            .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5] = lVar3;
                        iVar1 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                        if (500 < iVar1) {
                            DAT_MapPropertiesState::instance
                                .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5]
                                = DAT_MapPropertiesState::instance
                                      .SEC_StartingResources[DAT_MapPropertiesState::instance.indexStored + 5]
                                + (500 - iVar1);
                        }
                    } else if (DAT_MapPropertiesState::instance.indexStored == 30) {
                        pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                            DAT_UserTextHandlerState::ptr)(12);
                        DAT_MapPropertiesState::instance.SEC_StartingPopularity = atol(pcVar2);
                    }
                }
                goto LAB_004bf4f3;
            default:
                return;
            case 6:
                if (DAT_UserTextHandlerState::instance.textArrayIndex
                    == (OpenSHC::Text::TAIT_EIGHT__FILTER_B | OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 4 + iVar1, (int)(DAT_ButtonY::instance + 2),
                        DAT_ButtonX::instance + 5 + iVar1, (int)(DAT_ButtonH::instance - 4 + DAT_ButtonY::instance),
                        (ushort)(COL_DARK_LIME::instance.shortValue));
                }
                iVar1 = DAT_ButtonY::instance + 6;
                xParam = DAT_ButtonX::instance + 6;
                iVar4 = 14;
                break;
            case 7:
                if (DAT_UserTextHandlerState::instance.textArrayIndex == 12) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 9 + iVar1, (int)(DAT_ButtonY::instance + 2),
                        DAT_ButtonX::instance + 10 + iVar1, (int)(DAT_ButtonH::instance - 4 + DAT_ButtonY::instance),
                        (ushort)(COL_DARK_LIME::instance.shortValue));
                    pcVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(12);
                    lVar3 = atol(pcVar2);
                    *(short*)((int)&DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data
                        + DAT_MapPropertiesState::instance.invasionTroopIndex * 4 + 12) = (short)(lVar3
                        / DAT_MissionAestheticsDefinedData::instance
                            .EventConditionValueScale[DAT_MapPropertiesState::instance.invasionTroopIndex]);
                }
            LAB_004bf4f3:
                iVar1 = DAT_ButtonY::instance + 6;
                xParam = DAT_ButtonX::instance + 11;
                iVar4 = 12;
                break;
            case 100:
                // added by script: "Total Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 16,
                    (int)(DAT_ButtonW::instance / 2 - 20 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                    OpenSHC::Text::TTA_CENTER, 12775659, 18, FALSE);
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::sumUnitPoints, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    iVar1, (int)(DAT_ButtonW::instance / 2 - 10 + DAT_ButtonX::instance),
                    (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT, 12775659, 18, TRUE, 0);
                return;
            case 101:
                // added by script: "Total Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 16, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT, 12775659, 18, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::sumUnitCounts, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    number, (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                    OpenSHC::Text::TTA_RIGHT, 12775659, 18, FALSE, 0);
                return;
            case 102:
                // added by script: "Total Troops"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 16, (int)(DAT_ButtonX::instance + 20),
                    (int)(DAT_ButtonY::instance + 6), OpenSHC::Text::TTA_LEFT, 12775659, 18, FALSE);
                iVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::MapPropertiesState_Func::sumInvasionEventUnitCount, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    iVar1, (int)(DAT_ButtonW::instance - 10 + DAT_ButtonX::instance), (int)(DAT_ButtonY::instance + 6),
                    OpenSHC::Text::TTA_RIGHT, 12775659, 18, FALSE, 0);
                return;
            }
            pcVar2 = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(iVar4);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar2, xParam, iVar1, OpenSHC::Text::TTA_LEFT, 12775659, 18, FALSE, 0);
        }

    }
}
}
