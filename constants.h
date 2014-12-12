// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility
//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "Rogue Class";
const char GAME_TITLE[] = "Rogue";
const bool FULLSCREEN = false;          // windowed or fullscreen
const UINT GAME_WIDTH = 1280;			// width of game in pixels
const UINT GAME_HEIGHT = 720;			// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

const int MAX_NUMBER_PARTICLES = 1000;
const float MAX_PARTICLE_LIFETIME = 1.5f;

const int NUM_SCORES = 10;

const int MAX_WALLS = 300;
const int MAX_CRATES = 50;
const int MAX_GUARDS = 50;

const float FLASH_DURATION = 3.0f;
const float FLINCH_DURATION = 0.5f;
const float ALERT_DURATION = 4.0f;
const float WALKING_NOISE = 500.0f;
const float SNEAKING_NOISE = 200.0f;
const int NUM_WEAPONS = 10;

// audio files
const char WAVE_BANK[] = "Sound\\Win\\Wave Bank.xwb";
const char SOUND_BANK[] = "Sound\\Win\\Sound Bank.xsb";

// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = VK_OEM_3;    // `~ key for U.S.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SPACE_KEY	 = VK_SPACE;	// spacebar
const UCHAR ATTACK_KEY	 = VK_LBUTTON;   // left button
const UCHAR THROW_KEY	 = VK_RBUTTON;   // right button

const UCHAR W_KEY		 = 0x57;
const UCHAR S_KEY		 = 0x53;
const UCHAR A_KEY		 = 0x41;
const UCHAR D_KEY		 = 0x44;
const UCHAR E_KEY		 = 0x45;

// texture images
const char PLAYER_TEXTURE[] = "images\\player2x.png";
const char WALL_TEXTURE[] = "images\\wall2x.png";
const char EXIT_TEXTURE[] = "images\\exit2x.png";
const char BLOOD_IMAGE[] = "images\\blood.png";

// splash screen images


// States
enum GameStates {MAIN_MENU, LEVEL1, LEVEL2, LEVEL3, SPLASH1, SPLASH2, SPLASH3, GAME_OVER, GAME_WIN, TUTORIAL};

#endif
