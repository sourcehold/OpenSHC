/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/OS.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "crtdefs.h"
#include "fcntl.h"
#include "guiddef.h"
#include "mbstring.h"
#include "stdio.h"
#include "sys/stat.h"
#include "time.h"
#include "vadefs.h"
namespace OpenSHC {
namespace OS {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    int* __stdcall basic_ofstream_write(void* param_1, uint param_2);

    BOOLEnum __cdecl isEqualGUID(GUID* param_1, GUID* param_2);

    tm* __cdecl _localtime(time_t* _Time);

    __time64_t __cdecl __time64(__time64_t* _Time);

    void* __cdecl _memset(void* _Dst, int _Val, size_t _Size);

    int __cdecl _sprintf(char* _Dest, char* _Format, ...);

    int __cdecl __stricmp(char* _Str1, char* _Str2);

    int __cdecl _atexit(void* param_1);

    void __cdecl _free_base(void* _Memory);

    int __cdecl __tolower(int _C);

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

    void __cdecl _free_cpp(void* _Memory);

    int __cdecl _ucrt_close(int fileDescriptor);

    int __cdecl _ucrt_read(int fileDescriptor, void* destination, size_t size);

    int __cdecl _ucrt_open(char* _Filename, int _OpenFlag, int _PMode);

    int __cdecl _rand();

    char* __cdecl __strlwr(char* string);

    undefined4 __cdecl _ucrt_write(int fileDescriptor, void* src, uint size);

    void* __cdecl _memcpy(void* _Dst, void* _Src, size_t _Size);

    int __cdecl __toupper(int _C);

    int __cdecl _ucrt_lseek(int fileDescriptor, long lDistanceToMove, DWORD moveMethod);

    int __cdecl __strnicmp(char* _Str1, char* _Str2, size_t _MaxCount);

    void __cdecl _exit(int _Code);

} // namespace OS
} // namespace OpenSHC
