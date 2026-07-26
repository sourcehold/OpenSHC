#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CED90
    BOOLEnum AICState ::percentageNonMovingTribesGTEAICSpecified(int playerID)

    {

        int _tribe;

        int _index;

        short* _ptrTribeNumber;

        int _tribesCount;

        int _movingFewerThan20Percent;

        int* _ptrSize;

        AITypeInt _aiType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType == OpenSHC::AI::AIT_NULL) {

            return FALSE;
        }

        _tribesCount = 0;

        _movingFewerThan20Percent = 0;

        _ptrSize = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

        do {

            _index = 0;

            if (0 < *_ptrSize) {

                _ptrTribeNumber
                    = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + (*(int (*)[2])(_ptrSize + -1))[0];

                do {

                    _tribe = (int)*_ptrTribeNumber;

                    if (((_tribe != 0)
                            && (DAT_TribesState::instance.tribes[_tribe].uid
                                == DAT_GameState::instance.playerDataArray[playerID]
                                    .aiTribeUIDs[_index + (*(int (*)[2])(_ptrSize + -1))[0]]))
                        && (_tribesCount = _tribesCount + 1,
                            DAT_TribesState::instance.tribes[_tribe].percentageMovingUnk < 20)) {

                        _movingFewerThan20Percent = _movingFewerThan20Percent + 1;
                    }

                    _index = _index + 1;

                    _ptrTribeNumber = _ptrTribeNumber + 1;

                } while (_index < *_ptrSize);
            }

            _ptrSize = _ptrSize + 2;

        } while ((int)_ptrSize < 0xb42a2c);

        if (0 < _tribesCount) {

            return (uint)(*(int*)((int)this + (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4 + 0x204)
                <= (_movingFewerThan20Percent * 100) / _tribesCount);
        }

        return FALSE;
    }

}
}
