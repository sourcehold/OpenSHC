#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFA10
    void AICState ::addRallyPointForTribe(int tribeID)

    {

        short* psVar1;

        BOOLEnum _areInDifferentTeamsUnk;

        Unit* _ptrUnit;

        UnitTypeShort _unitType;

        DAT_TribesState::instance.tribes[tribeID].rallyPointCount = 0;

        _ptrUnit = &DAT_UnitsState::instance.units[1];

        do {

            if (_ptrUnit->logicalState != OpenSHC::Map::Units::ULS_INVISIBLE) {

                _areInDifferentTeamsUnk = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::getTeamsDifferent,
                    DAT_GameState::ptr)(DAT_TribesState::instance.tribes[tribeID].owner, (int)((int)(_ptrUnit->owner)));

                if (_areInDifferentTeamsUnk == FALSE) {

                    _unitType = _ptrUnit->unitType;

                    if ((((_unitType == OpenSHC::Map::Units::UT_S_CATAPULT)
                             || (_unitType == OpenSHC::Map::Units::UT_S_TREBUCHET))
                            || (_unitType == OpenSHC::Map::Units::UT_S_FBALLISTA))
                        && (_ptrUnit->unknownSiegeTentRelated02 == 3)) {

                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                            DAT_PathFindingState::ptr)(-1, (int)((int)(_ptrUnit->x)), (int)((int)(_ptrUnit->y)));

                        DAT_TribesState::instance.tribes[tribeID]
                            .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][0]
                            = (short)DAT_PathFindingState::instance.ALG_ResultX;

                        DAT_TribesState::instance.tribes[tribeID]
                            .rallyPointArray[DAT_TribesState::instance.tribes[tribeID].rallyPointCount][1]
                            = (short)DAT_PathFindingState::instance.ALG_ResultY;

                        psVar1 = &DAT_TribesState::instance.tribes[tribeID].rallyPointCount;

                        *psVar1 = *psVar1 + 1;

                        if (8 < DAT_TribesState::instance.tribes[tribeID].rallyPointCount)
                            break;
                    }
                }
            }

            _ptrUnit = _ptrUnit + 0x248;

        } while ((int)_ptrUnit < 0x165141a);

        if (DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex < 0) {

            DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        }

        if (DAT_TribesState::instance.tribes[tribeID].rallyPointCount
            <= DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex) {

            DAT_TribesState::instance.tribes[tribeID].currentRallyPointIndex = 0;
        }

        return;
    }

}
}
