#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2610
    void AICState::aiRecruitEngineerForOilDuty(int playerID)
    {
        BOOLEnum _hasTribes;
        int _newTribe;
        int _unitID;
        int _amount;
        int _oilSmelter;
        int _buildingUID;
        if (((((DAT_GameState::instance.playerDataArray[playerID].aiType != AITA_NULL)
                  && (_newTribe = DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id,
                      DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0))
                 && (29 < DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf]))
                && ((0 < _newTribe
                    && (DAT_BuildingsState::instance.buildings[_newTribe].buildingType
                        == Map::Buildings::BT_ENGINEERSGUILD))))
            && ((_oilSmelter = DAT_GameState::instance.playerDataArray[playerID].oilSmelter.id,
                0 < _oilSmelter
                    && ((DAT_BuildingsState::instance.buildings[_oilSmelter].buildingType
                            == Map::Buildings::BT_OILSMELTER
                        && (_amount
                            = DAT_GameState::instance.playerDataArray[playerID].aivUnitLocationSlotLocationCount[1] + 1,
                            1 < _amount)))))) {
            if ((DAT_BuildingsState::instance.buildings[_oilSmelter].resourcePitch < 1)
                && (DAT_GameState::instance.playerDataArray[playerID].currentResources[7] < 1)) {
                DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[7] = 4;
                return;
            }
            _hasTribes
                = MACRO_CALL(Global_Func::ChecksAndGenerateAITribesForPlayerIfNotExisting)(playerID, _amount, TRUE);
            if (_hasTribes != FALSE) {
                _newTribe = MACRO_CALL(Global_Func::ChecksAndGenerateAITribesForPlayerIfNotExisting)(
                    playerID, _amount, FALSE);
                _unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::nonEuroRecruit, DAT_UnitsState::ptr)(
                    Map::Units::UT_E_ENGINEER, DAT_GameState::instance.playerDataArray[playerID].engineersGuild.id,
                    playerID, 0);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    _unitID, _newTribe);
                if (_unitID != 0) {
                    DAT_UnitsState::instance.units[_unitID].engineerRelatedUnk = 1;
                    DAT_TribesState::instance.tribes[_newTribe].unitStance = Map::Units::Behavior::USE_DEFENSIVE;
                    _buildingUID = DAT_BuildingsState::instance.buildings[_oilSmelter].uid;
                    DAT_TribesState::instance.tribes[_newTribe].tribeType = Tribes::AITT_ENGINEERS;
                    DAT_TribesState::instance.tribes[_newTribe].tribeBehaviorType = Map::Units::STBT_0x41d;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        _newTribe, Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, _oilSmelter,
                        _buildingUID, 0);
                }
            }
        }
    }
}
}
