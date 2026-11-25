#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        // FUNCTION: STRONGHOLDCRUSADER 0x00433BC0
        void RenderConnectAndPathLinkageInfoTextDisplayElement(int posX, int posY, DWORD tileType)
        {
            if (tileType == 1) {
                // "Connect"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(s_Connect_005a25e8, posX, posY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
            } else if (tileType == 2) {
                // "Path linkage"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(s_Path_linkage_005a25d8, posX, posY, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
            }
        }

    }
}
}
