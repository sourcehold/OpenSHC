/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Menu.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuItemHandleStateInt.hpp"
#include "OpenSHC/UI/FwdMenuMenuItem.hpp"
#include "OpenSHC/UI/MenuItem.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::MenuItem;
    using OpenSHC::UI::Enums::MenuItemHandleStateInt;

#pragma pack(push, 1)

    // SIZE: 0x00000044
    class Menu {
    public:
        MenuItem* menuItemArray; // 0x00000000 length: 4
        int xPosition; // 0x00000004 length: 4
        int yPosition; // 0x00000008 length: 4
        int thousand; // 0x0000000C length: 4
        int one; // 0x00000010 length: 4
        int currentBuildMenuButtonShiftUnk_0x14; // 0x00000014 length: 4
        int zero; // 0x00000018 length: 4
        int mouseXScreenSpace; // 0x0000001C length: 4
        int mouseYScreenSpace; // 0x00000020 length: 4
        int field9_0x24; // 0x00000024 length: 4
        int field10_0x28; // 0x00000028 length: 4
        int field11_0x2c; // 0x0000002C length: 4
        int field12_0x30; // 0x00000030 length: 4
        int someTimestampUnk; // 0x00000034 length: 4
        MenuItem* hoveredItem; // 0x00000038 length: 4
        MenuItem* someMenuItemPtr_0x3c; // 0x0000003C length: 4
        int field16_0x40; // 0x00000040 length: 4

    private:
        Menu(Menu const&);
        void operator=(Menu const&);

        Menu();
        ~Menu();

    public:
        // Constructor
        Menu* Constructor_Menu(MenuItem* menuItemArrayAddress);

        void handleMenuItems(MenuItemHandleStateInt funcIndex);

        void updateMenuButtons();

        void renderConstructionMenu();

        void loadMenuElements(int ucPositionIndex);
    };

    static_assert_cpp98_obj(sizeof(Menu) == 68, Menu);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(Menu, false, Address::SHC_3BB0A8C1_0x00B983C0) pDAT_Menu;

} // namespace UI
} // namespace OpenSHC
