#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AFA80
    void DisplayElements::RenderSomeMissionNumberUnkDisplayElement9(int posX, int posY, DWORD MissionNumPlus1Unk)
    {
        int const missionNumber = MissionNumPlus1Unk - 1;
        if (missionNumber == 0) {
            // "Mission : Defaults"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                s_Mission___Defaults_005a7788, posX, posY, OpenSHC::Text::TTA_LEFT, 33023, 0, 15, FALSE, 0);
            return;
        }
        // "Mission :"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
            s_Mission___005a777c, posX, posY, OpenSHC::Text::TTA_LEFT, 33023, 0, 15, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
            missionNumber, posX + 3, posY, OpenSHC::Text::TTA_LEFT, 33023, 0, 15, TRUE, 0);
    }

}
}
