

// *********************************************************************
void mFunc_blende(uint8_t param)
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
    lcd.print(F("Blende: "));
    // Reset Button Value
    g_blende_value = blenden[0];
    i_blende = 0;

    // Disable the screensaver for this function until it is closed
    // LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    if (LCDML.BT_checkUp()) // check if button UP is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      i_blende++;
    }
    if (LCDML.BT_checkDown()) // check if button DOWN is pressed
    {
      LCDML.BT_resetDown(); // reset the left button
      i_blende--;
    }

    if (i_blende < 0)
    {
      i_blende = 27;
    }
    if (i_blende > 27)
    {
      i_blende = 0;
    }

    g_blende_value = blenden[i_blende];

    // update LCD content
    lcd.setCursor(8, 1); // set cursor
    lcd.print("                   ");
    lcd.setCursor(8, 1); // set cursor
    lcd.print(g_blende_value, 1); // print change content



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
