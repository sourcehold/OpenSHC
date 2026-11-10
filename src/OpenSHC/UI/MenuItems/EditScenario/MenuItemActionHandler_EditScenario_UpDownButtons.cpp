#include "../EditScenario.func.hpp"

#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace EditScenario {

            // FUNCTION: STRONGHOLDCRUSADER 0x004B9020
            void MenuItemActionHandler_EditScenario_UpDownButtons(int action, ...)
            {
                // the arrows do nothing while a dialog is open
                if (DAT_MenuModalComposition1::instance.activeModalDialogID != Enums::MMT_NONE) {
                    return;
                }
                // -2 scrolls the event list down and -1 up; it shows 20 events.
                switch (action) {
                case -2:
                    if (DAT_MapPropertiesState::instance.eventListScrollOffset
                        < DAT_MapPropertiesState::instance.eventsCount - 20) {
                        ++DAT_MapPropertiesState::instance.eventListScrollOffset;
                    }
                    break;
                case -1:
                    if (DAT_MapPropertiesState::instance.eventListScrollOffset > 0) {
                        --DAT_MapPropertiesState::instance.eventListScrollOffset;
                    }
                    break;
                }
            }

        }
    }
}
}
