#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046D390
    char* __cdecl GetStringBasedOnHardcodedMaps(char* mapName, int* hardcodedMapDescriptionGroupNum)
    {
        *hardcodedMapDescriptionGroupNum = 0;
        switch (MACRO_CALL(OS_Func::__toupper)(mapName[0])) {
        case 'A':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_A_resourceful_divide_005a61ac) == 0) {
                    *hardcodedMapDescriptionGroupNum = 2;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 1);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'W') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_A_New_Land_005a61a0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 112;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 111);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'F') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_A_Friend_Indeed_005a6190) == 0) {
                    *hardcodedMapDescriptionGroupNum = 62;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 61);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'T') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Antioch_005a6188) == 0) {
                    *hardcodedMapDescriptionGroupNum = 88;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 87);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_A_Mighty_Oasis_005a6178) == 0) {
                    *hardcodedMapDescriptionGroupNum = 94;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 93);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Armenia_005a6170) == 0) {
                    *hardcodedMapDescriptionGroupNum = 84;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 83);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'N') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Arnon_River_005a6164) == 0) {
                    *hardcodedMapDescriptionGroupNum = 124;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 123);
                }
            }
            break;
        case 'B':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Border_Patrol_005a6154) == 0) {
                    *hardcodedMapDescriptionGroupNum = 80;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 79);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'W') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Bow_Ridge_005a6148) == 0) {
                    *hardcodedMapDescriptionGroupNum = 12;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 11);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'O') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Broken_Dune_005a613c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 126;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 125);
                }
            }
            break;
        case 'C':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Centre_of_the_Oasis_005a6128) == 0) {
                    *hardcodedMapDescriptionGroupNum = 14;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 13);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 32) {
                if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'E') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Close_Encounters_005a6114) == 0) {
                        *hardcodedMapDescriptionGroupNum = 32;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 31);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'P') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Crete_Peninsula_005a6104) == 0) {
                        *hardcodedMapDescriptionGroupNum = 134;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 133);
                    }
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'S') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Cactus_Valley_005a60f4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 96;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 95);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'N') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Canyons_005a60ec) == 0) {
                    *hardcodedMapDescriptionGroupNum = 98;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 97);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'D') {
                if (MACRO_CALL(OS_Func::__toupper)(mapName[7]) == 'R') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Crusader_Demo_005a60dc) == 0) {
                        *hardcodedMapDescriptionGroupNum = 110;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 109);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[7]) == 'S') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Cyclades_005a60d0) == 0) {
                        *hardcodedMapDescriptionGroupNum = 136;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 135);
                    }
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Caesarea_Swampland_005a60bc) == 0) {
                    *hardcodedMapDescriptionGroupNum = 128;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 127);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'U') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Coconut_Twist_005a60ac) == 0) {
                    *hardcodedMapDescriptionGroupNum = 130;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 129);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'Y') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Craggy_Cliffs_005a609c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 132;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 131);
                }
            }
            break;
        case 'D':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Desert_Island_Blues_005a6088) == 0) {
                    *hardcodedMapDescriptionGroupNum = 18;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 17);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Drawn_and_Quartered_005a6074) == 0) {
                    *hardcodedMapDescriptionGroupNum = 138;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 137);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'U') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Dunes_of_Nicaea_005a6064) == 0) {
                    *hardcodedMapDescriptionGroupNum = 140;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 139);
                }
            }
            break;
        case 'E':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'M') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Empty_Handed_005a6054) == 0) {
                    *hardcodedMapDescriptionGroupNum = 64;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 63);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'D') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Edessa_005a604c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 86;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 85);
                }
            }
            break;
        case 'F':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'L') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Flood_Plains_of_Jordan_005a6034) == 0) {
                    *hardcodedMapDescriptionGroupNum = 142;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 141);
                }
            }
            break;
        case 'G':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'B') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Green_Belt_005a6028) == 0) {
                    *hardcodedMapDescriptionGroupNum = 28;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 27);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'H') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Green_Haven_005a601c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 40;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 39);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Great_Euphrates_005a600c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 144;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 143);
                }
            }
            break;
        case 'H':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'Y') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Happy_Land_005a6000) == 0) {
                    *hardcodedMapDescriptionGroupNum = 30;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 29);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'H') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Height_Advantage_005a5fec) == 0) {
                    *hardcodedMapDescriptionGroupNum = 10;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 9);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 32) {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Hell_On_The_Hill_005a5fd8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 74;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 73);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'T') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Hilltop_Hideout_005a5fc8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 72;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 71);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'S') {
                if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'R') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Halys_River_005a5fbc) == 0) {
                        *hardcodedMapDescriptionGroupNum = 146;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 145);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'O') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Hills_of_Antioch_005a5fa8) == 0) {
                        *hardcodedMapDescriptionGroupNum = 150;
                        DAT_GameCore::instance.mapDescUseStringTable = 1;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 149);
                    }
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Hidden_Crater_005a5f98) == 0) {
                    *hardcodedMapDescriptionGroupNum = 148;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 147);
                }
            }
            break;
        case 'I':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'H') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Inches_Apart_005a5f88) == 0) {
                    *hardcodedMapDescriptionGroupNum = 54;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 53);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'A') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Island_Hoppin_005a5f78) == 0) {
                    *hardcodedMapDescriptionGroupNum = 38;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 37);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'A') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Its_a_jungle_out_there_005a5f60) == 0) {
                    *hardcodedMapDescriptionGroupNum = 70;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 69);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[7]) == 'C') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_In_The_canyons_005a5f50) == 0) {
                    *hardcodedMapDescriptionGroupNum = 98;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 97);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'T') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_In_The_Shadow_005a5f40) == 0) {
                    *hardcodedMapDescriptionGroupNum = 114;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 113);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'J') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Its_just_not_fair_005a5f2c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 122;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 121);
                }
            }
            break;
        case 'L':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'H') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Love_Thy_Neighbour_005a5f18) == 0) {
                    *hardcodedMapDescriptionGroupNum = 58;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 57);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'B') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Large_Barren_Desert_005a5f04) == 0) {
                    *hardcodedMapDescriptionGroupNum = 100;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 99);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Large_Island_005a5ef4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 102;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 101);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'F') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Land_of_the_Cactus_005a5ee0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 120;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 119);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'M') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Lacus_Magnus_005a5ed0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 152;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 151);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'O') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Lakes_of_Konya_005a5ec0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 154;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 153);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'A') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Lake_Qaddas_005a5eb4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 156;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 155);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 32) {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Litani_and_Jordan_005a5ea0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 158;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 157);
                }
            }
            break;
        case 'N':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 32) {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_No_Escape_005a5e94) == 0) {
                    *hardcodedMapDescriptionGroupNum = 34;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 33);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_North_vs_South_005a5e84) == 0) {
                    *hardcodedMapDescriptionGroupNum = 42;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 41);
                }
            }
            break;
        case 'M':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Marshy_Mayhem_005a5e74) == 0) {
                    *hardcodedMapDescriptionGroupNum = 66;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 65);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'L') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Melos_005a5e6c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 160;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 159);
                }
            }
            break;
        case 'O':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'S') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Oasis_Struggle_005a5e5c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 4;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 3);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'B') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Oasis_by_the_Sea_005a5e48) == 0) {
                    *hardcodedMapDescriptionGroupNum = 108;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 107);
                }
            }
            break;
        case 'P':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'G') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Piggy_in_the_middle_005a5e34) == 0) {
                    *hardcodedMapDescriptionGroupNum = 24;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 23);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 32) {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Pig_in_a_Poke_005a5e24) == 0) {
                    *hardcodedMapDescriptionGroupNum = 162;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 161);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'V') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Province_of_Bodrum_005a5e10) == 0) {
                    *hardcodedMapDescriptionGroupNum = 164;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 163);
                }
            }
            break;
        case 'R':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Riverside_Rampage_005a5dfc) == 0) {
                    *hardcodedMapDescriptionGroupNum = 68;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 67);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'O') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Rocky_Oasis_005a5df0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 104;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 103);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Reed_Sea_005a5de4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 166;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 165);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 32) {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Region_of_Corinth_005a5dd0) == 0) {
                    *hardcodedMapDescriptionGroupNum = 168;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 167);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'A') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Rock_Face_005a5dc4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 170;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 169);
                }
            }
            break;
        case 'S':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'L') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Sleeping_With_The_Enemy_005a5dac) == 0) {
                    *hardcodedMapDescriptionGroupNum = 56;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 55);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'T') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Strati_005a5da4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 172;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 171);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'B') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Small_Barren_Desert_005a5d90) == 0) {
                    *hardcodedMapDescriptionGroupNum = 82;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 81);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Small_Island_005a5d80) == 0) {
                    *hardcodedMapDescriptionGroupNum = 106;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 105);
                }
            }
            break;
        case 'T':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'Y') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Tyre_005a5d78) == 0) {
                    *hardcodedMapDescriptionGroupNum = 92;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 91);
                }
            } else {
                switch (MACRO_CALL(OS_Func::__toupper)(mapName[4])) {
                case 'O':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'L') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Tripoli_005a5d70) == 0) {
                            *hardcodedMapDescriptionGroupNum = 90;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 89);
                        }
                    } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'S') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Thasos_005a5d68) == 0) {
                            *hardcodedMapDescriptionGroupNum = 174;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 173);
                        }
                    }
                    break;
                case 'V':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'A') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Valley_005a5d5c) == 0) {
                            *hardcodedMapDescriptionGroupNum = 78;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 77);
                        }
                    }
                    break;
                case 'B':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'U') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Bulls_Eye_005a5d4c) == 0) {
                            *hardcodedMapDescriptionGroupNum = 22;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 21);
                        }
                    }
                    break;
                case 'C':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'O') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Too_Close_For_Comfort_005a5d34) == 0) {
                            *hardcodedMapDescriptionGroupNum = 6;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 5);
                        }
                    }
                    break;
                case 'E':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'A') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Target_Zone_005a5d28) == 0) {
                            *hardcodedMapDescriptionGroupNum = 16;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 15);
                        }
                    } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'R') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Trapesac_Island_005a5d18) == 0) {
                            *hardcodedMapDescriptionGroupNum = 178;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 177);
                        }
                    }
                    break;
                case 'F':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[7]) == 'D') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_ford_across_the_river_005a5cfc) == 0) {
                            *hardcodedMapDescriptionGroupNum = 8;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 7);
                        }
                    } else if (MACRO_CALL(OS_Func::__toupper)(mapName[7]) == 'E') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Forest_Oasis_005a5ce8) == 0) {
                            *hardcodedMapDescriptionGroupNum = 52;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 51);
                        }
                    }
                    break;
                case 'G':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'R') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Great_lake_005a5cd8) == 0) {
                            *hardcodedMapDescriptionGroupNum = 26;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 25);
                        }
                    } else if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'U') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Guardians_005a5cc8) == 0) {
                            *hardcodedMapDescriptionGroupNum = 48;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 47);
                        }
                    }
                    break;
                case 'K':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'I') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Killing_Plains_005a5cb4) == 0) {
                            *hardcodedMapDescriptionGroupNum = 36;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 35);
                        }
                    }
                    break;
                case 'L':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'A') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Last_Stand_005a5ca4) == 0) {
                            *hardcodedMapDescriptionGroupNum = 50;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 49);
                        }
                    }
                    break;
                case 'R':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'I') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_River_005a5c98) == 0) {
                            *hardcodedMapDescriptionGroupNum = 20;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 19);
                        }
                    }
                    break;
                case 'T':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'R') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Trench_005a5c8c) == 0) {
                            *hardcodedMapDescriptionGroupNum = 60;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 59);
                        }
                    }
                    break;
                case 'W':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'E') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Wet_Lands_005a5c7c) == 0) {
                            *hardcodedMapDescriptionGroupNum = 76;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 75);
                        }
                    }
                    break;
                case 'D':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'U') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Dunes_005a5c70) == 0) {
                            *hardcodedMapDescriptionGroupNum = 118;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 117);
                        }
                    }
                    break;
                case 'S':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[3]) == 'O') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Tilos_005a5c68) == 0) {
                            *hardcodedMapDescriptionGroupNum = 176;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 175);
                        }
                    }
                    break;
                case 'I':
                    if (MACRO_CALL(OS_Func::__toupper)(mapName[5]) == 'N') {
                        if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Two_in_a_bed_005a5c58) == 0) {
                            *hardcodedMapDescriptionGroupNum = 180;
                            DAT_GameCore::instance.mapDescUseStringTable = 1;
                            return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 179);
                        }
                    }
                    break;
                }
            }
            break;
        case 'U':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'P') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Upwards_Alliance_005a5c44) == 0) {
                    *hardcodedMapDescriptionGroupNum = 44;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 43);
                }
            }
            break;
        case 'W':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'S') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_West_Coast_005a5c38) == 0) {
                    *hardcodedMapDescriptionGroupNum = 46;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 45);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'T') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Watering_Holes_005a5c28) == 0) {
                    *hardcodedMapDescriptionGroupNum = 116;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 115);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[2]) == 'L') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Wall_of_Iron_005a5c18) == 0) {
                    *hardcodedMapDescriptionGroupNum = 182;
                    DAT_GameCore::instance.mapDescUseStringTable = 1;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)219, 181);
                }
            }
            break;
        }
        switch (MACRO_CALL(OS_Func::__toupper)(mapName[0])) {
        case 'B':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Best_Friends_005a5c08) == 0) {
                    *hardcodedMapDescriptionGroupNum = 94;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 93);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Bird_In_Flight_005a5bf8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 83;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 82);
                }
            }
            break;
        case 'C':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'O') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Coastal_Trap_005a5be8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 88;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 87);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'R') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Crossroads_005a5bdc) == 0) {
                    *hardcodedMapDescriptionGroupNum = 100;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 99);
                }
            }
            break;
        case 'D':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Divided_005a5bd4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 96;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 95);
                }
            }
            break;
        case 'E':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'N') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Enclosure_005a5bc8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 91;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 90);
                }
            }
            break;
        case 'F':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'U') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Fury_Bay_005a5bbc) == 0) {
                    *hardcodedMapDescriptionGroupNum = 84;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 83);
                }
            }
            break;
        case 'J':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Jealous_Neighbours_005a5ba8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 97;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 96);
                }
            }
            break;
        case 'L':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Lionheart_005a5b9c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 99;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 98);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'O') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Look_Out_005a5b90) == 0) {
                    *hardcodedMapDescriptionGroupNum = 82;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 81);
                }
            }
            break;
        case 'M':
            switch (MACRO_CALL(OS_Func::__toupper)(mapName[3])) {
            case 'D':
                if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'I') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Divided_005a5b84) == 0) {
                        *hardcodedMapDescriptionGroupNum = 102;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 101);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'O') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Downhill_Scrum_005a5b70) == 0) {
                        *hardcodedMapDescriptionGroupNum = 103;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 102);
                    }
                }
                break;
            case 'N':
                if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'M') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_No_Mans_Land_005a5b60) == 0) {
                        *hardcodedMapDescriptionGroupNum = 104;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 103);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[6]) == 'W') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_No_Where_to_Hide_005a5b4c) == 0) {
                        *hardcodedMapDescriptionGroupNum = 105;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 104);
                    }
                }
                break;
            case 'S':
                if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'L') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Slopes_of_Doom_005a5b38) == 0) {
                        *hardcodedMapDescriptionGroupNum = 106;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 105);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'N') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Snake_River_005a5b28) == 0) {
                        *hardcodedMapDescriptionGroupNum = 107;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 106);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'U') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Surrounded_005a5b18) == 0) {
                        *hardcodedMapDescriptionGroupNum = 108;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 107);
                    }
                }
                break;
            case 'T':
                if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'H') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_The_Rocky_Divide_005a5b04) == 0) {
                        *hardcodedMapDescriptionGroupNum = 109;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 108);
                    }
                } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'W') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Two_Falls_005a5af4) == 0) {
                        *hardcodedMapDescriptionGroupNum = 110;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 109);
                    }
                }
                break;
            case 'V':
                if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'A') {
                    if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_MP_Valley_of_the_Lords_005a5adc) == 0) {
                        *hardcodedMapDescriptionGroupNum = 111;
                        return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 110);
                    }
                }
                break;
            }
            break;
        case 'P':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'H') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Phoenix_005a5ad4) == 0) {
                    *hardcodedMapDescriptionGroupNum = 87;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 86);
                }
            }
            break;
        case 'R':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Rivers_Fork_005a5ac8) == 0) {
                    *hardcodedMapDescriptionGroupNum = 90;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 89);
                }
            }
            break;
        case 'S':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'N') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Snake_River_005a5abc) == 0) {
                    *hardcodedMapDescriptionGroupNum = 85;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 84);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'P') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Spider_Island_005a5aac) == 0) {
                    *hardcodedMapDescriptionGroupNum = 95;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 94);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'W') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Swampy_Island_005a5a9c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 86;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 85);
                }
            }
            break;
        case 'T':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'H') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_The_Host_005a5a90) == 0) {
                    *hardcodedMapDescriptionGroupNum = 93;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 92);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[4]) == 'E') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Three_Little_Pigs_005a5a7c) == 0) {
                    *hardcodedMapDescriptionGroupNum = 98;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 97);
                }
            }
            break;
        case 'U':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'L') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Ultimate_Victory_005a5a68) == 0) {
                    *hardcodedMapDescriptionGroupNum = 101;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 100);
                }
            }
            break;
        case 'W':
            if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'A') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Wazirs_Fortress_005a5a58) == 0) {
                    *hardcodedMapDescriptionGroupNum = 89;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 88);
                }
            } else if (MACRO_CALL(OS_Func::__toupper)(mapName[1]) == 'I') {
                if (MACRO_CALL(OS_Func::__stricmp)(mapName, s_Wide_Open_Plain_005a5a48) == 0) {
                    *hardcodedMapDescriptionGroupNum = 92;
                    return MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((DE::SHCDE::eTextSections)245, 91);
                }
            }
            break;
        }
        return mapName;
    }

} // namespace Global
} // namespace OpenSHC
