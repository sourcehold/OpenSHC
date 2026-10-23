#include "OpenSHC/Globals/DAT_CurrentPlayerUnitLosses.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044aa70
    void UpdateUnitValueLoss(int value)
    {
        if (value > 0) {
            DAT_CurrentPlayerUnitLosses::instance += value;
        }
    }

} // namespace Game
} // namespace OpenSHC
