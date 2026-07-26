#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF920
    undefined4 AICState ::giveSomeRaidCommand(int tribeIndex, int tribeType)

    {

        int _chosenBuildingID;

        int _targetBuildingID;

        int _attacked;

        _targetBuildingID = (int)DAT_TribesState::instance.tribes[tribeIndex].targetBuildingID;

        if ((((tribeType != 0xba) && (tribeType != 0x12)) && (tribeType != 0xe)) && (tribeType != 0xd)) {

            if (((_targetBuildingID != 0)
                    && (DAT_BuildingsState::instance.buildings[_targetBuildingID].uid
                        == DAT_TribesState::instance.tribes[tribeIndex].targetBuildingUID))
                && (DAT_BuildingsState::instance.buildings[_targetBuildingID].fireDuration == 0)) {

                return (undefined4)(1);
            }

            _attacked = DAT_GameState::instance.playerDataArray[DAT_TribesState::instance.tribes[tribeIndex].owner]
                            .attackedPlayerID;

            DAT_TribesState::instance.tribes[tribeIndex].targetBuildingID = 0;

            _chosenBuildingID = MACRO_CALL_MEMBER(
                OpenSHC::AI::AICState_Func::chooseRandomBuildingIDFromPlayersArrayOfBuildings, this)(_attacked);

            if (_chosenBuildingID != 0) {

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueDisbandAndAttackCommand4Params,
                    DAT_UnitsState::ptr)(tribeIndex, 9, (undefined4)((int)(_chosenBuildingID)),
                    (undefined4)((int)(DAT_BuildingsState::instance.buildings[_chosenBuildingID].uid)));

                DAT_TribesState::instance.tribes[tribeIndex].targetBuildingUID
                    = DAT_BuildingsState::instance.buildings[_chosenBuildingID].uid;

                DAT_TribesState::instance.tribes[tribeIndex].targetBuildingID = (short)_chosenBuildingID;

                DAT_TribesState::instance.tribes[tribeIndex].unitStance = OpenSHC::Map::Units::Behavior::USE_DEFENSIVE;

                return (undefined4)(1);
            }
        }

        return (undefined4)(0);
    }

}
}
