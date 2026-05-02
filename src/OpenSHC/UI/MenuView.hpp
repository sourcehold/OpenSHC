/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuView.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuViewTypeInt;
    using OpenSHC::WindowsHelper::cdeclVoidFunc;

#pragma pack(push, 1)

    // SIZE: 0x00000018
    class MenuView {
    public:
        dword unknown_0x0; // 0x00000000 length: 4
        MenuViewTypeInt menuID; // 0x00000004 length: 4
        MenuView* nextMenuViewPtr; // 0x00000008 length: 4
        cdeclVoidFunc* prepare; // 0x0000000C length: 4
        cdeclVoidFunc* doInitial; // 0x00000010 length: 4
        cdeclVoidFunc* doEveryFrame; // 0x00000014 length: 4

    private:
        MenuView(MenuView const&);
        void operator=(MenuView const&);

        MenuView();
        ~MenuView();

    public:
        // Constructor
        MenuView* Constructor_MenuView(MenuViewTypeInt menuID, cdeclVoidFunc* prepareMenuView, cdeclVoidFunc* doInitial,
            cdeclVoidFunc* doEveryFrame);

        MenuView* Constructor_MenuView_Reduced(MenuViewTypeInt menuType);
    };

    static_assert_cpp98_obj(sizeof(MenuView) == 24, MenuView);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MenuView, false, Address::SHC_3BB0A8C1_0x00B983A4) pDAT_MenuView;

} // namespace UI
} // namespace OpenSHC
