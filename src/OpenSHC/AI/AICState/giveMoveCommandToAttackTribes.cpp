#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CEB50
    void AICState ::giveMoveCommandToAttackTribes(int playerID)

    {

        int _aiTribeID;

        int _counter;

        int _groupCounter;

        int* _ptrGroupCount;

        int _groupCount;

        int _playerID;

        int _tribeType;

        _playerID = playerID;

        if (DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL) {

            _counter = 0;

            _ptrGroupCount = &DAT_SkirmishDefinedData::instance.MaxAttackTribes1[0].tribeCount;

            do {

                _tribeType = (*(int (*)[2])(_ptrGroupCount + -1))[0];

                _groupCount = *_ptrGroupCount;

                if ((((_tribeType != 18) && (_tribeType != 190)) && (_tribeType != 15))
                    && (_groupCounter = 0, 0 < _groupCount)) {

                    /*
                              fixme: param reusage */

                    playerID = (_playerID * 0x1cfa + _tribeType) * 2 + 0x115ef04;

                    do {

                        _aiTribeID = (int)*(short*)playerID;

                        if ((_aiTribeID != 0)
                            && (DAT_TribesState::instance.tribes[_aiTribeID].uid
                                == DAT_GameState::instance.playerDataArray[_playerID]
                                    .aiTribeUIDs[_groupCounter + _tribeType])) {

                            /*
                                          bug: why give a random unit stance? */

                            DAT_TribesState::instance.tribes[_aiTribeID].unitStance
                                = (short)(char)((byte)SEC_RNG::instance.currentNumber2 & 1);

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction,
                                DAT_TribesState::ptr)(_aiTribeID,
                                (uint)((int)(DAT_GameState::instance.mapAndTime
                                        .aiTribeMoveDestinationXYPairArray1[_playerID * 5][_counter]
                                        .xOffset)),
                                (uint)((int)(DAT_GameState::instance.mapAndTime
                                        .aiTribeMoveDestinationXYPairArray1[_playerID * 5][_counter]
                                        .yOffset)),
                                0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);

                            _counter = _counter + 1;
                        }

                        playerID = playerID + 2;

                        _groupCounter = _groupCounter + 1;

                    } while (_groupCounter < _groupCount);
                }

                _ptrGroupCount = _ptrGroupCount + 2;

            } while ((int)_ptrGroupCount < 0xb42a2c);
        }

        return;
    }

}
}
