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

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B1D30
    void DisplayElements::RenderPlayerPingUnkDisplayElement22(int posX, int posY, DWORD elementState)
    {
        int integer;
        int* piVar1;
        int yPosition;
        if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY)
            && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            timeGetTime();
            integer = 1;
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(posX, posY, 0x78, 0xc0);
            DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            piVar1 = &DAT_GameSynchronyState::instance.connectionLagInfoArray[1].average2;
            yPosition = posY + 0x12;
            do {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[integer] != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        integer, posX + 0x18, yPosition, OpenSHC::Text::TTA_LEFT,
                        (uint)((int)(DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[integer]])),
                        0, 0x12, FALSE, 0);
                    if (integer != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            *piVar1 * 2, posX + 0x4c, yPosition, OpenSHC::Text::TTA_RIGHT,
                            (uint)((int)(DAT_RenderingDefinedData::instance
                                    .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[integer]])),
                            0, 0x12, FALSE, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                            DAT_TextManagerObject::ptr)("ms", posX + 0x4c, yPosition, OpenSHC::Text::TTA_LEFT,
                            (uint)((int)(DAT_RenderingDefinedData::instance
                                    .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[integer]])),
                            0, 0x12, FALSE, 0);
                    }
                }
                piVar1 = piVar1 + 9;
                integer = integer + 1;
                yPosition = yPosition + 0x14;
            } while ((int)piVar1 < 0x19983b0);
        }
        MACRO_CALL(OpenSHC::UI::DisplayElements_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
            OpenSHC::UI::Enums::DEID_PLAYER_PING_Unk_19, 0);
    }

}
}
