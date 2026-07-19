#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFF60
    BOOLEnum AICState::yieldCowThrow(int playerID)
    {
        int* _pCounter;
        int const _ai = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if ((((_ai != AITA_NULL) && (DAT_GameState::instance.mapAndTime.noCowThrowing == 0))
                && (this->aics[_ai - 1].CowThrowInterval != 0))
            && ((0 < DAT_GameState::instance.playerDataArray[playerID].counter
                && (_pCounter = &DAT_GameState::instance.playerDataArray[playerID].aiCowThrowCounter,
                    *_pCounter = *_pCounter + 1,
                    (int)this->aics[_ai - 1].CowThrowInterval
                        < DAT_GameState::instance.playerDataArray[playerID].aiCowThrowCounter)))) {
            DAT_GameState::instance.playerDataArray[playerID].aiCowThrowCounter = 0;
            return TRUE;
        }
        return FALSE;
    }
}
}
