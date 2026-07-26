#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      doc:|
         Retreat units to campfire or keep
       decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE4D0
    void AICState ::aiRetreatUnits(short* playerID)

    {

        BOOLEnum BVar1;

        int _counter;

        int _tribeID;

        int* local_8;

        int _aiBehaviourType;

        int _groupCount;

        short* _playerID;

        _playerID = playerID;

        if (DAT_GameState::instance.playerDataArray[(int)playerID].aiType != OpenSHC::AI::AIT_NULL) {

            local_8 = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[0] + 1;

            do {

                _groupCount = *local_8;

                _aiBehaviourType = (*(int (*)[2])(local_8 + -1))[0];

                _counter = 0;

                if (0 < _groupCount) {

                    playerID = DAT_GameState::instance.playerDataArray[(int)_playerID].aiTribeIDs + _aiBehaviourType;

                    do {

                        _tribeID = (int)*playerID;

                        if ((_tribeID != 0)
                            && (DAT_TribesState::instance.tribes[_tribeID].uid
                                == DAT_GameState::instance.playerDataArray[(int)_playerID]
                                    .aiTribeUIDs[_counter + _aiBehaviourType])) {

                            DAT_TribesState::instance.tribes[_tribeID].unitStance
                                = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                            if (_aiBehaviourType == 0xbe) {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                    _tribeID, (int)((int)(_playerID)));

                            }

                            else if (_aiBehaviourType == 0xd) {

                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                    _tribeID, (int)((int)(_playerID)));

                            }

                            else {

                                BVar1
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::selectionContainsHorses,
                                        DAT_TribesState::ptr)(_tribeID);

                                if (BVar1 == FALSE) {

                                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(
                                        _tribeID, (int)((int)(_playerID)));

                                }

                                else {

                                    MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                        _tribeID, (int)((int)(_playerID)));
                                }
                            }
                        }

                        playerID = playerID + 1;

                        _counter = _counter + 1;

                    } while (_counter < _groupCount);
                }

                local_8 = local_8 + 2;

            } while ((int)local_8 < 0xb42a2c);
        }

        return;
    }

}
}
