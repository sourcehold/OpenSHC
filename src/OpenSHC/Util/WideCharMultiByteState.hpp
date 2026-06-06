/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Util/WideCharMultiByteState.hpp'
*/

#pragma once

#include "winnt.h"

namespace OpenSHC {
namespace Util {

#pragma pack(push, 1)

    // SIZE: 0x00000001
    class WideCharMultiByteState {
    public:
        undefined1 padding_0x0[1]; // 0x00000000 length: 1

    private:
        WideCharMultiByteState(WideCharMultiByteState const&);
        void operator=(WideCharMultiByteState const&);

    public:
        WideCharMultiByteState();
        ~WideCharMultiByteState();

        int wideCharToMultiByteComplete(LPSTR charOut, LPCWSTR wideCharIn);

        void multiByteToWideCharacter(LPWSTR param_1, LPCSTR param_2);

        int wideCharToMultiByteWithSize(LPSTR lpMultiByteStr, LPWSTR lpWideCharStr, int numOfSymbols);

        void multiByteToWideCharThunk(LPWSTR param_1, LPCSTR param_2, int param_3);

        char wideCharToByteUnk(WCHAR wideChar);

        void multiByteToWideCharThunk2(undefined param_1);
    };

    static_assert_cpp98_obj(sizeof(WideCharMultiByteState) == 1, WideCharMultiByteState);

#pragma pack(pop)

} // namespace Util
} // namespace OpenSHC
