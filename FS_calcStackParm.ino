
// *********************************************************************
//
// schaerfentiefe = 2 * faktor * Blende * (massstab+1)/(massstab*massstab) (in mm)
// stackschritt = schaerfentiefe / Anzahl der Bilder in schaerfentiefe (in mm)
// theoretische stepgroesse = stackschritt / Anzahl steps pro Stackschritt * 1000 (in um)
// microsteps exponent = aufrunden(log(vollschrittgroesse/theoretische stepgroesse)/log(2))
// reale microsteps = 2 ^ microsteps exponent;

float g_schaerfentiefe_value = 0; // schaerfentiefe value counter (global variable)
float stackschritt = 0;
int anzahlBilderInSchaerfentiefe = 4;  // Todo Variable ?
int anzahlStepsProStackschritt = 10;  // Todo Variable ?
float theoretStepGroesse = 0;
float microstepExponent = 0;
float realeMicrosteps = 0;
float realeStepGroesse = 0;



float faktor = 0.02;
float vollschrittgroesse = 2.5; // in um

void mFunc_calcStackParm(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);


    // Reset Button Value
    g_schaerfentiefe_value = 0;

    // Disable the screensaver for this function until it is closed
   // LCDML.FUNC_disableScreensaver();

    g_schaerfentiefe_value = 2 * faktor * g_blende_value * ((g_massstab_value + 1) / (g_massstab_value * g_massstab_value));
    stackschritt = g_schaerfentiefe_value / anzahlBilderInSchaerfentiefe ;
    theoretStepGroesse = stackschritt / anzahlStepsProStackschritt * 1000;
    microstepExponent = ceil(log(vollschrittgroesse / theoretStepGroesse) / log(2.0));

    if (microstepExponent < 0 ) {
      microstepExponent = 0;
      realeMicrosteps = 0;
      realeStepGroesse = vollschrittgroesse / 1000;
    } else {
      realeMicrosteps = pow(2.0 , microstepExponent);
      realeStepGroesse = vollschrittgroesse / realeMicrosteps / 1000;
    }

    g_microstep_value = (int)(realeMicrosteps + 0.5); // wegen typecast float to int
    realeAnzahlproStackschritt = floor(stackschritt / realeStepGroesse);

    if (abs(realeMicrosteps) <= 0.0001) {
      max_speed = 800;
    } else if (realeMicrosteps > 1 && realeMicrosteps < 15) {
      max_speed = 1024;
    } else {
      max_speed = 2500;
    }

    if (DEBUG) {
      Serial.print("Blende: ");
      Serial.println(g_blende_value, 6);
      Serial.print("Massstab: ");
      Serial.println(g_massstab_value, 6);

      Serial.println("-------------------------");
      Serial.print("Schaerfentiefe: ");
      Serial.println(g_schaerfentiefe_value, 6);

      Serial.println("-------------------------");
      Serial.print("Anzahl Bilder in ST: ");
      Serial.println(anzahlBilderInSchaerfentiefe);
      Serial.print("Stackschritt: ");
      Serial.println(stackschritt, 6);
      Serial.println("-------------------------");
      Serial.print("Anzahl Steps pro Stackschritt: ");
      Serial.println(anzahlStepsProStackschritt);

      Serial.print("Theoretische Stepgroesse: ");
      Serial.println(theoretStepGroesse, 6);
      Serial.println("-------------------------");
      Serial.print("Exponent float: ");
      Serial.println(microstepExponent);

      Serial.print("reale Microsteps: ");
      Serial.println(realeMicrosteps);

      Serial.print("reale Microsteps setting: ");
      Serial.println(g_microstep_value);

      Serial.println("-------------------------");
      Serial.print("reale Stepgroesse: ");
      Serial.println(realeStepGroesse, 7);
      Serial.print("reale Anzahl Steps pro Stackschritt: ");
      Serial.println(realeAnzahlproStackschritt, 6);
      Serial.println("-------------------------");
      Serial.print("real Speed: ");
      Serial.println(max_speed);
    }

    // setup function
    // print LCD content
    lcd.setCursor(0, 0);
    lcd.print(F("Microsteps:"));
    lcd.setCursor(12, 0);
    lcd.print(realeMicrosteps, 0);
    lcd.setCursor(0, 1);
    lcd.print(F("Steps pro Move: "));
    lcd.setCursor(16, 1);
    lcd.print(realeAnzahlproStackschritt, 0);
    lcd.setCursor(0, 2);
    lcd.print(F("Speed: "));
    lcd.setCursor(7, 2);
    lcd.print(max_speed);
  }

  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    // the quit button works in every DISP function without any checks; it starts the loop_end function

  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
    // you can here reset some global vars or do nothing
  }
}
