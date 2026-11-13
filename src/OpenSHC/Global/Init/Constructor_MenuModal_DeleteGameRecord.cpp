#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/DeleteGameRecord.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_DeleteGameRecord.hpp"
#include "OpenSHC/Globals/Menu_DeleteGameRecord.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C300
    void Init::Constructor_MenuModal_DeleteGameRecord()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_DeleteGameRecord::ptr)(
            UI::Enums::MMT_DELETE_GAME_RECORD, -1, -1, 500, 150, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::DeleteGameRecord_Func::MenuModalRenderFunctionMenuModal_DeleteGameRecord::get(),
            Menu_DeleteGameRecord::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_DeleteGameRecord::get());
    }

}
}
