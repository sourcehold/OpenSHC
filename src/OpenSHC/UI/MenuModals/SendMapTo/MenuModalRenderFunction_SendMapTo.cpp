#include "../SendMapTo.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC310
        void SendMapTo::MenuModalRenderFunction_SendMapTo(int x, int y, int width, int height)
        {
            // "Send Map To"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 106, x, y, width, height);
            int rowOffsetY = 0;
            for (int playerID = 1; playerID < countof(DAT_GameSynchronyState::instance.mapTransferStatePerPlayer);
                ++playerID) {
                if (DAT_GameSynchronyState::instance.mapTransferStatePerPlayer[playerID] == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[playerID], x + 20, rowOffsetY + 80 + y,
                        OpenSHC::Text::TTA_LEFT,
                        DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[playerID]],
                        17, FALSE, 0);
                    if (DAT_GameSynchronyState::instance.DAT_MapFileReceivingState != 0) {
                        int barX = width / 2 + x;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                            DAT_PencilRenderCore::ptr)(barX - 1, rowOffsetY + 82 + y, width - 19 + x,
                            rowOffsetY + 99 + y, COL_BLACK::instance.shortValue);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                            DAT_PencilRenderCore::ptr)(barX, rowOffsetY + 83 + y,
                            ((width / 2 - 20) * DAT_GameSynchronyState::instance.mapSendingByteBufferAddress[playerID])
                                    / DAT_GameSynchronyState::instance.mapSendingFileSize
                                + width / 2 + x,
                            rowOffsetY + 98 + y, COL_DARK_LIME::instance.shortValue);
                    }
                    rowOffsetY += 30;
                }
            }
        }
    }
}
}
