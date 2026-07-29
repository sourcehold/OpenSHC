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

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE830
    void AICState::moveAttackTribesToLocations(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;

        int _destIndex = 0;

        for (int _index = 0; _index < 11; _index++) {
            int const _tribeTypeStart = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeType;
            int _tribeIndex = 0;
            int const _maxTribeCount = DAT_SkirmishDefinedData::instance.MaxAttackTribes1[_index].tribeCount;

            for (; _tribeIndex < _maxTribeCount; _tribeIndex++) {

                int const _tribeID
                    = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[_tribeTypeStart + _tribeIndex];

                if ((_tribeID != 0)
                    && (DAT_TribesState::instance.tribes[_tribeID].uid
                        == DAT_GameState::instance.playerDataArray[playerID]
                            .aiTribeUIDs[_tribeIndex + _tribeTypeStart])) {

                    DAT_TribesState::instance.tribes[_tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;

                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(_tribeID,
                        (uint)((int)(DAT_GameState::instance.mapAndTime
                                .aiTribeMoveDestinationXYPairArray1[playerID * 5][_destIndex]
                                .xOffset)),
                        (uint)((int)(DAT_GameState::instance.mapAndTime
                                .aiTribeMoveDestinationXYPairArray1[playerID * 5][_destIndex]
                                .yOffset)),
                        0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);

                    _destIndex = _destIndex + 1;
                }
            }
        }
    }

}
}
