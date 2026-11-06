#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAndStatusMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00466620
            void MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection(int bitIndex, ...)
            {
                int const unitBit = 1 << bitIndex;
                // Each outpost's title comes before its unit names; the Arabian outpost's follow the European ones.
                int textOffset = 0;
                if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                        .buildingType
                    == Map::Buildings::BT_OUTPOST_ARABIAN) {
                    textOffset = 9;
                }
                // The button shows pressed while the outpost has this unit selected.
                // The test and the draw in each branch (once, before the hover test: quick_diff 0.9206 -> 0.5854)
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    if (DAT_BuildingsState::instance.menuSelectedBuildingID != 0
                        && (unitBit
                               & DAT_BuildingsState::instance
                                   .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                   .outpostRelatedUnk1)
                            != 0) {
                        DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    } else {
                        DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    }
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    // One call per colour pair (one call with colour locals: quick_diff 0.9206 -> 0.4615)
                    // The position in each branch (in the calls: quick_diff 0.9206 -> 0.8730)
                    int const textY = DAT_ButtonY::instance + 7;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_IN_OUTPOST, textOffset + 1 + bitIndex),
                        textX, textY, Text::TTA_CENTER, Rendering::Colors::COL_C2F0EB, Rendering::Colors::COL_003E66,
                        18, FALSE, 0);
                    return;
                }
                if (DAT_BuildingsState::instance.menuSelectedBuildingID != 0
                    && (unitBit
                           & DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                               .outpostRelatedUnk1)
                        != 0) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                } else {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                MACRO_CALL(General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                int const textY = DAT_ButtonY::instance + 7;
                int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        DE::SHCDE::TEXT_IN_OUTPOST, textOffset + 1 + bitIndex),
                    textX, textY, Text::TTA_CENTER, Rendering::Colors::COL_CCFAFF, Rendering::Colors::COL_000000, 18,
                    FALSE, 0);
            }

        }
    }
}
}
