#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
        int integer = 1;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
            DAT_PencilRenderCore::ptr)(posX, posY, 0x78, 0xc0);
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        int* piVar1 = &DAT_GameSynchronyState::instance.connectionLagInfoArray[1].average2;
        int yPosition = posY + 0x12;
        while ((int)piVar1 < (int)&DAT_GameSynchronyState::instance + 0x7ac48) {
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[integer] != -1) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    integer, posX + 0x18, yPosition, OpenSHC::Text::TTA_LEFT,
                    (uint)(DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[integer]]),
                    0, 0x12, FALSE, 0);
                if (integer != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        *piVar1 * 2, posX + 0x4c, yPosition, OpenSHC::Text::TTA_RIGHT,
                        (uint)(DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[integer]]),
                        0, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)("ms", posX + 0x4c, yPosition, OpenSHC::Text::TTA_LEFT,
                        (uint)(DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[integer]]),
                        0, 0x12, FALSE, 0);
                }
            }
            piVar1 = piVar1 + 9;
            integer = integer + 1;
            yPosition = yPosition + 0x14;
        }
    }
}
}
