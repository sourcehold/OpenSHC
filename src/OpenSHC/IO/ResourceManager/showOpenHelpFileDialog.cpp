#include "../ResourceManager.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004720C0
    BOOLEnum ResourceManager::showOpenHelpFileDialog(LPCSTR param_1)
    {
        MACRO_CALL_MEMBER(ResourceManager_Func::resetOpenFileNameStruct, this)();
        MACRO_CALL_MEMBER(ResourceManager_Func::setHelpFileFilter, this)();
        this->openFileNameA.lpstrTitle = param_1;
        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        return GetOpenFileNameA((LPOPENFILENAMEA) & this->openFileNameA) != NULL;
    }

} // namespace IO
} // namespace OpenSHC
