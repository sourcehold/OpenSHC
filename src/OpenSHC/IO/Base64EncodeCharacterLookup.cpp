#include "OpenSHC/IO.func.hpp"

#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00487090
byte IO::Base64EncodeCharacterLookup(char param_1)
{
    if ('?' < param_1) {
        return (byte)(0x3d);
    }
    return DAT_ProtocolDefinedData::instance.field136_0x4f4[param_1];
}

}
