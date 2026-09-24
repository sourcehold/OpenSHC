#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004224F0
        void BuildingsState::updateGateDrawBridgeOpenCloseLogic()
        {
            // Updates the gatehouse DAT_CurrentBuildingID: capturing by enemy troops and opening/closing for its owner
            int gateX = (short)this->buildings[DAT_CurrentBuildingID::instance].x;
            int gateY = (short)this->buildings[DAT_CurrentBuildingID::instance].y;
            short gateOwner = this->buildings[DAT_CurrentBuildingID::instance].owner;

            if (DAT_GameState::instance.gameTicksLoadBalancer % 10
                == (this->buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 + 5) % 10) {
                // Count the troops of every player on the gatehouse and look for its flag.
                // The original does not check the tile count before the first iteration.
                int strength[9];
                for (int p = 0; p < 9; ++p) {
                    strength[p] = 0;
                }
                int defender = 0;
                int attacker = 0;
                int flagEntityID = 0;
                int t = 0;
                do {
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                        DAT_TileMapState::ptr)(t, this->buildings[DAT_CurrentBuildingID::instance].widthOrHeight);
                    int tile = DAT_ViewportRenderState::instance
                                   .translationMatrix[DAT_TileMapState::instance.buildingY + gateY]
                                   .addXgetTile
                        + DAT_TileMapState::instance.buildingX + gateX;
                    for (int unitID = (short)DAT_TileMapState::instance.UnitLayer[tile]; unitID != 0;
                        unitID = (short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
                            continue;
                        }
                        int unitOwner = DAT_UnitsState::instance.units[unitID].owner;
                        strength[unitOwner] += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType, DAT_TroopValueState::ptr)(
                            (UnitType)(short)DAT_UnitsState::instance.units[unitID].unitType);
                        if (DAT_GameState::instance.mapAndTime
                                .playerTeams[this->buildings[DAT_CurrentBuildingID::instance].owner]
                            == DAT_GameState::instance.mapAndTime.playerTeams[unitOwner]) {
                            defender = this->buildings[DAT_CurrentBuildingID::instance].owner;
                        } else if (this->buildings[DAT_CurrentBuildingID::instance].owner != 0) {
                            attacker = unitOwner;
                        }
                    }
                    int entityID = DAT_TileMapState::instance.EntityLayer[tile];
                    if (entityID != 0) {
                        for (int n = 1; n < 10; ++n) {
                            if (DAT_EntityState::instance.entityArray[entityID].entityType
                                    == OpenSHC::Map::Entities::ET_FLAG_1
                                || DAT_EntityState::instance.entityArray[entityID].entityType
                                    == OpenSHC::Map::Entities::ET_FLAG_4
                                || DAT_EntityState::instance.entityArray[entityID].entityType
                                    == OpenSHC::Map::Entities::ET_FLAG_2
                                || DAT_EntityState::instance.entityArray[entityID].entityType
                                    == OpenSHC::Map::Entities::ET_FLAG_3) {
                                flagEntityID = entityID;
                            }
                            int next = DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                            if (entityID == next || next == 0) {
                                break;
                            }
                            entityID = next;
                        }
                    }
                    ++t;
                } while (t < DAT_TileMapState::instance.constructionTileCount);

                int flagColor = 0;
                int newController = 0;
                if (defender == 0) {
                    if (attacker != 0) {
                        // Undefended and attacked, the strongest player captures the gatehouse
                        if (flagEntityID == 0) {
                            int owner = this->buildings[DAT_CurrentBuildingID::instance].owner;
                            int height = DAT_TileMapState::instance
                                             .HeightLayer[this->buildings[DAT_CurrentBuildingID::instance]
                                                     .currentTilePositionAdjusted]
                                + 30;
                            int microY = (short)this->buildings[DAT_CurrentBuildingID::instance].y * 8;
                            int microX = (short)this->buildings[DAT_CurrentBuildingID::instance].x * 8;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                                DAT_EntityState::ptr)(0, owner, owner, microX, microY, height, microX, microY, height,
                                OpenSHC::Map::Entities::ET_FLAG_1, 0);
                        }
                        int strongest = this->buildings[DAT_CurrentBuildingID::instance].owner;
                        int strongestStrength = 0;
                        for (int p = 1; p < 9; ++p) {
                            if (strongestStrength < strength[p]) {
                                strongest = p;
                                strongestStrength = strength[p];
                            }
                        }
                        flagColor = strongest;
                        newController = strongest;
                    }
                } else if (this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 == 0 || attacker == 0) {
                    // Defended, the owner keeps or regains control
                    this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 = 0;
                    flagColor = defender;
                }

                if (flagColor != 0 && flagEntityID != 0) {
                    // Color all flags on the gatehouse. The original does not check the tile count before the first
                    // iteration.
                    int t2 = 0;
                    do {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                            DAT_TileMapState::ptr)(t2, this->buildings[DAT_CurrentBuildingID::instance].widthOrHeight);
                        int entityID
                            = DAT_TileMapState::instance
                                  .EntityLayer[DAT_ViewportRenderState::instance
                                                   .translationMatrix[DAT_TileMapState::instance.buildingY + gateY]
                                                   .addXgetTile
                                      + DAT_TileMapState::instance.buildingX + gateX];
                        if (entityID != 0) {
                            for (int n = 1; n < 10; ++n) {
                                if (DAT_EntityState::instance.entityArray[entityID].entityType
                                        == OpenSHC::Map::Entities::ET_FLAG_1
                                    || DAT_EntityState::instance.entityArray[entityID].entityType
                                        == OpenSHC::Map::Entities::ET_FLAG_4
                                    || DAT_EntityState::instance.entityArray[entityID].entityType
                                        == OpenSHC::Map::Entities::ET_FLAG_2
                                    || DAT_EntityState::instance.entityArray[entityID].entityType
                                        == OpenSHC::Map::Entities::ET_FLAG_3) {
                                    DAT_EntityState::instance.entityArray[entityID].colorUnk = flagColor;
                                }
                                int next = DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                                if (entityID == next || next == 0) {
                                    break;
                                }
                                entityID = next;
                            }
                        }
                        ++t2;
                    } while (t2 < DAT_TileMapState::instance.constructionTileCount);
                }
                if (newController != 0) {
                    if (this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 != newController
                        && this->buildings[DAT_CurrentBuildingID::instance].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            (char*)SFX_WeLostControlOfAGatehouse);
                    }
                    this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 = newController;
                    this->buildings[DAT_CurrentBuildingID::instance].gateState = 11;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(
                        DAT_CurrentBuildingID::instance, TRUE, FALSE);
                }
            }

            if (this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 != 0) {
                // Captured gatehouses are released once the owner is back in control
                if (this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6
                    == this->buildings[DAT_CurrentBuildingID::instance].owner) {
                    this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 = 0;
                }
                return;
            }

            if (this->buildings[DAT_CurrentBuildingID::instance].gateState2 > 0) {
                --this->buildings[DAT_CurrentBuildingID::instance].gateState2;
                if (DAT_GameState::instance.playerDataArray[gateOwner].enemies == 0) {
                    this->buildings[DAT_CurrentBuildingID::instance].gateState2 = 0;
                }
            }
            // Gatehouses of players without human or AI control are not operated
            if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[this->buildings[DAT_CurrentBuildingID::instance].owner]
                    == -1
                && (this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6 == 0
                    || DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[this->buildings[DAT_CurrentBuildingID::instance].field244_0x2c6]
                        == -1)
                && DAT_GameState::instance.playerDataArray[gateOwner].aiPlayerState == 0) {
                this->buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer = 0;
            }
            if (this->buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer < 0) {
                return;
            }
            if (this->buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer > 0) {
                --this->buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer;
                return;
            }
            if (DAT_GameState::instance.gameTicksLoadBalancer % 50
                != this->buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 % 50) {
                return;
            }

            // Close the gate when enemies come near, open it again when they are gone
            bool enemyNear = false;
            for (int i = 0; i < DAT_GameState::instance.playerDataArray[gateOwner].enemies; ++i) {
                short enemyID = DAT_GameState::instance.playerDataArray[gateOwner].enemyIDArray[i];
                if (DAT_UnitsState::instance.units[enemyID].uid
                        != DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[gateOwner][i]
                    || DAT_UnitsState::instance.units[enemyID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                    || DAT_UnitsState::instance.units[enemyID].isSelectable_OR_matchTime == 0) {
                    continue;
                }
                int distanceX;
                if (DAT_UnitsState::instance.units[enemyID].microXPosition < gateX * 8) {
                    distanceX = gateX * 8 - DAT_UnitsState::instance.units[enemyID].microXPosition;
                } else {
                    distanceX = DAT_UnitsState::instance.units[enemyID].microXPosition - gateX * 8;
                }
                int distance;
                if (DAT_UnitsState::instance.units[enemyID].microYPosition < gateY * 8) {
                    distance = gateY * 8 - DAT_UnitsState::instance.units[enemyID].microYPosition;
                } else {
                    distance = DAT_UnitsState::instance.units[enemyID].microYPosition - gateY * 8;
                }
                if (distance <= distanceX) {
                    distance = distanceX;
                }
                if (distance < 200) {
                    enemyNear = true;
                    break;
                }
            }
            if (enemyNear) {
                this->buildings[DAT_CurrentBuildingID::instance].gateState2 = 1200;
                if (this->buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 0) {
                    this->buildings[DAT_CurrentBuildingID::instance].gateState = 10;
                    this->buildings[DAT_CurrentBuildingID::instance].field235_0x2b6 = 10;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(
                        DAT_CurrentBuildingID::instance, FALSE, FALSE);
                }
            } else if (this->buildings[DAT_CurrentBuildingID::instance].gateState2 == 0
                && this->buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 2) {
                this->buildings[DAT_CurrentBuildingID::instance].gateState = 11;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    this)(DAT_CurrentBuildingID::instance, TRUE, FALSE);
            }
            if (this->buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    this)(DAT_CurrentBuildingID::instance, TRUE, FALSE);
                return;
            }
            if (this->buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    this)(DAT_CurrentBuildingID::instance, FALSE, FALSE);
            }
        }

    }
}
}
