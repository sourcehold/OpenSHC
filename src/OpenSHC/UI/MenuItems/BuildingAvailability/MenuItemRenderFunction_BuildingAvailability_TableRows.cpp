#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
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
        namespace BuildingAvailability {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB3E0
            void MenuItemRenderFunction_BuildingAvailability_TableRows(int row, ...)
            {
                int const buildingIndex
                    = DAT_MissionAestheticsDefinedData::instance.BuildingAvailabilityStructIndexForNameArray
                          [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + row];
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                    DAT_PencilRenderCore::ptr)(FALSE, row, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                // The building's name: highlighted while hovered, grey when the building is not available.
                // One call per colour (one call with a colour local: quick_diff 0.9048 -> 0.5882)
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    // y then x in each branch (once, before the test: quick_diff 0.9048 -> 0.7857; x first: 0.8095)
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonX::instance + 20;
                    // The name last (before the test: quick_diff 0.9048 -> 0.7381; first: 0.7045; in the call: 0.5208)
                    int const nameNumber
                        = DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[buildingIndex]
                              .nameNumberInTextGroup;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, nameNumber),
                        textX, textY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                } else if (!DAT_MapPropertiesState::instance.buildingAvailability[buildingIndex]) {
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonX::instance + 20;
                    int const nameNumber
                        = DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[buildingIndex]
                              .nameNumberInTextGroup;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, nameNumber),
                        textX, textY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_7F7F7F, 19, FALSE, 0);
                } else {
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonX::instance + 20;
                    int const nameNumber
                        = DAT_MissionAestheticsDefinedData::instance.BuildingNameRelatedStructArray[buildingIndex]
                              .nameNumberInTextGroup;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_BUBBLE_HELP_TEXT, nameNumber),
                        textX, textY, Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE, 0);
                }
            }

        }
    }
}
}
