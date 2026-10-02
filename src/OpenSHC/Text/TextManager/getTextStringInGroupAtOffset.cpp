#include "../TextManager.func.hpp"

#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

namespace OpenSHC {
namespace Text {

    using OpenSHC::DE::SHCDE::eTextSections;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0046A050
    char* TextManager::getTextStringInGroupAtOffset(eTextSections offsetIndex, int numInGroup)
    {
        char* _textPtr;
        char _char;
        switch (offsetIndex) {
        case OpenSHC::DE::SHCDE::TEXT_MAINOPTIONS:
            if (numInGroup == 0x1a) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 1;
            } else if (numInGroup == 0x1b) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 0;
            } else if (numInGroup == 0x1c) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 2;
            }
            break;
        default:
            break;
        case OpenSHC::DE::SHCDE::TEXT_BUBBLE_HELP_TEXT:
            if (numInGroup == 0xe3) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 3;
            } else if (numInGroup == 0x104) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 4;
            } else if (numInGroup == 0x10c) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 0xe;
            }
            break;
        case OpenSHC::DE::SHCDE::TEXT_MAP_TITLES:
            if (numInGroup == 2) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 0xf;
            }
            break;
        case OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM:
            if (numInGroup == 0x19d) {
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 0xd;
            }
            break;
        case OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE:
            switch (numInGroup) {
            case 0:
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 5;
                break;
            case 1:
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 6;
                break;
            case 2:
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 7;
                break;
            case 4:
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 8;
            }
        }
        _textPtr = this->textStart + this->textOffsets[offsetIndex];
        if (0 < numInGroup) {
            _char = *_textPtr;
            do {
                numInGroup = numInGroup + -1;
                while (_char != '\0') {
                    _textPtr = _textPtr + 1;
                    _char = *_textPtr;
                }
                do {
                    _char = _textPtr[1];
                    _textPtr = _textPtr + 1;
                } while (_char == '\0');
            } while (0 < numInGroup);
        }
        return _textPtr;
    }

}
}
