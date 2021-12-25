

// *********************************************************************
int g_wartezeit_value = 0; // Wartezeit in s value counter (global variable)
void mFunc_wartezeit(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("press up or down"));
    lcd.setCursor(0, 1);
    lcd.print(F("Wartezeit(s): "));
    // Reset Button Value
    g_wartezeit_value = 1;

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    if (LCDML.BT_checkUp()) // check if button UP is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      g_wartezeit_value++;
    }
    if (LCDML.BT_checkDown()) // check if button DOWN is pressed
    {
      LCDML.BT_resetDown(); // reset the left button
      g_wartezeit_value--;
    }

    if (g_wartezeit_value < 0)
    {
      g_wartezeit_value = 10;
    }
    if (g_wartezeit_value > 10)
    {
      g_wartezeit_value = 0;
    }

    // update LCD content
    lcd.setCursor(14, 1); // set cursor
    lcd.print("       ");
    lcd.setCursor(14, 1); // set cursor
    lcd.print(g_wartezeit_value); // print change content


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
