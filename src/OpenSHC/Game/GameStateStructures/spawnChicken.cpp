#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::States::UnitState;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004580C0
    void GameStateStructures::spawnChicken()
    {
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
            return;
        }
        for (int playerID = 1; playerID < 9; playerID++) {
            if ((this->playerDataArray[playerID].keep.id > 0) && (this->playerDataArray[playerID].campground.id > 0)) {
                int wantedChickens;
                if (this->playerDataArray[playerID].totalFood <= 0) {
                    wantedChickens = 0;
                } else if (this->playerDataArray[playerID].totalFood < 10) {
                    wantedChickens = 1;
                } else if (this->playerDataArray[playerID].totalFood < 20) {
                    wantedChickens = 2;
                } else if (this->playerDataArray[playerID].totalFood < 30) {
                    wantedChickens = 3;
                } else {
                    int populationTwice = this->playerDataArray[playerID].currentPopulation * 2;
                    if (populationTwice <= 1) {
                        populationTwice = 1;
                    }
                    wantedChickens = this->playerDataArray[playerID].totalFood / populationTwice + 3;
                    if (wantedChickens > 10) {
                        wantedChickens = 10;
                    }
                }
                if (DAT_GameCore::instance.unknownAlwaysZero02 != 0) {
                    wantedChickens = 100;
                }
                if (this->playerDataArray[playerID].chickenCount2 < wantedChickens) {
                    int buildingID = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::pickARandomBuildingIDOfTheseThreeTypes,
                        DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_BAKERY,
                        OpenSHC::Map::Buildings::BT_MILL, OpenSHC::Map::Buildings::BT_GRANARY);
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::buildingIsAccessible,
                            DAT_BuildingsState::ptr)(buildingID, 0)
                        != 0) {
                        int tile
                            = DAT_ViewportRenderState::instance
                                  .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                                  .addXgetTile
                            + DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
                        int chickenUnitID = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(playerID, playerID,
                            DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX * 8,
                            DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY * 8,
                            DAT_TileMapState::instance.HeightLayer[tile], OpenSHC::Map::Units::UT_CHICKEN);
                        if (chickenUnitID != 0) {
                            int chickenY = DAT_UnitsState::instance.units[chickenUnitID].y;
                            int chickenX = DAT_UnitsState::instance.units[chickenUnitID].x;
                            DAT_UnitsState::instance.units[chickenUnitID].isDisappearingUnk = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                chickenX, chickenY, OpenSHC::DE::SHCDE::FX_CHICKEN_START);
                        }
                    }
                } else if (wantedChickens < this->playerDataArray[playerID].chickenCount2) {
                    for (int unitID = 1; unitID < (int)DAT_UnitsState::instance.maxUnitCount; unitID++) {
                        if ((DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                            && (DAT_UnitsState::instance.units[unitID].owner == playerID)
                            && (DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_CHICKEN)) {
                            DAT_UnitsState::instance.units[unitID].state.generic
                                = OpenSHC::Map::Units::States::US_DISAPPEAR;
                            break;
                        }
                    }
                }
            }
        }
    }
}
}
