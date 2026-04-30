/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
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

        WideCharMultiByteState();
        ~WideCharMultiByteState();

    public:
        int wideCharToMultiByteComplete(LPSTR charOut, LPCWSTR wideCharIn);

        void multiByteToWideCharacter(LPWSTR param_1, LPCSTR param_2);

        int wideCharToMultiByteWithSize(LPSTR lpMultiByteStr, LPWSTR lpWideCharStr, int numOfSymbols);

        void multiByteToWideCharThunk(LPWSTR param_1, LPCSTR param_2, int param_3);

        char wideCharToByteUnk(WCHAR wideChar);

        void multiByteToWideCharThunk2(undefined param_1);
    };

    static_assert_cpp98_obj(sizeof(WideCharMultiByteState) == 1, WideCharMultiByteState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(WideCharMultiByteState, false, Address::SHC_3BB0A8C1_0x00EE1099) pDAT_WideCharMultiByteState;

} // namespace Util
} // namespace OpenSHC
