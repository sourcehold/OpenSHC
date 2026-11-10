#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MissionScores.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DAF50
    void Helpers::LoadScoresFileToMemory(char* filename)
    {
        // "rb"
        FILE* const file = MACRO_CALL(OS_Func::_fopen)(filename, s_rb_005a4e18);
        if (file == NULL) {
            return;
        }
        MACRO_CALL(OS_Func::_fseek)(file, 4, FILE_BEGIN);
        for (int mission = 0; mission < 10; ++mission) {
            MACRO_CALL(OS_Func::_fread)(
                &DAT_MissionScores::instance[mission], sizeof(DAT_MissionScores::instance[mission]), 1, file);
        }
        MACRO_CALL(OS_Func::_fclose)(file);
    }

}
}
