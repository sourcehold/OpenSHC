// disable deprecation warnings, since we use the old calls on purpose
#pragma warning(disable : 4996)

#include "OpenSHC/OS.hpp"

#include "float.h"
#include "io.h"

// NOTE: Activating them in DLL mode currently results in heap corruption

// this one is hard to pin down, maybe an STL this-function, or a special buffer?
// STUB: STRONGHOLDCRUSADER 0x004791B0
// int* __stdcall basic_ofstream_write(void* param_1, uint param_2) {TODO}

// STUB: STRONGHOLDCRUSADER 0x0047C5D0
OpenSHC::OS::BOOLEnum OpenSHC::OS::isEqualGUID(GUID* param_1, GUID* param_2)
{
    return static_cast<BOOLEnum>(IsEqualGUID(*param_1, *param_2));
}

// STUB: STRONGHOLDCRUSADER 0x0057ECF1
int OpenSHC::OS::__isnan(double _X) { return _isnan(_X); }

// STUB: STRONGHOLDCRUSADER 0x0057ED20
// Used implicitly when converting floating-point → integer on x86
// int __cdecl __ftol2(float10 param);

// Used implicitly by CRT math pipeline (atan)
// STUB: STRONGHOLDCRUSADER 0x0057EE10
// void __cdecl math_atan_FUN_0057ee10(float10 param_1);

// Used implicitly by CRT math pipeline (atan variant)
// STUB: STRONGHOLDCRUSADER 0x0057EE68
// float10 __cdecl math_atan_FUN_0057ee68(float10 floatIn, uint eaxIn, int param_3, int param_4);

// Used implicitly by CRT math pipeline (sqrt)
// STUB: STRONGHOLDCRUSADER 0x0057EEF0
// float10 __cdecl math_sqrt_FUN_0057eef0(float10 param_1);

// Used implicitly by CRT math pipeline (sqrt variant)
// STUB: STRONGHOLDCRUSADER 0x0057EF0D
// float10 __cdecl math_sqrt_FUN_0057ef0d(int param_1, uint param_2, float10 param_3);

// Used implicitly by CRT math pipeline (tan)
// STUB: STRONGHOLDCRUSADER 0x0057EFF0
// void __cdecl math_tan_1_FUN_0057eff0(float10 param_1);

// Used implicitly by CRT math ?
// STUB: STRONGHOLDCRUSADER 0x0057F048
// float10 __cdecl math_FUN_0057f048(int param_1, int param_2);

// Possibly compiler-generated or CRT math thunk for cosine (sin/cos pipeline variant)
// STUB: STRONGHOLDCRUSADER 0x0057F120
// float10 __fastcall math_cos(float10 param_1);

// Possibly compiler-generated or CRT math thunk for sine (sin/cos pipeline variant)
// STUB: STRONGHOLDCRUSADER 0x0057F250
// float10 __fastcall math_sin(float10 param_1);

// Very likely just default function call, using time64_t and localtime64 behind
// STUB: STRONGHOLDCRUSADER 0x0057F5FE
tm* OpenSHC::OS::_localtime(time_t* _Time) { return localtime(_Time); }

// STUB: STRONGHOLDCRUSADER 0x0057F622
__time64_t OpenSHC::OS::__time64(__time64_t* _Time) { return _time64(_Time); }

// STUB: STRONGHOLDCRUSADER 0x0057F660
void* OpenSHC::OS::_memset(void* _Dst, int _Val, size_t _Size) { return memset(_Dst, _Val, _Size); }

// MACRO_FUNCTION_RESOLVER does not support variadic functions
// STUB: STRONGHOLDCRUSADER 0x0057F6DA
int OpenSHC::OS::_sprintf(char* _Dest, char* _Format, ...)
{
    // needed for proxy
    va_list args;
    va_start(args, _Format);
    int result = vsprintf(_Dest, _Format, args);
    va_end(args);
    return result;
}

// STUB: STRONGHOLDCRUSADER 0x0057F8EE
int OpenSHC::OS::__stricmp(char* _Str1, char* _Str2) { return _stricmp(_Str1, _Str2); }

// STUB: STRONGHOLDCRUSADER 0x0057FA62
int OpenSHC::OS::_atexit(void* param_1) { return atexit(reinterpret_cast<void(__cdecl*)()>(param_1)); }

// STUB: STRONGHOLDCRUSADER 0x0057FA74
// This seems to be the games main free function
void __cdecl OpenSHC::OS::_free(void* _Memory) { free(_Memory); }

// Used implicitly in character conversion pipeline (_tolower). Save if global locale never set.
// STUB: STRONGHOLDCRUSADER 0x0057FC19
// int __cdecl _tolower(int _C);

// STUB: STRONGHOLDCRUSADER 0x0057FCB2
int OpenSHC::OS::_fclose(FILE* _File) { return fclose(_File); }

// STUB: STRONGHOLDCRUSADER 0x0057FFCA
void OpenSHC::OS::_fread(void* dstBuffer, size_t elSize, size_t count, FILE* file)
{
    fread(dstBuffer, elSize, count, file);
}

// STUB: STRONGHOLDCRUSADER 0x00580034
void* OpenSHC::OS::_malloc(size_t _Size) { return malloc(_Size); }

// STUB: STRONGHOLDCRUSADER 0x0058028F
long OpenSHC::OS::_ftell(FILE* _File) { return ftell(_File); }

// STUB: STRONGHOLDCRUSADER 0x00580384
int __cdecl OpenSHC::OS::_fseek(FILE* _File, long _Offset, OpenSHC::OS::FilePtrMoveMethodInt _Origin)
{
    return fseek(_File, _Offset, _Origin);
}

