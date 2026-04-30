/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuItem.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuItemRenderFunctionTypeInt.hpp"
#include "OpenSHC/UI/Enums/MenuItemTypeInt.hpp"
#include "OpenSHC/UI/Enums/UserControlIDShort.hpp"
#include "OpenSHC/UI/FwdMenuMenuItem.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuItemActionHandler.hpp"
#include "OpenSHC/UI/MenuItemCallbackParameter.hpp"
#include "OpenSHC/UI/MenuItemFirstItemTypeData.hpp"
#include "OpenSHC/UI/MenuItemPosition.hpp"
#include "OpenSHC/UI/MenuItemRenderFunction.hpp"
#include "OpenSHC/UI/MenuItemSecondItemTypeData.hpp"
#include "OpenSHC/UI/UnknownMenuSubStruct.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuItemActionHandler;
    using OpenSHC::UI::MenuItemCallbackParameter;
    using OpenSHC::UI::MenuItemFirstItemTypeData;
    using OpenSHC::UI::MenuItemPosition;
    using OpenSHC::UI::MenuItemRenderFunction;
    using OpenSHC::UI::MenuItemSecondItemTypeData;
    using OpenSHC::UI::UnknownMenuSubStruct;
    using OpenSHC::UI::Enums::MenuItemRenderFunctionTypeInt;
    using OpenSHC::UI::Enums::MenuItemTypeInt;
    using OpenSHC::UI::Enums::UserControlIDShort;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000050
    class MenuItem {
    public:
        MenuItemTypeInt menuItemType; // 0x00000000 length: 4
        MenuItemPosition position; // 0x00000004 length: 8
        int itemWidth; // 0x0000000C length: 4
        int itemHeight; // 0x00000010 length: 4
        MenuItemActionHandler* menuItemActionHandler; // 0x00000014 length: 4
        MenuItemCallbackParameter callbackParameter; // 0x00000018 length: 4
        MenuItemRenderFunction* menuItemRenderFunction; // 0x0000001C length: 4
        MenuItemFirstItemTypeData firstItemTypeData; // 0x00000020 length: 4
        MenuItemRenderFunctionTypeInt menuItemRenderFunctionType; // 0x00000024 length: 4
        int testNotEqualZero; // 0x00000028 length: 4
        UnknownMenuSubStruct textMessageLookupIndex; // 0x0000002C length: 4
        UserControlIDShort ucID; // 0x00000030 length: 2
        short hovering; // 0x00000032 length: 2
        short clicked; // 0x00000034 length: 2
        ushort iconDeactivatedUnk_0x36; // 0x00000036 length: 2
        short unknownZero; // 0x00000038 length: 2
        short field16_0x3a; // 0x0000003A length: 2
        MenuItemSecondItemTypeData secondItemTypeData; // 0x0000003C length: 16
        Menu* menuPointer; // 0x0000004C length: 4

    private:
        MenuItem(MenuItem const&);
        void operator=(MenuItem const&);

        MenuItem();
        ~MenuItem();

    public:
        BOOLEnum handleMenuElementsCallbacks();

        void prepareAndRenderMenuItems();

        void resetMenuItemStateUnk();
    };

    static_assert_cpp98_obj(sizeof(MenuItem) == 80, MenuItem);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
