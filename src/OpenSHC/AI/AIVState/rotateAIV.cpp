#include "../AIVState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace AI {

    // rotates the loaded AIV grid to the keep orientation
    // FUNCTION: STRONGHOLDCRUSADER 0x004ED0B0
    void AIVState::rotateAIV(int orientation)
    {
        if (orientation == 0) {
            return;
        }
        if (orientation == 6) {
            for (int y = 0; y < 100; ++y) {
                for (int x = 0; x < 100; ++x) {
                    this->rotatedConstructions[x][99 - y] = this->constructions[y * 100 + x];
                    this->rotatedSteps[x][99 - y] = this->steps[y][x];
                }
            }
        } else if (orientation == 4) {
            for (int y = 0; y < 100; ++y) {
                for (int x = 0; x < 100; ++x) {
                    this->rotatedConstructions[99 - y][99 - x] = this->constructions[y * 100 + x];
                    this->rotatedSteps[99 - y][99 - x] = this->steps[y][x];
                }
            }
        } else if (orientation == 2) {
            for (int y = 0; y < 100; ++y) {
                for (int x = 0; x < 100; ++x) {
                    this->rotatedConstructions[99 - x][y] = this->constructions[y * 100 + x];
                    this->rotatedSteps[99 - x][y] = this->steps[y][x];
                }
            }
        }
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            sizeof(this->rotatedConstructions), this->rotatedConstructions, this->constructions);
        MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::copyData, DAT_LowLevelMemory::ptr)(
            sizeof(this->rotatedSteps), this->rotatedSteps, this->steps);
    }

}
}
