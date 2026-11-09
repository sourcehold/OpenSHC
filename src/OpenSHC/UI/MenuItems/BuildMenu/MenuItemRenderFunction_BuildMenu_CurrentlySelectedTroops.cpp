#include "../BuildMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
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
            void MenuItemRenderFunction_BuildMenu_CurrentlySelectedTroops(int slot, ...)
            {
                if (DAT_UnitsState::instance.nHasOwnedUnitInSelection == 0) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    return;
                }
                // an index into RenderingDefinedData::SelectionSlotUnitTypes
                int const troopType = DAT_UnitsState::instance.selectionSlots[slot];
                DAT_ButtonUnknownZero::instance = FALSE;
                if (troopType == -1) {
                    DAT_ButtonUnknownZero::instance = TRUE;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    return;
                }
                // The count goes under the button where it was before the portrait is moved into place.
                int const buttonY = DAT_ButtonY::instance;
                int const buttonX = DAT_ButtonX::instance;
                // no shared labels or fall-throughs, so MSVC copies the >= 19 test into each case as the original
                switch (troopType) {
                case 0: // archer
                    DAT_ButtonY::instance -= 14;
                    break;
                case 1: // spearman
                    DAT_ButtonX::instance -= 3;
                    break;
                case 2: // maceman
                    DAT_ButtonX::instance += 1;
                    break;
                case 4: // pikeman
                    DAT_ButtonX::instance += 2;
                    DAT_ButtonY::instance -= 20;
                    break;
                case 5: // swordsman
                    DAT_ButtonX::instance += 1;
                    DAT_ButtonY::instance -= 8;
                    break;
                case 6: // knight
                    DAT_ButtonY::instance -= 20;
                    DAT_ButtonX::instance -= 7;
                    break;
                case 7: // engineer
                    DAT_ButtonX::instance += 1;
                    break;
                case 8: // ladderman
                    DAT_ButtonY::instance -= 8;
                    break;
                case 9: // tunneler
                    DAT_ButtonY::instance -= 19;
                    break;
                case 17: // ballista
                    DAT_ButtonY::instance -= 4;
                    break;
                case 19: // Arabian archer
                    DAT_ButtonY::instance -= 8;
                    DAT_ButtonX::instance += 2;
                    break;
                case 20: // slave
                    DAT_ButtonY::instance -= 9;
                    DAT_ButtonX::instance += 1;
                    break;
                case 21: // slinger
                    DAT_ButtonY::instance -= 7;
                    break;
                case 22: // assassin
                    DAT_ButtonY::instance -= 1;
                    break;
                case 23: // horse archer
                    DAT_ButtonY::instance -= 13;
                    DAT_ButtonX::instance -= 6;
                    break;
                case 24: // Arabian swordsman
                    DAT_ButtonY::instance -= 9;
                    DAT_ButtonX::instance += 1;
                    break;
                case 25: // fire thrower
                    DAT_ButtonX::instance += 1;
                    break;
                case 26: // fire ballista
                    DAT_ButtonX::instance -= 6;
                    break;
                }
                // The Arabian troops' portraits (19 on) are a second set further along the button table.
                if (troopType >= 19) {
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
