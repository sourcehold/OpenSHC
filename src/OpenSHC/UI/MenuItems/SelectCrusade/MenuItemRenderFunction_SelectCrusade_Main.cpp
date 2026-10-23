#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/MenuItems/SelectCrusade.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_HighlightedSkirmishType.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SelectCrusade {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x0042C060
            void MenuItemRenderFunction_SelectCrusade_Main(int skirmishType, ...)
            {
                if (skirmishType == -1) {
                    DAT_HighlightedSkirmishType::instance = 0;
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    DAT_HighlightedSkirmishType::instance = skirmishType;
                }
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
            }

        }
    }
}
}
