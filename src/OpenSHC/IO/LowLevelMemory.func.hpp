/**
  path: 'OpenSHC/IO/LowLevelMemory.func.hpp'
*/

#include "OpenSHC/IO/LowLevelMemory.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "crtdefs.h"
namespace OpenSHC {
namespace IO {
    namespace LowLevelMemory_Func {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(undefined4*, undefined3*), false,
            Address::SHC_3BB0A8C1_0x0046A830, &LowLevelMemory::moveLowerThreeBytesIntoParam2)
        moveLowerThreeBytesIntoParam2;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046A850, &LowLevelMemory::setMemoryToValue0x001)
        setMemoryToValue0x001;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046A890, &LowLevelMemory::setMemoryToValue0x002)
        setMemoryToValue0x002;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046A8D0, &LowLevelMemory::setMemoryToValue0x004)
        setMemoryToValue0x004;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046A910, &LowLevelMemory::setMemoryToValue0x010)
        setMemoryToValue0x010;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046A970, &LowLevelMemory::setMemoryToValue0x100)
        setMemoryToValue0x100;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046AAF0, &LowLevelMemory::copyData0x001)
        copyData0x001;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046AB30, &LowLevelMemory::copyData0x010)
        copyData0x010;

        MACRO_FUNCTION_RESOLVER(
            void (LowLevelMemory::*)(), false, Address::SHC_3BB0A8C1_0x0046ABA0, &LowLevelMemory::copyData0x100)
        copyData0x100;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(char*, char*), false, Address::SHC_3BB0A8C1_0x0046AE50,
            &LowLevelMemory::copyStringUntilFirstDot)
        copyStringUntilFirstDot;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(char*, char*, char*), false, Address::SHC_3BB0A8C1_0x0046AE80,
            &LowLevelMemory::putFileNameAndAppendFileExtension)
        putFileNameAndAppendFileExtension;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (LowLevelMemory::*)(char*, char*), false, Address::SHC_3BB0A8C1_0x0046AEC0,
            &LowLevelMemory::isLordNameCallable)
        isLordNameCallable;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(size_t, void*, void*), false, Address::SHC_3BB0A8C1_0x00471830,
            &LowLevelMemory::copyData)
        copyData;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(int, int, void*), false, Address::SHC_3BB0A8C1_0x00471860,
            &LowLevelMemory::fillMemoryWithIntegerValue)
        fillMemoryWithIntegerValue;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(undefined*, uint, undefined*), false,
            Address::SHC_3BB0A8C1_0x00471890, &LowLevelMemory::fillMemoryWithShortValue)
        fillMemoryWithShortValue;

        MACRO_FUNCTION_RESOLVER(void (LowLevelMemory::*)(int, uchar, void*), false, Address::SHC_3BB0A8C1_0x004718C0,
            &LowLevelMemory::fillMemoryWithByteValue)
        fillMemoryWithByteValue;

    } // namespace LowLevelMemory_Func
} // namespace IO
} // namespace OpenSHC
