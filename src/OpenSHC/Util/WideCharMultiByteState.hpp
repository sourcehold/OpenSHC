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
        WideCharMultiByteState() {};
        ~WideCharMultiByteState() {};

        int wideCharToMultiByteComplete(LPSTR charOut, LPCWSTR wideCharIn);

        int multiByteToWideCharacter(LPWSTR lpWideCharStr, LPCSTR lpMultiByteStr);

        int wideCharToMultiByteWithSize(LPSTR lpMultiByteStr, LPWSTR lpWideCharStr, int numOfSymbols);

        int multiByteToWideCharWithSize(LPWSTR lpWideCharStr, LPCSTR lpMultiByteStr, int numberOfSymbols);

        char singleWideCharToMultiByte(WCHAR wideChar);

        WCHAR singleMultiByteToWideChar(char character);
    };

    static_assert_cpp98_obj(sizeof(WideCharMultiByteState) == 1, WideCharMultiByteState);

#pragma pack(pop)

} // namespace Util
} // namespace OpenSHC
