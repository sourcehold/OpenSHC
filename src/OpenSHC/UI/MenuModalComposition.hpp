/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuModalComposition.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/UI/MenuModal.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuModal;
    using OpenSHC::UI::Enums::MenuModalTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0000007C
    class MenuModalComposition {
    public:
        int slot; // 0x00000000 length: 4
        MenuModal modalMenu; // 0x00000004 length: 40
        MenuModalTypeInt activeModalDialogID; // 0x0000002C length: 4
        dword modalDragDropUnk; // 0x00000030 length: 4
        dword mouseRelativeX; // 0x00000034 length: 4
        dword mouseRelativeY; // 0x00000038 length: 4
        dword sliderMinimum; // 0x0000003C length: 4
        dword sliderMaximum; // 0x00000040 length: 4
        undefined1 padding_0x44[8]; // 0x00000044 length: 8
        int textGroup; // 0x0000004C length: 4
        int textIndex; // 0x00000050 length: 4
        dword sliderValue; // 0x00000054 length: 4
        int* destination; // 0x00000058 length: 4
        short* destination2; // 0x0000005C length: 4
        pointer* sliderCallbackFunction; // 0x00000060 length: 4
        dword mbr_0x64; // 0x00000064 length: 4
        dword disappearAfter; // 0x00000068 length: 4
        dword mbr_0x6c; // 0x0000006C length: 4
        dword timeItIsSet; // 0x00000070 length: 4
        int minus1; // 0x00000074 length: 4
        dword mbr_0x78; // 0x00000078 length: 4

    private:
        MenuModalComposition(MenuModalComposition const&);
        void operator=(MenuModalComposition const&);

        MenuModalComposition();
        ~MenuModalComposition();

    public:
        // Constructor
        MenuModalComposition* Constructor_MenuModalComposition(int slot);

        void loadAllMenuElementsOfMenuModals();

        MenuModal* findModalMenu(MenuModalTypeInt menuModalID);

        void activateModalDialog(MenuModalTypeInt menuModalID, BOOLEnum retainOther);

        void setExtraActiveModalDialog(MenuModalTypeInt menuModalID, int dialogX, int dialogY);

        void handleActiveModalDialogUnk();

        void fillWithMenuModalDimensions(int* xPtr, int* yPtr, int* widthPtr, int* heigthPtr);

        void setSliderParameters(int minimum, int maximum, int value, undefined* destination, void* callbackFunction);

        void setSliderParameters2(
            dword minimum, dword maximum, dword value, dword destination, undefined* callbackFunction);

        void meth_0x4aa930(
            int param_1, int param_2, dword param_3, dword param_4, undefined* param_5, undefined* param_6);

        void renderMenuModal();

        void activateModalDialog2(MenuModalTypeInt modalDialogID);
    };

    static_assert_cpp98_obj(sizeof(MenuModalComposition) == 124, MenuModalComposition);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MenuModalComposition, false, Address::SHC_3BB0A8C1_0x02403678) pDAT_MenuModalComposition;

} // namespace UI
} // namespace OpenSHC
