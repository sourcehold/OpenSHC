#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MissionScores.hpp"
#include "OpenSHC/Globals/INT_00ec0828.hpp"
#include "OpenSHC/Globals/INT_00ed2790.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E1810
    void Helpers::WriteMissionToScoresFile(char* fileName, int score)
    {
        INT_00ed2790::instance = -1;
        for (int rank = 0; rank < 10; ++rank) {
            DAT_MissionScores::instance[rank] = 0;
        }
        // "rb"
        FILE* file = MACRO_CALL(OS_Func::_fopen)(fileName, s_rb_005a4e18);
        // The file holds a version (1) and the 10 best scores, best first.
        int version = 1;
        int scores[10];
        // A flag rather than one condition: it keeps the new-file block before the read path, as in the original.
        BOOLEnum fileIsValid = FALSE;
        if (file != NULL) {
            MACRO_CALL(OS_Func::_fread)(&version, sizeof(version), 1, file);
            if (version == 1) {
                fileIsValid = TRUE;
            }
        }
        if (!fileIsValid) {
            // No usable file: start one with this score as the only entry.
            // The original clears the version before the open and sets it again after; both stores are kept.
            version = 0;
            // "wb"
            file = MACRO_CALL(OS_Func::_fopen)(fileName, s_wb_005a5510);
            if (file == NULL) {
                return;
            }
            version = 1;
            MACRO_CALL(OS_Func::_fwrite)(&version, sizeof(version), 1, file);
            if (score < 0) {
                score = 0;
            } else {
                INT_00ed2790::instance = 0;
            }
            MACRO_CALL(OS_Func::_fwrite)(&score, sizeof(score), 1, file);
            // The nine empty slots are written from the version variable set to 0, as in the original.
            version = 0;
            for (int empty = 0; empty < 9; ++empty) {
                MACRO_CALL(OS_Func::_fwrite)(&version, sizeof(version), 1, file);
            }
            MACRO_CALL(OS_Func::_fclose)(file);
            INT_00ec0828::instance = 0;
            MACRO_CALL(UI::Helpers_Func::LoadScoresFileToMemory)(fileName);
            return;
        }
        for (int entry = 0; entry < 10; ++entry) {
            MACRO_CALL(OS_Func::_fread)(&scores[entry], sizeof(scores[entry]), 1, file);
        }
        MACRO_CALL(OS_Func::_fclose)(file);
        INT_00ec0828::instance = scores[0];
        // The score goes in front of the first lower one; with none it isn't kept.
        for (int rank = 0; rank < 10; ++rank) {
            if (score <= scores[rank]) {
                continue;
            }
            for (int entry = 9; entry > rank; --entry) {
                scores[entry] = scores[entry - 1];
            }
            scores[rank] = score;
            INT_00ed2790::instance = rank;
            // Set before and after the open, as the original does.
            version = 1;
            // "wb"
            file = MACRO_CALL(OS_Func::_fopen)(fileName, s_wb_005a5510);
            if (file == NULL) {
                return;
            }
            version = 1;
            MACRO_CALL(OS_Func::_fwrite)(&version, sizeof(version), 1, file);
            for (int entry = 0; entry < 10; ++entry) {
                MACRO_CALL(OS_Func::_fwrite)(&scores[entry], sizeof(scores[entry]), 1, file);
            }
            MACRO_CALL(OS_Func::_fclose)(file);
            MACRO_CALL(UI::Helpers_Func::LoadScoresFileToMemory)(fileName);
            return;
        }
    }

}
}
