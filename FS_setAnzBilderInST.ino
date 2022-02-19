

// *********************************************************************
void mFunc_anzBilderInST(uint8_t param)
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
    lcd.print(F("Anzahl Bilder in ST"));
    // Reset Button Value
    g_anzahlbilderinST_value = 1;

    // Disable the screensaver for this function until it is closed
   //  LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    if (LCDML.BT_checkUp()) // check if button UP is pressed
    {
      LCDML.BT_resetUp(); // reset the left button
      g_anzahlbilderinST_value++;
    }
    if (LCDML.BT_checkDown()) // check if button DOWN is pressed
    {
      LCDML.BT_resetDown(); // reset the left button
      g_anzahlbilderinST_value--;
    }

    if (g_anzahlbilderinST_value < 3)
    {
      g_anzahlbilderinST_value = 6;
    }
    if (g_anzahlbilderinST_value > 6)
    {
      g_anzahlbilderinST_value = 3;
    }

    // update LCD content
    lcd.setCursor(1, 2); // set cursor
    lcd.print("       ");
    lcd.setCursor(1, 2); // set cursor
    lcd.print(g_anzahlbilderinST_value); // print change content


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
