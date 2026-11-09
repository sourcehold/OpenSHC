#include "../BottomLeftTextDisplayState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/TextMessageBLLookupStructTypeEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::MappersEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4E00
    void BottomLeftTextDisplayState::setBottomLeftTextDisplayText(int messageTypeUnk, int textGroupIndex,
        int textNumInGroup, int param_4, int importanceUnk, int displayDurationUnk)
    {
        if (messageTypeUnk == 0) {
            this->currentlyDisplayedTextIsDisplayedUnk = 0;
            return;
        }
        if (this->currentlyDisplayedTextIsDisplayedUnk != 0) {
            // a less important text doesn't replace the one shown
            if (importanceUnk < this->currentlyDisplayedTextImportanceUnk) {
                return;
            }
            if (textGroupIndex != this->currentlyDisplayedUnkTextGroupIndex_0x4
                || textNumInGroup != this->currentlyDisplayedUnkTextNumInGroup_0x8
                || param_4 != this->currentlyDisplayedUnktextExtraObject.buildingType) {
                this->countdown = 0;
            }
        } else {
            this->countdown = 0;
        }
        this->currentlyDisplayedTextIsDisplayedUnk = messageTypeUnk;
        if (textGroupIndex == -1) {
            // the text is looked up by the type of message and the object it is about
            // the index is set before the type, not in the for (in the for: quick_diff 0.9884 -> 0.9767)
            int i = 0;
            TextMessageBLLookupStructTypeEnumInt messageType = 0;
            if (messageTypeUnk == 2) {
                messageType = OpenSHC::UI::Enums::TMBLLSTE_BUILDING_TEXT;
            }
            for (; DAT_RenderingDefinedData::instance.TextMessageLookupTable[i].messageType != -1; ++i) {
                if (messageType == DAT_RenderingDefinedData::instance.TextMessageLookupTable[i].messageType
                    && param_4
                        == DAT_RenderingDefinedData::instance.TextMessageLookupTable[i].associatedType.buildingType) {
                    this->currentlyDisplayedUnkTextGroupIndex_0x4
                        = DAT_RenderingDefinedData::instance.TextMessageLookupTable[i].textGroupIndex;
                    this->currentlyDisplayedUnkTextNumInGroup_0x8
                        = DAT_RenderingDefinedData::instance.TextMessageLookupTable[i].textIndexInGroup;
                    break;
                }
            }
        } else {
            this->currentlyDisplayedUnkTextGroupIndex_0x4 = textGroupIndex;
            this->currentlyDisplayedUnkTextNumInGroup_0x8 = textNumInGroup;
            // "Not enough workers available to run this building."
            if (messageTypeUnk == 1 && textGroupIndex == 77 && textNumInGroup == 1) {
                // "placement_warning1.wav"
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    s_placement_warning1_wav_005ab8f4);
            }
        }
        this->currentlyDisplayedUnktextExtraObject.buildingType = (MappersEnum)param_4;
        this->currentlyDisplayedTextImportanceUnk = importanceUnk;
        if (displayDurationUnk != -1) {
            this->textMessageDurationUnk = displayDurationUnk;
            this->textMessageTime = timeGetTime();
        } else {
            this->textMessageDurationUnk = 0;
        }
    }

}
}
