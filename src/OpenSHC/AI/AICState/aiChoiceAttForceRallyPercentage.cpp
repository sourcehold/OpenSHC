#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEC80
    uint AICState ::aiChoiceAttForceRallyPercentage(int param_1)

    {

        AITypeInt _aiType = DAT_GameState::instance.playerDataArray[param_1].aiType;

        if (_aiType == OpenSHC::AI::AIT_NULL) {

            return 0;
        }

        int const _aiIndex = _aiType - 1;
        int _activeTribes = 0;
        int _nonMoving = 0;

        for (int _index = 0; _index < 11; _index++) {

            int const _tribeTypeStart = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeType;

            int const _maxTribeCount = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeCount;

            for (int _tribeIndex = 0; _tribeIndex < _maxTribeCount; _tribeIndex++) {

                int const _tribeID
                    = (int)DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs[_tribeTypeStart + _tribeIndex];

                if (((_tribeID != 0)
                        && (DAT_TribesState::instance.tribes[_tribeID].uid
                            == DAT_GameState::instance.playerDataArray[param_1]
                                .aiTribeUIDs[_tribeIndex + _tribeTypeStart]))
                    && (_activeTribes += 1, DAT_TribesState::instance.tribes[_tribeID].percentageMovingUnk < 0x14)) {

                    _nonMoving += 1;
                }
            }
        }

        if (_activeTribes <= 0) {

            return 0;
        }

        return (uint)((_nonMoving * 100) / _activeTribes >= (int)this->aics[_aiIndex].AttForceRallyPercentage);
    }

}
}
