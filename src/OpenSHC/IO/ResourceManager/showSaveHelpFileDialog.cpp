#include "../ResourceManager.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00472100
    BOOLEnum ResourceManager::showSaveHelpFileDialog()
    {
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resetOpenFileNameStruct, this)();
        MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::setHelpFileFilter, this)();
        this->openFileNameA.lpstrTitle = s_Select_help_file_to_save_005a6284;
        MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        return GetSaveFileNameA((LPOPENFILENAMEA) & this->openFileNameA) != NULL;
    }

} // namespace IO
} // namespace OpenSHC
