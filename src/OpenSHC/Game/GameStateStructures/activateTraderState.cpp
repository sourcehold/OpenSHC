#include "OpenSHC/Game/GameStateStructures.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x004586D0
    void GameStateStructures::activateTraderState()
    {
        this->mapAndTime.traderRelated2 = 2;
        this->mapAndTime.traderRelatedCounter1 = 0;
    }

}
}
