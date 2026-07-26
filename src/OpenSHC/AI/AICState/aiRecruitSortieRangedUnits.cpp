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

    // FUNCTION: STRONGHOLDCRUSADER 0x004CD560
    void AICState ::aiRecruitSortieRangedUnits(int playerID)

    {

        UnitType unitType;

        int iVar1;

        uint _unitID;

        int iVar2;

        int _buildingID;

        AITypeInt _aiType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType != OpenSHC::AI::AIT_NULL) {

            iVar1 = (_aiType + ~OpenSHC::AI::AIT_NULL) * 0x2a4;

            iVar2 = *(int*)((int)this + iVar1 + 0x14c);

            /*
                  bug: missing != 0? */

            if (((((-1 < iVar2)
                      && (DAT_GameState::instance.playerDataArray[playerID].totalTroopsType6
                          < DAT_GameState::instance.playerDataArray[playerID].unknownCounter_01 / 2 + iVar2))
                     && (0 < DAT_GameState::instance.playerDataArray[playerID].idlePeasantsCount))
                    && ((DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0
                        && (unitType = *(UnitType*)((int)this + iVar1 + 0x150),
                            unitType != OpenSHC::Map::Units::UT_E_ENGINEER))))
                && ((unitType != OpenSHC::Map::Units::UT_E_LADDER && (unitType != OpenSHC::Map::Units::UT_TUNNELER)))) {

                if ((int)unitType < 0x46) {

                    _buildingID = DAT_GameState::instance.playerDataArray[playerID].barracks.id;

                }

                else {

                    _buildingID = DAT_GameState::instance.playerDataArray[playerID].mercenaryPost.id;
                }

                if (_buildingID != 0) {

                    if ((int)unitType < 0x46) {

                        _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::euroRecruit,
                            DAT_UnitsState::ptr)(unitType, (undefined4)((int)(_buildingID)), playerID, 0);

                    }

                    else {

                        _unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::nonEuroRecruit,
                            DAT_UnitsState::ptr)(unitType, (undefined4)((int)(_buildingID)), playerID, 0);
                    }

                    if (_unitID == 0) {

                        iVar2 = *(int*)((int)this + iVar1 + 0x9c);

                        if ((0 < iVar2) && (DAT_UnitsState::instance.DAT_EuroUnitAcquisitionFailReason == 2)) {

                            DAT_GameState::instance.playerDataArray[playerID]
                                .resourcesToAcquireArray[DAT_UnitsState::instance.DAT_EuroUnitRequiredResource] = iVar2;

                            return;
                        }

                    }

                    else {

                        DAT_UnitsState::instance.units[_unitID].aiUnitBehaviourType = 6;

                        iVar2 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::createTribeForUnitType, this)(
                            playerID, (int)((int)(166)));

                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                            _unitID, iVar2);
                    }
                }
            }
        }

        return;
    }

}
}
