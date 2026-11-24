#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Rendering/Enums/ViewportConstants.hpp"

#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E26D0
    void ViewportRenderState::scheduleUnitForBatchedRendering(
        int unitIDOrStatus, int drawX, int drawY, int imageID, int blendStrength, int gmID, int batchesEarlier)
    {
        int batch;
        if (batchesEarlier == 1) {
            batch = this->unitBatchedRenderCounterUntil6 + 4;
            if (Enums::VC_UNIT_BATCH_COUNT < batch) {
                batch -= Enums::VC_UNIT_BATCH_COUNT;
            }
        } else if (batchesEarlier == 2) {
            batch = this->unitBatchedRenderCounterUntil6 + 3;
            if (Enums::VC_UNIT_BATCH_COUNT < batch) {
                batch -= Enums::VC_UNIT_BATCH_COUNT;
            }
        } else {
            batch = this->unitBatchedRenderCounterUntil6;
        }

        switch (batch) {
        case 1:
            if (this->unitRender1 < countof(this->unitBatch1)) {
                this->unitBatch1[this->unitRender1].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch1[this->unitRender1].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch1[this->unitRender1].spriteID = DAT_CurrentlyRenderedSpriteID::instance;
                this->unitBatch1[this->unitRender1].drawX = drawX;
                this->unitBatch1[this->unitRender1].drawY = drawY;
                this->unitBatch1[this->unitRender1].imageID = imageID;
                this->unitBatch1[this->unitRender1].blendStrength = blendStrength;
                this->unitBatch1[this->unitRender1].gmID = gmID;
                this->unitRender1++;
            }
            break;
        case 2:
            if (this->unitRender2 < countof(this->unitBatch2)) {
                this->unitBatch2[this->unitRender2].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch2[this->unitRender2].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch2[this->unitRender2].spriteID = DAT_CurrentlyRenderedSpriteID::instance;
                this->unitBatch2[this->unitRender2].drawX = drawX;
                this->unitBatch2[this->unitRender2].drawY = drawY;
                this->unitBatch2[this->unitRender2].imageID = imageID;
                this->unitBatch2[this->unitRender2].blendStrength = blendStrength;
                this->unitBatch2[this->unitRender2].gmID = gmID;
                this->unitRender2++;
            }
            break;
        case 3:
            if (this->unitRender3 < countof(this->unitBatch3)) {
                this->unitBatch3[this->unitRender3].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch3[this->unitRender3].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch3[this->unitRender3].spriteID = DAT_CurrentlyRenderedSpriteID::instance;
                this->unitBatch3[this->unitRender3].drawX = drawX;
                this->unitBatch3[this->unitRender3].drawY = drawY;
                this->unitBatch3[this->unitRender3].imageID = imageID;
                this->unitBatch3[this->unitRender3].blendStrength = blendStrength;
                this->unitBatch3[this->unitRender3].gmID = gmID;
                this->unitRender3++;
            }
            break;
        case 4:
            if (this->unitRender4 < countof(this->unitBatch4)) {
                this->unitBatch4[this->unitRender4].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch4[this->unitRender4].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch4[this->unitRender4].spriteID = DAT_CurrentlyRenderedSpriteID::instance;
                this->unitBatch4[this->unitRender4].drawX = drawX;
                this->unitBatch4[this->unitRender4].drawY = drawY;
                this->unitBatch4[this->unitRender4].imageID = imageID;
                this->unitBatch4[this->unitRender4].blendStrength = blendStrength;
                this->unitBatch4[this->unitRender4].gmID = gmID;
                this->unitRender4++;
            }
            break;
        case 5:
            if (this->unitRender5 < countof(this->unitBatch5)) {
                this->unitBatch5[this->unitRender5].unitIDOrStatus = unitIDOrStatus;
                this->unitBatch5[this->unitRender5].ownerColor = DAT_RenderedUnitOwner::instance;
                this->unitBatch5[this->unitRender5].spriteID = DAT_CurrentlyRenderedSpriteID::instance;
                this->unitBatch5[this->unitRender5].drawX = drawX;
                this->unitBatch5[this->unitRender5].drawY = drawY;
                this->unitBatch5[this->unitRender5].imageID = imageID;
                this->unitBatch5[this->unitRender5].blendStrength = blendStrength;
                this->unitBatch5[this->unitRender5].gmID = gmID;
                this->unitRender5++;
            }
            break;
        }
    }

}
}
