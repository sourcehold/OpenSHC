#include "../BuildMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Map/Units/Selection/UnitSelectionEnum.hpp"
#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00439160
            void MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops(int slotID, ...)
            {
                if (DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                Map::Units::Selection::UnitSelectionEnumInt const troopType
                    = DAT_UnitsState::instance.selectionSlots[slotID];
                DAT_ButtonUnknownZero::instance = FALSE;
                if (troopType == -1) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    return;
                }
                // The count goes under the button where it was before the portrait is moved into place.
                int const buttonY = DAT_ButtonY::instance;
                int const buttonX = DAT_ButtonX::instance;
                // Each troop its own case (shared labels and fall-throughs: quick_diff 0.9457 -> 0.7640)
                switch (troopType) {
                case Map::Units::Selection::USE_E_ARCHERS:
                    DAT_ButtonY::instance -= 14;
                    break;
                case Map::Units::Selection::USE_E_SPEARMEN:
                    DAT_ButtonX::instance -= 3;
                    break;
                case Map::Units::Selection::USE_E_MACEMEN:
                    DAT_ButtonX::instance += 1;
                    break;
                case Map::Units::Selection::USE_E_PIKEMEN:
                    DAT_ButtonX::instance += 2;
                    DAT_ButtonY::instance -= 20;
                    break;
                case Map::Units::Selection::USE_E_SWORDSMEN:
                    DAT_ButtonX::instance += 1;
                    DAT_ButtonY::instance -= 8;
                    break;
                case Map::Units::Selection::USE_E_KNIGHTS:
                    DAT_ButtonY::instance -= 20;
                    DAT_ButtonX::instance -= 7;
                    break;
                case Map::Units::Selection::USE_E_ENGINEERS:
                    DAT_ButtonX::instance += 1;
                    break;
                case Map::Units::Selection::USE_E_LADDERMEN:
                    DAT_ButtonY::instance -= 8;
                    break;
                case Map::Units::Selection::USE_E_TUNNELERS:
                    DAT_ButtonY::instance -= 19;
                    break;
                case Map::Units::Selection::USE_E_BALLISTAS:
                    DAT_ButtonY::instance -= 4;
                    break;
                case Map::Units::Selection::USE_A_ARAB_ARCHERS:
                    DAT_ButtonY::instance -= 8;
                    DAT_ButtonX::instance += 2;
                    break;
                case Map::Units::Selection::USE_A_SLAVES:
                    DAT_ButtonY::instance -= 9;
                    DAT_ButtonX::instance += 1;
                    break;
                case Map::Units::Selection::USE_A_SLINGERS:
                    DAT_ButtonY::instance -= 7;
                    break;
                case Map::Units::Selection::USE_A_ASSASSINS:
                    DAT_ButtonY::instance -= 1;
                    break;
                case Map::Units::Selection::USE_A_HORSE_ARCHERS:
                    DAT_ButtonY::instance -= 13;
                    DAT_ButtonX::instance -= 6;
                    break;
                case Map::Units::Selection::USE_A_SWORDSMEN:
                    DAT_ButtonY::instance -= 9;
                    DAT_ButtonX::instance += 1;
                    break;
                case Map::Units::Selection::USE_A_FIRETHROWERS:
                    DAT_ButtonX::instance += 1;
                    break;
                case Map::Units::Selection::USE_A_FIRE_BALLISTAS:
                    DAT_ButtonX::instance -= 6;
                    break;
                }
                // The Arabian troops' portraits are a second set further along the button table.
                if (troopType >= Map::Units::Selection::USE_A_ARAB_ARCHERS) {
                    DAT_CurrentButtonGmDataIndex::instance = troopType + 521;
                } else {
                    DAT_CurrentButtonGmDataIndex::instance = troopType + 380;
                }
                MACRO_CALL(General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_UnitsState::instance.selectionUnitType[troopType], DAT_ButtonW::instance / 2 + buttonX,
                    buttonY + 83, Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_FFFFFF, 0, 17, FALSE, 0);
            }

        }
    }
}
}
