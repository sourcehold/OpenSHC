#include "../DeleteGameRecord.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9CC0
        void DeleteGameRecord::MenuModalRenderFunctionMenuModal_DeleteGameRecord(int x, int y, int width, int height)
        {
            if ((DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_FRENCH)
                && (DAT_TextManagerObject::instance.gameLanguage != OpenSHC::Text::GL_SPANISH)) {
                // "Delete Game Record?"
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                    DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 13, x, y, width, height);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner,
                DAT_PencilRenderCore::ptr)(x, y, width, height);
            int const centerX = width / 2 + x;
            // "Delete Game Record?"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 13),
                centerX, y + 27, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
        }

    }
}
}
