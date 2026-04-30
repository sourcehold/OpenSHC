/**
  path: 'OpenSHC/IO/DecoderState.func.hpp'
*/

#include "OpenSHC/IO/DecoderState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace IO {
    namespace DecoderState_Func {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(int (DecoderState::*)(char*, int*, int), false, Address::SHC_3BB0A8C1_0x0046D150,
            &DecoderState::compressRLE)
        compressRLE;

        MACRO_FUNCTION_RESOLVER(int (DecoderState::*)(void*, undefined*), false, Address::SHC_3BB0A8C1_0x0046D200,
            &DecoderState::decompressRLE)
        decompressRLE;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (DecoderState::*)(int*, int*, undefined*, undefined*), false,
            Address::SHC_3BB0A8C1_0x004724C0, &DecoderState::doImplode)
        doImplode;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (DecoderState::*)(int*, undefined*, int*, undefined*), false,
            Address::SHC_3BB0A8C1_0x004725A0, &DecoderState::doExplode)
        doExplode;

        MACRO_FUNCTION_RESOLVER(int (DecoderState::*)(int, undefined*, undefined*), false,
            Address::SHC_3BB0A8C1_0x00473C10, &DecoderState::encodeData)
        encodeData;

        MACRO_FUNCTION_RESOLVER(
            dword (DecoderState::*)(void*, void*), false, Address::SHC_3BB0A8C1_0x00473C70, &DecoderState::decodeData)
        decodeData;

    } // namespace DecoderState_Func
} // namespace IO
} // namespace OpenSHC
