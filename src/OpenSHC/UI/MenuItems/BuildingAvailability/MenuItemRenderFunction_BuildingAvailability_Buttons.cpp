#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

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
        namespace BuildingAvailability {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB0D0
            void MenuItemRenderFunction_BuildingAvailability_Buttons(int button, ...)
            {
                // Buttons from 1000 show whether a row is allowed, from 2000 the row's own menu button.
                if (button >= 1000 && button < 2000) {
                    short const available
                        = DAT_MapPropertiesState::instance.buildingAvailability
                              [DAT_MissionAestheticsDefinedData::instance.BuildingAvailabilityStructIndexForNameArray
                                      [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset + button
                                          - 1000]];
                    // Set in each branch, for the original's neg/sbb (a default overridden: quick_diff 0.9000 ->
                    // 0.8545)
                    int textID;
                    if (available) {
                        textID = 172;
                    } else {
                        textID = 173;
                    }
                    MACRO_CALL_MEMBER(Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    // One call per colour, which MSVC merges (one call with a colour local: quick_diff 0.9000 ->
                    // 0.7763) The position in each branch (once, before the test: quick_diff 0.9000 -> 0.8909)
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        int const textY = DAT_ButtonY::instance + 6;
                        int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SCENARIO, textID),
                            textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE, 0);
                        return;
                    }
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_SCENARIO, textID),
                        textX, textY, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 19, FALSE, 0);
                    return;
                }
                if (button >= 2000 && button < 3000) {
                    // Only the weapon workshops and the two barracks have a menu.
                    // Set before the switch, cleared in the cases (in a default: arm: quick_diff 0.9000 -> 0.8869)
                    DAT_ButtonUnknownZero::instance = TRUE;
                    switch (DAT_MissionAestheticsDefinedData::instance
                            .BuildingNameRelatedStructArray[DAT_MissionAestheticsDefinedData::instance
                                    .BuildingAvailabilityStructIndexForNameArray
                                        [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                                            + button - 2000]]
                            .field_0x4[0]
                            .identifier1) {
                    case Commands::M_MAPPER_FLETCHER:
                    case Commands::M_MAPPER_POLETURNER:
                    case Commands::M_MAPPER_BLACKSMITH:
                    case Commands::M_MAPPER_BARRACKS_EURO:
                    case Commands::M_MAPPER_BARRACKS_ARAB:
                        DAT_ButtonUnknownZero::instance = FALSE;
                        MACRO_CALL_MEMBER(Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                            AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                        // One call per colour (one call with a colour local: quick_diff 0.9000 -> 0.8018)
                        if (!DAT_ButtonCurrentlyInteracting::instance) {
                            // "!"
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                s___005aa7fc, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                                DAT_ButtonY::instance + 6, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                                FALSE, 0);
                        } else {
                            // "!"
                            MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                s___005aa7fc, DAT_ButtonW::instance / 2 + DAT_ButtonX::instance,
                                DAT_ButtonY::instance + 6, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 19,
                                FALSE, 0);
                        }
                        return;
                    }
                    return;
                }
                // -2 and -1 are the scroll buttons.
                switch (button) {
                case -2:
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(
                        Rendering::PencilRenderCore_Func::renderUpDownButtonUnk, DAT_PencilRenderCore::ptr)(1, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                case -1:
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(
                        Rendering::PencilRenderCore_Func::renderUpDownButtonUnk, DAT_PencilRenderCore::ptr)(0, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                MACRO_CALL(Rendering_Func::RenderScenarioButtonWithText)(button);
            }

        }
    }
}
}
