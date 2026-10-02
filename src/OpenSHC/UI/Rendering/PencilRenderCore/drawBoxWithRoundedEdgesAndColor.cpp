#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/RoundedBoxEdgeRoundingLevel.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextInputDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::UI::Enums::RoundedBoxEdgeRoundingLevel;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          Found no moment, where this one was used. It seems similar to "drawTextEntryBox?" --TheRedDaemon
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00470EE0
        void PencilRenderCore::drawBoxWithRoundedEdgesAndColor(
            int left, int top, int right, int bottom, ushort color, RoundedBoxEdgeRoundingLevel roundingLevel)
        {
            dword dVar1;
            dword dVar2;
            BOOLEnum _drawReady;
            TextInputDefinedData* pTVar3;
            int _currentIndexForX;
            if (roundingLevel == OpenSHC::UI::Enums::RBERL_SLIGHT) {
                pTVar3 = DAT_TextInputDefinedData::ptr;
            } else {
                if (roundingLevel != OpenSHC::UI::Enums::RBERL_STRONG) {}
                pTVar3 = (TextInputDefinedData*)0xb37ce8;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            _drawReady = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                left, top, right, bottom, color);
            dVar2 = this->drawEndX;
            dVar1 = this->drawStartX;
            if ((_drawReady != FALSE) && ((int)(roundingLevel * 2) <= (int)(this->drawEndY - this->drawStartY))) {
                _currentIndexForX = 0;
                this->drawStartX = dVar1;
                this->drawEndX = dVar2;
                if (0 < (int)roundingLevel) {
                    do {
                        this->drawStartX = dVar1;
                        this->drawEndX = dVar2;
                        if (this->currentHeight_0x2c < 0)
                            break;
                        this->drawStartX = pTVar3->field0_0x0[_currentIndexForX] + dVar1;
                        this->drawEndX = dVar2 - pTVar3->field0_0x0[_currentIndexForX];
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                        this->currentHeight_0x2c = this->currentHeight_0x2c + -1;
                        this->drawStartY = this->drawStartY + 1;
                        _currentIndexForX = _currentIndexForX + 1;
                        this->drawStartX = dVar1;
                        this->drawEndX = dVar2;
                    } while (_currentIndexForX < (int)roundingLevel);
                }
                for (; (int)roundingLevel <= this->currentHeight_0x2c;
                    this->currentHeight_0x2c = this->currentHeight_0x2c + -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                    this->drawStartY = this->drawStartY + 1;
                }
                for (;
                    (-1 < (int)(roundingLevel - ((RoundedBoxEdgeRoundingLevel)1)) && (-1 < this->currentHeight_0x2c));
                    this->currentHeight_0x2c = this->currentHeight_0x2c + -1) {
                    this->drawStartX = pTVar3->field0_0x0[roundingLevel - 1] + dVar1;
                    this->drawEndX = dVar2 - pTVar3->field0_0x0[roundingLevel - 1];
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHorizontalLine, this)();
                    this->drawStartY = this->drawStartY + 1;
                    roundingLevel = (RoundedBoxEdgeRoundingLevel)(roundingLevel - 1);
                }
            }
        }

    }
}
}
