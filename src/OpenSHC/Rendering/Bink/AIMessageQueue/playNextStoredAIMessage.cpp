#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BE960
        BOOLEnum AIMessageQueue::playNextStoredAIMessage()
        {
            char cVar1;
            char* pcVar3;
            char (*pacVar4)[100];
            char (*pacVar5)[100];
            int* piVar6;
            int iVar7;
            char (*pacVar8)[100];
            if (this->currentMessageVfxFile_0xc[0] != '\0') {
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(
                    1);
            }
            this->mbr_0x928 = 0;
            DAT_GameCore::instance.countdown = 2;
            this->currentMessageVfxFile_0xc[0] = '\0';
            this->currentMessageSfxFile_0x70[0] = '\0';
            this->currentMessageText_0x8 = (char*)0x0;
            this->messagePlaying_0x0 = FALSE;
            if (this->storedMessages_0x924) {
                piVar6 = this->savedMessageUnknownValue_0x104;
                this->currentMessageUnknownValue_0x4 = this->savedMessageUnknownValue_0x104[0];
                this->currentMessageUnknownValue2_0xd4 = this->savedMessageUnknownValue2_0x8fc[0];
                this->currentMessageText_0x8 = this->savedMessageTextPtr_0xdc[0];
                MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::playVideoOverMap, this)(
                    this->savedMessageVfxFile_0x12c[0], (char*)((int)(this->savedMessageSfxFile_0x514[0])));
                iVar7 = 1;
                if (1 < this->storedMessages_0x924) {
                    pacVar5 = this->savedMessageVfxFile_0x12c;
                    do {
                        pacVar8 = pacVar5 + 1;
                        piVar6[-10] = (int)piVar6[-9];
                        *piVar6 = piVar6[1];
                        pacVar4 = pacVar8;
                        do {
                            pcVar3 = *pacVar4;
                            pacVar4[-1][0] = *pcVar3;
                            pacVar4 = (char (*)[100])(*pacVar4 + 1);
                        } while (*pcVar3 != '\0');
                        pacVar5 = pacVar5 + 0xb;
                        int iVar2 = 900 - (int)pacVar5;
                        do {
                            cVar1 = (*pacVar5)[0];
                            *(char*)((int)pacVar5 + (int)pacVar8 + iVar2) = cVar1;
                            pacVar5 = (char (*)[100])(*pacVar5 + 1);
                        } while (cVar1 != '\0');
                        piVar6[0x1fe] = piVar6[0x1ff];
                        iVar7 = iVar7 + 1;
                        piVar6 = piVar6 + 1;
                        pacVar5 = pacVar8;
                    } while (iVar7 < this->storedMessages_0x924);
                }
                this->storedMessages_0x924 = this->storedMessages_0x924 + -1;
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
