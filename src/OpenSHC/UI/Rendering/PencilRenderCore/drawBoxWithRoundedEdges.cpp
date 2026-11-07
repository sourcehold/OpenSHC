#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // Found no moment, where this one was used. --TheRedDaemon
        // FUNCTION: STRONGHOLDCRUSADER 0x004710A0
        void PencilRenderCore::drawBoxWithRoundedEdges(
            int left, int top, int right, int bottom, RoundedBoxEdgeRoundingLevel roundingLevel)
        {
            BOOLEnum _drawReady;
            TextInputDefinedData* pTVar3;
            int iVar4;
            if (roundingLevel == OpenSHC::UI::Enums::RBERL_SLIGHT) {
                pTVar3 = DAT_TextInputDefinedData::ptr;
            } else {
                if (roundingLevel != OpenSHC::UI::Enums::RBERL_STRONG) {}
                pTVar3 = (TextInputDefinedData*)0xb37ce8;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            _drawReady = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                left, top, right, bottom, 0);
            dword dVar2 = this->drawEndX;
            dword dVar1 = this->drawStartX;
            if (_drawReady && (int)(roundingLevel * 2) <= (int)(this->drawEndY - this->drawStartY)) {
                iVar4 = 0;
                this->drawStartX = dVar1;
                this->drawEndX = dVar2;
                if (0 < (int)roundingLevel) {
                    do {
                        this->drawStartX = dVar1;
                        this->drawEndX = dVar2;
                        if (this->currentHeight_0x2c < 0)
                            break;
                        this->drawStartX = pTVar3->field_0x0[iVar4] + dVar1;
                        this->drawEndX = dVar2 - pTVar3->field_0x0[iVar4];
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
                        --this->currentHeight_0x2c;
                        ++this->drawStartY;
                        ++iVar4;
                        this->drawStartX = dVar1;
                        this->drawEndX = dVar2;
                    } while (iVar4 < (int)roundingLevel);
                }
                for (; (int)roundingLevel <= this->currentHeight_0x2c;
                    this->currentHeight_0x2c = this->currentHeight_0x2c - 1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
                    ++this->drawStartY;
                }
                for (;
                    (0 <= (int)(roundingLevel - ((RoundedBoxEdgeRoundingLevel)1)) && (0 <= this->currentHeight_0x2c));
                    this->currentHeight_0x2c = this->currentHeight_0x2c - 1) {
                    this->drawStartX = pTVar3->field_0x0[roundingLevel - 1] + dVar1;
                    this->drawEndX = dVar2 - pTVar3->field_0x0[roundingLevel - 1];
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
                    ++this->drawStartY;
                    roundingLevel = (RoundedBoxEdgeRoundingLevel)(roundingLevel - 1);
                }
            }
        }

    }
}
}
