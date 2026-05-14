// disable deprecation warnings, since we use the old calls on purpose
#pragma warning(disable : 4996)

#include "OpenSHC/OS.hpp"

#include "float.h"
#include "io.h"

// NOTE: Activating them in DLL mode currently results in heap corruption

namespace OpenSHC {
namespace OS {

    // STUB: STRONGHOLDCRUSADER 0x0047C5D0
    BOOLEnum isEqualGUID(GUID* param_1, GUID* param_2)
    {
        return static_cast<BOOLEnum>(IsEqualGUID(*param_1, *param_2));
    }

    // Very likely just default function call, using time64_t and localtime64 behind
    // STUB: STRONGHOLDCRUSADER 0x0057F5FE
    tm* _localtime(time_t* _Time) { return localtime(_Time); }

    // STUB: STRONGHOLDCRUSADER 0x0057F622
    __time64_t __time64(__time64_t* _Time) { return _time64(_Time); }

    // STUB: STRONGHOLDCRUSADER 0x0057F660
    void* _memset(void* _Dst, int _Val, size_t _Size) { return memset(_Dst, _Val, _Size); }

    // STUB: STRONGHOLDCRUSADER 0x0057F6DA
    int _sprintf(char* _Dest, char* _Format, ...)
    {
        // needed for proxy
        va_list args;
        va_start(args, _Format);
        int result = vsprintf(_Dest, _Format, args);
        va_end(args);
        return result;
    }

    // STUB: STRONGHOLDCRUSADER 0x0057F8EE
    int __stricmp(char* _Str1, char* _Str2) { return _stricmp(_Str1, _Str2); }

    // STUB: STRONGHOLDCRUSADER 0x0057FA62
    int _atexit(void* param_1) { return atexit(reinterpret_cast<void(__cdecl*)()>(param_1)); }

    // This seems to be the games main free function
    // STUB: STRONGHOLDCRUSADER 0x0057FA74
    void __cdecl _free_base(void* _Memory) { free(_Memory); }

    // STUB: STRONGHOLDCRUSADER 0x0057FC19
    int __cdecl __tolower(int _C) { return tolower(_C); };

    // STUB: STRONGHOLDCRUSADER 0x0057FCB2
    int _fclose(FILE* _File) { return fclose(_File); }

    // STUB: STRONGHOLDCRUSADER 0x0057FFCA
    void _fread(void* dstBuffer, size_t elSize, size_t count, FILE* file) { fread(dstBuffer, elSize, count, file); }

    // STUB: STRONGHOLDCRUSADER 0x00580034
    void* _malloc(size_t _Size) { return malloc(_Size); }

    // STUB: STRONGHOLDCRUSADER 0x0058028F
    long _ftell(FILE* _File) { return ftell(_File); }

    // STUB: STRONGHOLDCRUSADER 0x00580384
    int __cdecl _fseek(FILE* _File, long _Offset, DWORD _Origin) { return fseek(_File, _Offset, _Origin); }

    // STUB: STRONGHOLDCRUSADER 0x005804CD
    FILE* _fopen(char* _Filename, char* _Mode) { return fopen(_Filename, _Mode); }

    // STUB: STRONGHOLDCRUSADER 0x00580577
    int __vswprintf(wchar_t* _Dest, wchar_t* _Format, va_list _Args) { return _vswprintf(_Dest, _Format, _Args); }

    // STUB: STRONGHOLDCRUSADER 0x00580735
    wint_t _fgetwc(FILE* _File) { return fgetwc(_File); }

    // STUB: STRONGHOLDCRUSADER 0x0058099B
    size_t _fwrite(void* _Str, size_t _Size, size_t _Count, FILE* _File) { return fwrite(_Str, _Size, _Count, _File); }

    // STUB: STRONGHOLDCRUSADER 0x00580A1D
    wchar_t* _wcsncpy(wchar_t* _Dest, wchar_t* _Source, size_t _Count) { return wcsncpy(_Dest, _Source, _Count); }

    // STUB: STRONGHOLDCRUSADER 0x00580B69
    int __wcsicmp(wchar_t* _Str1, wchar_t* _Str2) { return _wcsicmp(_Str1, _Str2); }

    // Only jumps to _free in game version
    // STUB: STRONGHOLDCRUSADER 0x00580DC1
    void __cdecl _free(void* _Memory) { free(_Memory); }

    // STUB: STRONGHOLDCRUSADER 0x00580DC6
    errno_t _memcpy_s(void* _Dst, rsize_t _DstSize, void* _Src, rsize_t _MaxCount)
    {
        return memcpy_s(_Dst, _DstSize, _Src, _MaxCount);
    }

    // Only jumps to _free
    // STUB: STRONGHOLDCRUSADER 0x00580E9C
    void __cdecl _free_cpp(void* _Memory) { free(_Memory); }

    // STUB: STRONGHOLDCRUSADER 0x00580F38
    int _ucrt_close(int fileDescriptor) { return _close(fileDescriptor); }

    // STUB: STRONGHOLDCRUSADER 0x005815C6
    int _ucrt_read(int fileDescriptor, void* destination, size_t size)
    {
        return _read(fileDescriptor, destination, size);
    }

    // STUB: STRONGHOLDCRUSADER 0x005816C3
    int _ucrt_open(char* _Filename, OpenFlagInt _OpenFlag, int _PMode) { return _open(_Filename, _OpenFlag, _PMode); }

    // STUB: STRONGHOLDCRUSADER 0x005816FB
    int _rand() { return rand(); }

    // STUB: STRONGHOLDCRUSADER 0x005818EB
    char* __strlwr(char* string) { return _strlwr(string); }

    // STUB: STRONGHOLDCRUSADER 0x00581F6F
    undefined4 _ucrt_write(int fileDescriptor, void* src, uint size) { return _write(fileDescriptor, src, size); }

    // STUB: STRONGHOLDCRUSADER 0x00582050
    void* _memcpy(void* _Dst, void* _Src, size_t _Size) { return memcpy(_Dst, _Src, _Size); }

    // STUB: STRONGHOLDCRUSADER 0x005824CD
    int __cdecl __toupper(int _C) { return toupper(_C); }

    // STUB: STRONGHOLDCRUSADER 0x0058277E
    int _ucrt_lseek(int fileDescriptor, long lDistanceToMove, DWORD moveMethod)
    {
        return _lseek(fileDescriptor, lDistanceToMove, moveMethod);
    }

    // STUB: STRONGHOLDCRUSADER 0x005835BB
    int __strnicmp(char* _Str1, char* _Str2, size_t _MaxCount) { return _strnicmp(_Str1, _Str2, _MaxCount); }

    // STUB: STRONGHOLDCRUSADER 0x00583D55
    void _exit(int _Code) { exit(_Code); }

}
}
