#include "../TacticalPowerBar.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TacticalPowersHelpTextDisplayBool.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::GameMode;
        using IO::Graphics::GmID;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9EC0
        void TacticalPowerBar::MenuItemRenderFunction_TacticalPowerBar_Main(int param_1, ...)
        {
            int iVar1;
            int blendStrengthUnk;
            int _level;
            _level = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                         .tacticalPowersBarLevel;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                DAT_ButtonX::instance + 0x14, (int)(DAT_ButtonY::instance + 10), (int)(DAT_ButtonX::instance + 0x1e),
                (int)(DAT_ButtonY::instance + 10), (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            iVar1 = param_1;
            switch (param_1) {
            case 0:
                iVar1 = 5;
                break;
            case 1:
                iVar1 = 6;
                break;
            case 2:
                iVar1 = 1;
                break;
            case 3:
                iVar1 = 3;
                break;
            case 4:
            case 8:
            case 9:
                iVar1 = 0;
                break;
            case 5:
                iVar1 = 7;
                break;
            case 6:
                iVar1 = 2;
                break;
            case 7:
                iVar1 = 4;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
                || DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER
                || !DAT_GameState::instance.mapAndTime.skirmishNoRushTicks) {
                blendStrengthUnk = DAT_ButtonBlendStrength::instance;
                if ((param_1 + 1) * 0x27c <= _level) {
                    if (!DAT_GameCore::instance.tacticalPowersDisplayFlag) {
                        DAT_TacticalPowersHelpTextDisplayBool::instance = true;
                        DAT_GameCore::instance.tacticalPowersDisplayFlag = 1;
                    }
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, iVar1 + 0x121,
                        (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonBlendStrength::instance));
                    if (!DAT_ButtonCurrentlyInteracting::instance) {}
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, 0x129,
                        (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance),
                        (int)(DAT_ButtonBlendStrength::instance));
                }
            } else {
                blendStrengthUnk = 0x20 - (0x20 - DAT_ButtonBlendStrength::instance) / 2;
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                DAT_TextureRenderCoreObject::ptr)(IO::Graphics::GID_INTERFACE_ICONS_3, iVar1 + 0x12a,
                (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance), blendStrengthUnk);
        }

    }
}
}
