#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052E960
        int UnitsState::euroRecruit(int unitType, undefined4 playersBarracksID, int playerID, int param_4)
        {
            /* archer is unittype 0x16 */
            this->euroUnitAcquisitionFailReason = 0;
            int _unitCost = DAT_TroopDefinedData::instance.MarketResourceCycleArray[unitType + -1];
            int _armourResource
                = DAT_UnitPropertiesDefinedData::instance.MELEE_DAMAGE[0x4e][unitType * 4 + 0x49];
            /* fixme: always 0 strange */
            int _unknownResource
                = DAT_UnitPropertiesDefinedData::instance.MELEE_DAMAGE[0x4e][unitType * 4 + 0x4a];
            /* bug: if unitType was 0, then it became -0x16, which results in requiring wood
               for creating this unit. This is nonsensical. It is wood because it will
               access memory DAT_MELEE_DAMAGE_MATRIX[78][72], which happens to be 2 */
            int _weaponResource
                = DAT_UnitPropertiesDefinedData::instance.MELEE_DAMAGE[0x4e][unitType * 4 + 0x48];
            int _horseResource = DAT_UnitPropertiesDefinedData::instance.MELEE_DAMAGE[0x4e][unitType * 4 + 0x4b];
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.skirmishTroopsCostGold == 0) {
                _unitCost = 0;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < _unitCost) {
                this->euroUnitAcquisitionFailReason = 1;
                /* if we do not have the gold resources */
                return 0;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[_weaponResource] < 1
                && _weaponResource > 0) {
                this->euroUnitAcquisitionFailReason = 2;
                this->euroUnitRequiredResource = (ResourceType)_weaponResource;
                /* we don't own the weapon required */
                return 0;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[_armourResource] < 1
                && _armourResource > 0) {
                this->euroUnitAcquisitionFailReason = 2;
                this->euroUnitRequiredResource = (ResourceType)_armourResource;
                /* if we do not own the required armor */
                return 0;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[_unknownResource] < 1
                && _unknownResource > 0) {
                this->euroUnitAcquisitionFailReason = 2;
                this->euroUnitRequiredResource = (ResourceType)_unknownResource;
                return 0;
            }
            if (_horseResource == -1) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Game::GameStateStructures_Func::recountStablesAndHorses, DAT_GameState::ptr)();
                if (DAT_GameState::instance.playerDataArray[playerID].availableHorses < 1) {
                    this->euroUnitAcquisitionFailReason = 4;
                    return 0;
                }
            }
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_PEASANT) {
                    continue;
                }
                if (this->units[unitID].owner != playerID) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk
                    && this->units[unitID].isDisappearingUnk != 0) {
                    continue;
                }
                if (param_4 != 0) {
                    return 1;
                }
                this->units[unitID].unitTypeToChangeInto = (UnitTypeShort)unitType;
                this->units[unitID].engineerManningSiegeStateRef_checkType = 1;
                this->units[unitID].isDisappearingUnk = 1;
                this->units[unitID].state_2 = 0;
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_JESTER_ROAM_TO;
                this->units[unitID].disappearFadeAlphaCountdown = 0;
                this->units[unitID].cachedState = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] -= _unitCost;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, (ResourceType)_weaponResource, 1, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, (ResourceType)_armourResource, 1, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceLoss,
                    DAT_BuildingsState::ptr)(playerID, (ResourceType)_unknownResource, 1, 0);
                if (_horseResource == -1) {
                    int _stableBuildingID = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::linkageBetweenHorseUnitAndStableUnk,
                        DAT_GameState::ptr)(playerID, unitID);
                    this->units[unitID].horseOriginStablesBuildingIndexUnk = (short)_stableBuildingID;
                    *(int*)&this->units[unitID].horseOriginStableIDUnk
                        = DAT_BuildingsState::instance.buildings[_stableBuildingID].uid;
                }
                DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[playerID] += 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::aiAssignNewUnitToTribe, DAT_TribesState::ptr)(
                    playerID, unitType, unitID);
                return unitID;
            }
            this->euroUnitAcquisitionFailReason = 3;
            /* units not allowed? over max amount units? */
            return 0;
        }

    }
}
}
