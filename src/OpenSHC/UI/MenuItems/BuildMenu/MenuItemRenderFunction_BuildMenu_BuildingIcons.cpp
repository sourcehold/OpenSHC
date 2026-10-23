#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/MenuItems/BuildMenu.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            using OpenSHC::Commands::MappersEnum;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x004668F0
            void MenuItemRenderFunction_BuildMenu_BuildingIcons(int mapper, ...)
            {
                if (MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::isMapperAvailable,
                        DAT_MapPropertiesState::ptr)((MappersEnum)mapper)
                    != FALSE) {
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
