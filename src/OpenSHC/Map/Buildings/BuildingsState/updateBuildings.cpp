#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AIVState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00422E20
        void BuildingsState::updateBuildings()
        {
            this->isFirstTickInLoop = (BOOLEnum)(DAT_GameCore::instance.performedGameTicksThisLoop == 0);

            // Every 10 ticks the number of used building slots is recomputed
            if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 5) {
                this->maxBuildingsCount = 0;
                for (DAT_CurrentBuildingID::instance = 1; DAT_CurrentBuildingID::instance < 2000;
                    ++DAT_CurrentBuildingID::instance) {
                    if (this->buildings[DAT_CurrentBuildingID::instance].logicalState != 0) {
                        this->maxBuildingsCount = DAT_CurrentBuildingID::instance + 1;
                    }
                }
            }

            this->structCount = 0;
            for (int p = 0; p < 9; ++p) {
                DAT_AIVState::instance.mapExtraInfo.playerTotalKillingPits[p] = 0;
            }
            for (int p = 0; p < 9; ++p) {
                DAT_GameState::instance.playerDataArray[p].dogCageCount = 0;
            }
            this->field1_0x4 = 0;

            // The update functions of the building types use DAT_CurrentBuildingID
            for (DAT_CurrentBuildingID::instance = 1; DAT_CurrentBuildingID::instance < this->maxBuildingsCount;
                ++DAT_CurrentBuildingID::instance) {
                if (this->buildings[DAT_CurrentBuildingID::instance].logicalState == 0) {
                    continue;
                }
                ++this->structCount;
                if (this->buildings[DAT_CurrentBuildingID::instance].logicalState == BLS_INITIAL) {
                    this->buildings[DAT_CurrentBuildingID::instance].logicalState = BLS_NORMAL;
                    continue;
                }
                if (this->buildings[DAT_CurrentBuildingID::instance].logicalState == BLS_REMOVE) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::deleteBuilding, this)(
                        DAT_CurrentBuildingID::instance);
                    continue;
                }

                if (this->buildings[DAT_CurrentBuildingID::instance].buildingType == BT_KILLINGPIT) {
                    ++DAT_AIVState::instance.mapExtraInfo
                          .playerTotalKillingPits[this->buildings[DAT_CurrentBuildingID::instance].owner];
                }

                // Advance the animation
                if (this->buildings[DAT_CurrentBuildingID::instance].renderAnimation != 0
                    && ++this->buildings[DAT_CurrentBuildingID::instance].animStateCounter
                            - this->buildings[DAT_CurrentBuildingID::instance].animStateCounterTracker
                        >= this->buildings[DAT_CurrentBuildingID::instance].animAdvanceThrottle) {
                    this->buildings[DAT_CurrentBuildingID::instance].animStateCounterTracker
                        = this->buildings[DAT_CurrentBuildingID::instance].animStateCounter;
                    this->buildings[DAT_CurrentBuildingID::instance].animationIndex
                        += this->buildings[DAT_CurrentBuildingID::instance].animationIncrement;
                    this->buildings[DAT_CurrentBuildingID::instance].animationActive = 1;
                } else {
                    this->buildings[DAT_CurrentBuildingID::instance].animationActive = 0;
                }

                ++this->buildings[DAT_CurrentBuildingID::instance].recruitTimer;
                if (this->buildings[DAT_CurrentBuildingID::instance].recruitTimer >= 100) {
                    this->buildings[DAT_CurrentBuildingID::instance].recruitTimer = 0;
                }
                ++this->buildings[DAT_CurrentBuildingID::instance].timeAlive;
                int owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
                if (this->buildings[DAT_CurrentBuildingID::instance].idleTimerUnk != 0) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
                        && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0) {
                        --this->buildings[DAT_CurrentBuildingID::instance].idleTimerUnk;
                    } else {
                        this->buildings[DAT_CurrentBuildingID::instance].idleTimerUnk = 0;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateNeededEmployeeCount, this)(
                    DAT_CurrentBuildingID::instance);
                if (this->buildings[DAT_CurrentBuildingID::instance].field127_0x194 > 0) {
                    --this->buildings[DAT_CurrentBuildingID::instance].field127_0x194;
                }
                DAT_GameState::instance.playerDataArray[owner].populationCap
                    += this->buildings[DAT_CurrentBuildingID::instance].numberOfPopulationProvided;

                // Building type specific update
                DAT_BuildingDefinedData::instance
                    .BuildingUpdateFunctions[this->buildings[DAT_CurrentBuildingID::instance].buildingType]();
                if (this->buildings[DAT_CurrentBuildingID::instance].logicalState == 0) {
                    continue;
                }

                if (DAT_TileMapState::instance.refreshRelatedTwo != 0
                    && this->buildings[DAT_CurrentBuildingID::instance].gfxOffset != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer,
                        DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance);
                }

                // Burning buildings take damage, grounds only burn for a while
                if (this->buildings[DAT_CurrentBuildingID::instance].fireDuration != 0) {
                    if (DAT_GameState::instance.gameTicksLoadBalancer % 20 == 5) {
                        int damage = 1;
                        switch (this->buildings[DAT_CurrentBuildingID::instance].buildingType) {
                        case BT_HOVEL:
                        case BT_WOODCUTTERSHUT:
                        case BT_HUNTERSHUT:
                        case BT_WHEATFARM:
                        case BT_HOPFARM:
                        case BT_APPLEFARM:
                        case BT_DAIRYFARM:
                            damage = 4;
                            break;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(
                            this->buildings[DAT_CurrentBuildingID::instance].currentTilePositionAdjusted,
                            (short)this->buildings[DAT_CurrentBuildingID::instance].x,
                            (short)this->buildings[DAT_CurrentBuildingID::instance].y, damage, 0,
                            (short)this->buildings[DAT_CurrentBuildingID::instance].ifFireThenResponsiblePlayer, FALSE,
                            0);
                        int buildingType = this->buildings[DAT_CurrentBuildingID::instance].buildingType;
                        if (buildingType == BT_PARADEGROUND
                            || (buildingType >= BT_CAMPGROUND && buildingType <= BT_PARADEGROUND5)) {
                            --this->buildings[DAT_CurrentBuildingID::instance].currentHealth;
                            if (this->buildings[DAT_CurrentBuildingID::instance].currentHealth < 490) {
                                this->buildings[DAT_CurrentBuildingID::instance].currentHealth = 500;
                                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::extinguishBuildingFire,
                                    this)(DAT_CurrentBuildingID::instance);
                                this->buildings[DAT_CurrentBuildingID::instance].fireDuration = -1;
                            }
                        }
                    }
                    ++this->buildings[DAT_CurrentBuildingID::instance].fireDuration;
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::spawnRandomFireEffectOnBuilding,
                        this)(DAT_CurrentBuildingID::instance,
                        (short)this->buildings[DAT_CurrentBuildingID::instance].ifFireThenResponsiblePlayer);
                }

                // Siege engines of the AI are removed after a while
                if (this->buildings[DAT_CurrentBuildingID::instance].unknownSiegeTentRelated01 == 2
                    && this->buildings[DAT_CurrentBuildingID::instance].attackWave == 0
                    && (this->buildings[DAT_CurrentBuildingID::instance].buildingType == BT_FIREBALLISTA
                        || this->buildings[DAT_CurrentBuildingID::instance].buildingType == BT_CATAPULT)
                    && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0
                    && (int)this->buildings[DAT_CurrentBuildingID::instance].timeAlive > 2400) {
                    this->buildings[DAT_CurrentBuildingID::instance].logicalState = BLS_REMOVE;
                }
                if (this->buildings[DAT_CurrentBuildingID::instance].cooldownTimer != 0) {
                    --this->buildings[DAT_CurrentBuildingID::instance].cooldownTimer;
                }
                for (int i = 0; i < 4; ++i) {
                    this->buildings[DAT_CurrentBuildingID::instance].workers[i] = 0;
                }
            }

            this->field14_0x18e024 = 0;
            this->field34_0x18e074 = 0;
            this->unknownCountdown01 = 2000 - this->structCount;
            if ((int)this->field4_0x10 > 0) {
                --this->field4_0x10;
            }
        }

    }
}
}
