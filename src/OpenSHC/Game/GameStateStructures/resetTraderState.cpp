#include "../GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004586F0
    void GameStateStructures::resetTraderState()
    {
        this->mapAndTime.traderRelated2 = 0;
        this->mapAndTime.traderRelatedCounter1 = 0;
    }

}
}
