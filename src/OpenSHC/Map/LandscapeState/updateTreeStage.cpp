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
        int* piVar1;
        BOOLEnum BVar2;
        int _stage;
        int iVar3;
        undefined4 size;
        int _treeID;
        int _treeType;
        TreeTypeShort _treeType_2;
        if ((((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY)
                 || ((!DAT_GameCore::instance.isTimeHalted
                     && (BVar2 = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                             UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO),
                         !BVar2))))
                && (((this->trees[treeID].rng1 & 0x3fU) == rng
                    && (((_treeType = (int)(short)this->trees[treeID].treeType, _treeType < 5 || (0x13 < _treeType))
                        && (this->trees[treeID].zeroUpTo2 == 0))))))
            && ((((short)this->trees[treeID].stageRelated2 <= (short)this->trees[treeID].stageRelated1
                     && (this->field1_0x4))
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)))) {
            piVar1 = &this->trees[treeID].stageTracker;
            *piVar1 = *piVar1 + 1;
            iVar3 = this->trees[treeID].stage;
            if (DAT_OrganismDefinedData::instance.TreeStageLevels[_treeType][iVar3 + 1]
                <= this->trees[treeID].stageTracker) {
                _stage = iVar3 + 1;
                this->trees[treeID].stage = _stage;
                MACRO_CALL_MEMBER(Map::LandscapeState_Func::setTreeStageRelatedValues, this)(treeID, _stage);
                iVar3 = this->trees[treeID].stage;
                if (5 < iVar3) {
                    this->trees[treeID].state = 3;
                }
                if (3 < iVar3) {
                    DAT_GameState::instance.mapAndTime.treeSpreadCounter
                        = DAT_GameState::instance.mapAndTime.treeSpreadCounter + 1;
                    if (DAT_GameState::instance.mapAndTime.treeSpreadInterval
                        < DAT_GameState::instance.mapAndTime.treeSpreadCounter) {
                        DAT_GameState::instance.mapAndTime.treeSpreadCounter = 0;
                        _treeType_2 = this->trees[treeID].treeType;
                        this->trees[treeID].stage = 5;
                        this->trees[treeID].stageTracker
                            = DAT_OrganismDefinedData::instance.TreeStageLevels[(short)_treeType_2][5];
                    }
                    /*
                      set spreadcounter to lowest value for tree type?
                     */
                    this->trees[treeID].stageTracker
                        = DAT_OrganismDefinedData::instance.TreeStageLevels[(short)this->trees[treeID].treeType][3];
                    this->trees[treeID].stage = 3;
                    DAT_GameState::instance.mapAndTime.newOrganismsValue2
                        = DAT_GameState::instance.mapAndTime.newOrganismsValue2 + 1;
                    iVar3 = MACRO_CALL_MEMBER(Map::LandscapeState_Func::setupBabyTreeLocation, this)(treeID,
                        (int)((int)((short)this->trees[treeID].treeType)),
                        (uint)((int)((int)(short)this->trees[treeID].xPosition)),
                        (uint)((int)((int)(short)this->trees[treeID].yPosition)));
                    if (iVar3) {
                        size = MACRO_CALL_MEMBER(
                            Map::LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage, this)(
                            (int)(short)this->trees[treeID].treeType, 0);
                        _treeID = MACRO_CALL_MEMBER(Map::LandscapeState_Func::createTree, this)(
                            DAT_PathFindingState::instance.ALG_ResultX,
                            (undefined4)((int)(DAT_PathFindingState::instance.ALG_ResultY)),
                            (TreeType)(short)this->trees[treeID].treeType, (undefined4)((int)(size)), 0, 0, 0);
                        iVar3 = DAT_PathFindingState::instance.ALG_ResultTile;
                        DAT_TileMapState::instance.LogicLayer[DAT_PathFindingState::instance.ALG_ResultTile]
                            = DAT_TileMapState::instance.LogicLayer[DAT_PathFindingState::instance.ALG_ResultTile]
                            | 0x1000;
                        DAT_TileMapState::instance.OrganismLayer[iVar3] = (short)_treeID;
                        MACRO_CALL_MEMBER(Map::TileMapState_Func::applyTreeBrushToLogicalLayer,
                            DAT_TileMapState::ptr)(_treeID, 0);
                        MACRO_CALL_MEMBER(
                            Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                            DAT_PathFindingState::ptr)(
                            (int)(short)this->trees[_treeID].yPosition, (int)((int)(this->trees[_treeID].tile)));
                        DAT_GameState::instance.mapAndTime.newOrganisms
                            = DAT_GameState::instance.mapAndTime.newOrganisms + 1;
                        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                    }
                }
            }
        }
    }

}
}
