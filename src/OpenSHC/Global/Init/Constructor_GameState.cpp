#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC20
    void Init::Constructor_GameState()
    {
        ((void*(__fastcall*)(GameStateStructures*))MACRO_CALL(Global::Init_Func::Constructor_Empty))(
            DAT_GameState::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d760::get());
    }

}
}
