#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/AI/Tribes/AIVUnitTypeTribeArrayOffset.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Game::GameMode;
        using Map::Units::SomeTribeBehaviorType;
        using Map::Units::UnitType;
        using Map::Units::States::UnitState;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x005254C0
        BOOLEnum TribesState::addUnitToNewTribe(uint unitID)
        {
            int _tribeID;
            if (DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY) {
                return FALSE;
            }
            int _playerID = (int)DAT_UnitsState::instance.units[unitID].owner;
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] == -1
                && ((_tribeID = (int)DAT_UnitsState::instance.units[unitID].tribeID,
                        _tribeID < 1 || (this->tribes[_tribeID].uid != DAT_UnitsState::instance.units[unitID].tribeUID))
                    || (this->tribes[_tribeID].tribeState == 0))) {
                int _newTribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(_playerID, 0);
                if (0 < _newTribeID) {
                    UnitTypeShort _unitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (_unitType == Map::Units::UT_E_ARCHER) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_ARCHERS;
                    } else if (_unitType == Map::Units::UT_E_XBOW) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_CROSSBOWMEN;
                    } else if (_unitType == Map::Units::UT_E_SPEAR) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_SPEARMEN;
                    } else if (_unitType == Map::Units::UT_E_PIKE) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_PIKEMEN;
                    } else if (_unitType == Map::Units::UT_E_MACE) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_MACEMEN;
                    } else if (_unitType == Map::Units::UT_E_SWORD) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_SWORDSMEN;
                    } else if (_unitType == Map::Units::UT_E_KNIGHT) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_KNIGHTS;
                    } else if (_unitType == Map::Units::UT_E_LADDER) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_LADDERMEN;
                    } else if (_unitType == Map::Units::UT_E_ENGINEER) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_ENGINEERS;
                    } else if (_unitType == Map::Units::UT_HOPSFARMER) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_LADDERMEN;
                    } else if (_unitType == Map::Units::UT_TUNNELER) {
                        this->tribes[_newTribeID].tribeType = AI::Tribes::AITT_TUNNELERS;
                    } else if (_unitType == Map::Units::UT_A_ARCHER) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x19);
                    } else if (_unitType == Map::Units::UT_A_SLAVE) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x1a);
                    } else if (_unitType == Map::Units::UT_A_SLINGER) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x1b);
                    } else if (_unitType == Map::Units::UT_A_ASSASSIN) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x1c);
                    } else if (_unitType == Map::Units::UT_A_HARCHER) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x1d);
                    } else if (_unitType == Map::Units::UT_A_SWORDSMAN) {
                        this->tribes[_newTribeID].tribeType
                            = (AI::Tribes::AITribeTypeShort)AI::Tribes::OFFSET_CROSSBOWMAN;
                    } else if (_unitType == Map::Units::UT_A_FIRETHROWER) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x1f);
                    } else if (_unitType == Map::Units::UT_S_FBALLISTA) {
                        this->tribes[_newTribeID].tribeType = ((AITribeType)0x18);
                    }
                    this->tribes[_newTribeID].someIndex = 1;
                    this->tribes[_newTribeID].attackWave = (short)DAT_TroopValueState::instance.attackInfo.inv_count;
                    _unitType = DAT_UnitsState::instance.units[unitID].unitType;
                    if (_unitType == Map::Units::UT_E_ENGINEER) {
                        if (DAT_UnitsState::instance.units[unitID].state.generic
                            == Map::Units::States::US_STAND_UPUnk) {
                            this->tribes[_newTribeID].tribeBehaviorType
                                = Map::Units::STBT_0x410_SIEGE_EQUIPMENT_CONSTRUCTION;
                        }
                    } else if ((_unitType == Map::Units::UT_TUNNELER)
                        && (DAT_UnitsState::instance.units[unitID].state.generic
                            == Map::Units::States::US_LOOK_AROUNDUnk)) {
                        this->tribes[_newTribeID].tribeBehaviorType = Map::Units::STBT_0x415;
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, _newTribeID);
                    return TRUE;
                }
            }
            return FALSE;
        }

    }
}
}
