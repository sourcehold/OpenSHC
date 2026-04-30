/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/IO/DecoderState.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace IO {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000014
    class DecoderState {
    public:
        uint implodingType; // 0x00000000 length: 4
        uint implodingTypeSize; // 0x00000004 length: 4
        dword crc32; // 0x00000008 length: 4
        dword sizeUncompressed; // 0x0000000C length: 4
        int sizeCompressed; // 0x00000010 length: 4

    private:
        DecoderState(DecoderState const&);
        void operator=(DecoderState const&);

        DecoderState();
        ~DecoderState();

    public:
        // Constructor
        DecoderState* Constructor_DecoderState();

        int compressRLE(char* src, int* dst, int size);

        int decompressRLE(void* param_1, undefined* param_2);

        BOOLEnum doImplode(int* ptrHash, int* ptrSize, undefined* src, undefined* dst);

        BOOLEnum doExplode(int* hash, undefined* src, int* decompressedSize, undefined* dst);

        int encodeData(int sizeUncompressed, undefined* src, undefined* dst);

        dword decodeData(void* source, void* destination);
    };

    static_assert_cpp98_obj(sizeof(DecoderState) == 20, DecoderState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(DecoderState, false, Address::SHC_3BB0A8C1_0x00F2CC24) pDAT_DecoderState;

} // namespace IO
} // namespace OpenSHC
