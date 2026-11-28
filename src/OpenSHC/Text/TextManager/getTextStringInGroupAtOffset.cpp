#include "../TextManager.func.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046A050
    char* TextManager::getTextStringInGroupAtOffset(eTextSections offsetIndex, int numInGroup)
    {
        switch (offsetIndex) {
        case DE::SHCDE::TEXT_MAINOPTIONS:
            switch (numInGroup) {
            case 26:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 1;
                break;
            case 27:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 0;
                break;
            case 28:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 2;
                break;
            }
            break;
        case DE::SHCDE::TEXT_BUBBLE_HELP_TEXT:
            switch (numInGroup) {
            case 227:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 3;
                break;
            case 260:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 4;
                break;
            case 268:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 14;
                break;
            }
            break;
        case DE::SHCDE::TEXT_SKIRMISH_CHOOSE:
            switch (numInGroup) {
            case 0:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 5;
                break;
            case 1:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 6;
                break;
            case 2:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 7;
                break;
            case 4:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 8;
                break;
            }
            break;
        // the single-case switches below do not match when written as an if
        case DE::SHCDE::TEXT_XPLAY_WAITING_ROOM:
            switch (numInGroup) {
            case 413:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 13;
                break;
            }
            break;
        case DE::SHCDE::TEXT_MAP_TITLES:
            switch (numInGroup) {
            case 2:
                offsetIndex = DE::SHCDE::TEXT_SKIRMISH_CHOOSE2;
                numInGroup = 15;
                break;
            }
            break;
        }
        char* text = this->textStart + this->textOffsets[offsetIndex];
        // the decrement has to come first in the body: in the for header this does not match
        for (; numInGroup > 0;) {
            --numInGroup;
            for (; *text != '\0'; ++text) {}
            for (; *text == '\0'; ++text) {}
        }
        return text;
    }

}
}
