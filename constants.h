// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Three Cs DX constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "ThreeCsDX";
const char GAME_TITLE[] = "Ninja Ghost";
const bool FULLSCREEN = false;          // windowed or fullscreen
const UINT GAME_WIDTH = 1280;			// width of game in pixels
const UINT GAME_HEIGHT = 720;			// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

const int MAX_PLATFORMS = 30;
const int MAX_SHURIKEN = 5;
const int MAX_GUARDS = 25;
const int BULLETS_PER_GUARD = 10;

const int LEVEL1_GUARDS = 6;
const int LEVEL2_GUARDS = 11;

const int LEVEL1_PLATFORMS = 14;
const int LEVEL2_PLATFORMS = 21;

const float THROW_COOLDOWN = 0.9f;
const float KATANA_COOLDOWN = 0.7f;
const float FLINCH_DURATION = 0.5f;

const int MAX_LIVES = 3;

const int AMMO_PER_MELEE_KILL = 2;
const int AMMO_PER_RANGED_KILL = 1;
const int SCORE_PER_MELEE_KILL = 100;
const int SCORE_PER_RANGED_KILL = 50;
const float HEALTH_PER_MELEE_KILL = 50.0f;
const float HEALTH_PER_RANGED_KILL = 25.0f;

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
const UCHAR ATTACK_KEY	 = VK_LBUTTON;   // left button
const UCHAR THROW_KEY	 = VK_RBUTTON;   // right button

const UCHAR W_KEY		 = 0x57;
const UCHAR S_KEY		 = 0x53;
const UCHAR E_KEY		 = 0x45;

// texture images
const char KATANA_IMAGE[] = "images\\katana.png";
const char SHURIKEN_IMAGE[] = "images\\shuriken2.png";
const char GUARD_TEXTURE[] = "images\\guard2.png";
const char DOOR_IMAGE[] = "images\\door.png";

// splash screen images
const char MAIN_MENU_IMAGE[] = "images\\menu.png";
const char SPLASH1_IMAGE[] = "images\\splash1.png";
const char SPLASH2_IMAGE[] = "images\\splash2.png";
const char TUTORIAL_IMAGE[] = "images\\tutorial.png";

// States
enum GameStates {MAIN_MENU, TUTORIAL, INTRO1, LEVEL1, INTRO2, LEVEL2, GAME_OVER, GAME_COMPLETE};

// Pattern Step Actions
enum PATTERN_STEP_ACTION {NONE, LEFT, RIGHT};


#endif
