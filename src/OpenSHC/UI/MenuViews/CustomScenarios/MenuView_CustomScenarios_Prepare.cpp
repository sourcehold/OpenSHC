#include "../CustomScenarios.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/INT_00b95abc.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00425EA0
        void CustomScenarios::MenuView_CustomScenarios_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            // "frontend_builder.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_frontend_builder_tgx_005a2084);
            // "frontend_builder2.tgx"
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                s_frontend_builder2_tgx_005a206c);
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            DWORD const now = timeGetTime();
            // the four buttons start their animation 1600 ms apart
            for (int i = 0; i < 4; ++i) {
                DAT_UIButtonDefinedData::instance.ButtonGmDataArray[364 + i].stateTransitionTimeBaseUnk_0x18
                    = now - (3 - i) * 1600;
            }
            INT_00b95abc::instance = -1;
            DAT_MenuTextInputState::instance.dialogResult = 0;
            DAT_GameCore::instance.missionNumber1to20 = 0;
            DAT_GameCore::instance.mapLoadedForEditor = FALSE;
            DAT_GameCore::instance.gameMode_2 = Game::GM_EDITOR;
            INT_00b960e4::instance = FALSE;
            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
            }
            DAT_GameSynchronyState::instance
                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
            DAT_UnknownGFXIndex::instance = 0;
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
        }

    }
}
}
