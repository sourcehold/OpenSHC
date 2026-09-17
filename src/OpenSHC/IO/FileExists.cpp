#include "../IO.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_FileDoesntExist.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x004BC5B0
BOOLEnum IO::FileExists(char* param_1)
{
    FILE* _File = MACRO_CALL(OpenSHC::OS_Func::_fopen)(param_1, s_rb_005a4e18);
    if (!_File) {
        DAT_FileDoesntExist::instance = TRUE;
        return FALSE;
    }
    MACRO_CALL(OpenSHC::OS_Func::_fclose)(_File);
    DAT_FileDoesntExist::instance = FALSE;
    return TRUE;
}

}
