
#pragma once

#include "util/interfacing/GlobalReference.h"
#include "util/interfacing/MemberFunctionPointerGenerator.h"

namespace Ghidra {
  typedef void* pointer;
	typedef void* pointer32;
	typedef unsigned char   undefined;

	// typedef unsigned char    bool;
	typedef unsigned char    byte;
	typedef unsigned int    dword;
	typedef unsigned long long    GUID;
	typedef pointer32 ImageBaseOffset32;

	typedef long long    longlong;
	typedef unsigned long long    qword;
	typedef unsigned char    uchar;
	typedef unsigned int    uint;
	typedef unsigned long long    uint16;
	typedef unsigned long    ulong;
	typedef unsigned long long    ulonglong;
	typedef unsigned char    undefined1;
	typedef unsigned short    undefined2;
	typedef unsigned int    undefined3;
	typedef unsigned int    undefined4;
	typedef unsigned long long    undefined6;
	typedef unsigned long long    undefined8;
	typedef unsigned short    ushort;
	// typedef short    wchar_t;
	typedef unsigned short    word;
}

using namespace Ghidra;
