#include "../MissingResourceState.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Audio {

    // FUNCTION: STRONGHOLDCRUSADER 0x004761E0
    void MissingResourceState::renderResourceMissingText(int posX, int posY, dword textGroup, dword unusedUnk)
    {
        if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
            || DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SHIELD) {
            MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_FEEDBACK, textGroup),
                posX, posY + 148, Text::TTA_LEFT, 0x00c2f0eb, 0, 17, FALSE, 0);
            return;
        }

        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
            if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                posY -= 20;
            } else if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_MERCENARYPOST) {
                posY -= 20;
            } else {
                posY -= 10;
            }
        }

        int const iVar2 = MACRO_CALL_MEMBER(
            Text::FontSizeClass_Func::renderMultilineTextUnk, &DAT_TextManagerObject::instance.fontSizeClassArray[17])(
            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_FEEDBACK, textGroup),
            0, 0, 520, 0, 0, 1);

        MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_FEEDBACK, textGroup),
            posX, (posY - iVar2) + 32, 520, 0x00c2f0eb, 0, 17, 0);
        return;
    }

}
}
