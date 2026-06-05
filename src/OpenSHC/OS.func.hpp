/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/OS.func.hpp'
*/

#pragma once

#include "OpenSHC/OS.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/OpenFlagInt.hpp"

#include "crtdefs.h"
#include "guiddef.h"
#include "mbstring.h"
#include "stdio.h"
#include "time.h"
#include "vadefs.h"
namespace OpenSHC {
namespace OS_Func {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::WindowsHelper::Enums::OpenFlagInt;

    MACRO_FUNCTION_RESOLVER(int*(__stdcall*)(void* param_1, uint param_2), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x004791B0, &OpenSHC::OS::basic_ofstream_write)
    basic_ofstream_write;

    MACRO_FUNCTION_RESOLVER(BOOLEnum(__cdecl*)(GUID* param_1, GUID* param_2), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0047C5D0, &OpenSHC::OS::isEqualGUID)
    isEqualGUID;

    MACRO_FUNCTION_RESOLVER(tm*(__cdecl*)(__time32_t * _Time), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0057F5FE,
        &OpenSHC::OS::__localtime64)
    __localtime64;

    MACRO_FUNCTION_RESOLVER(__time64_t(__cdecl*)(__time64_t* _Time), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0057F622, &OpenSHC::OS::__time64)
    __time64;

    MACRO_FUNCTION_RESOLVER(void*(__cdecl*)(void* _Dst, int _Val, size_t _Size), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0057F660, &OpenSHC::OS::_memset)
    _memset;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(char* _Dest, char* _Format), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0057F6DA, &OpenSHC::OS::_sprintf)
    _sprintf;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(char* _Str1, char* _Str2), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0057F8EE, &OpenSHC::OS::__stricmp)
    __stricmp;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(void* param_1), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0057FA62, &OpenSHC::OS::_atexit)
    _atexit;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(void* _Memory), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0057FA74, &OpenSHC::OS::_free_base)
    _free_base;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int _C), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0057FC19, &OpenSHC::OS::__tolower)
    __tolower;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(FILE* _File), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0057FCB2, &OpenSHC::OS::_fclose)
    _fclose;

    MACRO_FUNCTION_RESOLVER(void(__cdecl*)(void* dstBuffer, size_t elSize, size_t count, FILE* file), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0057FFCA, &OpenSHC::OS::_fread)
    _fread;

    MACRO_FUNCTION_RESOLVER(
        void*(__cdecl*)(size_t _Size), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00580034, &OpenSHC::OS::_malloc)
    _malloc;

    MACRO_FUNCTION_RESOLVER(
        long(__cdecl*)(FILE* _File), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0058028F, &OpenSHC::OS::_ftell)
    _ftell;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(FILE* _File, long _Offset, DWORD _Origin), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x00580384, &OpenSHC::OS::_fseek)
    _fseek;

    MACRO_FUNCTION_RESOLVER(FILE*(__cdecl*)(char* _Filename, char* _Mode), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x005804CD, &OpenSHC::OS::_fopen)
    _fopen;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(wchar_t* _Dest, wchar_t* _Format, va_list _Args), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x00580577, &OpenSHC::OS::__vswprintf)
    __vswprintf;

    MACRO_FUNCTION_RESOLVER(
        wint_t(__cdecl*)(FILE* _File), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00580735, &OpenSHC::OS::_fgetwc)
    _fgetwc;

    MACRO_FUNCTION_RESOLVER(size_t(__cdecl*)(void* _Str, size_t _Size, size_t _Count, FILE* _File), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x0058099B, &OpenSHC::OS::_fwrite)
    _fwrite;

    MACRO_FUNCTION_RESOLVER(wchar_t*(__cdecl*)(wchar_t * _Dest, wchar_t* _Source, size_t _Count), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x00580A1D, &OpenSHC::OS::_wcsncpy)
    _wcsncpy;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(wchar_t* _Str1, wchar_t* _Str2), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x00580B69, &OpenSHC::OS::__wcsicmp)
    __wcsicmp;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(void* _Memory), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00580DC1, &OpenSHC::OS::_free)
    _free;

    MACRO_FUNCTION_RESOLVER(errno_t(__cdecl*)(void* _Dst, rsize_t _DstSize, void* _Src, rsize_t _MaxCount),
        REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00580DC6, &OpenSHC::OS::_memcpy_s)
    _memcpy_s;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(void* _Memory), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00580E9C, &OpenSHC::OS::_free_cpp)
    _free_cpp;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int fileDescriptor), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00580F38,
        &OpenSHC::OS::_ucrt_close)
    _ucrt_close;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int fileDescriptor, void* destination, size_t size), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x005815C6, &OpenSHC::OS::_ucrt_read)
    _ucrt_read;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(char* _Filename, OpenFlagInt _OpenFlag, int _PMode), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x005816C3, &OpenSHC::OS::_ucrt_open)
    _ucrt_open;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x005816FB, &OpenSHC::OS::_rand)
    _rand;

    MACRO_FUNCTION_RESOLVER(
        char*(__cdecl*)(char* string), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x005818EB, &OpenSHC::OS::__strlwr)
    __strlwr;

    MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int fileDescriptor, void* src, uint size), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x00581F6F, &OpenSHC::OS::_ucrt_write)
    _ucrt_write;

    MACRO_FUNCTION_RESOLVER(void*(__cdecl*)(void* _Dst, void* _Src, size_t _Size), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x00582050, &OpenSHC::OS::_memcpy)
    _memcpy;

    MACRO_FUNCTION_RESOLVER(
        int(__cdecl*)(int _C), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x005824CD, &OpenSHC::OS::__toupper)
    __toupper;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int fileDescriptor, long lDistanceToMove, DWORD moveMethod),
        REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x0058277E, &OpenSHC::OS::_ucrt_lseek)
    _ucrt_lseek;

    MACRO_FUNCTION_RESOLVER(
        undefined4(__stdcall*)(), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x005834A0, &OpenSHC::OS::__alloca_probe)
    __alloca_probe;

    MACRO_FUNCTION_RESOLVER(int(__cdecl*)(char* _Str1, char* _Str2, size_t _MaxCount), REIMPLEMENTED_CRT,
        Address::SHC_3BB0A8C1_0x005835BB, &OpenSHC::OS::__strnicmp)
    __strnicmp;

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int _Code), REIMPLEMENTED_CRT, Address::SHC_3BB0A8C1_0x00583D55, &OpenSHC::OS::_exit)
    _exit;

} // namespace OS_Func
} // namespace OpenSHC
