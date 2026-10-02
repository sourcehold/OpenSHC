#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00466620
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_OutpostUnitSelection(int param_1, ...)
        {
            char* textAddress;
            int yParam;
            uint uVar1;
            int iVar2;
            TextAlignment alignment;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            uVar1 = 1 << ((byte)param_1 & 0x1f);
            iVar2 = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].buildingType
                == OpenSHC::Map::Buildings::BT_OUTPOST_ARABIAN) {
                iVar2 = 9;
            }
            if (DAT_ButtonCurrentlyInteracting::instance == FALSE) {
                if ((DAT_BuildingsState::instance.menuSelectedBuildingID == 0)
                    || (DAT_ButtonCurrentlyInteracting::instance = TRUE,
                        (uVar1
                            & (int)DAT_BuildingsState::instance
                                .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                .outpostRelatedUnk1)
                            == 0)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                backgroundColor = 0x3e66;
                uVar1 = 0xc2f0eb;
            } else {
                if ((DAT_BuildingsState::instance.menuSelectedBuildingID == 0)
                    || (DAT_ButtonCurrentlyInteracting::instance = TRUE,
                        (uVar1
                            & (int)DAT_BuildingsState::instance
                                .buildings[DAT_BuildingsState::instance.menuSelectedBuildingID]
                                .outpostRelatedUnk1)
                            == 0)) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                backgroundColor = 0;
                uVar1 = 0xccfaff;
            }
            blendStrength = 0;
            keepOffsetX = FALSE;
            fontSize = 0x12;
            alignment = OpenSHC::Text::TTA_CENTER;
            yParam = DAT_ButtonY::instance + 7;
            int xParam = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_OUTPOST, iVar2 + 1 + param_1), xParam, yParam, alignment, uVar1, backgroundColor, fontSize, keepOffsetX, blendStrength);
        }

    }
}
}
