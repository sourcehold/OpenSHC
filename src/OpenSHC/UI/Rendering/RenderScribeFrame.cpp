#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00433260
    void Rendering::RenderScribeFrame()
    {
        BOOLEnum _placementInfoShown;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_GameCore::instance.scribeAnimationFrame <= 0) {
            DAT_GameCore::instance.scribeAnimationFrame = 1;
        } else if (44 < DAT_GameCore::instance.scribeAnimationFrame) {
            DAT_GameCore::instance.scribeAnimationFrame = 44;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_SCRIBE, DAT_GameCore::instance.scribeAnimationFrame,
            DAT_MenuHandlerState::instance.x + 704, DAT_MenuHandlerState::instance.y + 399);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        if (DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU
            && DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_SIEGETENT_BATTERINGRAM
            && DAT_GameCore::instance.isTimeHalted == FALSE
            && (_placementInfoShown = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO),
                _placementInfoShown == FALSE)) {
            int const blendStrength = 0;
            BOOLEnum const withShadow = FALSE;
            int const fontSize = 18;
            uint const backgroundColor = 0;
            uint const foregroundColor = 0xb8eefb;
            TextAlignment const alignment = OpenSHC::Text::TTA_LEFT;
            int const yParam = DAT_WindowAndDirectDraw::instance.resolutionY - 20;
            int const xParam = DAT_MenuHandlerState::instance.x + 292;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameState::instance.mapAndTime.month),
                xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, withShadow, blendStrength);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_GameState::instance.mapAndTime.year, DAT_MenuHandlerState::instance.x + 296,
                DAT_WindowAndDirectDraw::instance.resolutionY - 20, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 18, TRUE, 0);
        }
    }

}
}
