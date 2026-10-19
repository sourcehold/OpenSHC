#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "string.h"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E490
    void GameSynchronyState::readGameSpyConfig()
    {
        LONG LVar2;
        FILE* _File;
        HKEY__* local_c;
        DWORD local_8;
        DWORD local_4;
        char const* _pathSeparator = s___005a6f60;
        local_8 = 0x200;
        this->gameSpyArcadeAvailable = 0;
        LVar2 = RegOpenKeyExA((HKEY__*)0x80000001, s_Software_GameSpy_GameSpy_Arcade_005a6f6c, 0, 0x20019, &local_c);
        if (!LVar2) {
            LVar2 = RegQueryValueExA(
                local_c, s_InstDir_005a6f64, (DWORD*)0x0, &local_4, (BYTE*)this->shellExecuteTarget, &local_8);
            RegCloseKey(local_c);
            if (!LVar2) {
                /*
                  The original indexes with the full length, so this reads the terminator and the branch is
                  always taken; a trailing-separator test would have wanted length - 1.
                 */
                if (this->shellExecuteTarget[strlen(this->shellExecuteTarget)] != '\\') {
                    strcat(this->shellExecuteTarget, _pathSeparator);
                }
                strcat(this->shellExecuteTarget, s_aphex_exe_005a6f54);
                _File = MACRO_CALL(OS_Func::_fopen)(this->shellExecuteTarget, s_rb_005a4e18);
                if (_File != (FILE*)0x0) {
                    this->gameSpyArcadeAvailable = 1;
                    MACRO_CALL(OS_Func::_fclose)(_File);
                }
            }
        }
    }

}
}
