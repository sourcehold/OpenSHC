#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_ArmoryIconsPositionNudges.hpp"
#include "OpenSHC/Globals/DAT_ArmoryMenuResourceIcons.hpp"
#include "OpenSHC/Globals/DAT_ArmoryMenuResourceTypes.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004401A0
    void StatusMenus::RenderStatusMenu_Weapons()
    {
        int const x = DAT_MenuHandlerState::instance.x;
        int const y = DAT_MenuHandlerState::instance.y;
        int const top = y + 507;
        int const left = x + 105;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Weapons"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 7),
            x + 25, y + 467, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        // an icon and the stock of each of the eight weapons
        for (int good = 0; good < 8; ++good) {
            int const iconX = left + good * 52;
            int const amount
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .currentResources[DAT_ArmoryMenuResourceTypes::instance[good]];
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                DAT_ArmoryMenuResourceIcons::instance[good], DAT_ArmoryIconsPositionNudges::instance[good].x + iconX,
                DAT_ArmoryIconsPositionNudges::instance[good].y + top);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                amount, iconX + 12, top + 50, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        }
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
