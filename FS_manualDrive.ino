
// *********************************************************************

void mFunc_manualDrive(uint8_t param)
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
    lcd.print(F("Speed: "));
    lcd.setCursor(7, 1); // set cursor
    lcd.print(max_speed);

    lcd.setCursor(0, 2);
    lcd.print(F("Microstep: "));
    lcd.setCursor(11, 2); // set cursor
    lcd.print(g_microstep_value);

    lcd.setCursor(0, 3);
    lcd.print(F("Position: "));

    // Disable the screensaver for this function until it is closed
   // LCDML.FUNC_disableScreensaver();

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
      lcd.setCursor(11, 3); // set cursor
      lcd.print("         ");
    }
      lcd.setCursor(11, 3); // set cursor
      lcd.print(g_position_value); // print change content

    stepper.moveTo(g_position_value);

  }

  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
