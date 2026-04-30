/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/BottomLeftTextDisplayState.hpp'
*/

#pragma once

#include "OpenSHC/UI/TextMessageBLLookupStructUnion.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::TextMessageBLLookupStructUnion;

#pragma pack(push, 1)

    // SIZE: 0x00000024
    class BottomLeftTextDisplayState {
    public:
        dword currentlyDisplayedTextIsDisplayedUnk; // 0x00000000 length: 4
        dword currentlyDisplayedUnkTextGroupIndex_0x4; // 0x00000004 length: 4
        dword currentlyDisplayedUnkTextNumInGroup_0x8; // 0x00000008 length: 4
        TextMessageBLLookupStructUnion currentlyDisplayedUnktextExtraObject; // 0x0000000C length: 4
        int currentlyDisplayedTextImportanceUnk; // 0x00000010 length: 4
        int textMessageDurationUnk; // 0x00000014 length: 4
        int textMessageTime; // 0x00000018 length: 4
        int unknownCountdown01; // 0x0000001C length: 4
        dword countdown; // 0x00000020 length: 4

    private:
        BottomLeftTextDisplayState(BottomLeftTextDisplayState const&);
        void operator=(BottomLeftTextDisplayState const&);

        BottomLeftTextDisplayState();
        ~BottomLeftTextDisplayState();

    public:
        void setBottomLeftTextDisplayText(int messageTypeUnk, int textGroupIndex, int textNumInGroup,
            TextMessageBLLookupStructUnion param_4, int importanceUnk, int displayDurationUnk);

        void hasPassedCountdownOrDuration();

        void renderCurrentlyDisplayedTextConstructionCost(int param_1);
    };

    static_assert_cpp98_obj(sizeof(BottomLeftTextDisplayState) == 36, BottomLeftTextDisplayState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(BottomLeftTextDisplayState, false, Address::SHC_3BB0A8C1_0x00EE106C)
    pDAT_BottomLeftTextDisplayState;

} // namespace UI
} // namespace OpenSHC
