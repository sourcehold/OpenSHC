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

        int _nonMoving = 0;
        int _activeTribes = 0;
        int _index = 0;
        int _maxTribeCount = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeCount;

        for (; _index < 11; _index++) {

            int const _tribeTypeStart = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeType;
            int _tribeIndex = 0;
            _maxTribeCount = (int)DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeCount;

            for (; _tribeIndex < _maxTribeCount; _tribeIndex++) {

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

        if (0 < _activeTribes) {

            return (uint)(((int)this->aics[_aiType - 1].AttForceRallyPercentage) <= (_nonMoving * 100) / _activeTribes);
        }

        return 0;
    }

}
}
