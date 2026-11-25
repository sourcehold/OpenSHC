#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x004710A0
        void PencilRenderCore::drawBoxWithRoundedEdges(
            int left, int top, int right, int bottom, RoundedBoxEdgeRoundingLevel roundingLevel)
        {
            // How far each of the first roundingLevel rows is indented at both ends, outermost row first.
            int* rowIndents;
            switch (roundingLevel) {
            case OpenSHC::UI::Enums::RBERL_SLIGHT:
                rowIndents = DAT_TextInputDefinedData::instance.field_0x0;
                break;
            case OpenSHC::UI::Enums::RBERL_STRONG:
                rowIndents = DAT_TextInputDefinedData::instance.field_0x2c;
                break;
            default:
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            // Darkens the box instead of filling it: setupPencil's colour is not used.
            if (!MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                    left, top, right, bottom, 0)) {
                return;
            }
            // Too low for both rounded ends
            if (this->drawEndY - this->drawStartY < roundingLevel * 2) {
                return;
            }
            int const startX = this->drawStartX;
            int const endX = this->drawEndX;
            for (int row = 0; row < roundingLevel && this->currentHeight_0x2c >= 0; ++row) {
                this->drawStartX = rowIndents[row] + startX;
                this->drawEndX = endX - rowIndents[row];
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
                --this->currentHeight_0x2c;
                ++this->drawStartY;
            }
            this->drawStartX = startX;
            this->drawEndX = endX;
            for (; this->currentHeight_0x2c >= roundingLevel; --this->currentHeight_0x2c, ++this->drawStartY) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
            }
            for (int row = roundingLevel - 1; row >= 0 && this->currentHeight_0x2c >= 0; --row) {
                this->drawStartX = rowIndents[row] + startX;
                this->drawEndX = endX - rowIndents[row];
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
                --this->currentHeight_0x2c;
                ++this->drawStartY;
            }
        }

    }
}
}
