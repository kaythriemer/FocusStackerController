// *********************************************************************
// ToDo set alle Variablen (aktuell/Ziel)
// Bildanzahl
// Schritte
// Zeit


void mFunc_startSequence(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // set motor parameter
    driver.microsteps(g_microstep_value);
    stepper.setMaxSpeed(max_speed);

    if (DEBUG) {

      Serial.println("----------- Start Sequence -------------");
      Serial.print("Microstep: ");
      Serial.println(g_microstep_value);
      Serial.print("Speed: ");
      Serial.println(max_speed);
      Serial.print("Aktuelle Position: ");
      Serial.println(stepper.currentPosition());
    }

    // setup function
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("BildNr:"));
    lcd.setCursor(0, 1);
    lcd.print(F("Position: "));
    // lcd.setCursor(0, 2);
    // lcd.print(F("Zeit: "));

    distanz = abs(g_end_value - g_start_value);

    g_bildanzahl_value = distanz / realeAnzahlproStackschritt;

    stepper.runToNewPosition(g_start_value);

    bild_count = 0;

    if (DEBUG) {
      Serial.print("Start: ");
      Serial.println(g_start_value);
      Serial.print("Ende: ");
      Serial.println(g_end_value);

      Serial.print("Distanz: ");
      Serial.println(distanz);

      Serial.print("Bildanzahl: ");
      Serial.println(g_bildanzahl_value);
    }


    // Disable the screensaver for this function until it is closed
    LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function

    while (bild_count <= g_bildanzahl_value && !LCDML.BT_checkEnter()) {
      g_position_value = stepper.currentPosition();
      if (bild_count == 0 && stepper.distanceToGo() == 0) {

        if (DEBUG) {
          Serial.println("Bild 0 ");
          Serial.print("Aktuelle Position: ");
          Serial.println(stepper.currentPosition());

          Serial.print("Aktuelles Bild: ");
          Serial.println(bild_count);
        }
        shotPhoto();
        bild_count++;
      }

      if (g_end_value > g_start_value) {
        if (DEBUG) {
          Serial.println("end > start ");
        }
        g_position_value = g_position_value + realeAnzahlproStackschritt;

      } else {
        if (DEBUG) {
          Serial.println("end < start ");
        }
        g_position_value = g_position_value - realeAnzahlproStackschritt;
      }

      stepper.runToNewPosition(g_position_value);

      if (bild_count <= g_bildanzahl_value && stepper.distanceToGo() == 0) {
        if (DEBUG) {
          Serial.print("Aktuelle Position: ");
          Serial.println(stepper.currentPosition());

          Serial.print("Aktuelles Bild: ");
          Serial.println(bild_count);
        }
        shotPhoto();

        lcd.setCursor(8, 0);
        lcd.print(bild_count);
        lcd.setCursor(16, 0);
        lcd.print(g_bildanzahl_value);
        lcd.setCursor(10, 1);
        lcd.print(stepper.currentPosition());
        lcd.setCursor(16, 1);
        lcd.print(g_end_value);

        bild_count++;
      }


    }
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
