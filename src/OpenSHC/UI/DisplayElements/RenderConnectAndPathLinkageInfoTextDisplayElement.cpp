#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433BC0
    void DisplayElements::RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType)
    {
        if (tileType == 1) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Connect", posX, posY, Text::TTA_LEFT, 0x80ff, 0, 0x11, FALSE, 0);
        }
        if (tileType == 2) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                "Path linkage", posX, posY, Text::TTA_LEFT, 0x80ff, 0, 0x11, FALSE, 0);
        }
    }

}
}
