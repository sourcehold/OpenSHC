#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/FindingNetworkSessions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_FindingNetworkSessions.hpp"
#include "OpenSHC/Globals/Menu_FindingNetworkSessions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B820
    void Init::Constructor_MenuModal_FindingNetworkSessions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_FindingNetworkSessions::ptr)(
            UI::Enums::MMT_FINDING_NETWORK_SESSIONS, -1, -1, 500, 360, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::FindingNetworkSessions_Func::MenuModalRenderFunction_FindingNetworkSessions::get(),
            Menu_FindingNetworkSessions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_FindingNetworkSessions::get());
    }

}
}
