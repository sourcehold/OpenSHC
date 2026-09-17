// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046C320
    void ResourceManager::loadConfigPathTxt()
    {
        FILE* _File = MACRO_CALL(OS_Func::_fopen)(s_configpath_txt_005a5a0c, s_rb_005a4e18);
        if (!_File) {
            return;
        }

        MACRO_CALL(OS_Func::_fseek)(_File, 0, FILE_END);
        int _count = MACRO_CALL(OS_Func::_ftell)(_File);
        MACRO_CALL(OS_Func::_fseek)(_File, 0, FILE_BEGIN);

        if (_count > 500) {
            _count = 500;
        }

        char _configPathBufferUnk[1000];
        MACRO_CALL(OS_Func::_fread)(_configPathBufferUnk, sizeof(char), _count, _File);

        _configPathBufferUnk[_count] = '\0';
        int index = 0;
        for (; index < _count; ++index) {
            if (_configPathBufferUnk[index] == '\r' || _configPathBufferUnk[index] == '\n') {
                _configPathBufferUnk[index] = '\0';
                break;
            }
        }
        if (index > 2) {
            if (_configPathBufferUnk[index + -1] == '\\') {
                _configPathBufferUnk[index + -1] = '\0';
            }
            this->configPathLoadedUnk_0x7da = true;
            strcpy(this->configPathUnk_0x7db, _configPathBufferUnk);
        }

        MACRO_CALL(OS_Func::_fclose)(_File);
    }

} // namespace IO
} // namespace OpenSHC
