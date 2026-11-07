#include "../Roundtable.func.hpp"

#include "OpenSHC/UI/BottomLeftTextDisplayState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df4288.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B1AC0
        void Roundtable::MenuModalRenderFunction_Roundtable(int x, int y, int width, int height)
        {
            if (DAT_MouseState::instance.rightClickStart != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx,
                DAT_TextureRenderCoreObject::ptr)(2, x + 8, y + 8);
            // Each seat's shield position at the table, clockwise from the top left
            int seatPositions[8][2] = {
                { 12, 12 },
                { 216, 12 },
                { 398, 12 },
                { 397, 103 },
                { 398, 193 },
                { 216, 192 },
                { 12, 193 },
                { 12, 103 },
            };
            // Players sit in their groups' order; each new group switches between the plain and the tinted shields
            int tint = 1;
            int group = 0;
            for (int seat = 1; seat < countof(DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray); ++seat) {
                int const player = DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[seat];
                if (player < 1 || DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[player] < 1) {
                    break;
                }
                if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[player] > group) {
                    ++group;
                    ++tint;
                    if (tint > 1) {
                        tint = 0;
                    }
                }
                if (tint == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGfxTgxWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        seat + 2, seatPositions[seat - 1][0] + group, seatPositions[seat - 1][1] + y, 16);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGfxTgxWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        seat + 2 + tint * 8, seatPositions[seat - 1][0] + group, seatPositions[seat - 1][1] + y, 20);
                }
            }
            DAT_ButtonY::instance = y + 380;
            DAT_ButtonX::instance = x + 24;
            DAT_ButtonW::instance = 380;
            DAT_ButtonH::instance = 40;
            if (DAT_00df4288::instance != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::BottomLeftTextDisplayState_Func::renderCurrentlyDisplayedTextConstructionCost,
                    DAT_BottomLeftTextDisplayState::ptr)(0);
                DAT_00df4288::instance = 0;
            }
        }

    }
}
}
