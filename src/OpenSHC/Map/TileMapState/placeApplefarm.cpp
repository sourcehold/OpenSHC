
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2.hpp"

#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::LogicHelpers::Logic1;
    using OpenSHC::Map::LogicHelpers::Logic2;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515740
    void TileMapState::placeApplefarm(
        int playerID, uint x, uint y, BuildingType buildingType, undefined4 param_5, int param_6, int* param_7)
    {
        int _buildingID;
        int iVar1;
        int local_4;
        int _buildingTileRef;
        local_4 = 0;
        _buildingID = MACRO_CALL_MEMBER(
            OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingData, DAT_BuildingsState::ptr)(
            playerID, x, y, (undefined4)((int)(param_7)), (int)(short)(undefined2)buildingType, 3, playerID, param_6);
        this->placedBuildingID = _buildingID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::markBuildingFootprintFlag, this)(x, (int)((int)(y)), 10);
        _buildingTileRef = DAT_TerrainDefinedData::instance.AppleFarmOffsets[1].y;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[0]
            = DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_TerrainDefinedData::instance.AppleFarmOffsets[0].y + y]
                  .addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[0].x + x;
        iVar1 = DAT_TerrainDefinedData::instance.AppleFarmOffsets[2].y + y;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[1]
            = DAT_ViewportRenderState::instance.translationMatrix[_buildingTileRef + y].addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[1].x + x;
        _buildingTileRef = DAT_TerrainDefinedData::instance.AppleFarmOffsets[3].y;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[2]
            = DAT_ViewportRenderState::instance.translationMatrix[iVar1].addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[2].x + x;
        iVar1 = DAT_TerrainDefinedData::instance.AppleFarmOffsets[4].y + y;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[3]
            = DAT_ViewportRenderState::instance.translationMatrix[_buildingTileRef + y].addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[3].x + x;
        _buildingTileRef = DAT_TerrainDefinedData::instance.AppleFarmOffsets[5].y;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[4]
            = DAT_ViewportRenderState::instance.translationMatrix[iVar1].addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[4].x + x;
        iVar1 = DAT_TerrainDefinedData::instance.AppleFarmOffsets[6].y + y;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[5]
            = DAT_ViewportRenderState::instance.translationMatrix[_buildingTileRef + y].addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[5].x + x;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[6]
            = DAT_ViewportRenderState::instance.translationMatrix[iVar1].addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[6].x + x;
        DAT_BuildingsState::instance.buildings[_buildingID].tileRefs[7]
            = DAT_ViewportRenderState::instance
                  .translationMatrix[DAT_TerrainDefinedData::instance.AppleFarmOffsets[7].y + y]
                  .addXgetTile
            + DAT_TerrainDefinedData::instance.AppleFarmOffsets[7].x + x;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(local_4, 3);
            param_6._0_2_ = (short)_buildingID;
            _buildingTileRef = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile + x
                + this->buildingX;
            this->HeightLayer[_buildingTileRef] = (byte)param_7;
            this->LogicLayer[_buildingTileRef] = this->LogicLayer[_buildingTileRef] | 0x400;
            this->BuildingLayer[_buildingTileRef] = (short)param_6;
            this->BuildingWasLayer[_buildingTileRef] = (undefined1)buildingType;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setTerrain, this)(playerID, _buildingTileRef,
                this->buildingY + y, 2, OpenSHC::Map::LogicHelpers::L_NONE, OpenSHC::Map::LogicHelpers::L2_THICK_SCRUB);
            local_4 = local_4 + 1;
            this->ChangedLayer[_buildingTileRef] = 2;
        } while (local_4 < this->constructionTileCount);
        /*
          &tileRefs[0] of buildingID
         */
        buildingType = _buildingID * 0x32c + OpenSHC::Map::Buildings::0xf986fc;
        /*
          apple tree relative coordinates
         */
        param_7 = &DAT_TerrainDefinedData::instance.AppleFarmOffsets[0].x;
        do {
            _buildingTileRef = *(int*)buildingType;
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetTileAndClearMoat, this)(_buildingTileRef);
            this->LogicLayer[_buildingTileRef] = this->LogicLayer[_buildingTileRef] | 0x4000000;
            this->ChangedLayer[_buildingTileRef] = 2;
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::placeAppleTree, DAT_LandscapeState::ptr)(
                _buildingID, (undefined4)((int)(*param_7 + x)), (undefined4)((int)(param_7[1] + y)));
            buildingType = buildingType + OpenSHC::Map::Buildings::BT_OXTETHER;
            param_7 = param_7 + 2;
        } while ((int)param_7 < 0xb49eb0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setMiscDisplayLayer, this)(_buildingID);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updatePathLinkagesForBuilding, this)(_buildingID);
        if (((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                && (DAT_GameState::instance.playerDataArray[playerID].availablePeasantsAtFire
                    < (int)DAT_BuildingsState::instance.buildings[_buildingID].buildingTypeBasedEmployeeCount))
            && ((DAT_GameState::instance.playerDataArray[playerID].populationCap
                    <= DAT_GameState::instance.playerDataArray[playerID].currentPopulation
                || (DAT_GameState::instance.playerDataArray[playerID].popularity < 5000)))) {
            MACRO_CALL_MEMBER(OpenSHC::UI::BottomLeftTextDisplayState_Func::setBottomLeftTextDisplayText,
                DAT_BottomLeftTextDisplayState::ptr)(1, 0x4d, 1, (TextMessageBLLookupStructUnion)0x0, 100, 6000);
        }
        return;
    }

}
}
