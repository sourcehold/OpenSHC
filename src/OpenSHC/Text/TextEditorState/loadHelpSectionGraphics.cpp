#include "../TextEditorState.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D370
    void TextEditorState::loadHelpSectionGraphics()
    {
        DAT_TextureRenderCoreObject::instance.backwardsLoadedGfxIndex_0x16C850 = 99;
        DAT_TextureRenderCoreObject::instance.loadedGfxArray[99].backwardsOffsetInBuffer = 0;
        for (int i = 0; i < this->graphicFileCount; ++i) {
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxAtBufferEnd,
                DAT_TextureRenderCoreObject::ptr)(this->graphicFileNames[i]);
        }
    }

}
}
