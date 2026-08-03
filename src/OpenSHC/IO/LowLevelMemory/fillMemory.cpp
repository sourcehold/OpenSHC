#include "../LowLevelMemory.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471860
    void LowLevelMemory::fillMemory_IntegerValue(size_t size, int value, void* destination)
    {
        this->size = size;
        this->value = value;
        this->destination = destination;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x004, this)();
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x00471890
    void LowLevelMemory::fillMemory_ShortValue(size_t size, unsigned short value, void* destination)
    {
        this->size = size;
        this->value = value * 0x00010001;
        this->destination = destination;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x002, this)();
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x004718c0
    void LowLevelMemory::fillMemory_ByteValue(size_t size, unsigned char value, void* destination)
    {
        this->size = size;
        this->value = value * 0x01010101;
        this->destination = destination;
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x100, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x010, this)();
        MACRO_CALL_MEMBER(LowLevelMemory_Func::fillMemory_setMemoryToValue_0x001, this)();
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A970
    void LowLevelMemory::fillMemory_setMemoryToValue_0x100()
    {
        unsigned int* localDest = (unsigned int*)this->destination;
        size_t localSize = this->size;
        int localValue = this->value;

        /*
            while (localSize >= 0x100) {
                // actually manually enrolled to 64 int assigns
                for (int i = 0; i < 64; i++) {
                    localDest[i] = localValue;
                }
                localSrc += 64;
                localDest += 64;
                localSize -= 0x100;
            }
        */

        __asm
        {
            mov edi, localDest
            mov ebx, localSize
            mov eax, localValue
        
        loop_start:
            cmp ebx, 0x100
            jl loop_end
        
            mov dword ptr [edi + 0x00], eax
            mov dword ptr [edi + 0x04], eax
            mov dword ptr [edi + 0x08], eax
            mov dword ptr [edi + 0x0c], eax
            mov dword ptr [edi + 0x10], eax
            mov dword ptr [edi + 0x14], eax
            mov dword ptr [edi + 0x18], eax
            mov dword ptr [edi + 0x1c], eax
            mov dword ptr [edi + 0x20], eax
            mov dword ptr [edi + 0x24], eax
            mov dword ptr [edi + 0x28], eax
            mov dword ptr [edi + 0x2c], eax
            mov dword ptr [edi + 0x30], eax
            mov dword ptr [edi + 0x34], eax
            mov dword ptr [edi + 0x38], eax
            mov dword ptr [edi + 0x3c], eax
            mov dword ptr [edi + 0x40], eax
            mov dword ptr [edi + 0x44], eax
            mov dword ptr [edi + 0x48], eax
            mov dword ptr [edi + 0x4c], eax
            mov dword ptr [edi + 0x50], eax
            mov dword ptr [edi + 0x54], eax
            mov dword ptr [edi + 0x58], eax
            mov dword ptr [edi + 0x5c], eax
            mov dword ptr [edi + 0x60], eax
            mov dword ptr [edi + 0x64], eax
            mov dword ptr [edi + 0x68], eax
            mov dword ptr [edi + 0x6c], eax
            mov dword ptr [edi + 0x70], eax
            mov dword ptr [edi + 0x74], eax
            mov dword ptr [edi + 0x78], eax
            mov dword ptr [edi + 0x7c], eax
            mov dword ptr [edi + 0x80], eax
            mov dword ptr [edi + 0x84], eax
            mov dword ptr [edi + 0x88], eax
            mov dword ptr [edi + 0x8c], eax
            mov dword ptr [edi + 0x90], eax
            mov dword ptr [edi + 0x94], eax
            mov dword ptr [edi + 0x98], eax
            mov dword ptr [edi + 0x9c], eax
            mov dword ptr [edi + 0xa0], eax
            mov dword ptr [edi + 0xa4], eax
            mov dword ptr [edi + 0xa8], eax
            mov dword ptr [edi + 0xac], eax
            mov dword ptr [edi + 0xb0], eax
            mov dword ptr [edi + 0xb4], eax
            mov dword ptr [edi + 0xb8], eax
            mov dword ptr [edi + 0xbc], eax
            mov dword ptr [edi + 0xc0], eax
            mov dword ptr [edi + 0xc4], eax
            mov dword ptr [edi + 0xc8], eax
            mov dword ptr [edi + 0xcc], eax
            mov dword ptr [edi + 0xd0], eax
            mov dword ptr [edi + 0xd4], eax
            mov dword ptr [edi + 0xd8], eax
            mov dword ptr [edi + 0xdc], eax
            mov dword ptr [edi + 0xe0], eax
            mov dword ptr [edi + 0xe4], eax
            mov dword ptr [edi + 0xe8], eax
            mov dword ptr [edi + 0xec], eax
            mov dword ptr [edi + 0xf0], eax
            mov dword ptr [edi + 0xf4], eax
            mov dword ptr [edi + 0xf8], eax
            mov dword ptr [edi + 0xfc], eax
        
            sub ebx, 0x100
            add edi, 0x100
        
            jmp loop_start
        loop_end:
            mov localDest, edi
            mov localSize, ebx
        }

        this->destination = (void*)localDest;
        this->size = localSize;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a910
    void LowLevelMemory::fillMemory_setMemoryToValue_0x010()
    {
        unsigned int* localDest = (unsigned int*)this->destination;
        size_t localSize = this->size;
        int localValue = this->value;

        /*
            while (localSize >= 0x10) {
                // actually manually enrolled to 4 int assigns
                for (int i = 0; i < 4; i++) {
                    localDest[i] = localValue;
                }
                localSrc += 4;
                localDest += 4;
                localSize -= 0x10;
            }
         */

        __asm
        {
            mov edi, localDest
            mov ebx, localSize
            mov eax, localValue
        
        loop_start:
            cmp ebx, 0x10
            jl loop_end
        
            mov dword ptr [edi + 0x00], eax
            mov dword ptr [edi + 0x04], eax
            mov dword ptr [edi + 0x08], eax
            mov dword ptr [edi + 0x0c], eax
        
            sub ebx, 0x10
            add edi, 0x10
        
            jmp loop_start
        loop_end:
            mov localDest, edi
            mov localSize, ebx
        }

        this->destination = (void*)localDest;
        this->size = localSize;
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a8d0
    void LowLevelMemory::fillMemory_setMemoryToValue_0x004()
    {
        unsigned int* localDest = (unsigned int*)this->destination;
        size_t localSize = this->size;
        int localValue = this->value;

        /*
            // assembly logic just uses localSize to count down and dest up
            for(size_t i = 0; i < localSize; ++i) {
                localDest[i] = localValue;
            }
        */

        __asm
        {
            mov edi, localDest
            mov ebx, localSize
            mov eax, localValue
        
        loop_start:
            cmp ebx, 0
            jle loop_end
        
            mov [edi], eax
        
            sub ebx, 4
            add edi, 4
        
            jmp loop_start
        loop_end:
        }
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a890
    void LowLevelMemory::fillMemory_setMemoryToValue_0x002()
    {
        unsigned short* localDest = (unsigned short*)this->destination;
        size_t localSize = this->size;
        int localValue = this->value;

        /*
            // assembly logic just uses localSize to count down and dest up
            for(size_t i = 0; i < localSize; ++i) {
                localDest[i] = localValue;
            }
        */

        __asm
        {
            mov edi, localDest
            mov ebx, localSize
            mov eax, localValue
        
        loop_start:
            cmp ebx, 0
            jle loop_end
        
            mov word ptr [edi], ax
        
            sub ebx, 2
            add edi, 2
        
            jmp loop_start
        loop_end:
        }
    }

    // FUNCTION: STRONGHOLDCRUSADER 0x0046a850
    void LowLevelMemory::fillMemory_setMemoryToValue_0x001()
    {
        unsigned short* localDest = (unsigned short*)this->destination;
        size_t localSize = this->size;
        int localValue = this->value;

        /*
            // assembly logic just uses localSize to count down and dest up
            for(size_t i = 0; i < localSize; ++i) {
                localDest[i] = localValue;
            }
        */

        __asm
        {
            mov edi, localDest
            mov ebx, localSize
            mov eax, localValue
        
        loop_start:
            cmp ebx, 0
            jle loop_end
        
            mov byte ptr [edi], al
        
            sub ebx, 1
            add edi, 1
        
            jmp loop_start
        loop_end:
        }
    }

}
}
