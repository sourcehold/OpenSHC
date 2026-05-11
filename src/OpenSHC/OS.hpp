/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/OS.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/OpenFlagInt.hpp"
#include "crtdefs.h"
#include "fileapi.h"
#include "guiddef.h"
#include "mbstring.h"
#include "time.h"
#include "vadefs.h"
namespace OpenSHC {
namespace OS {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::WindowsHelper::Enums::OpenFlagInt;

    int* __stdcall basic_ofstream_write(void* param_1, uint param_2);

    BOOLEnum __cdecl isEqualGUID(GUID* param_1, GUID* param_2);

    int __cdecl __isnan(double _X);

    int __cdecl __ftol2(float10 param);

    void __cdecl math_atan_FUN_0057ee10(float10 param_1);

    float10 __cdecl math_atan_FUN_0057ee68(float10 floatIn, uint eaxIn, int param_3, int param_4);

    float10 __cdecl math_sqrt_FUN_0057eef0(float10 param_1);

    float10 __cdecl math_sqrt_FUN_0057ef0d(int param_1, uint param_2, float10 param_3);

    void __cdecl math_tan_1_FUN_0057eff0(float10 param_1);

    float10 __cdecl math_FUN_0057f048(int param_1, int param_2);

    float10 __fastcall math_cos(float10 param_1);

    float10 __fastcall math_sin(float10 param_1);

    tm* __cdecl __localtime64(__time32_t* _Time);

    __time64_t __cdecl __time64(__time64_t* _Time);

    void* __cdecl _memset(void* _Dst, int _Val, size_t _Size);

    int __cdecl _sprintf(char* _Dest, char* _Format);

    int __cdecl __stricmp(char* _Str1, char* _Str2);

    int __cdecl _atexit(void* param_1);

    void __cdecl _free(void* _Memory);

    int __cdecl _tolower(int _C);

    int __cdecl _fclose(FILE* _File);

    void __cdecl _fread(void* dstBuffer, size_t elSize, size_t count, FILE* file);

    void* __cdecl _malloc(size_t _Size);

    long __cdecl _ftell(FILE* _File);

    int __cdecl _fseek(FILE* _File, long _Offset, DWORD _Origin);

    FILE* __cdecl _fopen(char* _Filename, char* _Mode);

    int __cdecl __vswprintf(wchar_t* _Dest, wchar_t* _Format, va_list _Args);

    wint_t __cdecl _fgetwc(FILE* _File);

    size_t __cdecl _fwrite(void* _Str, size_t _Size, size_t _Count, FILE* _File);

    wchar_t* __cdecl _wcsncpy(wchar_t* _Dest, wchar_t* _Source, size_t _Count);

    int __cdecl __wcsicmp(wchar_t* _Str1, wchar_t* _Str2);

    void __cdecl _free(void* _Memory);

    errno_t __cdecl _memcpy_s(void* _Dst, rsize_t _DstSize, void* _Src, rsize_t _MaxCount);

    void __cdecl _free(void* _Memory);

    int __cdecl _ucrt_close(int fileDescriptor);

    int __cdecl _ucrt_read(int fileDescriptor, void* destination, size_t size);

    int __cdecl _ucrt_open(char* _Filename, OpenFlagInt _OpenFlag, int _PMode);

    int __cdecl _rand();

    char* __cdecl __strlwr(char* string);

    undefined4 __cdecl _ucrt_write(int fileDescriptor, void* src, uint size);

    void* __cdecl _memcpy(void* _Dst, void* _Src, size_t _Size);

    int __cdecl _toupper(int _C);

    int __cdecl _ucrt_lseek(int fileDescriptor, long lDistanceToMove, DWORD moveMethod);

    longlong __stdcall __alldiv(
        long dividend_lowOrder, long dividend_highOrder, long divisor_lowOrder, long divisor_highOrder);

    ulonglong __stdcall __allmul(
        ulong factor1_lowOrder, ulong factor1_highOrder, ulong factor2_lowOrder, ulong factor2_highOrder);

    undefined4 __stdcall __alloca_probe();

    int __cdecl __strnicmp(char* _Str1, char* _Str2, size_t _MaxCount);

    void __cdecl _exit(int _Code);

    uint __cdecl math_FUN_00588628(undefined4 param_1, uint param_2);

    float10 __fastcall math_FUN_0058864b(float10 param_1, char* param_2, int param_3, undefined4 param_4,
        undefined4 param_5, undefined4 param_6, undefined4 param_7);

    float10 __fastcall math_FUN_005887ae();

} // namespace OS
} // namespace OpenSHC
