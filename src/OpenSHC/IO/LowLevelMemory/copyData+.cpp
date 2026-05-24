#include "OpenSHC/IO/LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // NOTE: The calls to the copyData... functions are optimized, which means the compiler knew the content of these
    //   functions. The most likely thing is, that these functions shared a file. It does therefore only work if the
    //   resolvers are active.

    // FUNCTION: STRONGHOLDCRUSADER 0x00471830
    void LowLevelMemory::copyData(size_t size, void* src, void* destination)
    {
        this->size = size;
        this->src = src;
        this->destination = destination;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData0x100, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData0x010, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::copyData0x001, this)();
    }

    // NOTE: Heavy use of assembly.
    //   In the original code, these functions have a strange structure, using a simple loop jmp and writing the values
    //   to the stack before moving them into a register again. /O2 would normally optimize the prolog and epilog code
    //   to not use the stack and use a more optimized loop. Regardless what the original reason was, no other way was
    //   found so far aside of using assembly, which provokes the strange "store in stack then load" pattern.
    //
    //   Since these are low level support functions anyway, I would consider this good enough. They can be visited if
    //   anything else is done to be rejudged.

    // FUNCTION: STRONGHOLDCRUSADER 0x0046ABA0
    void LowLevelMemory::copyData0x100()
    {
        unsigned int* localDest = (unsigned int*)this->destination;
        unsigned int* localSrc = (unsigned int*)this->src;
        size_t localSize = this->size;

        __asm
        {
            mov edi, localDest
            mov esi, localSrc
            mov ebx, localSize
        
         loop_start:
            cmp ebx, 0x100
            jl loop_end
        
            mov eax, dword ptr [esi + 0x00]
            mov dword ptr [edi + 0x00], eax
            mov eax, dword ptr [esi + 0x04]
            mov dword ptr [edi + 0x04], eax
            mov eax, dword ptr [esi + 0x08]
            mov dword ptr [edi + 0x08], eax
            mov eax, dword ptr [esi + 0x0c]
            mov dword ptr [edi + 0x0c], eax
            mov eax, dword ptr [esi + 0x10]
            mov dword ptr [edi + 0x10], eax
            mov eax, dword ptr [esi + 0x14]
            mov dword ptr [edi + 0x14], eax
            mov eax, dword ptr [esi + 0x18]
            mov dword ptr [edi + 0x18], eax
            mov eax, dword ptr [esi + 0x1c]
            mov dword ptr [edi + 0x1c], eax
            mov eax, dword ptr [esi + 0x20]
            mov dword ptr [edi + 0x20], eax
            mov eax, dword ptr [esi + 0x24]
            mov dword ptr [edi + 0x24], eax
            mov eax, dword ptr [esi + 0x28]
            mov dword ptr [edi + 0x28], eax
            mov eax, dword ptr [esi + 0x2c]
            mov dword ptr [edi + 0x2c], eax
            mov eax, dword ptr [esi + 0x30]
            mov dword ptr [edi + 0x30], eax
            mov eax, dword ptr [esi + 0x34]
            mov dword ptr [edi + 0x34], eax
            mov eax, dword ptr [esi + 0x38]
            mov dword ptr [edi + 0x38], eax
            mov eax, dword ptr [esi + 0x3c]
            mov dword ptr [edi + 0x3c], eax
            mov eax, dword ptr [esi + 0x40]
            mov dword ptr [edi + 0x40], eax
            mov eax, dword ptr [esi + 0x44]
            mov dword ptr [edi + 0x44], eax
            mov eax, dword ptr [esi + 0x48]
            mov dword ptr [edi + 0x48], eax
            mov eax, dword ptr [esi + 0x4c]
            mov dword ptr [edi + 0x4c], eax
            mov eax, dword ptr [esi + 0x50]
            mov dword ptr [edi + 0x50], eax
            mov eax, dword ptr [esi + 0x54]
            mov dword ptr [edi + 0x54], eax
            mov eax, dword ptr [esi + 0x58]
            mov dword ptr [edi + 0x58], eax
            mov eax, dword ptr [esi + 0x5c]
            mov dword ptr [edi + 0x5c], eax
            mov eax, dword ptr [esi + 0x60]
            mov dword ptr [edi + 0x60], eax
            mov eax, dword ptr [esi + 0x64]
            mov dword ptr [edi + 0x64], eax
            mov eax, dword ptr [esi + 0x68]
            mov dword ptr [edi + 0x68], eax
            mov eax, dword ptr [esi + 0x6c]
            mov dword ptr [edi + 0x6c], eax
            mov eax, dword ptr [esi + 0x70]
            mov dword ptr [edi + 0x70], eax
            mov eax, dword ptr [esi + 0x74]
            mov dword ptr [edi + 0x74], eax
            mov eax, dword ptr [esi + 0x78]
            mov dword ptr [edi + 0x78], eax
            mov eax, dword ptr [esi + 0x7c]
            mov dword ptr [edi + 0x7c], eax
            mov eax, dword ptr [esi + 0x80]
            mov dword ptr [edi + 0x80], eax
            mov eax, dword ptr [esi + 0x84]
            mov dword ptr [edi + 0x84], eax
            mov eax, dword ptr [esi + 0x88]
            mov dword ptr [edi + 0x88], eax
            mov eax, dword ptr [esi + 0x8c]
            mov dword ptr [edi + 0x8c], eax
            mov eax, dword ptr [esi + 0x90]
            mov dword ptr [edi + 0x90], eax
            mov eax, dword ptr [esi + 0x94]
            mov dword ptr [edi + 0x94], eax
            mov eax, dword ptr [esi + 0x98]
            mov dword ptr [edi + 0x98], eax
            mov eax, dword ptr [esi + 0x9c]
            mov dword ptr [edi + 0x9c], eax
            mov eax, dword ptr [esi + 0xa0]
            mov dword ptr [edi + 0xa0], eax
            mov eax, dword ptr [esi + 0xa4]
            mov dword ptr [edi + 0xa4], eax
            mov eax, dword ptr [esi + 0xa8]
            mov dword ptr [edi + 0xa8], eax
            mov eax, dword ptr [esi + 0xac]
            mov dword ptr [edi + 0xac], eax
            mov eax, dword ptr [esi + 0xb0]
            mov dword ptr [edi + 0xb0], eax
            mov eax, dword ptr [esi + 0xb4]
            mov dword ptr [edi + 0xb4], eax
            mov eax, dword ptr [esi + 0xb8]
            mov dword ptr [edi + 0xb8], eax
            mov eax, dword ptr [esi + 0xbc]
            mov dword ptr [edi + 0xbc], eax
            mov eax, dword ptr [esi + 0xc0]
            mov dword ptr [edi + 0xc0], eax
            mov eax, dword ptr [esi + 0xc4]
            mov dword ptr [edi + 0xc4], eax
            mov eax, dword ptr [esi + 0xc8]
            mov dword ptr [edi + 0xc8], eax
            mov eax, dword ptr [esi + 0xcc]
            mov dword ptr [edi + 0xcc], eax
            mov eax, dword ptr [esi + 0xd0]
            mov dword ptr [edi + 0xd0], eax
            mov eax, dword ptr [esi + 0xd4]
            mov dword ptr [edi + 0xd4], eax
            mov eax, dword ptr [esi + 0xd8]
            mov dword ptr [edi + 0xd8], eax
            mov eax, dword ptr [esi + 0xdc]
            mov dword ptr [edi + 0xdc], eax
            mov eax, dword ptr [esi + 0xe0]
            mov dword ptr [edi + 0xe0], eax
            mov eax, dword ptr [esi + 0xe4]
            mov dword ptr [edi + 0xe4], eax
            mov eax, dword ptr [esi + 0xe8]
            mov dword ptr [edi + 0xe8], eax
            mov eax, dword ptr [esi + 0xec]
            mov dword ptr [edi + 0xec], eax
            mov eax, dword ptr [esi + 0xf0]
            mov dword ptr [edi + 0xf0], eax
            mov eax, dword ptr [esi + 0xf4]
            mov dword ptr [edi + 0xf4], eax
            mov eax, dword ptr [esi + 0xf8]
            mov dword ptr [edi + 0xf8], eax
            mov eax, dword ptr [esi + 0xfc]
            mov dword ptr [edi + 0xfc], eax
        
            sub ebx, 0x100
            add esi, 0x100
            add edi, 0x100
        
            jmp loop_start
         loop_end:
            mov localDest, edi
            mov localSrc, esi
            mov localSize, ebx
        }

        this->destination = (void*)localDest;
        this->src = (void*)localSrc;
        this->size = localSize;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AB30
    void LowLevelMemory::copyData0x010()
    {
        unsigned int* localDest = (unsigned int*)this->destination;
        unsigned int* localSrc = (unsigned int*)this->src;
        size_t localSize = this->size;

        __asm
        {
            mov edi, localDest
            mov esi, localSrc
            mov ebx, localSize
        
         loop_start:
            cmp ebx, 0x10
            jl loop_end
        
            mov eax, dword ptr [esi + 0x00]
            mov dword ptr [edi + 0x00], eax
            mov eax, dword ptr [esi + 0x04]
            mov dword ptr [edi + 0x04], eax
            mov eax, dword ptr [esi + 0x08]
            mov dword ptr [edi + 0x08], eax
            mov eax, dword ptr [esi + 0x0c]
            mov dword ptr [edi + 0x0c], eax
        
            sub ebx, 0x10
            add esi, 0x10
            add edi, 0x10
        
            jmp loop_start
         loop_end:
            mov localDest, edi
            mov localSrc, esi
            mov localSize, ebx
        }

        this->destination = (void*)localDest;
        this->src = (void*)localSrc;
        this->size = localSize;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AAF0
    void LowLevelMemory::copyData0x001()
    {
        unsigned char* localDest = (unsigned char*)this->destination;
        unsigned char* localSrc = (unsigned char*)this->src;
        size_t localSize = this->size;

        __asm
        {
            mov edi, localDest
            mov esi, localSrc
            mov ebx, localSize
        
         loop_start:
            cmp ebx, 0
            jle loop_end
        
            mov al, [esi]
            mov [edi], al
        
            sub ebx, 1
            add esi, 1
            add edi, 1
        
            jmp loop_start
         loop_end:
        }
    }

}
}
