#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    using Map::Trees::TreeTypeShort;


    // FUNCTION: STRONGHOLDCRUSADER 0x004F1CE0
    int LandscapeState::createTree(undefined4 x, undefined4 y, TreeType treeType, undefined4 size,
        int stageRelatedValue, undefined4 param_6, int stage)
    {
        undefined2 uVar1;
        short sVar2;
        undefined4 uVar3;
        Tree* _ptrState;
        uint uVar4;
        uint _tile;
        int _treeID;
        /*
         ***   Find a free tree slot   ***
         */
        _treeID = 1;
        _ptrState = &this->trees[1];
        do {
            if (!_ptrState->state)
                break;
            if (1999 < _treeID) {
                return 0;
            }
            _treeID = _treeID + 1;
            _ptrState = _ptrState + 0x4e;
        } while (_treeID < 2000);
        /*
         ***   Increment the max tree count on this map   ***
         */
        if (this->maxTreeCount <= _treeID) {
            this->maxTreeCount = _treeID + 1;
        }
        /*
         ***   Assign uid to tree   ***
         */
        this->trees[_treeID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
        /*
         ***   Set initial state of tree   ***
         */
        if (((int)treeType < 0x10) || (0x13 < (int)treeType)) {
            this->trees[_treeID].state = 1;
        } else {
            this->trees[_treeID].state = 4;
        }
        /*
         ***   Set (initial) values for tree   ***
         */
        this->trees[_treeID].size = (short)size;
        this->trees[_treeID].xPosition = (ushort)x;
        this->trees[_treeID].yPosition = (ushort)y;
        this->trees[_treeID].treeType = (TreeTypeShort)treeType;
        _tile
            = (int)(short)(ushort)x + DAT_ViewportRenderState::instance.translationMatrix[(short)(ushort)y].addXgetTile;
        this->trees[_treeID].microX = (ushort)x * 8 + 3;
        this->trees[_treeID].microY = (ushort)y * 8 + 3;
        this->trees[_treeID].tile = _tile;
        this->trees[_treeID].rng1 = DAT_TileMapState::instance.RandomLayer[_tile] & 0x7ff;
        this->trees[_treeID].appleTreeColorVariation = stageRelatedValue;
        this->trees[_treeID].param_6 = (short)param_6;
        this->trees[_treeID].treeTypeBasedValue1
            = (short)DAT_OrganismDefinedData::instance.TreeTypeBasedValueMapping[treeType];
        uVar1 = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated1[treeType][stage];
        this->trees[_treeID].stageRelated4 = uVar1;
        this->trees[_treeID].treeAdultHoodStageRelatedVisual3 = uVar1;
        uVar1 = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated2[treeType][stage];
        this->trees[_treeID].stageRelated2 = uVar1;
        this->trees[_treeID].stageRelated1 = uVar1;
        sVar2 = this->trees[_treeID].treeTypeBasedValue1;
        this->trees[_treeID].gmOriginX
            = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[sVar2].originX;
        this->trees[_treeID].gmOriginY
            = (short)DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[sVar2].originY;
        this->trees[_treeID].treeTypeRelated2 = DAT_OrganismDefinedData::instance.field28_0x854[treeType];
        this->trees[_treeID].zero = 0;
        this->trees[_treeID].animationFrameIndex = (byte)DAT_TileMapState::instance.RandomLayer[_tile] & 0x1f;
        this->trees[_treeID].one = 1;
        this->trees[_treeID].stage = stage;
        this->trees[_treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[treeType][stage];
        DAT_CurrentTreeID::instance = _treeID;
        /*
         ***   Set tree type dependent values   ***
         */
        switch (treeType) {
        case ((TreeType)1):
            uVar4 = this->trees[_treeID].rng1 & 0xf;
            this->trees[_treeID].appleTreeColorVariation = uVar4;
            if (0xe < uVar4) {
                this->trees[_treeID].appleTreeColorVariation = 4;
                break;
            }
            if (0xc < uVar4) {
                this->trees[_treeID].appleTreeColorVariation = 6;
                break;
            }
            if (10 < uVar4) {
                this->trees[_treeID].appleTreeColorVariation = 1;
                break;
            }
            if (uVar4 < 9)
                break;
            goto LAB_004f1fb5;
        case ((TreeType)2):
            uVar4 = this->trees[_treeID].rng1 & 0xf;
            this->trees[_treeID].appleTreeColorVariation = uVar4;
            if (8 < uVar4) {
                this->trees[_treeID].appleTreeColorVariation = 8;
            }
            break;
        case ((TreeType)3):
            this->trees[_treeID].appleTreeColorVariation = _treeID % 9;
            break;
        case ((TreeType)4):
            uVar4 = this->trees[_treeID].rng1 & 0xf;
            this->trees[_treeID].appleTreeColorVariation = uVar4;
            if (uVar4 < 0xf) {
                if (uVar4 < 0xd) {
                    if (uVar4 < 0xb) {
                        if (8 < uVar4) {
                            this->trees[_treeID].appleTreeColorVariation = 0;
                        }
                    } else {
                        this->trees[_treeID].appleTreeColorVariation = 1;
                    }
                } else {
                    this->trees[_treeID].appleTreeColorVariation = 6;
                }
            } else {
                this->trees[_treeID].appleTreeColorVariation = 4;
            }
            if (this->trees[_treeID].appleTreeColorVariation < 9)
                break;
            goto LAB_004f1fb5;
        case ((TreeType)5):
        case ((TreeType)10):
        case ((TreeType)0x10):
        case ((TreeType)0x11):
        case ((TreeType)0x12):
        case ((TreeType)0x13):
            this->trees[_treeID].stage = 4;
        LAB_004f1fb5:
            this->trees[_treeID].appleTreeColorVariation = 0;
            break;
        case ((TreeType)6):
            this->trees[_treeID].appleTreeColorVariation = 3;
            this->trees[_treeID].stage = 4;
            break;
        case ((TreeType)7):
            this->trees[_treeID].appleTreeColorVariation = 4;
            this->trees[_treeID].stage = 4;
            break;
        case ((TreeType)8):
            this->trees[_treeID].appleTreeColorVariation = 7;
            this->trees[_treeID].stage = 4;
            break;
        case ((TreeType)9):
            this->trees[_treeID].appleTreeColorVariation = 8;
            this->trees[_treeID].stage = 4;
        }
        uVar3 = this->field0_0x0;
        this->field0_0x0 = 0;
        /*
         ***   Update the tree state   ***
         */
        (*DAT_OrganismDefinedData::instance.UpdateTree[(short)this->trees[_treeID].treeType])();
        this->field0_0x0 = uVar3;
        return _treeID;
    }

}
}
