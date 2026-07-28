#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {
    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE4D0
    void AICState::aiRetreatUnits(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;

        for (int _index1 = 0; _index1 < 11; _index1++) {
            int* _mappingPtr
                = DAT_SkirmishDefinedData::instance.DAT_AttackTribes_AITribeType_MaxTribeCount_Mapping[_index1] + 1;
            int const _maxTribeCount = *_mappingPtr;
            int const _tribeTypeStart = (*(int (*)[2])(_mappingPtr - 1))[0];
            int _tribeIndex = 0;

            if (0 < _maxTribeCount) {

                for (; _tribeIndex < _maxTribeCount; _tribeIndex++) {
                    int const _tribeID
                        = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[_tribeTypeStart + _tribeIndex];

                    if ((_tribeID != 0)
                        && (DAT_TribesState::instance.tribes[_tribeID].uid
                            == DAT_GameState::instance.playerDataArray[playerID]
                                .aiTribeUIDs[_tribeIndex + _tribeTypeStart])) {

                        DAT_TribesState::instance.tribes[_tribeID].unitStance
                            = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                        if (_tribeTypeStart == 0xbe) {
                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                _tribeID, playerID);
                        } else if (_tribeTypeStart == 0xd) {
                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                _tribeID, playerID);
                        } else {
                            int const _hasHorses
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::selectionContainsHorses,
                                    DAT_TribesState::ptr)(_tribeID);
                            if (_hasHorses != FALSE) {
                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                    _tribeID, playerID);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToKeep, this)(
                                    _tribeID, playerID);
                            }
                        }
                    }
                }
            }
        }
    }
}
}
