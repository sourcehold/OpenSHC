#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIVUnitType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIVUnitType;
    using OpenSHC::Map::Units::UnitInstructionType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D44E0
    void AICState ::sendOilMenForOilPickupOrToAIVLocations(int playerID)

    {

        short* _ptrTribeIDArray;

        int _oilManLocationsCount;

        int _tribeID;

        int _index;

        int _oilSmelter;

        _oilSmelter = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.id;

        _oilManLocationsCount = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[1];

        if (0 < _oilManLocationsCount) {

            if (_oilManLocationsCount == 10) {

                _oilManLocationsCount = 9;
            }

            _index = 1;

            if (0 < _oilManLocationsCount) {

                /*
                        oil men offset in tribe id array */

                _ptrTribeIDArray = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 71;

                do {

                    _tribeID = (int)*_ptrTribeIDArray;

                    if ((_tribeID != 0)
                        && (DAT_TribesState::instance.tribes[_tribeID].uid
                            == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_index + 0x46])) {

                        if (DAT_UnitsState::instance
                                .units[DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID]
                                .resourceToDeposit
                            == 0) {

                            if (_oilSmelter != 0) {

                                /*
                                                send for oil duty */

                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction,
                                    DAT_UnitsState::ptr)(_tribeID,
                                    OpenSHC::Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED,
                                    _oilSmelter, DAT_BuildingsState::instance.buildings[_oilSmelter].uid, 0);
                            }

                        }

                        else {

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::unsetRallyRelatedFlagOnUnits,
                                DAT_TribesState::ptr)(_tribeID);

                            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendTribeToAIVLocationSlot, this)(
                                _tribeID, OpenSHC::AI::AIVUT_ENGINEER, _index + -1);
                        }
                    }

                    _index = _index + 1;

                    _ptrTribeIDArray = _ptrTribeIDArray + 1;

                } while (_index <= _oilManLocationsCount);
            }
        }

        return;
    }

}
}
