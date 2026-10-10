#include "../NewInvasion.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B9110
        void NewInvasion::MenuItemActionHandler_NewInvasion_UnitButtons(int unitTypeMenuID, ...)
        {
            int _limit;
            int _currentUnitCountOfType;
            int _gmID = 0;
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::sumUnitCounts, DAT_MapPropertiesState::ptr)();
            _currentUnitCountOfType = *(int*)((int)&DAT_MapPropertiesState::instance
                                                  .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                                                  .data
                + unitTypeMenuID * 4 + 4);
            _limit
                = (_currentUnitCountOfType - DAT_MapPropertiesState::instance.DAT_InvasionEventItemUnitCountSum) + 500;
            if (DAT_MissionAestheticsDefinedData::instance.InvasionUnitLimits[unitTypeMenuID] < _limit) {
                _limit = DAT_MissionAestheticsDefinedData::instance.InvasionUnitLimits[unitTypeMenuID];
            }
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setSliderParameters, DAT_MenuModalComposition2::ptr)(0,
                _limit, _currentUnitCountOfType,
                (undefined*)((int)(

                    ((int)&DAT_MapPropertiesState::instance
                            .scenarioEvents[DAT_MapPropertiesState::instance.currentEventID]
                            .data
                        + unitTypeMenuID * 4 + 4))),
                (void*)MACRO_CALL(Global_Func::DoNothing));
            switch (unitTypeMenuID) {
            case 0:
                _gmID = 0x5b;
                break;
            case 1:
                _gmID = 0x5c;
                break;
            case 2:
                _gmID = 0x5d;
                break;
            case 3:
                _gmID = 0x5e;
                break;
            case 4:
                _gmID = 0x5f;
                break;
            case 5:
                _gmID = 0x60;
                break;
            case 6:
                _gmID = 0x61;
                break;
            case 7:
                _gmID = 0x62;
                break;
            case 8:
                _gmID = 99;
                break;
            case 9:
                _gmID = 0x9d;
                break;
            case 10:
                _gmID = 0x9e;
                break;
            case 0xb:
                _gmID = 0x9f;
                break;
            case 0xc:
                _gmID = 0xa0;
                break;
            case 0xd:
                _gmID = 0xa1;
                break;
            case 0xe:
                _gmID = 0xa2;
                break;
            case 0xf:
                _gmID = 0xaa;
                break;
            case 0x10:
                _gmID = 0xd5;
                break;
            case 0x11:
                _gmID = 0xd6;
                break;
            case 0x12:
                _gmID = 0xd7;
                break;
            case 0x13:
                _gmID = 0xd8;
                break;
            case 0x14:
                _gmID = 0xd9;
                break;
            case 0x15:
                _gmID = 0xda;
                break;
            case 0x16:
                _gmID = 0xdb;
                break;
            case 0x17:
                _gmID = 0xdc;
            }
            DAT_MenuModalComposition2::instance.textGroup = 199;
            DAT_MenuModalComposition2::instance.textIndex = _gmID;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_OVERLAY_SLIDER, (int)(DAT_ButtonX::instance + -0x3e),
                (int)(DAT_ButtonY::instance + 0x19));
            return;
        }

    }
}
}
