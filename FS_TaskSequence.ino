

void runSequence() {
  // set motor parameter

  driver.microsteps(g_microstep_value);
  stepper.setMaxSpeed(max_speed);

  if (bild_count == 0)  // erstes Bild
  {
    if (DEBUG) {
      Serial.println("----------- Start Sequence -------------");
      Serial.print("Microstep: ");
      Serial.println(g_microstep_value);
      Serial.print("Speed: ");
      Serial.println(max_speed);
      Serial.print("Aktuelle Position: ");
      Serial.println(stepper.currentPosition());
      Serial.print("Aktuelles Bild: ");
      Serial.println(bild_count);
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
    // LCDML.FUNC_disableScreensaver();


    // the quit button works in every DISP function without any checks; it starts the loop_end function

    g_position_value = stepper.currentPosition();
    if (bild_count == 0 && stepper.distanceToGo() == 0) {
      shotPhoto();
      bild_count++;
      lcd.setCursor(8, 0);
      lcd.print(bild_count);
      lcd.setCursor(16, 0);
      lcd.print(g_bildanzahl_value);
      lcd.setCursor(0, 2);
      lcd.print(stepper.currentPosition());
      lcd.setCursor(10, 2);
      lcd.print(g_end_value);
      if (DEBUG) {
        Serial.println("Bild 0 ");
        Serial.print("Aktuelle Position: ");
        Serial.println(stepper.currentPosition());

        Serial.print("Aktuelles Bild: ");
        Serial.println(bild_count);
      }
    }
  }

  if (bild_count < g_bildanzahl_value) {
    if ( g_end_value > g_start_value) {
      if (DEBUG) {
        Serial.println("end > start ");
        Serial.print ("move +");
        Serial.print(realeAnzahlproStackschritt);
        Serial.println(" Schritte");
      }
      g_position_value += realeAnzahlproStackschritt;
      stepper.runToNewPosition(g_position_value);
    } else {
      if (DEBUG) {
        Serial.println("end < start ");
        Serial.print ("move -");
        Serial.print(realeAnzahlproStackschritt);
        Serial.println(" Schritte");
      }
      g_position_value -= realeAnzahlproStackschritt;
      stepper.runToNewPosition(g_position_value);
    }
  }


  if (bild_count < g_bildanzahl_value && stepper.distanceToGo() == 0) {
    shotPhoto();
    bild_count++;


    lcd.setCursor(8, 0); // set cursor
    lcd.print("        ");

    lcd.setCursor(8, 0);
    lcd.print(bild_count);
    lcd.setCursor(16, 0);
    lcd.print(g_bildanzahl_value);

    lcd.setCursor(0, 2); // set cursor
    lcd.print("         ");

    lcd.setCursor(0, 2);
    lcd.print(stepper.currentPosition());

    lcd.setCursor(10, 2);
    lcd.print(g_end_value);
    if (DEBUG) {
      Serial.print("Aktuelle Position: ");
      Serial.println(stepper.currentPosition());

      Serial.print("Aktuelles Bild: ");
      Serial.println(bild_count);
    }
  }

  if (bild_count == g_bildanzahl_value) {
    lcd.setCursor(0, 3);
    lcd.print(F("Sequence finished"));
  }
}
