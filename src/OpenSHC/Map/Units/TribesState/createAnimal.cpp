#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using AI::Tribes::AITribeType;
        using Commands::MappersEnum;
        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525BA0
        dword TribesState::createAnimal(MappersEnum animalType, uint x, uint y, int tile)
        {
            uint unitID;
            UnitType unitType = ((UnitType)0);
            int _rng2 = 0;
            dword tribeID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::createTribe, this)(0, 0);
            if ((int)tribeID <= 0) {
                return (dword)(0);
            }
            if (399 < x || 399 < y || *(char*)(y * 400 + 0x21aec98 + x) == '\0') {
                return (dword)(0);
            }
            int _tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            if (animalType == Commands::M_MAPPER_DEER) {
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x4a5014b1U)) {
                    return (dword)(0);
                }
                this->tribes[tribeID].tribeType = AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_SPEARMEN;
                unitType = Map::Units::UT_ANTELOPESHDEER;
                _rng2 = ((byte)SEC_RNG::instance.currentNumber2 & 3) + 9;
            } else if (animalType == Commands::M_MAPPER_LION) {
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x4a5014b1U)) {
                    return (dword)(0);
                }
                this->tribes[tribeID].tribeType = AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_PIKEMEN;
                unitType = Map::Units::UT_LIONSHWOLF;
                _rng2 = ((byte)SEC_RNG::instance.currentNumber2 & 1) + 3;
            } else if (animalType == Commands::M_MAPPER_RABBIT) {
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x4a5014b1U)) {
                    return (dword)(0);
                }
                this->tribes[tribeID].tribeType = AI::Tribes::AITT_SWORDSMEN | AI::Tribes::AITT_CROSSBOWMEN;
                unitType = Map::Units::UT_RABBIT;
                _rng2 = ((byte)SEC_RNG::instance.currentNumber2 & 7) + 0xe;
            } else if (animalType == Commands::M_MAPPER_CAMEL) {
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x4a5014b1U)) {
                    return (dword)(0);
                }
                this->tribes[tribeID].tribeType = ((AITribeType)0x10);
                unitType = Map::Units::UT_CAMELSHBEAR;
                _rng2 = ((byte)SEC_RNG::instance.currentNumber2 & 3) + 2;
            } else {
                if (animalType == Commands::M_MAPPER_CROW_SEAGULL) {
                    MACRO_CALL_MEMBER(Map::LandscapeState_Func::markNearbyTreesAsCrowTargets, DAT_LandscapeState::ptr)(
                        x, (int)(y));
                    return (dword)(0);
                }
                if (animalType == Commands::M_MAPPER_SEAGULL) {
                    if (!(DAT_TileMapState::instance.LogicLayer[_tile] & 1)) {
                        return (dword)(0);
                    }
                    MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::createSeagull, DAT_EntityState::ptr)(
                        x * 8, (int)(y * 8));
                    return (dword)(0);
                }
            }
            int iVar3 = 0;
            if (_rng2) {
                do {
                    unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        0, 0, (int)(x * 8), (int)(y * 8), tile, unitType);
                    if (unitID) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(unitID, (int)(tribeID));
                        DAT_UnitsState::instance.units[unitID].substate
                            = (byte)DAT_UnitsState::instance.units[unitID].fixedRng & 3;
                        if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                            byte bVar2 = (byte)DAT_UnitsState::instance.units[unitID].fixedRng & 7;
                            DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = bVar2;
                            if (bVar2 == 3) {
                                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                            } else if (bVar2 == 4) {
                                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                            } else if (bVar2 == 5) {
                                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                            } else if ((bVar2 == 6) || (bVar2 == 7)) {
                                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 2;
                            }
                            if (!iVar3) {
                                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 0;
                            } else if ((iVar3 == 1) || (iVar3 == 2)) {
                                DAT_UnitsState::instance.units[unitID].antelopeBasedRngValue = 1;
                            }
                        }
                        DAT_UnitsState::instance.units[unitID].disappearFadeAlphaCountdown = 0x20;
                    }
                    iVar3 = iVar3 + 1;
                } while (iVar3 < _rng2);
            }
            short sVar1 = this->tribes[tribeID].size;
            this->tribes[tribeID].herdMinSize = sVar1 / 2;
            if (animalType == Commands::M_MAPPER_LION) {
                this->tribes[tribeID].herdMaxSize = sVar1;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::storeLionXAndYInMapInfo, this)(
                    x, (undefined4)((int)(y)));
                return (dword)(tribeID);
            }
            this->tribes[tribeID].herdMaxSize = sVar1 * 2;
            if (animalType == Commands::M_MAPPER_DEER) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::storeDeerXAndYinMapInfo, this)(
                    x, (undefined4)((int)(y)));
                return (dword)(tribeID);
            }
            if (animalType == Commands::M_MAPPER_RABBIT) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setRabbitSpawnXY, this)(x, (undefined4)((int)(y)));
                return (dword)(tribeID);
            }
            if (animalType == Commands::M_MAPPER_CAMEL) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setCamelSpawnXY, this)(x, (undefined4)((int)(y)));
            }
            return (dword)(tribeID);
        }

    }
}
}
