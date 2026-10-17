#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00519790
        void TroopValueState::setRallyPointForLaddermenTribe(int param_1)
        {
            BOOLEnum BVar2;
            Tribe* _pTribe;
            int iVar3 = 0;
            int iVar5 = 1;
            _pTribe = &DAT_TribesState::instance.tribes[1];
            do {
                if (_pTribe->tribeState != 0) {
                    BVar2 = MACRO_CALL_MEMBER(Game::GameStateStructures_Func::isFullIDEqualsToMinus1,
                        DAT_GameState::ptr)(_pTribe->owner);
                    if (BVar2 && _pTribe->tribeType == AI::Tribes::AITT_LADDERMEN
                        && (iVar3 = iVar3 + 1, iVar3 == DAT_TribesState::instance.tribes[param_1].someCounter1 + 1)) {
                        int _unitID = DAT_TribesState::instance.tribes[iVar5].selectionTargetUnitID;
                        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::computeNextRallyPointDestination,
                            DAT_PathFindingState::ptr)(-1, (int)(DAT_UnitsState::instance.units[_unitID].x),
                            (int)(DAT_UnitsState::instance.units[_unitID].y));
                        short sVar1 = (short)DAT_PathFindingState::instance.ALG_ResultY;
                        DAT_TribesState::instance.tribes[param_1].rallyPointArray[0][0] = (short)DAT_PathFindingState::instance.ALG_ResultX;
                        DAT_TribesState::instance.tribes[param_1].rallyPointArray[0][1] = sVar1;
                        return;
                    }
                }
                _pTribe = _pTribe + 1;
                iVar5 = iVar5 + 1;
            } while (_pTribe < &DAT_TribesState::instance.tribes[1250]);
        }

    }
}
}
