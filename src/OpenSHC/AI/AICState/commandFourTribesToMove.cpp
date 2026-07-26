#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF7C0
    void AICState ::commandFourTribesToMove(int playerID)

    {

        if (DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL) {

            int _counter2 = 0;

            int _counter = 0;

            short* _ptrTribeIDArray = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 0xba;

            do {

                int _tribeID = (int)*_ptrTribeIDArray;

                if ((_tribeID != 0)
                    && (DAT_TribesState::instance.tribes[_tribeID].uid
                        == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_counter + 0xba])) {

                    DAT_TribesState::instance.tribes[_tribeID].unitStance
                        = OpenSHC::Map::Units::Behavior::USE_STAND_GROUND;

                    /*
                              fixme: array too small? */

                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(_tribeID,
                        (uint)((int)(DAT_GameState::instance.mapAndTime
                                .aiTribeMoveDestinationXYPairArray1[playerID * 5][_counter2]
                                .xOffset)),
                        (uint)((int)(DAT_GameState::instance.mapAndTime
                                .aiTribeMoveDestinationXYPairArray1[playerID * 5][_counter2]
                                .yOffset)),
                        0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);

                    _counter2 = _counter2 + 1;
                }

                _counter = _counter + 1;

                _ptrTribeIDArray = _ptrTribeIDArray + 1;

            } while (_counter < 3);
        }

        return;
    }

}
}
