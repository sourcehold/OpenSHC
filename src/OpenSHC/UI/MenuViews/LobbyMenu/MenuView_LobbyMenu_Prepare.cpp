#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b95f6c.hpp"
#include "OpenSHC/Globals/INT_00b960f0.hpp"
#include "OpenSHC/Globals/INT_00b960fc.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00427320
        void LobbyMenu::MenuView_LobbyMenu_Prepare()
        {
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
                UI::Enums::MMT_NONE, FALSE);
            DAT_GameCore::instance.gameMode_2 = Game::GM_SKIRMISH_AND_MULTIPLAYER;
            DAT_GameCore::instance.currentTrailType = Game::TT_FIRST_EDITION;
            DAT_GameCore::instance.currentlyInGameUnk_0xa4 = FALSE;
            DAT_GameSynchronyState::instance.field_0x106ee4 = 0;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            // "frontend_combat3.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_frontend_combat3_tgx_005a2134);
            // "firefly-small.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_firefly_small_tgx_005a226c);
            // "table.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_table_tgx_005a2260);
            // "tslice1.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice1_tgx_005a2254);
            // "tslice2.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice2_tgx_005a2248);
            // "tslice3.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice3_tgx_005a223c);
            // "tslice4.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice4_tgx_005a2230);
            // "tslice5.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice5_tgx_005a2224);
            // "tslice6.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice6_tgx_005a2218);
            // "tslice7.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice7_tgx_005a220c);
            // "tslice8.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice8_tgx_005a2200);
            // "tslice1b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice1b_tgx_005a21f0);
            // "tslice2b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice2b_tgx_005a21e0);
            // "tslice3b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice3b_tgx_005a21d0);
            // "tslice4b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice4b_tgx_005a21c0);
            // "tslice5b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice5b_tgx_005a21b0);
            // "tslice6b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice6b_tgx_005a21a0);
            // "tslice7b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice7b_tgx_005a2190);
            // "tslice8b.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_tslice8b_tgx_005a2180);
            // "pick_opponent_normal.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_pick_opponent_normal_tgx_005a2164);
            // "pick_opponent_large.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_pick_opponent_large_tgx_005a214c);
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            int const borderHeight = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const borderWidth = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->xPosition = borderWidth;
            menu->yPosition = borderHeight;
            DAT_MenuHandlerState::instance.x = borderWidth;
            DAT_MenuHandlerState::instance.y = borderHeight;
            DAT_UserTextHandlerState::instance.allowUserTextInput = 0;
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                Text::TAIT_UNKNOWN);
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearTextAndCursor, DAT_UserTextHandlerState::ptr)();
            INT_00b960fc::instance = timeGetTime();
            INT_00b95f6c::instance = 0;
            INT_00b960f0::instance = INT_00b960fc::instance;
        }

    }
}
}
