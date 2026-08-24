#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion;
    using OpenSHC::UI::Enums::MenuModalType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB9F0
    void MapPropertiesState::openEventTriggerMenu(undefined4 eventType)

    {
        this->eventType = eventType;
        MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::resetEvent,
            (InGameEventUnionVersion*)&this->invasionEvent)();
        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_TRIGGER_EVENT_OR_INVASION);
        return;
    }

}
}
