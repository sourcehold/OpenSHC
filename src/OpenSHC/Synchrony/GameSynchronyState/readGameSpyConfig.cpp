#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "string.h"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047E490
    void GameSynchronyState::readGameSpyConfig()
    {
        HKEY__* _key;
        DWORD _valueType;
        DWORD _valueSize = 512;
        this->gameSpyArcadeAvailable = 0;
        LONG _result = RegOpenKeyExA(HKEY_CURRENT_USER, s_Software_GameSpy_GameSpy_Arcade_005a6f6c, 0, KEY_READ, &_key);
        if (!_result) {
            _result = RegQueryValueExA(
                _key, s_InstDir_005a6f64, (DWORD*)0x0, &_valueType, (BYTE*)this->shellExecuteTarget, &_valueSize);
            RegCloseKey(_key);
            if (!_result) {
                // The original indexes with the full length, so this reads the terminator and the
                // branch is always taken; a trailing-separator test would have wanted length - 1.
                if (this->shellExecuteTarget[strlen(this->shellExecuteTarget)] != '\\') {
                    strcat(this->shellExecuteTarget, s___005a6f60);
                }
                strcat(this->shellExecuteTarget, s_aphex_exe_005a6f54);
                FILE* _file = MACRO_CALL(OS_Func::_fopen)(this->shellExecuteTarget, s_rb_005a4e18);
                if (_file != (FILE*)0x0) {
                    this->gameSpyArcadeAvailable = 1;
                    MACRO_CALL(OS_Func::_fclose)(_file);
                }
            }
        }
    }

}
}
