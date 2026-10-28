#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041E650
    void Buildings::UpdateKillingPit()
    {
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        short const tileBuildingID
            = DAT_TileMapState::instance.BuildingLayer
                  [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentTilePositionAdjusted];
        if (tileBuildingID == 0 || DAT_CurrentBuildingID::instance != tileBuildingID) {
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                DAT_CurrentBuildingID::instance);
        }
        switch (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state) {
        case -2:
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
                = (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7) + 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            {
                int const frame
                    = DAT_BuildingDefinedData::instance.field417_0xa53c
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame == -1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer,
                        DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance);
                    return;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
                if (frame != 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame
                        + (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7)
                            * 4;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            return;
        case -1:
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
                = (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7) + 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = -2;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7) * 4 + 4;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            return;
        case 0:
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
                = (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7) + 9;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    DAT_CurrentBuildingID::instance);
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 1;
            }
            return;
        case 1:
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteID
                = (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7) + 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            {
                int const frame
                    = DAT_BuildingDefinedData::instance.field418_0xa5a4
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
                if (frame == -1) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].state = 2;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a = 0;
                    MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer,
                        DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance);
                    return;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame;
                if (frame != 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = frame
                        + (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 & 7)
                            * 4;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            return;
        case 2:
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a += 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field117_0x11a < 2000) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                    DAT_CurrentBuildingID::instance);
                return;
            }
            DAT_TileMapState::instance.showNoRubbleWhenDestroyingBuilding = 1;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                DAT_CurrentBuildingID::instance);
            return;
        }
    }

}
}
