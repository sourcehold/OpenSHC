/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuView.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/cdeclVoidFunc.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Enums::MenuViewType;
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

    public:
        MenuView();
        ~MenuView();

        // Constructor
        MenuView* Constructor_MenuView(
            MenuViewType menuID, cdeclVoidFunc* prepareMenuView, cdeclVoidFunc* doInitial, cdeclVoidFunc* doEveryFrame);

        MenuView* Constructor_MenuView_Reduced(MenuViewType menuType);
    };

    static_assert_cpp98_obj(sizeof(MenuView) == 24, MenuView);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
