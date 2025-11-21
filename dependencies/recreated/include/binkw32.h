#ifndef BINKW32
#define BINKW32

/*
    Only contains declarations that are needed by OpenSHC to function.
    Switch to another Open Source library if extensions or other targets are needed.
*/

struct BINK {
    unsigned int Width;                 // Width (1 based, 640 for example)
    unsigned int Height;                // Height (1 based, 480 for example)
    unsigned int Frames;                // Number of frames (1 based, 100 = 100 frames)
    unsigned int FrameNum;              // Frame to *be* displayed (1 based)
    // ... object much bigger
};
typedef BINK* HBINK;

// SHC: Only flag used by BinkOpen
#define BINKNOSKIP 0x00080000L          // Don't skip frames if falling behind

// SHC: Only flag next to the surface type used by BinkCopyToBuffer
#define BINKCOPYALL 0x80000000L         // copy all pixels (not just changed)

// SHC: Only possible surfaces returned by BinkDDSurfaceType
#define BINKSURFACE555 9 
#define BINKSURFACE565 10

extern "C" __declspec(dllimport) HBINK          __stdcall BinkOpen              (const char* name, unsigned int flags);
extern "C" __declspec(dllimport) int            __stdcall BinkDoFrame           (HBINK bnk);
extern "C" __declspec(dllimport) void           __stdcall BinkNextFrame         (HBINK bnk);
extern "C" __declspec(dllimport) int            __stdcall BinkWait              (HBINK bnk);
extern "C" __declspec(dllimport) void           __stdcall BinkClose             (HBINK bnk);
extern "C" __declspec(dllimport) int            __stdcall BinkPause             (HBINK bnk, int pause);
extern "C" __declspec(dllimport) int            __stdcall BinkCopyToBuffer      (HBINK bnk, void* dest, int destpitch, int destheight, int destx, int desty, unsigned int flags);
extern "C" __declspec(dllimport) void           __stdcall BinkSetVolume         (HBINK bnk, unsigned int trackid, int volume);

struct BINKSND {
    // ... object much bigger
};
typedef                          unsigned int   (__stdcall* BINKSNDOPEN)        (BINKSND* BnkSnd, unsigned int freq, int bits, int chans, unsigned int flags, HBINK bink);
typedef                          BINKSNDOPEN    (__stdcall* BINKSNDSYSOPEN)     (unsigned int param);

extern "C" __declspec(dllimport) int            __stdcall BinkSetSoundSystem    (BINKSNDSYSOPEN open, unsigned int param);
extern "C" __declspec(dllimport) BINKSNDOPEN    __stdcall BinkOpenMiles         (unsigned int param);
#define BinkSoundUseMiles(hdigdriver)                     BinkSetSoundSystem    (BinkOpenMiles, (unsigned int)hdigdriver)

extern "C" __declspec(dllimport) int            __stdcall BinkDDSurfaceType     (void* lpDDS);

#endif // BINKW32
