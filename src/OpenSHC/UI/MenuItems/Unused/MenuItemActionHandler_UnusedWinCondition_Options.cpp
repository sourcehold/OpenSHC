#include "OpenSHC/UI/MenuItems/Unused.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace Unused {

            using OpenSHC::UI::Enums::MenuModalType;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x004B1090
            void MenuItemActionHandler_UnusedWinCondition_Options(int value, ...)
            {
                if (value >= (int)DAT_MenuModalComposition1::instance.mbr_0x64) {
                    return;
                }
                DAT_MenuModalComposition1::instance.sliderValue = value;
                *DAT_MenuModalComposition1::instance.destination = value;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                if (DAT_MenuModalComposition1::instance.sliderCallbackFunction != NULL) {
                    ((void (*)())DAT_MenuModalComposition1::instance.sliderCallbackFunction)();
                }
            }

        }
    }
}
}
