#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/AlliesSendGoods.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_AlliesSendGoods.hpp"
#include "OpenSHC/Globals/Menu_AlliesSendGoods.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C280
    void Init::Constructor_MenuModal_AlliesSendGoods()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_AlliesSendGoods::ptr)(
            UI::Enums::MMT_ALLIES_SEND_GOODS, -1, -1, 600, 408, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::AlliesSendGoods_Func::MenuModalRenderFunction_AlliesSendGoods::get(),
            Menu_AlliesSendGoods::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_AlliesSendGoods::get());
    }

}
}
