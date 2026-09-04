#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"



#include "OpenSHC/Globals/DAT_00ed27a0.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_StoredGameMode.hpp"

namespace OpenSHC {




/* 
  WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
 */

/* 
  WARNING: Enum "DPERRInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004D9700
void UI::MenuView_RankingGames_Prepare()

{
MACRO_CALL(OpenSHC::Game::Skirmish_Func::Skirmish_PrepareLeaderboardView)();
DAT_00ed27a0::instance = 0;
DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)("frontend_combat3.tgx");
MACRO_CALL(OpenSHC::UI_Func::LoadTGX_shc_back)();
DAT_StoredGameMode::instance = DAT_GameSynchronyState::instance.currentGameMode;
return;
}


}