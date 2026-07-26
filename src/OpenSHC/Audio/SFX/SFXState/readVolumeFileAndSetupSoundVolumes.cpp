#include "../SFXState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_SpeechDefinedData.hpp"

namespace OpenSHC {
namespace Audio {
    namespace SFX {

        // FUNCTION: STRONGHOLDCRUSADER 0x0044AE90
        void SFXState::readVolumeFileAndSetupSoundVolumes()
        {
            if (this->DAT_SoundFileNameArrayMemoryPointer) {
                MACRO_CALL(OS_Func::_free_base)(this->DAT_SoundFileNameArrayMemoryPointer);
            }
            FILE* _File = MACRO_CALL(OS_Func::_fopen)(s_fx_volume_txt_005a4e08, s_rb_005a4e18);
            if (!_File) {
                return;
            }

            MACRO_CALL(OS_Func::_fseek)(_File, 0, FILE_END);
            long const _Size = MACRO_CALL(OS_Func::_ftell)(_File);
            MACRO_CALL(OS_Func::_fseek)(_File, 0, FILE_BEGIN);

            this->DAT_SoundFileNameArrayMemoryPointer = (char*)MACRO_CALL(OS_Func::_malloc)(_Size);
            MACRO_CALL(OS_Func::_fread)(this->DAT_SoundFileNameArrayMemoryPointer, 1, _Size, _File);
            MACRO_CALL(OS_Func::_fclose)(_File);

            int fileIndex = 0;
            int soundIndex = 0;
            int volume = 0;
            while (fileIndex < _Size) {
                while (fileIndex < _Size) {
                    while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '-'
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\"') {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                    if (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '-') {
                        break;
                    }
                    volume = 0;
                    do {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    } while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] < '0'
                        || '9' < this->DAT_SoundFileNameArrayMemoryPointer[fileIndex]);

                    while ('0' <= this->DAT_SoundFileNameArrayMemoryPointer[fileIndex]
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] <= '9') {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }

                    do {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    } while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] < '0'
                        || '9' < this->DAT_SoundFileNameArrayMemoryPointer[fileIndex]);

                    int isNegative = FALSE;
                    if (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex - 1] == '-') {
                        isNegative = TRUE;
                    }
                    while ('0' <= this->DAT_SoundFileNameArrayMemoryPointer[fileIndex]
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] <= '9') {
                        volume *= 10;
                        volume += this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] - 48;
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                    if (isNegative) {
                        volume = -volume;
                    }

                    while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\n'
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\r') {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                }

                while (fileIndex < _Size) {
                    if (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\"') {
                        break;
                    }
                    ++fileIndex;
                    this->DAT_SoundFileNamePointersArray[soundIndex]
                        = this->DAT_SoundFileNameArrayMemoryPointer + fileIndex;
                    while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\"'
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\r'
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\n') {

                        this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] = (char)MACRO_CALL(OS_Func::__tolower)(
                            this->DAT_SoundFileNameArrayMemoryPointer[fileIndex]);
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                    if (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] == '\"') {
                        this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] = '\0';
                    }
                    ++fileIndex;
                    while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] == ' '
                        || this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] == '\t') {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                    this->DAT_SoundVolumeArray[soundIndex] = 0;

                    // Read numbers by: Reading first char, transform to int (-48) and then combine with previous
                    // int * 10, to handle number index.
                    while ('0' <= this->DAT_SoundFileNameArrayMemoryPointer[fileIndex]
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] <= '9') {
                        this->DAT_SoundVolumeArray[soundIndex] *= 10;
                        this->DAT_SoundVolumeArray[soundIndex]
                            += this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] - 48;
                        ++fileIndex;
                        if (fileIndex < _Size) {
                            continue;
                        }
                        this->DAT_SoundVolumeArray[soundIndex] += volume;
                        if (this->DAT_SoundVolumeArray[soundIndex] < 0) {
                            this->DAT_SoundVolumeArray[soundIndex] = 0;
                        }
                        if (127 < this->DAT_SoundVolumeArray[soundIndex]) {
                            this->DAT_SoundVolumeArray[soundIndex] = 127;
                        }
                        goto break_parse;
                    }

                    this->DAT_SoundVolumeArray[soundIndex] += volume;

                    // Applies enough register pressure to produce the fitting opcodes, but does not look very nice
                    int& volumeRef = this->DAT_SoundVolumeArray[soundIndex];
                    if (volumeRef < 0) {
                        volumeRef = 0;
                    } else if (127 < volumeRef) {
                        volumeRef = 127;
                    }
                    while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\n'
                        && this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] != '\r') {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                    while (this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] == '\n'
                        || this->DAT_SoundFileNameArrayMemoryPointer[fileIndex] == '\r') {
                        ++fileIndex;
                        if (fileIndex >= _Size)
                            goto break_parse;
                    }
                    ++soundIndex;
                }
            }
        break_parse:

            this->DAT_SoundTotalCount = soundIndex;

            for (int i = 0; i < 1000; ++i) {
                if (!this->DAT_SoundStructures[i].pointerToFilename) {
                    continue;
                }
                this->DAT_SoundStructures[i].baseVolumePercentageUnk = MACRO_CALL_MEMBER(
                    SFXState_Func::getSoundVolumeForFilename, this)(this->DAT_SoundStructures[i].pointerToFilename);
            }

            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 8; ++j) {
                    DAT_SpeechDefinedData::instance.field5_0x41eb04[i].volumeUnk_0x28[j]
                        = MACRO_CALL_MEMBER(SFXState_Func::getSoundVolumeForFilename, this)(
                            DAT_SpeechDefinedData::instance.field5_0x41eb04[i].ambientWavs_0x8[j]);
                }
            }
        }

    }
}
}
