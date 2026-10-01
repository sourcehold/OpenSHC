#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/MenuItems/BuildMenu.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            // FUNCTION: STRONGHOLDCRUSADER 0x00466920
            void MenuItemRenderFunction_BuildMenu_BuildingSubcategoryButton(int buildingType, ...)
            {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::isMercRecruitableForBuildingType,
                        DAT_MapPropertiesState::ptr)(buildingType)
                    != 0) {
                    MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    DAT_ButtonUnknownZero::instance = 0;
                    return;
                }
                DAT_ButtonUnknownZero::instance = 1;
            }

        }
    }
}
}
