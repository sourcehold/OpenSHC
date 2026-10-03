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

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
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
        if ((DAT_GameCore::instance.isTimeHalted == FALSE)
            && (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)) {
            _menuStateNotZero = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
            if ((_menuStateNotZero == FALSE)
                && ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
                    || ((DAT_GameCore::instance.activeMenuTab.tabType
                            != OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                        && (DAT_GameCore::instance.activeMenuTab.tabType
                            != OpenSHC::UI::Enums::BASMTT_MERCENARYPOST)))))) {
                blendStrength = 0;
                _menuStateNotZero = FALSE;
                fontSize = 0x12;
                color = 0;
                alignment = OpenSHC::Text::TTA_LEFT;
                _xParam = posX;
                _yParam = posY;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameState::instance.mapAndTime.month),
                    _xParam, _yParam, alignment, color, fontSize, _menuStateNotZero, blendStrength);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.mapAndTime.year, posX + 4, posY, OpenSHC::Text::TTA_LEFT, 0, 0x12, TRUE, 0);
            }
        }
    }

}
}
