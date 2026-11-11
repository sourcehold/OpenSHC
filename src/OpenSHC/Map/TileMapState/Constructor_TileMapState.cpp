#include "../TileMapState.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

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
        this->editorSnapToMode = 0;
        this->editorAffectType = 0;
        this->unknownZero_0x554900 = 0;
        this->currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
        this->refreshRelatedOne = 1;
        this->disableElevationRendering = 0;
        this->refreshRelatedTwo = 0;
        this->forceUpdateLogicalAndMiscDisplayLayers = TRUE;
        this->forceUpdateTextureTilemap = TRUE;
        this->forceUpdateGFXLayers = TRUE;
        this->refreshCertainTileMap_old = 4;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        this->moatTileCount = 0;
        this->skipPlacementCheck = 0;
        this->gateOrientationVariant = 80;
        this->lastTime = timeGetTime();
        this->rockOrientation = 0;
        this->editorRockType = 0;
        this->cursorAnimationTime = timeGetTime();
        this->cursorOverlayAnimationFrame = 1;
        this->temporaryTerrainTypeIndex = 0;
        this->skipPlacementFailChecks = 0;
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameState::instance.mapAndTime.skirmishFogOfWar = 0;
        this->ptr_LogicLayer = this->LogicLayer;
        this->ptr_TerrainTypeTileMap = this->Logic2Layer;
        this->ptr_TerrainHeightTileMap = this->HeightLayer;
        this->ptr_ChangedLayer = this->ChangedLayer;
        this->ptr_OccupancyLayer = this->OccupancyLayer;
        this->ptr_DamageLayer = this->DamageLayer;
        this->ptr_PathConnectionLayer = this->PathConnectionLayer;
        this->ptr_MovementDirectionTranslationMatrix = this;
        this->ptr_SpecialAreasArray = this->specialAreasArray;
        this->ptr_AIZoneLayer = this->AIZoneLayer;
        this->ptr_MiscDisplayLayer = this->MiscDisplayLayer;
        this->currentMoatCount = 16000;
        this->maxPitchDitchCount = 4000;
        return this;
    }

}
}
