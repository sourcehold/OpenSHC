#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00433BC0
    void DisplayElements::RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType)
    {
        if (tileType == 1) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Connect", posX, posY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0, 0x11, FALSE, 0);
        }
        if (tileType == 2) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Path linkage", posX, posY, OpenSHC::Text::TTA_LEFT, 0x80ff, 0, 0x11, FALSE, 0);
        }
    }

}
}
