#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C9A0
    void Init::Constructor_TextureRenderingCore()
    {
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::Constructor_TextureRenderCore,
            DAT_TextureRenderCoreObject::ptr)(68100000, (int)((int)(18250000)), 0);
        MACRO_CALL(OS_Func::_atexit)(MACRO_CALL(Meta_Func::Destructor_TextureRenderingCore));
        return;
    }

}
}
