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
        // The file holds a version (1) and the 10 best scores, best first.
        INT_00ed2790::instance = -1;
        for (int mission = 0; mission < 10; ++mission) {
            DAT_MissionScores::instance[mission] = 0;
        }
        // "rb"
        FILE* file = MACRO_CALL(OS_Func::_fopen)(fileName, s_rb_005a4e18);
        struct {
            int version;
            int scores[10];
        } scoresFile;
        scoresFile.version = 1;
        if (file == NULL || (MACRO_CALL(OS_Func::_fread)(&scoresFile.version, 4, 1, file), scoresFile.version != 1)) {
            // No usable file: start one with this score as the only entry.
            scoresFile.version = 0;
            // "wb"
            file = MACRO_CALL(OS_Func::_fopen)(fileName, s_wb_005a5510);
            if (file == NULL) {
                return;
            }
            scoresFile.version = 1;
            MACRO_CALL(OS_Func::_fwrite)(&scoresFile.version, 4, 1, file);
            if (score < 0) {
                score = 0;
            } else {
                INT_00ed2790::instance = 0;
            }
            MACRO_CALL(OS_Func::_fwrite)(&score, 4, 1, file);
            scoresFile.version = 0;
            for (int empty = 0; empty < 9; ++empty) {
                MACRO_CALL(OS_Func::_fwrite)(&scoresFile.version, 4, 1, file);
            }
            MACRO_CALL(OS_Func::_fclose)(file);
            INT_00ec0828::instance = 0;
            MACRO_CALL(UI::Helpers_Func::LoadScoresFileToMemory)(fileName);
            return;
        }
        for (int entry = 0; entry < 10; ++entry) {
            MACRO_CALL(OS_Func::_fread)(&scoresFile.scores[entry], 4, 1, file);
        }
        MACRO_CALL(OS_Func::_fclose)(file);
        INT_00ec0828::instance = scoresFile.scores[0];
        int rank = 0;
        for (; score <= scoresFile.scores[rank];) {
            ++rank;
            if (rank >= 10) {
                return;
            }
        }
        for (int entry = 9; entry > rank; --entry) {
            scoresFile.scores[entry] = scoresFile.scores[entry - 1];
        }
        scoresFile.scores[rank] = score;
        INT_00ed2790::instance = rank;
        scoresFile.version = 1;
        // "wb"
        file = MACRO_CALL(OS_Func::_fopen)(fileName, s_wb_005a5510);
        if (file == NULL) {
            return;
        }
        scoresFile.version = 1;
        MACRO_CALL(OS_Func::_fwrite)(&scoresFile.version, 4, 1, file);
        for (int entry = 0; entry < 10; ++entry) {
            MACRO_CALL(OS_Func::_fwrite)(&scoresFile.scores[entry], 4, 1, file);
        }
        MACRO_CALL(OS_Func::_fclose)(file);
        MACRO_CALL(UI::Helpers_Func::LoadScoresFileToMemory)(fileName);
    }

}
}
