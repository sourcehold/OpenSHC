#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433D00
    void DisplayElements::RenderBottomLeftDateDisplayElement(int posX, int posY, DWORD elementState)
    {
        BOOLEnum _menuStateNotZero;
        if ((!DAT_GameCore::instance.isTimeHalted)
            && (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
            _menuStateNotZero = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
            if ((!_menuStateNotZero)
                && ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                    || ((DAT_GameCore::instance.activeMenuTab.tabType
                            != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                            != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))))) {
                _menuStateNotZero = FALSE;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameState::instance.mapAndTime.month),
                    posX, posY, OpenSHC::Text::TTA_LEFT, 0, 18, _menuStateNotZero, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.mapAndTime.year, posX + 4, posY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
            }
        }
    }

}
}
