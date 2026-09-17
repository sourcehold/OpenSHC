#include "../IO.func.hpp"

#include "OpenSHC/Globals/DAT_ProtocolDefinedData.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00487090
char IO::Base64Encode_CharacterLookup(char param_1)
{
    if ('?' < param_1) {
        return '=';
    }
    return DAT_ProtocolDefinedData::instance.field136_0x4f4[param_1];
}

// FUNCTION: STRONGHOLDCRUSADER 0x004870B0
int IO::Base64Encode(char* input, int length, char* output, Base64State* state)
{
    char* inputEnd = input + length;
    char* outputRunPtr = output;

    char carryByte = state->carryByte;
    switch (state->phase) {
        while (true) {
        case 0: {
            if (input == inputEnd) {
                state->phase = 0;
                state->carryByte = carryByte;
                return outputRunPtr - output;
            }
            char currentByte = *input;
            ++input;
            *outputRunPtr = MACRO_CALL(OpenSHC::IO_Func::Base64Encode_CharacterLookup)(currentByte >> 2 & 0x3f);
            ++outputRunPtr;
            carryByte = (currentByte & 0x3) << 4;
        }
        case 1: {
            if (input == inputEnd) {
                state->phase = 1;
                state->carryByte = carryByte;
                return outputRunPtr - output;
            }
            char currentByte = *input;
            ++input;
            *outputRunPtr
                = MACRO_CALL(OpenSHC::IO_Func::Base64Encode_CharacterLookup)(currentByte >> 4 & 0xf | carryByte);
            ++outputRunPtr;
            carryByte = (currentByte & 0xf) << 2;
        }
        case 2: {
            if (input == inputEnd) {
                state->phase = 2;
                state->carryByte = carryByte;
                return outputRunPtr - output;
            }
            char currentByte = *input;
            ++input;
            *outputRunPtr
                = MACRO_CALL(OpenSHC::IO_Func::Base64Encode_CharacterLookup)(currentByte >> 6 & 0x3 | carryByte);
            ++outputRunPtr;
            carryByte = currentByte & 0x3f;
            *outputRunPtr = MACRO_CALL(OpenSHC::IO_Func::Base64Encode_CharacterLookup)(carryByte);
            ++outputRunPtr;
            ++state->lineCharacterCounter;
            if (state->lineCharacterCounter != 7200) {
                continue;
            }
            *outputRunPtr = '\n';
            ++outputRunPtr;
            state->lineCharacterCounter = 0;
        }
        }
    }
    return 0;
}

}
