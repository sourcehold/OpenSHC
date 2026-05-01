/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/Helpers/OPENFILENAMEA_Truncated.hpp'
*/

#pragma once

#include "WinDef.h"
#include "commdlg.h"
#include "winnt.h"

namespace OpenSHC {
namespace IO {
    namespace Helpers {

#pragma pack(push, 1)
        // SIZE: 0x0000004C
        typedef struct OPENFILENAMEA_Truncated {

            DWORD lStructSize; // 0x00000000 length: 4
            HWND hwndOwner; // 0x00000004 length: 4
            HINSTANCE hInstance; // 0x00000008 length: 4
            LPCSTR lpstrFilter; // 0x0000000C length: 4
            LPSTR lpstrCustomFilter; // 0x00000010 length: 4
            DWORD nMaxCustFilter; // 0x00000014 length: 4
            DWORD nFilterIndex; // 0x00000018 length: 4
            LPSTR lpstrFile; // 0x0000001C length: 4
            DWORD nMaxFile; // 0x00000020 length: 4
            LPSTR lpstrFileTitle; // 0x00000024 length: 4
            DWORD nMaxFileTitle; // 0x00000028 length: 4
            LPCSTR lpstrInitialDir; // 0x0000002C length: 4
            LPCSTR lpstrTitle; // 0x00000030 length: 4
            DWORD Flags; // 0x00000034 length: 4
            WORD nFileOffset; // 0x00000038 length: 2
            WORD nFileExtension; // 0x0000003A length: 2
            LPCSTR lpstrDefExt; // 0x0000003C length: 4
            LPARAM lCustData; // 0x00000040 length: 4
            LPOFNHOOKPROC lpfnHook; // 0x00000044 length: 4
            LPCSTR lpTemplateName; // 0x00000048 length: 4

        } OPENFILENAMEA_Truncated;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(OPENFILENAMEA_Truncated) == 76, OPENFILENAMEA_Truncated);
    } // namespace Helpers
} // namespace IO
} // namespace OpenSHC
