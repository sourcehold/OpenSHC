#include "../ResourceManager.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

#include "shlobj.h"

namespace OpenSHC {
namespace IO {

    // NOTE: "string_prependUserPathToString" can likely not be resolved, since the call is optimized and ignores proper
    // call conventions in the game. Trying it does not make much sense also, since the strings interact with the
    // allocator of the game, causing memory issues if hooked anyway.

    // FUNCTION: STRONGHOLDCRUSADER 0x00477710
    static bool string_prependUserPathToString(std::string& out, char const* path, int csidl)
    {
        if (DAT_ResourceManager::instance.configPathLoadedUnk_0x7da) {
            std::string localStr(DAT_ResourceManager::instance.configPathUnk_0x7db);
            out = localStr;
            out.append(path);
        } else {
            // apparently, SHGetFolderPathW only returns a maximum of MAX_PATH, which is 260, so they overdid it
            WCHAR pszPath[2000];
            if (SHGetFolderPathW(NULL, csidl | CSIDL_FLAG_CREATE, NULL, NULL, pszPath) < S_OK) {
                return false;
            }

            WCHAR _wideCharStr[2000];
            GetShortPathNameW(pszPath, _wideCharStr, sizeof(_wideCharStr) / sizeof(WCHAR));

            CHAR _multiByteStr[2000];
            MACRO_CALL_MEMBER(Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                DAT_WideCharMultiByteState::ptr)(_multiByteStr, _wideCharStr, sizeof(_multiByteStr) - 1);

            out.append(_multiByteStr);
            out.append(path);
        }
        if (GetFileAttributesA(out.c_str()) == INVALID_FILE_ATTRIBUTES && !CreateDirectoryA(out.c_str(), NULL)) {
            return false;
        }
        return true;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x004778E0
    std::string ResourceManager::paths_getDocumentsFolderString(bool param_2)
    {
        std::string suffix(s__Stronghold_Crusader__005a6434);
        std::string userPath;
        string_prependUserPathToString(userPath, suffix.c_str(), CSIDL_PERSONAL);
        if (param_2) {
            return userPath;
        } else {
            return suffix;
        }
    }

    // Return Value Optimization is not compatible with the resolver, therefore, the call needs to be direct.

    // FUNCTION: STRONGHOLDCRUSADER 0x004779F0
    std::string ResourceManager::paths_getSavesPath(bool param_2)
    {
        std::string suffix(this->paths_getDocumentsFolderString(false));
        suffix.append(s_Saves__005a644c);
        std::string userPath;
        string_prependUserPathToString(userPath, suffix.c_str(), CSIDL_PERSONAL);
        if (param_2) {
            return userPath;
        } else {
            return suffix;
        }
    }

} // namespace IO
} // namespace OpenSHC
