#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
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
        undefined4 BuildingsState::lightUpBuilding(int buildingID, int burnerPlayerID, int spareGrounds)
        {
            switch (this->buildings[buildingID].buildingType) {
            case BT_CAMPFIRE:
            case BT_PARADEGROUND:
            case BT_CAMPGROUND:
            case BT_PARADEGROUND2:
            case BT_PARADEGROUND3:
            case BT_PARADEGROUND4:
            case BT_PARADEGROUND5:
                // Grounds ignore the cooldown
                break;
            default:
                if (this->buildings[buildingID].cooldownTimer != 0) {
                    return 0;
                }
                break;
            }
            if (this->buildings[buildingID].fireDuration != 0) {
                return 1;
            }
            if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(
                    buildingID)
                == 0) {
                return 0;
            }
            // A player can only burn his own buildings with fire ballistae (flammability factor 4)
            int owner = this->buildings[buildingID].owner;
            if (owner == burnerPlayerID
                && MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingFlammabilityFactor, this)(
                       buildingID)
                    != 4) {
                return 0;
            }
            if (spareGrounds != 0) {
                switch (this->buildings[buildingID].buildingType) {
                case BT_CAMPFIRE:
                case BT_PARADEGROUND:
                case BT_CAMPGROUND:
                case BT_PARADEGROUND2:
                case BT_PARADEGROUND3:
                case BT_PARADEGROUND4:
                case BT_PARADEGROUND5:
                    return 1;
                }
            }
            this->buildings[buildingID].fireDuration = 1;
            this->buildings[buildingID].ifFireThenResponsiblePlayer = burnerPlayerID;
            if (owner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && (int)DAT_GameCore::instance.mapTimeInTicks
                        - DAT_GameState::instance.playerDataArray[owner].ignitionTime
                    > 800) {
                DAT_GameState::instance.playerDataArray[owner].ignitionTime = DAT_GameCore::instance.mapTimeInTicks;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    (char*)SFX_BuildingsAreOnFireSire);
            }

            // Set all tiles of the building on fire. The original does not check the tile count before the
            // first iteration.
            int x = (short)this->buildings[buildingID].x;
            int y = (short)this->buildings[buildingID].y;
            int t = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData,
                    DAT_TileMapState::ptr)(t, this->buildings[buildingID].widthOrHeight);
                int tile = DAT_ViewportRenderState::instance.translationMatrix[DAT_TileMapState::instance.buildingY + y]
                               .addXgetTile
                    + DAT_TileMapState::instance.buildingX + x;
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Entities::EntityState_Func::getFireEntityIDAtTile, DAT_EntityState::ptr)(tile)
                    == 0) {
                    uint entityID = MACRO_CALL(OpenSHC::Map::Entities_Func::IgniteFireAtMiniTile_Convenience)(
                        burnerPlayerID, (DAT_TileMapState::instance.buildingX + x) * 8,
                        (DAT_TileMapState::instance.buildingY + y) * 8,
                        DAT_TileMapState::instance.HeightLayer[tile] - 8, 2);
                    if (entityID != 0) {
                        DAT_EntityState::instance.entityArray[entityID].someTracker
                            = -(SEC_RNG::instance.currentNumber2 % 120);
                        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                    }
                }
                ++t;
            } while (t < DAT_TileMapState::instance.constructionTileCount);
            return 1;
        }

    }
}
}
