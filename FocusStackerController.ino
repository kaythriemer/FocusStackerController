// ============================================================
// Example:     DisplayType - I2C LiquidCrystal
// ============================================================
// Description:
// This example includes the complete functionality over some
// tabs. All Tabs which are started with "LCDML_display_.."
// generates an output on the display / console / ....
// This example is for the author to test the complete functionality
// ============================================================
// *********************************************************************
// special settings
// *********************************************************************
// enable this line when you are not usigng a standard arduino
// for example when your chip is an ESP or a STM or SAM or something else

//#define _LCDML_cfg_use_ram

#define DEBUG 1

#define shutterPin 30
#define focusPin   34

// *********************************************************************
// includes
// *********************************************************************
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib2.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
// settings for LCD
#define _LCDML_DISP_cols  20
#define _LCDML_DISP_rows  4

#define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
#define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar

// LCD object
// for i2c there are many different steps for initialization, some are listed here
// when the rows and cols are not set here, they have to be set in the setup
//LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address
//LiquidCrystal_I2C lcd(0x27, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, _LCDML_DISP_cols, _LCDML_DISP_rows);
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const uint8_t scroll_bar[5][8] = {
  {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
  {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
  {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
  {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
  {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
};

// *********************************************************************
// Prototypes
// *********************************************************************
void lcdml_menu_display();
void lcdml_menu_clear();
void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************

float g_blende_value = 0; // blende value counter (global variable);
float g_massstab_value = 0;
long  g_position_value = 0; // position value counter (global variable)
long  stored_position = 0; // fuer Anzeige

float blenden [28] = {1.4, 1.6, 1.8, 2, 2.2, 2.5, 2.8, 3.2, 3.5, 4, 4.5 , 5 , 5.6, 6.3, 7.1, 8, 9, 10, 11, 13, 14, 16, 18, 20, 22, 25, 29, 32};
int i_blende = 0;

String s_massstab [18] = {"1:5", "1:4", "1:3", "1:2", "1:1", "1,5:1", "2:1", "2,5:1", "3:1", "3,5:1", "4:1", "4,5:1", "5:1",  "6:1", "7:1", "8:1", "9:1", "10:1"};
float    massstab [18] = { 0.2 ,  0.25,  0.33,  0.5 ,  1   ,  1.5   ,  2   ,  2.5   ,  3   ,  3.5   ,  4   ,  4.5   ,  5   ,   6   ,  7   ,  8   ,  9   ,  10   };
int i_massstab = 0;

uint32_t g_microstep_value = 0; // microstep value counter (global variable)
uint32_t TMCmicrosteps[9]   = {   0,    2,     4,      8,      16,       32,        64,        128,         256};
uint32_t TMCsteps_per_mm[9] = { 400,  800,  1600,   3200,    6400,    12800,     25600,      51200,      102400};
float    TMCum_per_step[9]  = { 2.5, 1.25, 0.625, 0.3125, 0.15625, 0.078125, 0.0390625, 0.01953125, 0.009765625};
uint32_t TMCspeed[9]        = { 800, 1024,  1024,   2500,    2500,     2500,      2500,       2500,        2500};
int i_step = 0;


// unter Beachtung der Microsteps
uint32_t steps_per_mm = 0;
uint32_t um_per_step = 0;
uint32_t max_speed = 800;

constexpr uint32_t acceleration = 500;
constexpr uint32_t current = 1000;

long g_start_value = 0; // blende value counter (global variable)
long g_end_value = 0; // end Position value  (global variable)

long g_bildanzahl_value = 0; // bildanzahl value counter (global variable)
long bild_count = 0;
long distanz = 0;

// *********************************************************************
// Objects
// *********************************************************************
LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
// LCDML_0        => layer 0
// LCDML_0_X      => layer 1
// LCDML_0_X_X    => layer 2
// LCDML_0_X_X_X  => layer 3
// LCDML_0_...      => layer ...

// LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)

LCDML_add         (0  , LCDML_0         , 1  , "Manual Drive"     , mFunc_manualDrive);       // this menu function can be found on "LCDML_display_menuFunction" tab

LCDML_add         (1  , LCDML_0         , 2  , "Settings"         , NULL);                    // NULL = no menu function
LCDML_add         (2  , LCDML_0_2       , 1  , "Massstab"         , mFunc_massstab);          // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (3  , LCDML_0_2       , 2  , "Blende"           , mFunc_blende);            // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (4  , LCDML_0_2       , 3  , "Wartezeit"        , mFunc_wartezeit);         // this menu function can be found on "LCDML_display_menuFunction" tab
LCDML_add         (5  , LCDML_0_2       , 4  , "Microstep"        , mFunc_microstep);

LCDML_add         (6  , LCDML_0         , 3  , "Calc Stack Param" , mFunc_calcStackParm);

LCDML_add         (7  , LCDML_0         , 4  , "Start/End Pos"    , NULL);
LCDML_add         (8  , LCDML_0_4       , 1  , "Set Start Pos"    , mFunc_setStartPosition);
LCDML_add         (9  , LCDML_0_4       , 2  , "Set End Pos"    , mFunc_setEndPosition);

LCDML_add         (10  , LCDML_0         , 5  , "Start Sequence"    , mFunc_startSequence);


LCDML_add         (11  , LCDML_0         , 6  , "Motor Test"    , mFunc_motorTest);


// ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

// menu element count - last element id
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    11

// create menu
LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// TMC Values

#include <TMCStepper.h>

#define EN_PIN           40 // Enable 38
#define DIR_PIN          46 // Direction 
#define STEP_PIN         44 // Step
#define CS_PIN           38 // Chip select


#define R_SENSE 0.075f // Match to your driver
// SilentStepStick series use 0.11
// UltiMachine Einsy and Archim2 boards use 0.2
// Panucatt BSD2660 uses 0.1
// Watterott TMC5160 uses 0.075


TMC5160Stepper driver = TMC5160Stepper(CS_PIN, R_SENSE);
//TMC5160Stepper driver = TMC5160Stepper(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

// lt. Datenblatt max 2500 puls per second

// Microsteps - steps/mm - um/ step          - max speed (steps/s)
//    0       -    400   -   2,5             -  800
//    2       -    800   -   1,25            - 1024
//    4       -   1600   -   0,625           - 1024
//    8       -   3200   -   0,3125          - 1024
//   16       -   6400   -   0,15625         - 2500
//   32       -  12800   -   0,078125        - 2500
//   64       -  25600   -   0,0390625       - 2500
//  128       -  51200   -   0,01953125      - 2500
//  256       - 102400   -   0,009765625     - 2500

// constexpr uint32_t micro_steps = 128;
// constexpr uint32_t steps_per_mm = 51200;  // unter Beachtung der Microsteps
// constexpr uint32_t max_speed = 2500;


int i = 0;


#include <AccelStepper.h>
AccelStepper stepper = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);

// *********************************************************************

// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{
  // serial init; only be needed if serial control is used
  Serial.begin(9600);                // start serial
  Serial.println(F(_LCDML_VERSION)); // only for examples

  // LCD Begin
  lcd.init();
  lcd.backlight();
  //lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  // some display types needs here the initialization


  // set special chars for scrollbar
  lcd.createChar(0, (uint8_t*)scroll_bar[0]);
  lcd.createChar(1, (uint8_t*)scroll_bar[1]);
  lcd.createChar(2, (uint8_t*)scroll_bar[2]);
  lcd.createChar(3, (uint8_t*)scroll_bar[3]);
  lcd.createChar(4, (uint8_t*)scroll_bar[4]);

  // LCDMenuLib Setup
  LCDML_setup(_LCDML_DISP_cnt);

  // Some settings which can be used

  // Enable Menu Rollover
  LCDML.MENU_enRollover();

  // Enable Screensaver (screensaver menu function, time to activate in ms)
  LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
  //LCDML.SCREEN_disable();

  // Some needful methods

  // You can jump to a menu function from anywhere with
  //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name


  // TMC Setup

  SPI.begin();

  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  driver.begin();             // Initiate pins and registeries
  driver.rms_current(current);    // Set stepper current to 1000mA.
  driver.en_pwm_mode(1);      // Enable extremely quiet stepping
  driver.pwm_autoscale(1);

  //*************
  driver.microsteps(g_microstep_value);

  stepper.setMaxSpeed(max_speed);
  stepper.setAcceleration(acceleration);

  stepper.setEnablePin(EN_PIN);
  stepper.setPinsInverted(false, false, true);
  stepper.enableOutputs();

  // init
  g_blende_value = blenden[0];
  i_blende = 0;
  // Reset Microstep Value
  g_microstep_value = TMCmicrosteps[0];
  i_step = 0;
  // Reset Button Value
  g_massstab_value = massstab[0];
  i_massstab = 0;
}

// *********************************************************************
// LOOP
// *********************************************************************
void loop()
{
  LCDML.loop();
  stepper.run();
}
