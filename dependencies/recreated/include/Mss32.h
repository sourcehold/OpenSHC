#ifndef MSS32
#define MSS32

/*
    Only contains declarations that are needed by OpenSHC to function.
    Switch to another Open Source library if extensions or other targets are needed.
*/

#include <windows.h>
#include <mmsystem.h>

struct _DIG_DRIVER {
    // ... object much bigger
};
typedef _DIG_DRIVER* HDIGDRIVER;

struct _SAMPLE {
    // ... object much bigger
};
typedef _SAMPLE* HSAMPLE;

// SHC: Maybe used as return for actions? But listed under "FILE_ERRS". There is a mentioning in a struct where 1 might
// indicate driver successfully init, but there is no mentioned connection to startup
#define AIL_NO_ERROR 0

// SHC: Maybe also used for STREAM status?
#define SMP_PLAYING 0x0004              // Sample is playing

// SHC: Format, used by set_sample_type and AIL_minimum_sample_buffer_size
#define DIG_F_16BITS_MASK 1
#define DIG_F_STEREO_MASK 2
#define DIG_F_STEREO_16 (DIG_F_STEREO_MASK | DIG_F_16BITS_MASK)

// SHC: Also present in mmsystem header
#define WAVE_FORMAT_PCM 1

extern "C" __declspec(dllimport) void*          __stdcall AIL_mem_alloc_lock                (unsigned int size);
extern "C" __declspec(dllimport) void           __stdcall AIL_mem_free_lock                 (void* ptr);

extern "C" __declspec(dllimport) int            __stdcall AIL_file_size                     (const char* filename);
extern "C" __declspec(dllimport) void*          __stdcall AIL_file_read                     (const char* filename, void* dest);

extern "C" __declspec(dllimport) int            __stdcall AIL_startup                       ();
extern "C" __declspec(dllimport) void           __stdcall AIL_shutdown                      ();
extern "C" __declspec(dllimport) void           __stdcall AIL_close_digital_driver          (HDIGDRIVER dig);
extern "C" __declspec(dllimport) int            __stdcall AIL_waveOutOpen                   (HDIGDRIVER* drvr, LPHWAVEOUT* lphWaveOut, int wDeviceID, LPWAVEFORMATEX lpFormat);             // SHC: unknown where "-1" for device ID comes from, did not find defined value
extern "C" __declspec(dllimport) char*          __stdcall AIL_set_redist_directory          (const char* dir);                                                                              // SHC: uses "miles", no idea from where

extern "C" __declspec(dllimport) HSAMPLE        __stdcall AIL_allocate_sample_handle        (HDIGDRIVER dig);
extern "C" __declspec(dllimport) void           __stdcall AIL_release_sample_handle         (HSAMPLE S);
extern "C" __declspec(dllimport) void           __stdcall AIL_init_sample                   (HSAMPLE S);
extern "C" __declspec(dllimport) int            __stdcall AIL_set_named_sample_file         (HSAMPLE S, const char* file_type_suffix, const void* file_image, int file_size, int block);
extern "C" __declspec(dllimport) void           __stdcall AIL_set_sample_type               (HSAMPLE S, int format, unsigned int flags);
extern "C" __declspec(dllimport) void           __stdcall AIL_start_sample                  (HSAMPLE S);
extern "C" __declspec(dllimport) void           __stdcall AIL_stop_sample                   (HSAMPLE S);
extern "C" __declspec(dllimport) void           __stdcall AIL_resume_sample                 (HSAMPLE S);
extern "C" __declspec(dllimport) void           __stdcall AIL_end_sample                    (HSAMPLE S);
extern "C" __declspec(dllimport) void           __stdcall AIL_set_sample_playback_rate      (HSAMPLE S, int playback_rate);
extern "C" __declspec(dllimport) void           __stdcall AIL_set_sample_volume             (HSAMPLE S, int volume);                                                                        // Sample volume 0-127
extern "C" __declspec(dllimport) void           __stdcall AIL_set_sample_pan                (HSAMPLE S, int pan);                                                                           // Mono panpot/stereo balance (0=L ... 127=R)
extern "C" __declspec(dllimport) void           __stdcall AIL_set_sample_loop_count         (HSAMPLE S, int loop_count);                                                                    // # of cycles-1 (1=one-shot, 0=indefinite)
extern "C" __declspec(dllimport) unsigned int   __stdcall AIL_sample_status                 (HSAMPLE s);
extern "C" __declspec(dllimport) int            __stdcall AIL_minimum_sample_buffer_size    (HDIGDRIVER dig, int playback_rate, int format);
extern "C" __declspec(dllimport) int            __stdcall AIL_sample_buffer_ready           (HSAMPLE S);                                                                                    // SHC: code suggests the returned value is the -1 if not, or buffer number is yes
extern "C" __declspec(dllimport) void           __stdcall AIL_load_sample_buffer            (HSAMPLE S, unsigned int buff_num, const void* buffer, unsigned int len);

struct _STREAM {
    // ... object much bigger
};
typedef _STREAM* HSTREAM;

extern "C" __declspec(dllimport) HSTREAM        __stdcall AIL_open_stream                   (HDIGDRIVER dig, const char* filename, int stream_mem);                                         // SHC: 0 used for mem (default, or no buffer?)
extern "C" __declspec(dllimport) void           __stdcall AIL_close_stream                  (HSTREAM stream);
extern "C" __declspec(dllimport) void           __stdcall AIL_start_stream                  (HSTREAM stream);
extern "C" __declspec(dllimport) void           __stdcall AIL_pause_stream                  (HSTREAM stream, int onoff);
extern "C" __declspec(dllimport) void           __stdcall AIL_set_stream_volume             (HSTREAM stream, int volume);                                                                   // SHC: Same as sample volume?
extern "C" __declspec(dllimport) void           __stdcall AIL_set_stream_loop_count         (HSTREAM stream, unsigned int count);                                                           // SHC: Same as sample loop count?
extern "C" __declspec(dllimport) int            __stdcall AIL_stream_status                 (HSTREAM stream);

// SHC: Needs implementation
                                 int            __cdecl   MSS_auto_cleanup                  ();
#define                                                   AIL_startup()                     (MSS_auto_cleanup(), AIL_startup())

#endif // MSS32
