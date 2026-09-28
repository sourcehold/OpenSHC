
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515F40
    TileMapState* TileMapState::Constructor_TileMapState()
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupMovementDirectionTranslationMatrix, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupBuildingSizeIndexMapping, this)();
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setupTileMapSections, this)();
        this->editorActiveBrush = 7;
        this->refreshCertainTileMap = 2;
        this->counter1 = 0;
        this->mapperMax = FALSE;
        this->unknownZero_0x5548fc = 0;
        this->unknownZero_0x554904 = 0;
        this->unknownZero_0x554900 = 0;
        this->currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
        this->refreshRelatedOne = 1;
        this->field93_0x5548c8 = 0;
        this->refreshRelatedTwo = 0;
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
        this->forceUpdateTextureTilemap = 1;
        this->forceUpdateGFXLayers = 1;
        this->refreshCertainTileMap_old = 4;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        this->moatTileCount = 0;
        this->field122_0x554930 = 0;
        this->field78_0x55488c = 0x50;
        this->lastTime = timeGetTime();
        this->rockOrientation = 0;
        this->field80_0x554894 = 0;
        this->unknownTime_0x5549bc = timeGetTime();
        this->field161_0x5549c0 = 1;
        this->temporaryTerrainTypeIndex = 0;
        this->field188_0x554a14 = 0;
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameState::instance.mapAndTime.skirmishFogOfWar = 0;
        this->ptr_LogicLayer = this->LogicLayer;
        this->ptr_ChangedLayer = this->ChangedLayer;
        this->ptr_TerrainTypeTileMap = this->Logic2Layer;
        this->ptr_TerrainHeightTileMap = this->HeightLayer;
        this->ptr_PathConnectionLayer = this->PathConnectionLayer;
        this->ptr_OccupancyLayer = this->OccupancyLayer;
        this->ptr_DamageLayer = this->DamageLayer;
        this->ptr_MiscDisplayLayer = this->MiscDisplayLayer;
        this->ptr_MovementDirectionTranslationMatrix = this;
        this->ptr_SpecialAreasArray = this->specialAreasArray;
        this->ptr_AIZoneLayer = this->AIZoneLayer;
        this->currentMoatCount = 16000;
        this->maxPitchDitchCount = 4000;
        return this;
    }

}
}
