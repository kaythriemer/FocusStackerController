
// *********************************************************************
int i_test = 0;
void mFunc_motorTest(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);


    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

    driver.microsteps(g_microstep_value);
    stepper.setMaxSpeed(max_speed);

    if (DEBUG) {
      Serial.println("Vor move ");
      Serial.print("Aktuelle Position: ");
      Serial.println(stepper.currentPosition());
      Serial.print("i: ");
      Serial.println(i_test);
    }

    // stepper.moveTo(1000);
    stepper.runToNewPosition(-1000);


    if (DEBUG) {
      Serial.println("nach move ");
      Serial.print("Aktuelle Position: ");
      Serial.println(stepper.currentPosition());
      Serial.print("i: ");
      Serial.println(i_test);
    }

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    i_test++;

    Serial.print("i_loop: ");
    Serial.println(i_test);

    g_position_value = stepper.currentPosition();

    g_position_value = g_position_value - 100;

    stepper.runToNewPosition(g_position_value);

    if (LCDML.BT_checkLeft()) // check if button LEFT is pressed
    {
      LCDML.BT_resetLeft(); // reset the left button
      if (DEBUG ) {

        Serial.print("Left Pressed: ");


      }
    }



    if (DEBUG ) {
      Serial.println("in loop");
      Serial.print("Aktuelle Position: ");
      Serial.println(stepper.currentPosition());

    }
    // check if enter button is pressed
    if (LCDML.BT_checkEnter()) {
      g_end_value = g_position_value;
      LCDML.FUNC_goBackToMenu();      // leave this function
    }

  }

  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
