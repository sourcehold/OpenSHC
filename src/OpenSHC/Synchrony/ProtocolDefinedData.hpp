/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/ProtocolDefinedData.hpp'
*/

#pragma once

#include "OpenSHC/Util/FunctionTypes/NoArgCallback.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Util::FunctionTypes::NoArgCallback;

#pragma pack(push, 1)
    // SIZE: 0x000004F8
    typedef struct ProtocolDefinedData {

        undefined1 padding_0x0[4]; // 0x00000000 length: 4
        int field_0x4[12][2]; // 0x00000004 length: 96
        int field_0x64[39][3]; // 0x00000064 length: 468
        undefined1 padding_0x238[8]; // 0x00000238 length: 8
        char** insultWavFiles[21]; // 0x00000240 length: 84
        NoArgCallback* commandFunctions[120]; // 0x00000294 length: 480
        int field_0x474[32]; // 0x00000474 length: 128
        char* field_0x4f4; // 0x000004F4 length: 4

    } ProtocolDefinedData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(ProtocolDefinedData) == 1272, ProtocolDefinedData);
} // namespace Synchrony
} // namespace OpenSHC
