#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnum.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    using UI::Enums::TextMessageBLLookupStructTypeEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4E00
    void BottomLeftTextDisplayState::setBottomLeftTextDisplayText(int messageTypeUnk, int textGroupIndex,
        int textNumInGroup, TextMessageBLLookupStructUnion param_4, int importanceUnk, int displayDurationUnk)
    {
        int iVar1;
        TextMessageBLLookupStructTypeEnumInt TVar2;
        int iVar3;
        TextMessageBLLookupStructTypeEnumInt TVar4;
        TVar4 = ((TextMessageBLLookupStructTypeEnum)0);
        if (!messageTypeUnk) {
            /*
              basically clear!
             */
            this->currentlyDisplayedTextIsDisplayedUnk = 0;
        }
        if (this->currentlyDisplayedTextIsDisplayedUnk) {
            if (importanceUnk < this->currentlyDisplayedTextImportanceUnk) {}
            if (textGroupIndex == this->currentlyDisplayedUnkTextGroupIndex_0x4
                && textNumInGroup == this->currentlyDisplayedUnkTextNumInGroup_0x8
                && param_4.buildingType == this->currentlyDisplayedUnktextExtraObject.buildingType)
                goto LAB_004f4e46;
        }
        this->countdown = 0;
    LAB_004f4e46:
        this->currentlyDisplayedTextIsDisplayedUnk = messageTypeUnk;
        if (textGroupIndex == -1) {
            if (messageTypeUnk == 2) {
                TVar4 = UI::Enums::TMBLLSTE_BUILDING_TEXT;
            }
            if (DAT_RenderingDefinedData::instance.TextMessageLookupTable[0].messageType
                != (TextMessageBLLookupStructTypeEnum)0xffffffff) {
                iVar1 = 0;
                TVar2 = DAT_RenderingDefinedData::instance.TextMessageLookupTable[0].messageType;
                iVar3 = 0;
                do {
                    if (TVar4 == TVar2
                        && param_4.buildingType
                            == *(MappersEnum*)((int)&DAT_RenderingDefinedData::instance.TextMessageLookupTable[0]
                                                   .associatedType
                                + iVar1)) {
                        this->currentlyDisplayedUnkTextGroupIndex_0x4
                            = DAT_RenderingDefinedData::instance.TextMessageLookupTable[iVar3].textGroupIndex;
                        this->currentlyDisplayedUnkTextNumInGroup_0x8
                            = DAT_RenderingDefinedData::instance.TextMessageLookupTable[iVar3].textIndexInGroup;
                        break;
                    }
                    iVar1 = iVar3 * 0x10 + 0x10;
                    TVar2 = DAT_RenderingDefinedData::instance.TextMessageLookupTable[iVar3 + 1].messageType;
                    iVar3 = iVar3 + 1;
                } while (TVar2 != ((TextMessageBLLookupStructTypeEnum)0xffffffff));
            }
        } else {
            this->currentlyDisplayedUnkTextGroupIndex_0x4 = textGroupIndex;
            this->currentlyDisplayedUnkTextNumInGroup_0x8 = textNumInGroup;
            if (messageTypeUnk == 1 && textGroupIndex == 0x4d && textNumInGroup == 1) {
                /*
                  "Not enough workers available to run this building."
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)("placement_warning1.wav");
            }
        }
        this->currentlyDisplayedUnktextExtraObject = param_4;
        this->currentlyDisplayedTextImportanceUnk = importanceUnk;
        if (displayDurationUnk == -1) {
            this->textMessageDurationUnk = 0;
        }
        this->textMessageDurationUnk = displayDurationUnk;
        this->textMessageTime = timeGetTime();
    }

}
}
