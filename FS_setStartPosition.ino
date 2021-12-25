
// *********************************************************************

void mFunc_setStartPosition(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup function
    lcd.setCursor(0, 0);
    lcd.print(F("press left or right"));

    lcd.setCursor(0, 1);
    lcd.print(F("to go to start pos"));

    lcd.setCursor(0, 2);
    lcd.print(F("Position: "));

    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

    driver.microsteps(g_microstep_value);
    stepper.setMaxSpeed(max_speed);

    g_position_value = stepper.currentPosition();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    if (LCDML.BT_checkLeft()) // check if button LEFT is pressed
    {
      LCDML.BT_resetLeft(); // reset the left button
      g_position_value++;
    }

    if (LCDML.BT_checkRight()) // check if button Right is pressed
    {
      LCDML.BT_resetRight(); // reset the Right button
      g_position_value--;
    }


    // Neue Anzeige nur wenn sich wert geaendert hat , wegen flackern
    if (stored_position != g_position_value)
    {
      stored_position = g_position_value;
      lcd.setCursor(11, 2); // set cursor
      lcd.print("         ");
    }
      lcd.setCursor(11, 2); // set cursor
      lcd.print(g_position_value); // print change content
    

    // ToDo drive to new startposition
    stepper.moveTo(g_position_value);

    // check if enter button is pressed
    if (LCDML.BT_checkEnter()) {
      g_start_value = g_position_value;
      LCDML.FUNC_goBackToMenu();      // leave this function
    }
  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
