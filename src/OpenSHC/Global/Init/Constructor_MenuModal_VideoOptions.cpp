#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/VideoOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_VideoOptions.hpp"
#include "OpenSHC/Globals/Menu_VideoOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B3E0
    void Init::Constructor_MenuModal_VideoOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_VideoOptions::ptr)(
            UI::Enums::MMT_VIDEO_OPTIONS, -1, -1, 500, 357, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::VideoOptions_Func::MenuModalRenderFunction_VideoOptions::get(), Menu_VideoOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_VideoOptions::get());
    }

}
}
