#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0047F860
    void GameSynchronyState::renderInGameChat(int xPos, int yPos, int unused)
    {
        // The last four messages, newest at the bottom, each shown for ten seconds.
        this->chatMessageRenderIndex = this->DAT_ChatMessageArrayIndex;
        for (int message = 4; message != 0; --message) {
            if (this->DAT_ChatEventArray[this->chatMessageRenderIndex].flag == 1) {
                int const index = this->chatMessageRenderIndex;
                if ((int)(timeGetTime() - this->DAT_ChatEventArray[index].time) > 10000) {
                    this->DAT_ChatEventArray[index].flag = 0;
                } else {
                    int const sender = this->DAT_ChatEventArray[index].subjectPlayer;
                    int const lordID = DAT_GameState::instance.playerDataArray[sender].lordID;
                    int width = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                                    this->DAT_ChatMessageSubjectPlayerNameArray[index], 19)
                        + 6;
                    width += MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                                 this->DAT_ChatMessageArray[this->chatMessageRenderIndex], 19)
                        + 6;
                    if (this->DAT_ChatEventArray[this->chatMessageRenderIndex].objectPlayer != 0) {
                        width
                            += MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                                   this->DAT_ChatMessageObjectPlayerNameArray[this->chatMessageRenderIndex], 19)
                            + 6;
                    }
                    // A sender whose lord is dead gets "(deceased)" after the name.
                    if ((lordID == 0
                            || DAT_UnitsState::instance.units[lordID].uid
                                != DAT_GameState::instance.playerDataArray[sender].lordUID
                            || DAT_UnitsState::instance.units[lordID].logicalState != Map::Units::ULS_NORMAL)
                        && (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127) > 200) {
                        // "(deceased)"
                        width
                            += MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                                   MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                       DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 44),
                                   19)
                            + 6;
                    }
                    DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_MAP_GAME;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(xPos - 5, yPos - 4, width + xPos, yPos + 9, 16);
                    DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
                    int textX = xPos;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageSubjectPlayerNameArray[this->chatMessageRenderIndex], textX, yPos,
                        Text::TTA_LEFT,
                        DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor
                                    [this->DAT_ChatEventArray[this->chatMessageRenderIndex].subjectPlayer]],
                        0, 19, FALSE, 0);
                    if ((lordID == 0
                            || DAT_UnitsState::instance.units[lordID].uid
                                != DAT_GameState::instance.playerDataArray[sender].lordUID
                            || DAT_UnitsState::instance.units[lordID].logicalState != Map::Units::ULS_NORMAL)
                        && (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127) > 200) {
                        textX += 6;
                        // "(deceased)"
                        MACRO_CALL_MEMBER(
                            Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 44),
                            textX, yPos, Text::TTA_LEFT, Rendering::Colors::COL_B8EEFB, 0, 19, TRUE, 0);
                    }
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageArray[this->chatMessageRenderIndex], textX + 6, yPos, Text::TTA_LEFT,
                        Rendering::Colors::COL_B8EEFB, 0, 19, TRUE, 0);
                    int const recipient = this->DAT_ChatEventArray[this->chatMessageRenderIndex].objectPlayer;
                    if (recipient != 0) {
                        MACRO_CALL_MEMBER(
                            Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            this->DAT_ChatMessageObjectPlayerNameArray[this->chatMessageRenderIndex], textX + 12, yPos,
                            Text::TTA_LEFT,
                            DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[recipient]],
                            0, 19, TRUE, 0);
                    }
                }
            }
            --this->chatMessageRenderIndex;
            // Back to the last of the 20 chat slots.
            if (this->chatMessageRenderIndex < 0) {
                this->chatMessageRenderIndex = 19;
            }
            yPos -= 14;
        }
    }

}
}
