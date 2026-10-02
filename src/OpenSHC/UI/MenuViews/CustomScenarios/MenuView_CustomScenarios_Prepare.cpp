#include "../CustomScenarios.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"

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

        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00425EA0
        void CustomScenarios::MenuView_CustomScenarios_Prepare()
        {
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_builder.tgx");
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_builder2.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16f].stateTransitionTimeBaseUnk_0x18 = timeGetTime();
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16c].stateTransitionTimeBaseUnk_0x18
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16f].stateTransitionTimeBaseUnk_0x18 - 0x12c0;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16e].stateTransitionTimeBaseUnk_0x18
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16f].stateTransitionTimeBaseUnk_0x18 - 0x640;
            DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16d].stateTransitionTimeBaseUnk_0x18
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[0x16f].stateTransitionTimeBaseUnk_0x18 - 0xc80;
            INT_00b95abc::instance = -1;
            DAT_MenuTextInputState::instance.dialogResult = 0;
            DAT_GameCore::instance.missionNumber1to20 = 0;
            DAT_GameCore::instance.field115_0x1d98 = 0;
            DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_EDITOR;
            INT_00b960e4::instance = 0;
            if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
            }
            DAT_GameSynchronyState::instance
                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 1;
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
            DAT_UnknownGFXIndex::instance = 0;
            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_HUNTERSHUT;
        }

    }
}
}
