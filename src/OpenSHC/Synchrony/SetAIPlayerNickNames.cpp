#include "../Synchrony.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042A8E0
void Synchrony::SetAIPlayerNickNames()
{
    for (int player = 1; player < 9; ++player) {
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
            || DAT_GameSynchronyState::instance.currentAIArray[player] == AI::AIT_NULL) {
            continue;
        }
        switch (DAT_GameSynchronyState::instance.currentAIArray[player]) {
        case 1:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 111));
            break;
        case 2:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 119));
            break;
        case 3:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 127));
            break;
        case 4:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 135));
            break;
        case 5:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 143));
            break;
        case 6:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 151));
            break;
        case 7:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 159));
            break;
        case 8:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 167));
            break;
        case 9:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 175));
            break;
        case 10:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 183));
            break;
        case 11:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 191));
            break;
        case 12:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 199));
            break;
        case 13:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 207));
            break;
        case 14:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 215));
            break;
        case 15:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 223));
            break;
        case 16:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 231));
            break;
        }
    }
}

}
