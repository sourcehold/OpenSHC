#include "../Helpers.func.hpp"

#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventExtra.hpp"
#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/INT_00ec02e8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb1238.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2630.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2fc8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed3070.hpp"

namespace OpenSHC {
namespace UI {
    using Game::ScenarioEvents::InGameEventExtra;
    using Game::ScenarioEvents::InGameEventUnionVersion;
    using Game::ScenarioEvents::ScenarioEventCondition;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D7200
    void Helpers::ResetEventStatusUnk()
    {
        int iVar2;
        int iVar3;
        InGameEventUnionVersion* _event;
        int iVar4;
        InGameEventUnionVersion* _event2;
        InGameEventUnionVersion* pIVar4;
        int iVar5;
        InGameEventExtra* pIVar6;
        ScenarioEventCondition* pSVar7;
        INT_ARRAY_00eb1238::instance[0] = 0;
        INT_ARRAY_00eb1238::instance[1] = 0;
        INT_ARRAY_00eb1238::instance[2] = 0;
        INT_ARRAY_00eb1238::instance[3] = 0;
        INT_ARRAY_00eb1238::instance[4] = 0;
        INT_ARRAY_00eb1238::instance[5] = 0;
        INT_ARRAY_00eb1238::instance[6] = 0;
        INT_ARRAY_00eb1238::instance[7] = 0;
        INT_ARRAY_00eb1238::instance[8] = 0;
        INT_ARRAY_00eb1238::instance[9] = 0;
        INT_ARRAY_00eb1238::instance[10] = 0;
        INT_ARRAY_00eb1238::instance[0xb] = 0;
        INT_ARRAY_00eb1238::instance[0xc] = 0;
        INT_ARRAY_00eb1238::instance[0xd] = 0;
        INT_ARRAY_00eb1238::instance[0xe] = 0;
        INT_ARRAY_00eb1238::instance[0xf] = 0;
        INT_ARRAY_00eb1238::instance[0x10] = 0;
        INT_ARRAY_00eb1238::instance[0x11] = 0;
        INT_ARRAY_00eb1238::instance[0x12] = 0;
        INT_ARRAY_00eb1238::instance[0x13] = 0;
        INT_ARRAY_00eb1238::instance[0x14] = 0;
        INT_ARRAY_00eb1238::instance[0x15] = 0;
        INT_ARRAY_00eb1238::instance[0x16] = 0;
        INT_ARRAY_00eb1238::instance[0x17] = 0;
        INT_ARRAY_00eb1238::instance[0x18] = 0;
        INT_ARRAY_00eb1238::instance[0x19] = 0;
        INT_ARRAY_00eb1238::instance[0x1a] = 0;
        INT_ARRAY_00eb1238::instance[0x1b] = 0;
        INT_ARRAY_00eb1238::instance[0x1c] = 0;
        INT_ARRAY_00eb1238::instance[0x1d] = 0;
        INT_ARRAY_00eb1238::instance[0x1e] = 0;
        INT_ARRAY_00eb1238::instance[0x1f] = 0;
        INT_ARRAY_00eb1238::instance[0x20] = 0;
        INT_ARRAY_00eb1238::instance[0x21] = 0;
        INT_ARRAY_00eb1238::instance[0x22] = 0;
        INT_ARRAY_00eb1238::instance[0x23] = 0;
        INT_ARRAY_00eb1238::instance[0x24] = 0;
        INT_ARRAY_00eb1238::instance[0x25] = 0;
        INT_ARRAY_00eb1238::instance[0x26] = 0;
        INT_ARRAY_00eb1238::instance[0x27] = 0;
        INT_ARRAY_00ed2fc8::instance[0] = 0;
        INT_ARRAY_00ed2fc8::instance[1] = 0;
        INT_ARRAY_00ed2fc8::instance[2] = 0;
        INT_ARRAY_00ed2fc8::instance[3] = 0;
        INT_ARRAY_00ed2fc8::instance[4] = 0;
        INT_ARRAY_00ed2fc8::instance[5] = 0;
        INT_ARRAY_00ed2fc8::instance[6] = 0;
        INT_ARRAY_00ed2fc8::instance[7] = 0;
        INT_ARRAY_00ed2fc8::instance[8] = 0;
        INT_ARRAY_00ed2fc8::instance[9] = 0;
        INT_ARRAY_00ed2fc8::instance[10] = 0;
        INT_ARRAY_00ed2fc8::instance[0xb] = 0;
        INT_ARRAY_00ed2fc8::instance[0xc] = 0;
        INT_ARRAY_00ed2fc8::instance[0xd] = 0;
        INT_ARRAY_00ed2fc8::instance[0xe] = 0;
        INT_ARRAY_00ed2fc8::instance[0xf] = 0;
        INT_ARRAY_00ed2fc8::instance[0x10] = 0;
        INT_ARRAY_00ed2fc8::instance[0x11] = 0;
        INT_ARRAY_00ed2fc8::instance[0x12] = 0;
        INT_ARRAY_00ed2fc8::instance[0x13] = 0;
        INT_ARRAY_00ed2fc8::instance[0x14] = 0;
        INT_ARRAY_00ed2fc8::instance[0x15] = 0;
        INT_ARRAY_00ed2fc8::instance[0x16] = 0;
        INT_ARRAY_00ed2fc8::instance[0x17] = 0;
        INT_ARRAY_00ed2fc8::instance[0x18] = 0;
        INT_ARRAY_00ed2fc8::instance[0x19] = 0;
        INT_ARRAY_00ed2fc8::instance[0x1a] = 0;
        INT_ARRAY_00ed2fc8::instance[0x1b] = 0;
        INT_ARRAY_00ed2fc8::instance[0x1c] = 0;
        INT_ARRAY_00ed2fc8::instance[0x1d] = 0;
        INT_ARRAY_00ed2fc8::instance[0x1e] = 0;
        INT_ARRAY_00ed2fc8::instance[0x1f] = 0;
        INT_ARRAY_00ed2fc8::instance[0x20] = 0;
        INT_ARRAY_00ed2fc8::instance[0x21] = 0;
        INT_ARRAY_00ed2fc8::instance[0x22] = 0;
        INT_ARRAY_00ed2fc8::instance[0x23] = 0;
        INT_ARRAY_00ed2fc8::instance[0x24] = 0;
        INT_ARRAY_00ed2fc8::instance[0x25] = 0;
        INT_ARRAY_00ed2fc8::instance[0x26] = 0;
        INT_ARRAY_00ed2fc8::instance[0x27] = 0;
        INT_ARRAY_00ed3070::instance[0] = 0;
        INT_ARRAY_00ed3070::instance[1] = 0;
        INT_ARRAY_00ed3070::instance[2] = 0;
        INT_ARRAY_00ed3070::instance[3] = 0;
        INT_ARRAY_00ed3070::instance[4] = 0;
        INT_ARRAY_00ed3070::instance[5] = 0;
        INT_ARRAY_00ed3070::instance[6] = 0;
        INT_ARRAY_00ed3070::instance[7] = 0;
        INT_ARRAY_00ed3070::instance[8] = 0;
        INT_ARRAY_00ed3070::instance[9] = 0;
        INT_ARRAY_00ed3070::instance[10] = 0;
        INT_ARRAY_00ed3070::instance[0xb] = 0;
        INT_ARRAY_00ed3070::instance[0xc] = 0;
        INT_ARRAY_00ed3070::instance[0xd] = 0;
        INT_ARRAY_00ed3070::instance[0xe] = 0;
        INT_ARRAY_00ed3070::instance[0xf] = 0;
        INT_ARRAY_00ed3070::instance[0x10] = 0;
        INT_ARRAY_00ed3070::instance[0x11] = 0;
        INT_ARRAY_00ed3070::instance[0x12] = 0;
        INT_ARRAY_00ed3070::instance[0x13] = 0;
        INT_ARRAY_00ed3070::instance[0x14] = 0;
        INT_ARRAY_00ed3070::instance[0x15] = 0;
        INT_ARRAY_00ed3070::instance[0x16] = 0;
        INT_ARRAY_00ed3070::instance[0x17] = 0;
        INT_ARRAY_00ed3070::instance[0x18] = 0;
        INT_ARRAY_00ed3070::instance[0x19] = 0;
        INT_ARRAY_00ed3070::instance[0x1a] = 0;
        INT_ARRAY_00ed3070::instance[0x1b] = 0;
        INT_ARRAY_00ed3070::instance[0x1c] = 0;
        INT_ARRAY_00ed3070::instance[0x1d] = 0;
        INT_ARRAY_00ed3070::instance[0x1e] = 0;
        INT_ARRAY_00ed3070::instance[0x1f] = 0;
        INT_ARRAY_00ed3070::instance[0x20] = 0;
        INT_ARRAY_00ed3070::instance[0x21] = 0;
        INT_ARRAY_00ed3070::instance[0x22] = 0;
        INT_ARRAY_00ed3070::instance[0x23] = 0;
        INT_ARRAY_00ed3070::instance[0x24] = 0;
        INT_ARRAY_00ed3070::instance[0x25] = 0;
        INT_ARRAY_00ed3070::instance[0x26] = 0;
        INT_ARRAY_00ed3070::instance[0x27] = 0;
        INT_ARRAY_00ed2630::instance[0] = 0;
        INT_ARRAY_00ed2630::instance[1] = 0;
        INT_ARRAY_00ed2630::instance[2] = 0;
        INT_ARRAY_00ed2630::instance[3] = 0;
        INT_ARRAY_00ed2630::instance[4] = 0;
        INT_ARRAY_00ed2630::instance[5] = 0;
        INT_ARRAY_00ed2630::instance[6] = 0;
        INT_ARRAY_00ed2630::instance[7] = 0;
        INT_ARRAY_00ed2630::instance[8] = 0;
        INT_ARRAY_00ed2630::instance[9] = 0;
        INT_ARRAY_00ed2630::instance[10] = 0;
        INT_ARRAY_00ed2630::instance[0xb] = 0;
        INT_ARRAY_00ed2630::instance[0xc] = 0;
        INT_ARRAY_00ed2630::instance[0xd] = 0;
        INT_ARRAY_00ed2630::instance[0xe] = 0;
        INT_ARRAY_00ed2630::instance[0xf] = 0;
        INT_ARRAY_00ed2630::instance[0x10] = 0;
        INT_ARRAY_00ed2630::instance[0x11] = 0;
        INT_ARRAY_00ed2630::instance[0x12] = 0;
        INT_ARRAY_00ed2630::instance[0x13] = 0;
        INT_ARRAY_00ed2630::instance[0x14] = 0;
        INT_ARRAY_00ed2630::instance[0x15] = 0;
        INT_ARRAY_00ed2630::instance[0x16] = 0;
        INT_ARRAY_00ed2630::instance[0x17] = 0;
        INT_ARRAY_00ed2630::instance[0x18] = 0;
        INT_ARRAY_00ed2630::instance[0x19] = 0;
        INT_ARRAY_00ed2630::instance[0x1a] = 0;
        INT_ARRAY_00ed2630::instance[0x1b] = 0;
        INT_ARRAY_00ed2630::instance[0x1c] = 0;
        INT_ARRAY_00ed2630::instance[0x1d] = 0;
        INT_ARRAY_00ed2630::instance[0x1e] = 0;
        INT_ARRAY_00ed2630::instance[0x1f] = 0;
        INT_ARRAY_00ed2630::instance[0x20] = 0;
        INT_ARRAY_00ed2630::instance[0x21] = 0;
        INT_ARRAY_00ed2630::instance[0x22] = 0;
        INT_ARRAY_00ed2630::instance[0x23] = 0;
        INT_ARRAY_00ed2630::instance[0x24] = 0;
        INT_ARRAY_00ed2630::instance[0x25] = 0;
        INT_ARRAY_00ed2630::instance[0x26] = 0;
        INT_ARRAY_00ed2630::instance[0x27] = 0;
        if (0 < DAT_MapPropertiesState::instance.eventsCount) {
            _event = (InGameEventUnionVersion*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[0]);
            iVar5 = DAT_MapPropertiesState::instance.eventsCount;
            do {
                if (_event->header.tl_type == 3
                    && (iVar4 = (_event->data).scenario.ScenarioEventType, iVar4 == 1 || (iVar4 == 0x1b))
                    && *(char*)((int)&_event->data + 0xf) != '\0') {
                    INT_00ec02e8::instance = 1;
                }
                _event = _event + 0xe4;
                iVar5 = iVar5 + -1;
            } while (iVar5);
        }
        iVar5 = 0;
        if (DAT_MapPropertiesState::instance.eventsCount < 1) {
            INT_ARRAY_00eb1238::instance[0] = 0;
            INT_ARRAY_00eb1238::instance[1] = 0;
            INT_ARRAY_00eb1238::instance[2] = 0;
            INT_ARRAY_00eb1238::instance[3] = 0;
            INT_ARRAY_00eb1238::instance[4] = 0;
            INT_ARRAY_00eb1238::instance[5] = 0;
            INT_ARRAY_00eb1238::instance[6] = 0;
            INT_ARRAY_00eb1238::instance[7] = 0;
            INT_ARRAY_00eb1238::instance[8] = 0;
            INT_ARRAY_00eb1238::instance[9] = 0;
            INT_ARRAY_00eb1238::instance[10] = 0;
            INT_ARRAY_00eb1238::instance[0xb] = 0;
            INT_ARRAY_00eb1238::instance[0xc] = 0;
            INT_ARRAY_00eb1238::instance[0xd] = 0;
            INT_ARRAY_00eb1238::instance[0xe] = 0;
            INT_ARRAY_00eb1238::instance[0xf] = 0;
            INT_ARRAY_00eb1238::instance[0x10] = 0;
            INT_ARRAY_00eb1238::instance[0x11] = 0;
            INT_ARRAY_00eb1238::instance[0x12] = 0;
            INT_ARRAY_00eb1238::instance[0x13] = 0;
            INT_ARRAY_00eb1238::instance[0x14] = 0;
            INT_ARRAY_00eb1238::instance[0x15] = 0;
            INT_ARRAY_00eb1238::instance[0x16] = 0;
            INT_ARRAY_00eb1238::instance[0x17] = 0;
            INT_ARRAY_00eb1238::instance[0x18] = 0;
            INT_ARRAY_00eb1238::instance[0x19] = 0;
            INT_ARRAY_00eb1238::instance[0x1a] = 0;
            INT_ARRAY_00eb1238::instance[0x1b] = 0;
            INT_ARRAY_00eb1238::instance[0x1c] = 0;
            INT_ARRAY_00eb1238::instance[0x1d] = 0;
            INT_ARRAY_00eb1238::instance[0x1e] = 0;
            INT_ARRAY_00eb1238::instance[0x1f] = 0;
            INT_ARRAY_00eb1238::instance[0x20] = 0;
            INT_ARRAY_00eb1238::instance[0x21] = 0;
            INT_ARRAY_00eb1238::instance[0x22] = 0;
            INT_ARRAY_00eb1238::instance[0x23] = 0;
            INT_ARRAY_00eb1238::instance[0x24] = 0;
            INT_ARRAY_00eb1238::instance[0x25] = 0;
            INT_ARRAY_00eb1238::instance[0x26] = 0;
            INT_ARRAY_00eb1238::instance[0x27] = 0;
            INT_ARRAY_00ed2630::instance[0] = 0;
            INT_ARRAY_00ed2630::instance[1] = 0;
            INT_ARRAY_00ed2630::instance[2] = 0;
            INT_ARRAY_00ed2630::instance[3] = 0;
            INT_ARRAY_00ed2630::instance[4] = 0;
            INT_ARRAY_00ed2630::instance[5] = 0;
            INT_ARRAY_00ed2630::instance[6] = 0;
            INT_ARRAY_00ed2630::instance[7] = 0;
            INT_ARRAY_00ed2630::instance[8] = 0;
            INT_ARRAY_00ed2630::instance[9] = 0;
            INT_ARRAY_00ed2630::instance[10] = 0;
            INT_ARRAY_00ed2630::instance[0xb] = 0;
            INT_ARRAY_00ed2630::instance[0xc] = 0;
            INT_ARRAY_00ed2630::instance[0xd] = 0;
            INT_ARRAY_00ed2630::instance[0xe] = 0;
            INT_ARRAY_00ed2630::instance[0xf] = 0;
            INT_ARRAY_00ed2630::instance[0x10] = 0;
            INT_ARRAY_00ed2630::instance[0x11] = 0;
            INT_ARRAY_00ed2630::instance[0x12] = 0;
            INT_ARRAY_00ed2630::instance[0x13] = 0;
            INT_ARRAY_00ed2630::instance[0x14] = 0;
            INT_ARRAY_00ed2630::instance[0x15] = 0;
            INT_ARRAY_00ed2630::instance[0x16] = 0;
            INT_ARRAY_00ed2630::instance[0x17] = 0;
            INT_ARRAY_00ed2630::instance[0x18] = 0;
            INT_ARRAY_00ed2630::instance[0x19] = 0;
            INT_ARRAY_00ed2630::instance[0x1a] = 0;
            INT_ARRAY_00ed2630::instance[0x1b] = 0;
            INT_ARRAY_00ed2630::instance[0x1c] = 0;
            INT_ARRAY_00ed2630::instance[0x1d] = 0;
            INT_ARRAY_00ed2630::instance[0x1e] = 0;
            INT_ARRAY_00ed2630::instance[0x1f] = 0;
            INT_ARRAY_00ed2630::instance[0x20] = 0;
            INT_ARRAY_00ed2630::instance[0x21] = 0;
            INT_ARRAY_00ed2630::instance[0x22] = 0;
            INT_ARRAY_00ed2630::instance[0x23] = 0;
            INT_ARRAY_00ed2630::instance[0x24] = 0;
            INT_ARRAY_00ed2630::instance[0x25] = 0;
            INT_ARRAY_00ed2630::instance[0x26] = 0;
            INT_ARRAY_00ed2630::instance[0x27] = 0;
            INT_ARRAY_00ed2fc8::instance[0] = 0;
            INT_ARRAY_00ed2fc8::instance[1] = 0;
            INT_ARRAY_00ed2fc8::instance[2] = 0;
            INT_ARRAY_00ed2fc8::instance[3] = 0;
            INT_ARRAY_00ed2fc8::instance[4] = 0;
            INT_ARRAY_00ed2fc8::instance[5] = 0;
            INT_ARRAY_00ed2fc8::instance[6] = 0;
            INT_ARRAY_00ed2fc8::instance[7] = 0;
            INT_ARRAY_00ed2fc8::instance[8] = 0;
            INT_ARRAY_00ed2fc8::instance[9] = 0;
            INT_ARRAY_00ed2fc8::instance[10] = 0;
            INT_ARRAY_00ed2fc8::instance[0xb] = 0;
            INT_ARRAY_00ed2fc8::instance[0xc] = 0;
            INT_ARRAY_00ed2fc8::instance[0xd] = 0;
            INT_ARRAY_00ed2fc8::instance[0xe] = 0;
            INT_ARRAY_00ed2fc8::instance[0xf] = 0;
            INT_ARRAY_00ed2fc8::instance[0x10] = 0;
            INT_ARRAY_00ed2fc8::instance[0x11] = 0;
            INT_ARRAY_00ed2fc8::instance[0x12] = 0;
            INT_ARRAY_00ed2fc8::instance[0x13] = 0;
            INT_ARRAY_00ed2fc8::instance[0x14] = 0;
            INT_ARRAY_00ed2fc8::instance[0x15] = 0;
            INT_ARRAY_00ed2fc8::instance[0x16] = 0;
            INT_ARRAY_00ed2fc8::instance[0x17] = 0;
            INT_ARRAY_00ed2fc8::instance[0x18] = 0;
            INT_ARRAY_00ed2fc8::instance[0x19] = 0;
            INT_ARRAY_00ed2fc8::instance[0x1a] = 0;
            INT_ARRAY_00ed2fc8::instance[0x1b] = 0;
            INT_ARRAY_00ed2fc8::instance[0x1c] = 0;
            INT_ARRAY_00ed2fc8::instance[0x1d] = 0;
            INT_ARRAY_00ed2fc8::instance[0x1e] = 0;
            INT_ARRAY_00ed2fc8::instance[0x1f] = 0;
            INT_ARRAY_00ed2fc8::instance[0x20] = 0;
            INT_ARRAY_00ed2fc8::instance[0x21] = 0;
            INT_ARRAY_00ed2fc8::instance[0x22] = 0;
            INT_ARRAY_00ed2fc8::instance[0x23] = 0;
            INT_ARRAY_00ed2fc8::instance[0x24] = 0;
            INT_ARRAY_00ed2fc8::instance[0x25] = 0;
            INT_ARRAY_00ed2fc8::instance[0x26] = 0;
            INT_ARRAY_00ed2fc8::instance[0x27] = 0;
            INT_ARRAY_00ed3070::instance[0] = 0;
            INT_ARRAY_00ed3070::instance[1] = 0;
            INT_ARRAY_00ed3070::instance[2] = 0;
            INT_ARRAY_00ed3070::instance[3] = 0;
            INT_ARRAY_00ed3070::instance[4] = 0;
            INT_ARRAY_00ed3070::instance[5] = 0;
            INT_ARRAY_00ed3070::instance[6] = 0;
            INT_ARRAY_00ed3070::instance[7] = 0;
            INT_ARRAY_00ed3070::instance[8] = 0;
            INT_ARRAY_00ed3070::instance[9] = 0;
            INT_ARRAY_00ed3070::instance[10] = 0;
            INT_ARRAY_00ed3070::instance[0xb] = 0;
            INT_ARRAY_00ed3070::instance[0xc] = 0;
            INT_ARRAY_00ed3070::instance[0xd] = 0;
            INT_ARRAY_00ed3070::instance[0xe] = 0;
            INT_ARRAY_00ed3070::instance[0xf] = 0;
            INT_ARRAY_00ed3070::instance[0x10] = 0;
            INT_ARRAY_00ed3070::instance[0x11] = 0;
            INT_ARRAY_00ed3070::instance[0x12] = 0;
            INT_ARRAY_00ed3070::instance[0x13] = 0;
            INT_ARRAY_00ed3070::instance[0x14] = 0;
            INT_ARRAY_00ed3070::instance[0x15] = 0;
            INT_ARRAY_00ed3070::instance[0x16] = 0;
            INT_ARRAY_00ed3070::instance[0x17] = 0;
            INT_ARRAY_00ed3070::instance[0x18] = 0;
            INT_ARRAY_00ed3070::instance[0x19] = 0;
            INT_ARRAY_00ed3070::instance[0x1a] = 0;
            INT_ARRAY_00ed3070::instance[0x1b] = 0;
            INT_ARRAY_00ed3070::instance[0x1c] = 0;
            INT_ARRAY_00ed3070::instance[0x1d] = 0;
            INT_ARRAY_00ed3070::instance[0x1e] = 0;
            INT_ARRAY_00ed3070::instance[0x1f] = 0;
            INT_ARRAY_00ed3070::instance[0x20] = 0;
            INT_ARRAY_00ed3070::instance[0x21] = 0;
            INT_ARRAY_00ed3070::instance[0x22] = 0;
            INT_ARRAY_00ed3070::instance[0x23] = 0;
            INT_ARRAY_00ed3070::instance[0x24] = 0;
            INT_ARRAY_00ed3070::instance[0x25] = 0;
            INT_ARRAY_00ed3070::instance[0x26] = 0;
            INT_ARRAY_00ed3070::instance[0x27] = 0;
        }
        _event2 = (InGameEventUnionVersion*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[0]);
        do {
            if (_event2->header.tl_type == 3) {
                iVar4 = (_event2->data).scenario.ScenarioEventType;
                if (((iVar4 == 1) || (iVar4 == 0x1b)) && *(char*)((int)&_event2->data + 0xf) != '\0') {
                    INT_00ec02e8::instance = 1;
                }
                iVar4 = (_event2->data).scenario.ScenarioEventType;
                if ((!iVar4) || (iVar4 == 0x1a)) {
                    if ((DAT_GameCore::instance.gameSuspended != 1)
                        || (iVar4 = iVar5 + 1, DAT_MapPropertiesState::instance.eventsCount <= iVar4))
                        goto LAB_004d7613;
                    pIVar4
                        = (InGameEventUnionVersion*)((int)&DAT_MapPropertiesState::instance.scenarioEvents[iVar5 + 1]);
                    break;
                }
            }
            iVar5 = iVar5 + 1;
            _event2 = _event2 + 0xe4;
            if (DAT_MapPropertiesState::instance.eventsCount <= iVar5) {}
        } while (true);
        while (true) {
            iVar5 = iVar3;
            iVar4 = iVar4 + 1;
            pIVar4 = pIVar4 + 0xe4;
            if (DAT_MapPropertiesState::instance.eventsCount <= iVar4)
                break;
            iVar3 = iVar5;
            if (pIVar4->header.tl_type == 3
                && (iVar2 = (pIVar4->data).scenario.ScenarioEventType, !iVar2 || (iVar2 == 0x1a))
                && (iVar2 = pIVar4->header.year,
                    DAT_GameState::instance.mapAndTime.year < iVar2
                        || ((iVar3 = iVar4,
                            iVar2 == DAT_GameState::instance.mapAndTime.year
                                && (DAT_GameState::instance.mapAndTime.month < pIVar4->header.month)))))
                break;
        }
    LAB_004d7613:
        iVar4 = 0;
        pSVar7 = DAT_MapPropertiesState::instance.scenarioEvents[iVar5].data.scenario.conditions;
        pIVar6 = DAT_MapPropertiesState::instance.SEC_EventsExtra + iVar5;
        do {
            iVar5 = pIVar6->conditionIsTrue[iVar4];
            INT_ARRAY_00ed2630::instance[iVar4] = (int)(char)pSVar7->enabled;
            short sVar1 = pSVar7->value;
            INT_ARRAY_00ed3070::instance[iVar4] = iVar5;
            INT_ARRAY_00ed2fc8::instance[iVar4] = (int)sVar1;
            if (iVar4 == 4 || iVar4 == 5 || iVar4 == 6 || iVar4 == 0x11 || iVar4 == 7 || iVar4 == 1) {
                iVar5 = MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::getDifficultyMultipliedValue,
                    DAT_MapPropertiesState::ptr)((int)sVar1);
                INT_ARRAY_00ed2fc8::instance[iVar4] = iVar5;
            }
            INT_ARRAY_00eb1238::instance[iVar4] = (int)(char)pSVar7->subType;
            iVar4 = iVar4 + 1;
            pSVar7 = pSVar7 + 1;
        } while (iVar4 < 0x28);
    }

}
}
