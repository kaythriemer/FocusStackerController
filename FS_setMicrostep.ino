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

// uint32_t g_microstep_value = 0;

// unter Beachtung der Microsteps
// uint32_t steps_per_mm = 0;  
// uint32_t um_per_step = 0;  
// uint32_t max_speed = 0;



// *********************************************************************
void mFunc_microstep(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("press up or down"));
    lcd.setCursor(0, 1);
    lcd.print(F("microstep:"));

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    if (LCDML.BT_checkUp()) // check if button UP is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      i_step++;
    }
    if (LCDML.BT_checkDown()) // check if button DOWN is pressed
    {
      LCDML.BT_resetDown(); // reset the left button
      i_step--;
    }
    if (DEBUG)
    {
      Serial.println(i_step);
    }
    if (i_step < 0)
    {
      i_step = 8;
    }
    if (i_step > 8)
    {
      i_step = 0;
    }
    if (DEBUG)
    {
      Serial.println(i_step);
    }
    g_microstep_value = TMCmicrosteps[i_step];
    steps_per_mm = TMCsteps_per_mm[i_step];  
    um_per_step  = TMCum_per_step[i_step];  
    max_speed    = TMCspeed[i_step];
    if (DEBUG)
    {
      Serial.println(g_microstep_value);
    }

    // update LCD content
    lcd.setCursor(11, 1); // set cursor
    lcd.print("                   ");
    lcd.setCursor(11, 1); // set cursor
    lcd.print(g_microstep_value); // print change content


    // check if enter button is pressed
    if (LCDML.BT_checkEnter()) {
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
