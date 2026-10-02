#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00433780
    void Rendering::RenderGoldValue()
    {
        int numberToRenderUnk;
        int iVar1;
        int iVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        int local_c;
        int _gold;
        iVar3 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .populationCap;
        iVar4 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentPopulation;
        numberToRenderUnk
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].popularity
            / 100;
        _gold = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentResources[0xf];
        DAT_TextManagerObject::instance.currentXOffset_0x0
            = (int)DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[0x2e] + 0x7b].width;
        iVar5 = 0;
        if (999 < _gold) {
            iVar5 = 2;
        }
        if (_gold < 1) {
            _gold = 0;
            local_c = 0xff;
        } else {
            local_c = 0x7d3e;
        }
        iVar5 = iVar5 + 1;
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::calcRenderedNumberWidth, DAT_TextManagerObject::ptr)(
            _gold, iVar5);
        if (99999 < _gold) {
            iVar1 = iVar1 + -2;
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(_gold,
            (DAT_MenuHandlerState::instance.x - iVar1) + 0x2e7, DAT_MenuHandlerState::instance.y + 0x219, 5, local_c,
            iVar5, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(_gold,
            (DAT_MenuHandlerState::instance.x - iVar1) + 0x2e7, DAT_MenuHandlerState::instance.y + 0x219, 4, local_c,
            iVar5, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(_gold,
            (DAT_MenuHandlerState::instance.x - iVar1) + 0x2e7, DAT_MenuHandlerState::instance.y + 0x219, 3, local_c,
            iVar5, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(_gold,
            (DAT_MenuHandlerState::instance.x - iVar1) + 0x2e7, DAT_MenuHandlerState::instance.y + 0x219, 2, local_c,
            iVar5, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(_gold,
            (DAT_MenuHandlerState::instance.x - iVar1) + 0x2e7, DAT_MenuHandlerState::instance.y + 0x219, 1, local_c,
            iVar5, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(_gold,
            (DAT_MenuHandlerState::instance.x - iVar1) + 0x2e7, DAT_MenuHandlerState::instance.y + 0x219, 0, local_c,
            iVar5, 1);
        local_c = 0;
        iVar3 = ((100 < DAT_GameState::instance.playerDataArray[iVar3].crowding) - 1 & 0x7c3f) + 0xff;
        if (iVar2 == 0) {
            iVar3 = 0x7d3e;
        } else {
            if (99 < iVar2) {
                local_c = 2;
            }
            if (-1 < iVar4) {
                if (99 < iVar4) {
                    local_c = 2;
                }
                goto LAB_004339a1;
            }
        }
        iVar4 = 0;
    LAB_004339a1:
        iVar1 = local_c + 1;
        iVar5 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::calcRenderedNumberWidth, DAT_TextManagerObject::ptr)(
            iVar4, iVar1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar4,
            (DAT_MenuHandlerState::instance.x - iVar5) + 0x2d9, DAT_MenuHandlerState::instance.y + 0x228, 2, iVar3,
            iVar1, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar4,
            (DAT_MenuHandlerState::instance.x - iVar5) + 0x2d9, DAT_MenuHandlerState::instance.y + 0x228, 1, iVar3,
            iVar1, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar4,
            (DAT_MenuHandlerState::instance.x - iVar5) + 0x2d9, DAT_MenuHandlerState::instance.y + 0x228, 0, iVar3,
            iVar1, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar4,
            DAT_MenuHandlerState::instance.x + 0x2d9, DAT_MenuHandlerState::instance.y + 0x228, -1, iVar3, iVar1, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar2,
            DAT_MenuHandlerState::instance.x + 0x2d7 + local_c, DAT_MenuHandlerState::instance.y + 0x228, 2, iVar3,
            iVar1, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar2,
            DAT_MenuHandlerState::instance.x + 0x2d7 + local_c, DAT_MenuHandlerState::instance.y + 0x228, 1, iVar3,
            iVar1, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(iVar2,
            DAT_MenuHandlerState::instance.x + 0x2d7 + local_c, DAT_MenuHandlerState::instance.y + 0x228, 0, iVar3,
            iVar1, 1);
        iVar2 = ((0x31 < numberToRenderUnk) - 1 & 0xffff83c1) + 0x7d3e;
        iVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::calcRenderedNumberWidth, DAT_TextManagerObject::ptr)(
            numberToRenderUnk, 0);
        iVar4 = iVar4 / 2;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(
            numberToRenderUnk, (DAT_MenuHandlerState::instance.x - iVar4) + 0x2eb,
            DAT_MenuHandlerState::instance.y + 0x203, 2, iVar2, 0, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(
            numberToRenderUnk, (DAT_MenuHandlerState::instance.x - iVar4) + 0x2eb,
            DAT_MenuHandlerState::instance.y + 0x203, 1, iVar2, 0, 1);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(
            numberToRenderUnk, (DAT_MenuHandlerState::instance.x - iVar4) + 0x2eb,
            DAT_MenuHandlerState::instance.y + 0x203, 0, iVar2, 0, 1);
    }

}
}
