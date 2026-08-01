#include "../LowLevelMemory.func.hpp"

#include "OpenSHC/OS.func.hpp"

namespace OpenSHC {
namespace IO {

    void* __strlwr = OS_Func::__strlwr::get();

    // FUNCTION: STRONGHOLDCRUSADER 0x0046AEC0
    BOOLEnum LowLevelMemory::isLordNameCallable(char* playerLordNameUnk, char* callableLordName)
    {
        int const lenText = strlen(playerLordNameUnk);
        int const lenPattern = strlen(callableLordName);
        int diff = lenText - lenPattern;
        if (diff < 0) {
            return false;
        }

        MACRO_CALL(OS_Func::__strlwr)(playerLordNameUnk);
        MACRO_CALL(OS_Func::__strlwr)(callableLordName);

        //
        // Fast path
        //
        if (diff <= 1) {
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
            return false;
        }

        int const extendedPattern = lenPattern + 2;

        //
        // General path
        //
        for (int offset = 0; offset <= diff; offset++) {
            if (offset == 0) {
                bool match = true;
                for (int i = 0; i < extendedPattern - 1; i++) {
                    if (i == extendedPattern - 2) {
                        char c = playerLordNameUnk[offset + i];
                        if (c == ' ' || c == '.' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6'
                            || c == '7' || c == '8' || c == '9' || c == '\0') {
                            continue;
                        }
                        match = false;
                        break;
                    } else if (playerLordNameUnk[offset + i] != callableLordName[i]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    return true;
                }
                continue;
            }

            //
            // Compare candidate text window against pattern.
            //
            bool match = true;
            for (int i = 0; i < extendedPattern; i++) {

                if (i == 0) {
                    if (playerLordNameUnk[i + offset] == ' ') {
                        continue;
                    }
                    match = false;
                    break;
                }
                if (i == extendedPattern - 1) {
                    char c = playerLordNameUnk[i + offset];
                    if (c == ' ' || c == '.' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6'
                        || c == '7' || c == '8' || c == '9' || c == '\0') {
                        continue;
                    }
                    match = false;
                    break;
                }
                if (playerLordNameUnk[i + offset] != callableLordName[i - 1]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                return true;
            }
        }
        return false;
    }

}
}
