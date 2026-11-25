#include "../Init.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C8A0
    void Init::Constructor_GameCore()
    {
        MACRO_CALL_MEMBER(Game::GameCore_Func::Constructor_GameCore, DAT_GameCore::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_GameCoreAndRendering::get());
    }

}
}
