#include "../Synchrony.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {

using DE::SHCDE::eTextSections;

// FUNCTION: STRONGHOLDCRUSADER 0x0042A8E0
void Synchrony::SetAIPlayerNickNames()
{
    char cVar1;
    char* pcVar2;
    char (*pacVar3)[250];
    GameSynchronyState* piVar4;
    char (*pacVar4)[250];
    pacVar4 = DAT_GameSynchronyState::instance.DAT_PlayerNames;
    piVar4 = (GameSynchronyState*)(&DAT_GameSynchronyState::instance.aiVariationArray + 1);
    do {
        pacVar4 = pacVar4 + 1;
        if ((piVar4->currentPlayerFullIDArray[1] == -1) && (piVar4->currentAIArray[1] != 0)) {
            switch (piVar4->currentAIArray[1]) {
            case 1:
                /*
                  AI Nicknames: rat
                 */
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x6f));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 2:
                /*
                  AI Nicknames: snake
                 */
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x77));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 3:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x7f));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 4:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x87));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 5:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x8f));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 6:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x97));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 7:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0x9f));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 8:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xa7));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 9:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xaf));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 10:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xb7));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 0xb:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xbf));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 0xc:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 199));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 0xd:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xcf));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 0xe:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xd7));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 0xf:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xdf));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
                break;
            case 0x10:
                pcVar2 = MACRO_CALL_MEMBER(
                    Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, (int)(piVar4->aiVariationArray[1] + 0xe7));
                pacVar3 = pacVar4;
                do {
                    cVar1 = *pcVar2;
                    (*pacVar3)[0] = cVar1;
                    pcVar2 = pcVar2 + 1;
                    pacVar3 = (char (*)[250])(*pacVar3 + 1);
                } while (cVar1 != '\0');
            }
        }
        piVar4 = (GameSynchronyState*)(piVar4->aiVariationArray + 2);
    } while ((int)piVar4 < 0x191dec4);
}

}
