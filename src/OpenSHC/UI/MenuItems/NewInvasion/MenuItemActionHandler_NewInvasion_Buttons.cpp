#include "../NewInvasion.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnion.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include "stdlib.h"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Game::ScenarioEvents::InGameEventUnion;
        using Game::ScenarioEvents::InGameEventUnionVersion;
        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BF760
        void NewInvasion::MenuItemActionHandler_NewInvasion_Buttons(int param_1, ...)
        {
            InGameEventUnion* pIVar1;
            InGameEventUnionVersion* pIVar2;
            InGameEventUnionVersion* pIVar3;
            undefined1 uVar4;
            undefined1 uVar5;
            char* _Str;
            long _year;
            int iVar6;
            switch (param_1) {
            case 0x13:
                MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::removeEventAtIndex,
                    DAT_MapPropertiesState::ptr)(DAT_MapPropertiesState::instance.currentEventID);
                goto LAB_004bf791;
            case 0x25:
                _Str = MACRO_CALL_MEMBER(
                    Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0xb);
                _year = atol(_Str);
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.year = _year;
                pIVar2
                    = DAT_MapPropertiesState::instance.scenarioEvents + DAT_MapPropertiesState::instance.currentEventID;
                uVar4 = *(undefined1*)((int)&(pIVar2->header).year + 2);
                uVar5 = *(undefined1*)((int)&(pIVar2->header).year + 3);
                pIVar3
                    = DAT_MapPropertiesState::instance.scenarioEvents + DAT_MapPropertiesState::instance.currentEventID;
                /*
                  set message year
                 */
                *(undefined2*)((int)&pIVar3->data + 0x6c) = *(undefined2*)&(pIVar2->header).year;
                *(undefined1*)((int)&pIVar3->data + 0x6e) = uVar4;
                *(undefined1*)((int)&pIVar3->data + 0x6f) = uVar5;
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.totalUnitCount = 0;
                iVar6 = 0;
                do {
                    pIVar1 = &DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data;
                    (pIVar1->invasion).totalUnitCount = (pIVar1->invasion).totalUnitCount
                        + *(int*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + iVar6 * 4 + 4);
                    pIVar1 = &DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data;
                    (pIVar1->invasion).totalUnitCount = (pIVar1->invasion).totalUnitCount
                        + *(int*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + iVar6 * 4 + 8);
                    pIVar1 = &DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data;
                    (pIVar1->invasion).totalUnitCount = (pIVar1->invasion).totalUnitCount
                        + *(int*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + iVar6 * 4 + 0xc);
                    pIVar1 = &DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data;
                    (pIVar1->invasion).totalUnitCount = (pIVar1->invasion).totalUnitCount
                        + *(int*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + iVar6 * 4 + 0x10);
                    pIVar1 = &DAT_MapPropertiesState::instance
                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                  .data;
                    (pIVar1->invasion).totalUnitCount = (pIVar1->invasion).totalUnitCount
                        + *(int*)((int)&DAT_MapPropertiesState::instance
                                      .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                      .data
                            + iVar6 * 4 + 0x14);
                    iVar6 = iVar6 + 5;
                } while (iVar6 < 25);
            LAB_004bf791:
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(
                    Map::MapPropertiesState_Func::sortEventsByDate, DAT_MapPropertiesState::ptr)();
                MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(
                    0xf);
                return;
            case 0x57:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.crusaderArabian = 4;
                break;
            case 0xdd:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.crusaderArabian = 0;
                return;
            case 0xde:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .data.invasion.crusaderArabian = 1;
                return;
            case -1:
                DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                    .header.month
                    = DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                          .header.month
                    + 1;
                if (0xc
                    <= DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month) {
                    DAT_MapPropertiesState::instance.scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                        .header.month = 0;
                    return;
                }
            }
            return;
        }

    }
}
}
