#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;

        // FUNCTION: STRONGHOLDCRUSADER 0x00468C50
        void PencilRenderCore::setupPencilSurface()
        {
            Ghidra::ushort* surface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
            if (this->surfaceTarget == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                surface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
            }
            this->surfacePtr = surface;

            if (this->surfaceTarget != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                this->horizontalByteSize = 8112;
                return;
            }
            this->horizontalByteSize = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
        }

    }
}
}
