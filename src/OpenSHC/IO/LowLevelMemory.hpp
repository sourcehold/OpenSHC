/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/LowLevelMemory.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "crtdefs.h"

namespace OpenSHC {
namespace IO {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000014
    class LowLevelMemory {
    public:
        int src; // 0x00000000 length: 4
        pointer* destination; // 0x00000004 length: 4
        pointer* size; // 0x00000008 length: 4
        int value; // 0x0000000C length: 4
        int field4_0x10; // 0x00000010 length: 4

    private:
        LowLevelMemory(LowLevelMemory const&);
        void operator=(LowLevelMemory const&);

        LowLevelMemory();
        ~LowLevelMemory();

    public:
        void moveLowerThreeBytesIntoParam2(undefined4* src, undefined3* dst);

        void setMemoryToValue0x001();

        void setMemoryToValue0x002();

        void setMemoryToValue0x004();

        void setMemoryToValue0x010();

        void setMemoryToValue0x100();

        void copyData0x001();

        void copyData0x010();

        void copyData0x100();

        void copyStringUntilFirstDot(char* param_1, char* param_2);

        void putFileNameAndAppendFileExtension(char* sourceName, char* dest, char* extension);

        BOOLEnum isLordNameCallable(char* playerLordNameUnk, char* callableLordName);

        void copyData(size_t size, void* src, void* destination);

        void fillMemoryWithIntegerValue(int size, int value, void* destination);

        void fillMemoryWithShortValue(undefined* size, uint shortValue, undefined* dst);

        void fillMemoryWithByteValue(int size, uchar value, void* destination);
    };

    static_assert_cpp98_obj(sizeof(LowLevelMemory) == 20, LowLevelMemory);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(LowLevelMemory, false, Address::SHC_3BB0A8C1_0x0165272C) pDAT_LowLevelMemory;

} // namespace IO
} // namespace OpenSHC
