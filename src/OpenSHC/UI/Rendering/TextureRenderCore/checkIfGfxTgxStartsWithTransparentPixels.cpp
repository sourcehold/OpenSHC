// ============================================================================
// Program   : Stronghold Crusader.exe
// Namespace : _HoldStrong::UI::Rendering::TextureRenderCore
// Function  : checkIfGfxTgxStartsWithTransparentPixels
// Address   : 004549c0
// Signature : BOOLEnum __thiscall checkIfGfxTgxStartsWithTransparentPixels(TextureRenderCore * this, int gfxIndex)
// ============================================================================

#include "OpenSHC/IO/Graphics/GfxRef.hpp"
#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        /* decompilerscript: committed: 2025-01-30 21:57:43.216000 */
        // FUNCTION: STRONGHOLDCRUSADER 0x004549C0
        BOOLEnum TextureRenderCore::checkIfGfxTgxStartsWithTransparentPixels(int gfxIndex)

        {
            // Match: 40% - Best achievable with current compiler
            // Differences in register allocation (original uses edx/dl, recomp uses eax/cl)
            // Disabling optimizations produces worse match (21.4%) due to frame pointer overhead
            int index = gfxIndex;
            GfxRef& ref = this->loadedGfxArray[index];
            return (uint)((*(byte*)(ref.offsetInBuffer + 8 + (int)this->gmAndGfxImageDataBuffer)
                              & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER)
                == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
        }

    }
}
}
