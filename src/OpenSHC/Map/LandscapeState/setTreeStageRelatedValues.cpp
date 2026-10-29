#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2020
    void LandscapeState::setTreeStageRelatedValues(int treeID, int stage)
    {
        int const treeType = this->trees[treeID].treeType;
        undefined2 const woodChunks = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated1[treeType][stage];
        this->trees[treeID].stageRelated4 = woodChunks;
        this->trees[treeID].treeAdultHoodStageRelatedVisual3 = woodChunks;
        undefined2 const stageRelated1 = (undefined2)DAT_OrganismDefinedData::instance.TreeRelated2[treeType][stage];
        this->trees[treeID].stageRelated2 = stageRelated1;
        this->trees[treeID].stageRelated1 = stageRelated1;
    }

}
}
