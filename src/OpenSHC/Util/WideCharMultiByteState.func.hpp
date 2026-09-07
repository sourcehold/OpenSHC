/**
  path: 'OpenSHC/Util/WideCharMultiByteState.func.hpp'
*/

#include "OpenSHC/Util/WideCharMultiByteState.hpp"

#include "winnt.h"
namespace OpenSHC {
namespace Util {
    namespace WideCharMultiByteState_Func {

        MACRO_FUNCTION_RESOLVER(int (WideCharMultiByteState::*)(LPSTR, LPCWSTR), false,
            Address::SHC_3BB0A8C1_0x0046B080, &WideCharMultiByteState::wideCharToMultiByteComplete)
        wideCharToMultiByteComplete;

        MACRO_FUNCTION_RESOLVER(int (WideCharMultiByteState::*)(LPWSTR, LPCSTR), false,
            Address::SHC_3BB0A8C1_0x0046B0D0, &WideCharMultiByteState::multiByteToWideCharacter)
        multiByteToWideCharacter;

        MACRO_FUNCTION_RESOLVER(int (WideCharMultiByteState::*)(LPSTR, LPWSTR, int), false,
            Address::SHC_3BB0A8C1_0x0046B110, &WideCharMultiByteState::wideCharToMultiByteWithSize)
        wideCharToMultiByteWithSize;

        MACRO_FUNCTION_RESOLVER(int (WideCharMultiByteState::*)(LPWSTR, LPCSTR, int), false,
            Address::SHC_3BB0A8C1_0x0046B140, &WideCharMultiByteState::multiByteToWideCharWithSize)
        multiByteToWideCharWithSize;

        MACRO_FUNCTION_RESOLVER(char (WideCharMultiByteState::*)(WCHAR), false, Address::SHC_3BB0A8C1_0x0046B170,
            &WideCharMultiByteState::singleWideCharToMultiByte)
        singleWideCharToMultiByte;

        MACRO_FUNCTION_RESOLVER(WCHAR (WideCharMultiByteState::*)(char), false, Address::SHC_3BB0A8C1_0x0046B1B0,
            &WideCharMultiByteState::singleMultiByteToWideChar)
        singleMultiByteToWideChar;

    } // namespace WideCharMultiByteState_Func
} // namespace Util
} // namespace OpenSHC
