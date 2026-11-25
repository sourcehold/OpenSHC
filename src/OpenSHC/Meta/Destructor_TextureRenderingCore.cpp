#include "../Meta.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0059D620
void Meta::Destructor_TextureRenderingCore()
{
    MACRO_CALL_MEMBER(
        UI::Rendering::TextureRenderCore_Func::Destructor_TextureRenderCore, DAT_TextureRenderCoreObject::ptr)();
}

}
