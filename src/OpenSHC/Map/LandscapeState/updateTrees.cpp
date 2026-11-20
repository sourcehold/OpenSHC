#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_00ed31a0.hpp"
#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3D60
    void LandscapeState::updateTrees()
    {
        BOOLEnum updateStages = FALSE;
        uint stageRng = 0;
        DAT_GameState::instance.mapAndTime.burningTreeCount = 0;
        DAT_00ed31a0::instance = timeGetTime();
        if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 8) {
            this->maxTreeCount = 0;
            for (DAT_CurrentTreeID::instance = 1; (int)DAT_CurrentTreeID::instance < 2000;
                DAT_CurrentTreeID::instance += 1) {
                if (this->trees[DAT_CurrentTreeID::instance].state != 0) {
                    this->maxTreeCount = DAT_CurrentTreeID::instance + 1;
                }
            }
        }
        if (DAT_GameState::instance.gameTicksLoadBalancer % 8 == 4) {
            updateStages = TRUE;
            stageRng = (byte)SEC_RNG::instance.currentNumber2 & 0x3f;
        }
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_EDITOR) {
            updateStages = FALSE;
        }
        this->field_0x0 = 0;
        if (DAT_TileMapState::instance.refreshRelatedOne == 0 || DAT_TileMapState::instance.flatViewToggleValue1 != 0) {
            this->field_0x0 = 1;
        }
        DAT_GameState::instance.mapAndTime.newOrganisms = 0;
        this->DAT_TotalOrganisms = 0;
        for (DAT_CurrentTreeID::instance = 1; (int)DAT_CurrentTreeID::instance < this->maxTreeCount;
            DAT_CurrentTreeID::instance += 1) {
            switch (this->trees[DAT_CurrentTreeID::instance].state) {
            case 0:
                break;
            case 1:
                this->trees[DAT_CurrentTreeID::instance].state = 2;
                break;
            case 4:
                if (this->field_0x0 != 0) {
                    this->trees[DAT_CurrentTreeID::instance].animationFrameUnk = 0;
                } else {
                    this->trees[DAT_CurrentTreeID::instance].animationFrameUnk
                        = this->trees[DAT_CurrentTreeID::instance].animationFrame2Unk;
                }
                break;
            case 3:
                MACRO_CALL_MEMBER(LandscapeState_Func::removeTree, this)(DAT_CurrentTreeID::instance);
                break;
            case 2:
            default: {
                this->DAT_TotalOrganisms += 1;
                if ((this->trees[DAT_CurrentTreeID::instance].yPosition & 0x1f) >= this->wind.countdown) {
                    this->trees[DAT_CurrentTreeID::instance].one = this->wind.value;
                }
                if (this->trees[DAT_CurrentTreeID::instance].one == 3
                    && this->trees[DAT_CurrentTreeID::instance].zeroUpTo2 == 0) {
                    this->trees[DAT_CurrentTreeID::instance].zeroUpTo2 = 1;
                    this->trees[DAT_CurrentTreeID::instance].animationFrameIndex = 1;
                    this->trees[DAT_CurrentTreeID::instance].field_0x14 = DAT_00ed31a0::instance;
                }
                if ((int)(DAT_00ed31a0::instance - this->trees[DAT_CurrentTreeID::instance].field_0x14)
                    >= this->trees[DAT_CurrentTreeID::instance].treeTypeRelated2) {
                    this->trees[DAT_CurrentTreeID::instance].field_0x14 = DAT_00ed31a0::instance;
                    if (this->trees[DAT_CurrentTreeID::instance].one != 0) {
                        this->trees[DAT_CurrentTreeID::instance].animationFrameIndex += 1;
                    }
                }
                if (this->trees[DAT_CurrentTreeID::instance].rng200till300 != 0) {
                    this->trees[DAT_CurrentTreeID::instance].rng200till300 -= 1;
                }
                if (updateStages) {
                    // createTree inside updateTreeStage overwrites the current tree ID
                    int const savedTreeID = DAT_CurrentTreeID::instance;
                    MACRO_CALL_MEMBER(LandscapeState_Func::updateTreeStage, this)(
                        DAT_CurrentTreeID::instance, stageRng);
                    DAT_CurrentTreeID::instance = savedTreeID;
                }
                DAT_OrganismDefinedData::instance.UpdateTree[this->trees[DAT_CurrentTreeID::instance].treeType]();
                if (this->trees[DAT_CurrentTreeID::instance].field_0x98 != 0) {
                    if (this->trees[DAT_CurrentTreeID::instance].treeType != Trees::TT_APPLEUnk) {
                        DAT_GameState::instance.mapAndTime.burningTreeCount += 1;
                    }
                    if (this->trees[DAT_CurrentTreeID::instance].field_0x98 > 1) {
                        this->trees[DAT_CurrentTreeID::instance].field_0x98 -= 1;
                    }
                }
                break;
            }
            }
        }
    }

}
}
