#include "../Synchrony.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x0042A8E0
void Synchrony::SetAIPlayerNickNames()
{
    for (int player = 1; player < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++player) {
        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[player] != -1
            || DAT_GameSynchronyState::instance.currentAIArray[player] == AI::AITA_NULL) {
            continue;
        }
        switch (DAT_GameSynchronyState::instance.currentAIArray[player]) {
        case AI::AITA_RAT:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 111));
            break;
        case AI::AITA_SNAKE:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 119));
            break;
        case AI::AITA_PIG:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 127));
            break;
        case AI::AITA_WOLF:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 135));
            break;
        case AI::AITA_SALADIN:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 143));
            break;
        case AI::AITA_CALIPH:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 151));
            break;
        case AI::AITA_SULTAN:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 159));
            break;
        case AI::AITA_RICHARD:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 167));
            break;
        case AI::AITA_FREDERICK:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 175));
            break;
        case AI::AITA_PHILIPP:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 183));
            break;
        case AI::AITA_WAZIR:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 191));
            break;
        case AI::AITA_EMIR:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 199));
            break;
        case AI::AITA_NIZAR:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 207));
            break;
        case AI::AITA_SHERIFF:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 215));
            break;
        case AI::AITA_MARSHAL:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 223));
            break;
        case AI::AITA_ABBOT:
            strcpy(DAT_GameSynchronyState::instance.DAT_PlayerNames[player],
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                    DAT_GameSynchronyState::instance.aiVariationArray[player] + 231));
            break;
        }
    }
}

}
