#include "../ResourceManager.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472140
    BOOLEnum ResourceManager::showOpenSoundFileDialog()
    {
        MACRO_CALL_MEMBER(ResourceManager_Func::resetOpenFileNameStruct, this)();
        MACRO_CALL_MEMBER(ResourceManager_Func::setSoundFileFilter, this)();
        this->openFileNameA.lpstrTitle = s_Select_sound_file_to_import_005a62a0;
        MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        return GetOpenFileNameA((LPOPENFILENAMEA) & this->openFileNameA) != NULL;
    }

} // namespace IO
} // namespace OpenSHC
