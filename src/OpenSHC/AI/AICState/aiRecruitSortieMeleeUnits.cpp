#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Map::Units::UnitType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD690
    void AICState ::aiRecruitSortieMeleeUnits(int playerID)

    {

        AITypeInt AVar1;

        int iVar2;

        int _unitID;

        int _section1016id;

        UnitType _unitType;

        AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar1 != OpenSHC::AI::AIT_NULL) {

            iVar2 = (AVar1 + ~OpenSHC::AI::AIT_NULL) * 0x2a4;

            _section1016id = *(int*)((int)this + iVar2 + 0x154);

            if (((((-1 < _section1016id)
                      && (DAT_GameState::instance.playerDataArray[playerID].totalTroopsType7 < _section1016id))
                     && (0 < DAT_GameState::instance.playerDataArray[playerID].idlePeasantsCount))
                    && ((DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0
                        && (_unitType = *(UnitType*)((int)this + iVar2 + 0x158),
                            _unitType != OpenSHC::Map::Units::UT_E_ENGINEER))))
                && ((_unitType != OpenSHC::Map::Units::UT_E_LADDER
                    && (_unitType != OpenSHC::Map::Units::UT_TUNNELER)))) {

                if ((int)_unitType < 0x46) {

                    _section1016id = DAT_GameState::instance.playerDataArray[playerID].barracks.id;

                }

                else {

                    _section1016id = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id;
                }

                if (_section1016id != 0) {

                    if ((int)_unitType < 0x46) {

                        _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit,
                            DAT_UnitsState::ptr)(_unitType, (undefined4)((int)(_section1016id)), playerID, 0);

                    }

                    else {

                        _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit,
                            DAT_UnitsState::ptr)(_unitType, (undefined4)((int)(_section1016id)), playerID, 0);
                    }

                    if (_unitID == 0) {

                        _section1016id = *(int*)((int)this + iVar2 + 0x9c);

                        if ((0 < _section1016id) && (DAT_UnitsState::instance.DAT_EuroUnitAcquisitionFailReason == 2)) {

                            DAT_GameState::instance.playerDataArray[playerID]
                                .resourcesToAcquireArray[DAT_UnitsState::instance.DAT_EuroUnitRequiredResource]
                                = _section1016id;

                            return;
                        }

                    }

                    else {

                        DAT_UnitsState::instance.units[_unitID].aiUnitBehaviourType = 7;

                        _section1016id = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::createTribeForUnitType, this)(
                            playerID, (int)((int)(167)));

                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            _unitID, _section1016id);
                    }
                }
            }
        }

        return;
    }

}
}
