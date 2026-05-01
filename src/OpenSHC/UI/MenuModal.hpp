/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuModal.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuModalTypeInt.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuModalRenderFunction.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuModalRenderFunction;
    using OpenSHC::UI::Enums::MenuModalTypeInt;

#pragma pack(push, 1)

    // SIZE: 0x00000028
    class MenuModal {
    public:
        MenuModalTypeInt menuModalID; // 0x00000000 length: 4
        int x; // 0x00000004 length: 4
        int y; // 0x00000008 length: 4
        int width; // 0x0000000C length: 4
        int height; // 0x00000010 length: 4
        int borderStyle; // 0x00000014 length: 4
        int backgroundColourIndex; // 0x00000018 length: 4
        MenuModalRenderFunction* menuModalRenderFunction; // 0x0000001C length: 4
        Menu* pointerToMenu; // 0x00000020 length: 4
        MenuModal* pointerToNextModalMenu; // 0x00000024 length: 4

    private:
        MenuModal(MenuModal const&);
        void operator=(MenuModal const&);

        MenuModal();
        ~MenuModal();

    public:
        // Constructor
        MenuModal* Constructor_MenuModal(MenuModalTypeInt menuModalId, int xPos, int yPos, int width, int height,
            int borderStyle, int backgroundColourIndex, MenuModalRenderFunction* renderFunctionPtr, Menu* menuPtr);
    };

    static_assert_cpp98_obj(sizeof(MenuModal) == 40, MenuModal);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MenuModal, false, Address::SHC_3BB0A8C1_0x00DF51C8) pDAT_MenuModal;

} // namespace UI
} // namespace OpenSHC
