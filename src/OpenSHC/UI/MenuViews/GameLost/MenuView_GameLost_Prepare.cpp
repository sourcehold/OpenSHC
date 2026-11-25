#include "../GameLost.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ed279c.hpp"
#include "OpenSHC/Globals/CHAR_00eb0e44.hpp"
#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00ed27b4.hpp"
#include "OpenSHC/Globals/INT_00ec082c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D55D0
        void GameLost::MenuView_GameLost_Prepare()
        {
            DAT_GameCore::instance.gameDuration = timeGetTime() - DAT_GameCore::instance.timeSum_2;
            BOOLEnum_00ed279c::instance = FALSE;
            DAT_FinalResultsOrderByColumn::instance = 0;
            DAT_00eb9af8::instance = 0;
            CHAR_00eb0e44::instance = 0;
            DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                INT_00ec082c::instance = 0;
            } else {
                DAT_GameCore::instance.activeMenuTab.tabType = OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX;
                INT_00ec082c::instance = 2;
            }
            MACRO_CALL(OpenSHC::Game::Skirmish_Func::StoreLocalTime)();
            DWORD_00ed27b4::instance = 0;
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setupLossMusic, DAT_SoundSystemState::ptr)();
            int const menuY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            int const menuX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            // currentMenu read once (read twice: quick_diff 0.9909 -> 0.9774)
            Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
            menu->xPosition = menuX;
            menu->yPosition = menuY;
            DAT_MenuHandlerState::instance.y = menuY;
            DAT_MenuHandlerState::instance.x = menuX;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0,
                0, DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                COL_BLACK::instance.shortValue);
            // the defeat video unless at the skirmish end screen: Arabian for missions 6 to 10 or an Arabian lord
            // four calls (one call after picking the file: quick_diff 0.9909 -> 0.7282)
            if (DAT_GameSynchronyState::instance.currentGameMode
                != OpenSHC::Game::GM_SKIRMISH_END_OF_GAME_SINGLE_PLAYER) {
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CAMPAIGN_MISSION) {
                    if (DAT_GameCore::instance.missionNumber1to20 >= 6
                        && DAT_GameCore::instance.missionNumber1to20 <= 10) {
                        // "arabian_lose.bik"
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, s_arabian_lose_bik_005aaf04, 0, 0,
                            DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                    } else {
                        // "crusader_lose.bik"
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                            DAT_BinkControlState::ptr)(0, s_crusader_lose_bik_005aaef0, 0, 0,
                            DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                    }
                } else if (MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::getLordTypeForPlayer,
                               DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    == 1) {
                    // "arabian_lose.bik"
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                        DAT_BinkControlState::ptr)(0, s_arabian_lose_bik_005aaf04, 0, 0,
                        DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                } else {
                    // "crusader_lose.bik"
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::playBINK,
                        DAT_BinkControlState::ptr)(0, s_crusader_lose_bik_005aaef0, 0, 0,
                        DAT_MenuHandlerState::instance.x + 80, DAT_MenuHandlerState::instance.y + 60, 2);
                }
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_MenuTextInputState::instance.DAT_SomeTextArrayIndex = OpenSHC::Text::TAIT_NINE__FILTER_B;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::MenuTextInputState_Func::clearAnyOtherModalDialogs, DAT_MenuTextInputState::ptr)();
        }

    }
}
}
