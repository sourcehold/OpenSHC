#include "../LowLevelMemory.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AEC0
    BOOLEnum LowLevelMemory::isLordNameCallable(char* playerLordNameUnk, char* callableLordName)
    {
        int const lenText = strlen(playerLordNameUnk);
        int lenPattern = strlen(callableLordName);
        int diff = lenText - lenPattern;
        if (diff < 0) {
            return false;
        }

        MACRO_CALL(OS_Func::__strlwr)(playerLordNameUnk);
        MACRO_CALL(OS_Func::__strlwr)(callableLordName);

        if (diff <= 1) {
            //
            // Fast path
            //

            int offset = 0;
            do {
                bool equal = true;

                for (int i = 0; i < lenPattern; i++) {
                    if (playerLordNameUnk[offset + i] != callableLordName[i]) {
                        equal = false;
                        break;
                    }
                }

                if (equal) {
                    return true;
                }

                offset++;
            } while (offset <= 0);
        } else {
            //
            // General path
            //

            lenPattern += 2;
            for (int offset = 0; offset <= diff; offset++) {
                bool match = true;
                if (offset == 0) {
                    for (int i = 0; i < lenPattern - 1; ++i) {
                        if (i == lenPattern - 2) {
                            char c = playerLordNameUnk[offset + i];
                            if (c == ' ' || c == '.' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
                                || c == '6' || c == '7' || c == '8' || c == '9' || c == '\0') {
                                continue;
                            }
                            match = false;
                            break;
                        } else if (playerLordNameUnk[offset + i] != callableLordName[i]) {
                            match = false;
                            break;
                        }
                    }
                } else {
                    for (int i = 0; i < lenPattern; ++i) {
                        if (i == 0) {
                            if (playerLordNameUnk[offset + i] == ' ') {
                                continue;
                            }
                            match = false;
                            break;
                        }
                        if (i == lenPattern - 1) {
                            char c = playerLordNameUnk[offset + i];
                            if (c == ' ' || c == '.' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5'
                                || c == '6' || c == '7' || c == '8' || c == '9' || c == '\0') {
                                continue;
                            }
                            match = false;
                            break;
                        }
                        if (playerLordNameUnk[offset + i] != callableLordName[i - 1]) {
                            match = false;
                            break;
                        }
                    }
                }
                if (match) {
                    return true;
                }
            }
        }

        return false;
    }

}
}
