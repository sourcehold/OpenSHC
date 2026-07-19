#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB1B0
    int AICState::setNextFarmTypeToBuild(PlayerID playerID)

    {
        int const _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType == AITA_NULL) {
            return 0;
        }
        int* _ptrAiFarmIndex = &DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex;
        *_ptrAiFarmIndex = *_ptrAiFarmIndex + 1;
        if (7 < DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex) {
            DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex = 0;
        }
        if ((&this->DAT_AICArray[_aiType - 1].farm1)[DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex]
            == 0) {
            DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex = 0;
        }
        return (&this->DAT_AICArray[_aiType - 1].farm1)[DAT_GameState::instance.playerDataArray[playerID].aiFarmIndex];
    }
}
}
