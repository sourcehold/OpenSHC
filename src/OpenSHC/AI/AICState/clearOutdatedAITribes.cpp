#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF870
    void AICState ::clearOutdatedAITribes(int playerID)

    {

        if (DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL) {

            int _index = 0;

            do {

                if (_index != 8) {

                    int _groupCount
                        = DAT_SkirmishDefinedData::instance.DAT_BreachTribeTypes_TribeGroupCount_Mapping[_index][1];

                    int _tribeType
                        = DAT_SkirmishDefinedData::instance.DAT_BreachTribeTypes_TribeGroupCount_Mapping[_index][0];

                    int _offset = 0;

                    if (0 < _groupCount) {

                        short* _ptrTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + _tribeType;

                        do {
                            int _tribeIDVal = (int)*_ptrTribeID;
                            if ((_tribeIDVal != 0)
                                && (DAT_TribesState::instance.tribes[_tribeIDVal].uid
                                    != DAT_GameState::instance.playerDataArray[playerID]
                                        .aiTribeUIDs[_offset + _tribeType])) {

                                *_ptrTribeID = 0;

                                DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_offset + _tribeType] = 0;
                            }

                            _offset = _offset + 1;

                            _ptrTribeID = _ptrTribeID + 1;

                        } while (_offset < _groupCount);
                    }
                }

                _index = _index + 1;

            } while (_index < 0xb);
        }

        return;
    }

}
}
