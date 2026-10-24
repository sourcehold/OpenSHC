#include "../BuildingsState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041C810
        BOOLEnum BuildingsState::lightUpBuilding(int buildingID, int burnerPlayerID, int spareGrounds)
        {
            int const type = this->buildings[buildingID].buildingType;
            switch (type) {
            case BT_CAMPFIRE:
            case BT_PARADEGROUND:
            case BT_CAMPGROUND:
            case BT_PARADEGROUND2:
            case BT_PARADEGROUND3:
            case BT_PARADEGROUND4:
            case BT_PARADEGROUND5:
                break;
            default:
                if (this->buildings[buildingID].cooldownTimer != 0) {
                    return FALSE;
                }
                break;
            }
            if (this->buildings[buildingID].fireDuration != 0) {
                return TRUE;
            }
            if (MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID) == 0) {
                return FALSE;
            }
            if (this->buildings[buildingID].owner == burnerPlayerID
                && MACRO_CALL_MEMBER(BuildingsState_Func::getBuildingFlammabilityFactor, this)(buildingID) != 4) {
                return FALSE;
            }
            if (spareGrounds != 0) {
                switch (type) {
                case BT_CAMPFIRE:
                case BT_PARADEGROUND:
                case BT_CAMPGROUND:
                case BT_PARADEGROUND2:
                case BT_PARADEGROUND3:
                case BT_PARADEGROUND4:
                case BT_PARADEGROUND5:
                    return TRUE;
                }
            }
            this->buildings[buildingID].fireDuration = 1;
            this->buildings[buildingID].ifFireThenResponsiblePlayer = burnerPlayerID;
            if (this->buildings[buildingID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && DAT_GameCore::instance.mapTimeInTicks
                        - DAT_GameState::instance.playerDataArray[this->buildings[buildingID].owner].ignitionTime
                    > 800) {
                DAT_GameState::instance.playerDataArray[this->buildings[buildingID].owner].ignitionTime
                    = DAT_GameCore::instance.mapTimeInTicks;
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_BuildingsAreOnFireSire);
            }
            int const x = this->buildings[buildingID].x;
            int const y = this->buildings[buildingID].y;
            int i = 0;
            do {
                MACRO_CALL_MEMBER(TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    i, this->buildings[buildingID].widthOrHeight);
                int const tile
                    = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.buildingY + y]
                          .addXgetTile
                    + DAT_TileMapState::instance.buildingX + x;
                if (MACRO_CALL_MEMBER(Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(tile)
                    == 0) {
                    int const entityID = MACRO_CALL(Entities_Func::IgniteFireAtMiniTile_Convenience)(burnerPlayerID,
                        (DAT_TileMapState::instance.buildingX + x) * 8, (DAT_TileMapState::instance.buildingY + y) * 8,
                        DAT_TileMapState::instance.HeightLayer[tile] - 8, 2);
                    if (entityID != 0) {
                        DAT_EntityState::instance.entityArray[entityID].someTracker
                            = -(SEC_RNG::instance.currentNumber2 % 120);
                        MACRO_CALL_MEMBER(Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                    }
                }
                ++i;
            } while (i < DAT_TileMapState::instance.constructionTileCount);
            return TRUE;
        }

    }
}
}
