#include "../Init.func.hpp"

#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059CC60
    void Init::Constructor_TextEditorState()
    {
        MACRO_CALL_MEMBER(Text::TextEditorState_Func::Constructor_TextEditorState, DAT_TextEditorState::ptr)();
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_0059d780::get());
    }

}
}
