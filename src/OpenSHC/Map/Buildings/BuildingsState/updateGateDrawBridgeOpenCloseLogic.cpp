#include "../BuildingsState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
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
            // Updates the gatehouse DAT_CurrentBuildingID: capturing by enemy troops and opening/closing for its owner.
            // DAT_CurrentBuildingID is not reloaded after applyGateOrDrawbridgeOpenCloseChange, which needs /GL
            // (cmake/compiler-flags-gl.txt) together with the callee chain findParticularBuilding and
            // setupBuildingEntrancesOffset.
            // Matching note: these stay declared up front; moving the zeroed ones (0.97) or gateMicroX/Y (0.89) to
            // their first use loses the match, as the original stores them all before the tick test.
            int const gateX = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x;
            int const gateMicroX = gateX * 8;
            int const gateY = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y;
            int const gateMicroY = gateY * 8;
            int t = 0;
            int defender = 0;
            int attacker = 0;
            int flagEntityID = 0;
            int const gateOwner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;

            if (DAT_GameState::instance.gameTicksLoadBalancer % 10
                == (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 + 5) % 10) {
                // Count the troops of every player on the gatehouse and look for its flag.
                // The original does not check the tile count before the first iteration.
                int strength[9];
                for (int p = 0; p < 9; ++p) {
                    strength[p] = 0;
                }
                do {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                        t, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].widthOrHeight);
                    int const tile = DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_TileMapState::instance.buildingY + gateY]
                                         .addXgetTile
                        + DAT_TileMapState::instance.buildingX + gateX;
                    for (int unitID = DAT_TileMapState::instance.UnitLayer[tile]; unitID != 0;
                        unitID = DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile) {
                        if (DAT_UnitsState::instance.units[unitID].isSelectable_OR_matchTime == 0) {
                            continue;
                        }
                        int const unitOwner = DAT_UnitsState::instance.units[unitID].owner;
                        strength[unitOwner]
                            += MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::getValueOfTroopType,
                                DAT_TroopValueState::ptr)((UnitType)DAT_UnitsState::instance.units[unitID].unitType);
                        if (DAT_GameState::instance.mapAndTime.playerTeams
                                [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                            == DAT_GameState::instance.mapAndTime.playerTeams[unitOwner]) {
                            defender = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
                        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner != 0) {
                            attacker = unitOwner;
                        }
                    }
                    int entityID = DAT_TileMapState::instance.EntityLayer[tile];
                    // Matching note: written as for (int n = 1; entityID != 0 && n < 10; ++n) this drops to 0.83
                    int n = 0;
                    while (entityID != 0 && ++n < 10) {
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
                        if (entityID == DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID) {
                            break;
                        }
                        entityID = DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                    }
                    ++t;
                } while (t < DAT_TileMapState::instance.constructionTileCount);

                int flagColor = 0;
                int newController = 0;
                if (defender != 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6 == 0
                        || attacker == 0) {
                        // Defended, the owner keeps or regains control
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6 = 0;
                        flagColor = defender;
                        newController = 0;
                    }
                } else if (attacker != 0) {
                    // Undefended and attacked, the strongest player captures the gatehouse
                    if (flagEntityID == 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x * 8,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y * 8,
                            DAT_TileMapState::instance
                                    .HeightLayer[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                            .currentTilePositionAdjusted]
                                + 30,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x * 8,
                            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y * 8,
                            DAT_TileMapState::instance
                                    .HeightLayer[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance]
                                            .currentTilePositionAdjusted]
                                + 30,
                            OpenSHC::Map::Entities::ET_FLAG_1, 0);
                    }
                    int strongest = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
                    int strongestStrength = 0;
                    for (int p = 1; p < 9; ++p) {
                        if (strength[p] > strongestStrength) {
                            strongestStrength = strength[p];
                            strongest = p;
                        }
                    }
                    flagColor = strongest;
                    newController = strongest;
                }

                if (flagColor != 0 && flagEntityID != 0) {
                    // Color all flags on the gatehouse. The original does not check the tile count before the first
                    // iteration.
                    int t2 = 0;
                    do {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                            t2, DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].widthOrHeight);
                        int entityID
                            = DAT_TileMapState::instance
                                  .EntityLayer[DAT_ViewportRenderState::instance
                                                   .translationMatrix[DAT_TileMapState::instance.buildingY + gateY]
                                                   .addXgetTile
                                      + DAT_TileMapState::instance.buildingX + gateX];
                        int n = 0;
                        while (entityID != 0 && ++n < 10) {
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
                            if (entityID == DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID) {
                                break;
                            }
                            entityID = DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                        }
                        ++t2;
                    } while (t2 < DAT_TileMapState::instance.constructionTileCount);
                }
                if (newController != 0) {
                    if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6
                            != newController
                        && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                            SFX_WeLostControlOfAGatehouse);
                    }
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6 = newController;
                    // gateState 11 requests opening, 10 closing
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState = 11;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(
                        DAT_CurrentBuildingID::instance, TRUE, FALSE);
                }
            }

            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6 != 0) {
                // Captured gatehouses are released once the owner is back in control
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6
                    == DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6 = 0;
                }
                return;
            }

            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState2 > 0) {
                --DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState2;
                if (DAT_GameState::instance.playerDataArray[gateOwner].enemies == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState2 = 0;
                }
            }
            // Gatehouses of players without human or AI control are not operated
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner]
                    == -1
                && (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6 == 0
                    || DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                            [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2c6]
                        == -1)
                && DAT_GameState::instance.playerDataArray[gateOwner].aiPlayerState == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer = 0;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer < 0) {
                return;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer > 0) {
                --DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateCloseOpenTimer;
                return;
            }
            if (DAT_GameState::instance.gameTicksLoadBalancer % 50
                != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 % 50) {
                return;
            }

            // Close the gate when enemies come near, open it again when they are gone. pathLinkageRelated2 is 0 for an
            // open gate and 2 for a closed one.
            bool enemyNear = false;
            for (int i = 0; i < DAT_GameState::instance.playerDataArray[gateOwner].enemies; ++i) {
                int const enemyID = DAT_GameState::instance.playerDataArray[gateOwner].enemyIDArray[i];
                if (DAT_UnitsState::instance.units[enemyID].uid
                        != DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[gateOwner][i]
                    || DAT_UnitsState::instance.units[enemyID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                    || DAT_UnitsState::instance.units[enemyID].isSelectable_OR_matchTime == 0) {
                    continue;
                }
                int distanceX;
                if (gateMicroX > DAT_UnitsState::instance.units[enemyID].microXPosition) {
                    distanceX = gateMicroX - DAT_UnitsState::instance.units[enemyID].microXPosition;
                } else {
                    distanceX = DAT_UnitsState::instance.units[enemyID].microXPosition - gateMicroX;
                }
                int distanceY;
                if (gateMicroY > DAT_UnitsState::instance.units[enemyID].microYPosition) {
                    distanceY = gateMicroY - DAT_UnitsState::instance.units[enemyID].microYPosition;
                } else {
                    distanceY = DAT_UnitsState::instance.units[enemyID].microYPosition - gateMicroY;
                }
                int const distance = distanceX >= distanceY ? distanceX : distanceY;
                if (distance < 200) {
                    enemyNear = true;
                    break;
                }
            }
            if (enemyNear) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState2 = 1200;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState = 10;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field_0x2b6 = 10;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange, this)(
                        DAT_CurrentBuildingID::instance, FALSE, FALSE);
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState2 == 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState = 11;
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    this)(DAT_CurrentBuildingID::instance, TRUE, FALSE);
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    this)(DAT_CurrentBuildingID::instance, TRUE, FALSE);
                return;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::applyGateOrDrawbridgeOpenCloseChange,
                    this)(DAT_CurrentBuildingID::instance, FALSE, FALSE);
            }
        }

    }
}
}