// STUB: STRONGHOLDCRUSADER 0x005804CD
FILE* OpenSHC::OS::_fopen(char* _Filename, char* _Mode) { return fopen(_Filename, _Mode); }

// STUB: STRONGHOLDCRUSADER 0x00580577
int OpenSHC::OS::__vswprintf(wchar_t* _Dest, wchar_t* _Format, va_list _Args)
{
    return _vswprintf(_Dest, _Format, _Args);
}

// STUB: STRONGHOLDCRUSADER 0x00580735
wint_t OpenSHC::OS::_fgetwc(FILE* _File) { return fgetwc(_File); }

// STUB: STRONGHOLDCRUSADER 0x0058099B
size_t OpenSHC::OS::_fwrite(void* _Str, size_t _Size, size_t _Count, FILE* _File)
{
    return fwrite(_Str, _Size, _Count, _File);
}

// STUB: STRONGHOLDCRUSADER 0x00580A1D
wchar_t* OpenSHC::OS::_wcsncpy(wchar_t* _Dest, wchar_t* _Source, size_t _Count)
{
    return wcsncpy(_Dest, _Source, _Count);
}

// STUB: STRONGHOLDCRUSADER 0x00580B69
int OpenSHC::OS::__wcsicmp(wchar_t* _Str1, wchar_t* _Str2) { return _wcsicmp(_Str1, _Str2); }

// Only jumps to _free
// STUB: STRONGHOLDCRUSADER 0x00580DC1
// void __cdecl OpenSHC::OS::_free(void* _Memory) { free(_Memory); }

// STUB: STRONGHOLDCRUSADER 0x00580DC6
errno_t OpenSHC::OS::_memcpy_s(void* _Dst, rsize_t _DstSize, void* _Src, rsize_t _MaxCount)
{
    return memcpy_s(_Dst, _DstSize, _Src, _MaxCount);
}

// Only jumps to _free
// STUB: STRONGHOLDCRUSADER 0x00580E9C
// void __cdecl OpenSHC::OS::_free(void* _Memory) { free(_Memory); }

// STUB: STRONGHOLDCRUSADER 0x00580F38
int OpenSHC::OS::_ucrt_close(int fileDescriptor) { return _close(fileDescriptor); }

// STUB: STRONGHOLDCRUSADER 0x005815C6
int OpenSHC::OS::_ucrt_read(int fileDescriptor, void* destination, size_t size)
{
    return _read(fileDescriptor, destination, size);
}

// STUB: STRONGHOLDCRUSADER 0x005816C3
int OpenSHC::OS::_ucrt_open(char* _Filename, OpenFlagInt _OpenFlag, int _PMode)
{
    return _open(_Filename, _OpenFlag, _PMode);
}

// STUB: STRONGHOLDCRUSADER 0x005816FB
int OpenSHC::OS::_rand() { return rand(); }

// STUB: STRONGHOLDCRUSADER 0x005818EB
char* OpenSHC::OS::__strlwr(char* string) { return _strlwr(string); }

// STUB: STRONGHOLDCRUSADER 0x00581F6F
undefined4 OpenSHC::OS::_ucrt_write(int fileDescriptor, void* src, uint size)
{
    return _write(fileDescriptor, src, size);
}

// STUB: STRONGHOLDCRUSADER 0x00582050
void* OpenSHC::OS::_memcpy(void* _Dst, void* _Src, size_t _Size) { return memcpy(_Dst, _Src, _Size); }

// Used implicitly in character conversion pipeline (_toupper) Save if global locale never set.
// STUB: STRONGHOLDCRUSADER 0x005824CD
// int __cdecl _toupper(int _C);

// STUB: STRONGHOLDCRUSADER 0x0058277E
int OpenSHC::OS::_ucrt_lseek(int fileDescriptor, long lDistanceToMove, FilePtrMoveMethodInt moveMethod)
{
    return _lseek(fileDescriptor, lDistanceToMove, moveMethod);
}

// Compiler-emitted ABI helper (__alldiv)
// STUB: STRONGHOLDCRUSADER 0x00582C30
// longlong __stdcall __alldiv(long, long, long, long);

// Compiler-emitted ABI helper (__allmul)
// STUB: STRONGHOLDCRUSADER 0x00582CE0
// ulonglong __stdcall __allmul(ulong, ulong, ulong, ulong);

// Compiler-emitted stack probe helper (__alloca_probe)
// STUB: STRONGHOLDCRUSADER 0x005834A0
// undefined4 __stdcall __alloca_probe();

// STUB: STRONGHOLDCRUSADER 0x005835BB
int OpenSHC::OS::__strnicmp(char* _Str1, char* _Str2, size_t _MaxCount) { return _strnicmp(_Str1, _Str2, _MaxCount); }

// STUB: STRONGHOLDCRUSADER 0x00583D55
void OpenSHC::OS::_exit(int _Code) { exit(_Code); }

// Unknown math function?
// STUB: STRONGHOLDCRUSADER 0x00588628
// uint OpenSHC::OS::math_FUN_00588628(undefined4 param_1, uint param_2) { TODO };

// Likely some internal math call?
// STUB: STRONGHOLDCRUSADER 0x00588628
// float10 __fastcall OpenSHC::OS::math_FUN_0058864b(float10 param_1, char* param_2, int param_3, undefined4 param_4,
//     undefined4 param_5, undefined4 param_6, undefined4 param_7);

// Likely some internal math call?
// STUB: STRONGHOLDCRUSADER 0x00588628
// float10 __fastcall math_FUN_005887ae();
