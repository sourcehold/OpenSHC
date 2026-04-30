/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/MenuHandlerState.hpp'
*/

#pragma once

#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/UI/MenuIDMenuElementAddressPair.hpp"
#include "OpenSHC/UI/UC.hpp"
#include "OpenSHC/UI/UCPointerStruct.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::Menu;
    using OpenSHC::UI::MenuIDMenuElementAddressPair;
    using OpenSHC::UI::UC;
    using OpenSHC::UI::UCPointerStruct;
    using OpenSHC::UI::Enums::MenuViewTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00000040
    class MenuHandlerState {
    public:
        MenuIDMenuElementAddressPair* pointerToMenuIDMenuElementAddressMap; // 0x00000000 length: 4
        Menu* currentMenu; // 0x00000004 length: 4
        UCPointerStruct ucPtrStruct; // 0x00000008 length: 4
        undefined1 padding_0xc[4]; // 0x0000000C length: 4
        int x; // 0x00000010 length: 4
        int y; // 0x00000014 length: 4
        BOOLEnum isBuildMenuTransitioning_0x18; // 0x00000018 length: 4
        dword const017; // 0x0000001C length: 4
        dword const516; // 0x00000020 length: 4
        int buildMenuBackgroundLeftShift_0x24; // 0x00000024 length: 4
        dword buildMenuItemsLeftShift_0x28; // 0x00000028 length: 4
        int buildMenuTransitionDirection_0x2c; // 0x0000002C length: 4
        int buildMenuTransitionStartTime_0x30; // 0x00000030 length: 4
        int buildMenuTransitionDuration_0x34; // 0x00000034 length: 4
        int buildMenuTransitionProgress_0x38; // 0x00000038 length: 4
        dword field18_0x3c; // 0x0000003C length: 4

    private:
        MenuHandlerState(MenuHandlerState const&);
        void operator=(MenuHandlerState const&);

        MenuHandlerState();
        ~MenuHandlerState();

    public:
        void setupBuildMenuState(dword param_1, dword param_2);

        void startBuildMenuTransition(int transitionDuration);

        void computeBuildMenuTransitionShift();

        void initializeUI(
            MenuIDMenuElementAddressPair* menuIDMenuElementAddressPair, UC* ucPtr, char* ptrStrongholdUCString);

        void setupMenuForRendering(MenuViewTypeInt menuID);
    };

    static_assert_cpp98_obj(sizeof(MenuHandlerState) == 64, MenuHandlerState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MenuHandlerState, false, Address::SHC_3BB0A8C1_0x00F2B390) pDAT_MenuHandlerState;

} // namespace UI
} // namespace OpenSHC
