#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE790
    void AICState ::clearRallyFlagOnAllAIAttackTribes(int param_1)

    {

        int _tribeID;

        int _counter;

        short* _ptrTribeID;

        int* _ptrTribeCount;

        int _tribeCount;

        int _tribeType;

        if (DAT_GameState::instance.playerDataArray[param_1].aiType != OpenSHC::AI::AIT_NULL) {

            _ptrTribeCount
                = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

            do {

                /*
                        first iteration: 3 */

                _tribeCount = *_ptrTribeCount;

                /*
                        first iteration: 186 */

                _tribeType = (*(int (*)[2])(_ptrTribeCount + -1))[0];

                /*
                        first iteration: 0 */

                _counter = 0;

                if (0 < _tribeCount) {

                    _ptrTribeID = DAT_GameState::instance.playerDataArray[param_1].aiTribeIDs + _tribeType;

                    do {

                        _tribeID = (int)*_ptrTribeID;

                        if ((_tribeID != 0)
                            && (DAT_TribesState::instance.tribes[_tribeID].uid
                                == DAT_GameState::instance.playerDataArray[param_1]
                                    .aiTribeUIDs[_counter + _tribeType])) {

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits,
                                DAT_TribesState::ptr)(_tribeID);
                        }

                        _counter = _counter + 1;

                        _ptrTribeID = _ptrTribeID + 1;

                    } while (_counter < _tribeCount);
                }

                _ptrTribeCount = _ptrTribeCount + 2;

            } while ((int)_ptrTribeCount < 0xb42a2c);
        }

        return;
    }

}
}
