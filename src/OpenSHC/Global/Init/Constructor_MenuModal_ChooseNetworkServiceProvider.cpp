#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/ChooseNetworkServiceProvider.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_ChooseNetworkServiceProvider.hpp"
#include "OpenSHC/Globals/Menu_ChooseNetworkServiceProvider.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B7E0
    void Init::Constructor_MenuModal_ChooseNetworkServiceProvider()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_ChooseNetworkServiceProvider::ptr)(
            UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER, 150, 80, 500, 408, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::ChooseNetworkServiceProvider_Func::MenuModalRenderFunction_ChooseNetworkServiceProvider::
                get(),
            Menu_ChooseNetworkServiceProvider::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_ChooseNetworkServiceProvider::get());
    }

}
}
