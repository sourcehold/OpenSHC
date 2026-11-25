#include "../NetworkSessions.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047C670
        void NetworkSessions::MenuItemRenderFunction_NetworkSessions_Buttons(int button, ...)
        {
            if (button == -10000) {
                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                return;
            }
            if (button == 10000) {
                // the second "Join" button, greyed out while no session is selected
                button = 8;
                if (DAT_GameSynchronyState::instance.scrollBarIndex == -1) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    // y and x go through locals as in the original: inlining them loses the match
                    int const textY = DAT_ButtonY::instance + 6;
                    int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                    // "Join"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 8),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F, 17, FALSE, 0);
                    return;
                }
            } else {
                // "No configuration needed", "Configuration is done later"
                if (button == 9 || button == 10) {
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                }
                if (button == -10) {
                    if (DAT_GameSynchronyState::instance.gameSpyArcadeAvailable != 0) {
                        MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    }
                    return;
                }
                if (button == -1000) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    return;
                }
            }
            if (button >= 0) {
                DAT_ButtonUnknownZero::instance = 0;
                // "Host" and "Join" over a modem, greyed out while no modem is found
                if ((button == 7 || button == 8)
                    && DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM
                    && DAT_GameSynchronyState::instance.modemScrollbarCount == 0) {
                    DAT_ButtonUnknownZero::instance = 1;
                    DAT_ButtonCurrentlyInteracting::instance = FALSE;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, button,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_7F7F7F, 17, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                    AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, button,
                        DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                        OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, button,
                    DAT_ButtonW::instance / 2 + DAT_ButtonX::instance, DAT_ButtonY::instance + 6,
                    OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE);
                return;
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (button == -1) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk,
                    DAT_PencilRenderCore::ptr)(0, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::renderUpDownButtonUnk, DAT_PencilRenderCore::ptr)(1, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
