#include "../../Map.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode;
    using Map::Trees::TreeTypeShort;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3960
    void LandscapeState::updateTreeStage(uint treeID, uint rng)
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
            if (DAT_GameCore::instance.isTimeHalted) {
                return;
            }
            if (MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)) {
                return;
            }
        }
        if ((this->trees[treeID].rng1 & 0x3fU) != rng) {
            return;
        }
        int const treeType = this->trees[treeID].treeType;
        if (treeType >= 5 && treeType <= 19) {
            return;
        }
        if (this->trees[treeID].zeroUpTo2 != 0) {
            return;
        }
        if (this->trees[treeID].stageRelated1 < (short)this->trees[treeID].stageRelated2) {
            return;
        }
        if (!this->field_0x4) {
            return;
        }
        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
            return;
        }
        this->trees[treeID].stageTracker = this->trees[treeID].stageTracker + 1;
        if (this->trees[treeID].stageTracker
            < DAT_OrganismDefinedData::instance.TreeStageLevels[treeType][this->trees[treeID].stage + 1]) {
            return;
        }
        this->trees[treeID].stage = this->trees[treeID].stage + 1;
        MACRO_CALL_MEMBER(Map::LandscapeState_Func::setTreeStageRelatedValues, this)(treeID, this->trees[treeID].stage);
        if (this->trees[treeID].stage >= 6) {
            this->trees[treeID].state = 3;
            return;
        }
        if (this->trees[treeID].stage < 4) {
            return;
        }
        DAT_GameState::instance.mapAndTime.treeSpreadCounter = DAT_GameState::instance.mapAndTime.treeSpreadCounter + 1;
        if (DAT_GameState::instance.mapAndTime.treeSpreadCounter
            > DAT_GameState::instance.mapAndTime.treeSpreadInterval) {
            DAT_GameState::instance.mapAndTime.treeSpreadCounter = 0;
            this->trees[treeID].stage = 5;
            this->trees[treeID].stageTracker
                = DAT_OrganismDefinedData::instance.TreeStageLevels[this->trees[treeID].treeType][5];
            return;
        }
        // set the spread counter to the lowest value for the tree type
        this->trees[treeID].stageTracker
            = DAT_OrganismDefinedData::instance.TreeStageLevels[this->trees[treeID].treeType][3];
        this->trees[treeID].stage = 3;
        DAT_GameState::instance.mapAndTime.newOrganismsValue2
            = DAT_GameState::instance.mapAndTime.newOrganismsValue2 + 1;
        if (!MACRO_CALL_MEMBER(Map::LandscapeState_Func::setupBabyTreeLocation, this)(
                treeID, this->trees[treeID].treeType, this->trees[treeID].xPosition, this->trees[treeID].yPosition)) {
            return;
        }
        int const size = MACRO_CALL_MEMBER(Map::LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage,
            DAT_LandscapeState::ptr)(this->trees[treeID].treeType, 0);
        int const newTreeID = MACRO_CALL_MEMBER(Map::LandscapeState_Func::createTree, DAT_LandscapeState::ptr)(
            DAT_PathFindingState::instance.ALG_ResultX, DAT_PathFindingState::instance.ALG_ResultY,
            (TreeType)this->trees[treeID].treeType, size, 0, 0, 0);
        DAT_TileMapState::instance.LogicLayer[DAT_PathFindingState::instance.ALG_ResultTile]
            = DAT_TileMapState::instance.LogicLayer[DAT_PathFindingState::instance.ALG_ResultTile] | 0x1000;
        DAT_TileMapState::instance.OrganismLayer[DAT_PathFindingState::instance.ALG_ResultTile] = (short)newTreeID;
        MACRO_CALL_MEMBER(Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(newTreeID, 0);
        MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(this->trees[newTreeID].yPosition, this->trees[newTreeID].tile);
        DAT_GameState::instance.mapAndTime.newOrganisms = DAT_GameState::instance.mapAndTime.newOrganisms + 1;
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
