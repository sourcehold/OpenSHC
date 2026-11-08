#include "../TileMapState.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WallAndPitchState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00512100
    void TileMapState::setupAllMapSections()
    {
        this->temporaryTerrainTypeIndex = 0;
        this->SEC_Section1052 = 0;
        this->SEC_Section1053 = 0;
        this->SEC_Section1054 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupTileMapSections, this)();
        DAT_WallAndPitchState::instance.countdown = 0;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setTileSystemMemoryLookupArrays,
            DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::tweakValidTilesToExcludeMapBorders,
            DAT_ViewportRenderState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::setupViewport, DAT_ViewportRenderState::ptr)(
            0, 0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY - 128);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupLogicalMapBorders, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateShowHiLayerOrResetChangedLayer, this)();

        // the border tiles get their own graphic, everything else the plain one
        for (int tile = 0; tile < MC_MAP_TILES_COUNT; tile++) {
            if (this->LogicLayer[tile] == L_BORDER) {
                this->GfxLayer[tile] = (ushort)GMFirstPictureIndex::instance[2];
            } else if (this->LogicLayer[tile] == L_BORDER_EDGE) {
                this->GfxLayer[tile] = (ushort)GMFirstPictureIndex::instance[2] + 1;
            } else {
                this->GfxLayer[tile] = (ushort)GMFirstPictureIndex::instance[2] + 2;
            }
        }

        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
            MC_MAP_TILES_COUNT, 1, this->PillarGFXLayer);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->HeightLayer), '\b', this->HeightLayer);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(this->DefaultHeightLayer), '\b', this->DefaultHeightLayer);
        DAT_PathFindingState::instance.searchGeneration = 1;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(DAT_TileMapState::instance.WalkLayer), '\0', DAT_TileMapState::instance.WalkLayer);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::setChangedLayerZeroBasedOn40x40Layer,
            DAT_PathFindingState::ptr)(0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateLogicalTileMapRelatedSections, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateGfxLayer, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateGFXLayers, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetMoatArray, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::resetPitchDitchArray, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::toggleFlatView, this)(0);
        DAT_TileMapState::instance.field_0x5548d0 = 0;
        DAT_TileMapState::instance.flatViewToggleValue2 = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::clearBuildings, DAT_BuildingsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::clearRocksAndTrees, DAT_LandscapeState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::resetWind, DAT_LandscapeState::ptr)();
        // the original calls this empty function as a member (object in ecx), of UnitsState here and of UnitsState
        // and LandscapeState below; the generated header has it as a global, so pass the object through a one-argument
        // __fastcall pointer
        ((void(__fastcall*)(OpenSHC::Map::Units::UnitsState*))MACRO_CALL(OpenSHC::Global_Func::DoNothing))(
            DAT_UnitsState::ptr);
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::clearAllUnits, DAT_UnitsState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearAllTribes, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::clearMapAndTimeAndPlayerData, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::resetVariousCountsAndStatisticsAndStartGoodsAndResources,
            DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::clearCurrentResourcesAndStrongWalls, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::initializeGameStateAfterMapLoad, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::fillWith0xFF, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::clearAnimalSpawnLocationsUnk, DAT_TribesState::ptr)();

        for (int tribe = 0; tribe < 1000; tribe++) {
            DAT_AICState::instance.tribeIDArray[tribe] = 0;
            DAT_AICState::instance.tribeUIDArray[tribe] = 0;
        }
        ((void(__fastcall*)(OpenSHC::Map::Units::UnitsState*))MACRO_CALL(OpenSHC::Global_Func::DoNothing))(
            DAT_UnitsState::ptr);
        ((void(__fastcall*)(OpenSHC::Map::LandscapeState*))MACRO_CALL(OpenSHC::Global_Func::DoNothing))(
            DAT_LandscapeState::ptr);
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Entities::EntityState_Func::clearEntityArrayAndSeagullArray, DAT_EntityState::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
        this->forceUpdateTextureTilemap = 1;
        this->forceUpdateGFXLayers = 1;
        this->forceUpdateMacroLayerFlag = 1;
        this->field_0x55487c = 200;
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageLayerForEachBuildingAtEachTile,
            DAT_PathFindingState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateSeparateAreaTileMap, DAT_PathFindingState::ptr)(1);
        this->forceUpdateMacroLayerFlag = 1;
        this->field_0x55487c = 500;
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, DAT_MinimapViewState::ptr)(0, 100);
        DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
        MACRO_CALL(OpenSHC::Map_Func::ResetSomeValuesFunctionUnk)();
    }

}
}
