#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B1D30
    void DisplayElements::RenderPlayerPingUnkDisplayElement22(int posX, int posY, DWORD elementState)
    {
        if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
            || (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
                OpenSHC::UI::Enums::DEID_PLAYER_PING_Unk_19, 0);
            return;
        }
        timeGetTime();
        int playerID = 1;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX, posY, 120, 192);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        int* average = &DAT_GameSynchronyState::instance.connectionLagInfoArray[1].average2;
        int yPosition = posY + 18;
        // a pointer over the lag entries, compared as an address (a for over the player index:
        // quick_diff 0.9595 -> 0.9364)
        while ((int)average < (int)&DAT_GameSynchronyState::instance.connectionLagInfoArray[9].average2) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(playerID,
                    posX + 24, yPosition, OpenSHC::Text::TTA_LEFT,
                    (uint)(DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerID]]),
                    0, 18, FALSE, 0);
                if (playerID != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        *average * 2, posX + 76, yPosition, OpenSHC::Text::TTA_RIGHT,
                        (uint)(DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerID]]),
                        0, 18, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s_ms_005a77d4, posX + 76, yPosition, OpenSHC::Text::TTA_LEFT,
                        (uint)(DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerID]]),
                        0, 18, FALSE, 0);
                }
            }
            average += 9;
            ++playerID;
            yPosition += 20;
        }
    }
}
}
