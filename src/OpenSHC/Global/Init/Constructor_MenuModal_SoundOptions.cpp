#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/SoundOptions.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/MenuModal_SoundOptions.hpp"
#include "OpenSHC/Globals/Menu_SoundOptions.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B420
    void Init::Constructor_MenuModal_SoundOptions()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_SoundOptions::ptr)(
            UI::Enums::MMT_SOUND_OPTIONS, -1, -1, 500, 357, 512, COL_WHITE::instance.shortValue,
            UI::MenuModals::SoundOptions_Func::MenuModalRenderFunction_SoundOptions::get(), Menu_SoundOptions::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_SoundOptions::get());
    }

}
}
