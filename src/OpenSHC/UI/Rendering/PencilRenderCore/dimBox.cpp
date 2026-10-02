#include "../PencilRenderCore.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          "Dim" might not be the perfect word.   It reduces the color space by halving it.   --TheRedDameon
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00471050
        void PencilRenderCore::dimBox(int left, int top, int right, int bottom)
        {
            BOOLEnum _drawReady;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, this)();
            _drawReady = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencil, this)(
                left, top, right, bottom, 0);
            if (_drawReady != FALSE) {
                for (; -1 < this->currentHeight_0x2c; this->currentHeight_0x2c = this->currentHeight_0x2c + -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimHorizontalLine, this)();
                    this->drawStartY = this->drawStartY + 1;
                }
            }
        }

    }
}
}
