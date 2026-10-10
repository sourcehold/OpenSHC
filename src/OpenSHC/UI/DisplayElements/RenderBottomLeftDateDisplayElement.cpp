#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
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

    using DE::SHCDE::eTextSections;
    using Rendering::Colors::BGR24;
    using Text::TextAlignment;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::DisplayElementID;
    using UI::Enums::MenuViewType;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433D00
    void DisplayElements::RenderBottomLeftDateDisplayElement(int posX, int posY, DWORD elementState)
    {
        BOOLEnum _menuStateNotZero;
        char* _textAddress;
        TextAlignment alignment;
        BGR24 color;
        int fontSize;
        int blendStrength;
        int _xParam;
        int _yParam;
        if ((!DAT_GameCore::instance.isTimeHalted)
            && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
            _menuStateNotZero = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
            if (!_menuStateNotZero
                && (DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                    || ((DAT_GameCore::instance.activeMenuTab.tabType != UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        && (DAT_GameCore::instance.activeMenuTab.tabType != UI::Enums::BASMTT_MERCENARYPOST))))) {
                blendStrength = 0;
                _menuStateNotZero = FALSE;
                fontSize = 0x12;
                color = 0;
                alignment = Text::TTA_LEFT;
                _xParam = posX;
                _yParam = posY;
                _textAddress = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MONTHS, DAT_GameState::instance.mapAndTime.month);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    _textAddress, _xParam, _yParam, alignment, color, fontSize, _menuStateNotZero, blendStrength);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.mapAndTime.year, posX + 4, posY, Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            }
        }
    }

}
}
