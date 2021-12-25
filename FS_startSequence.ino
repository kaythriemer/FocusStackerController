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
    // remove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // setup
   
    // start thread 
    if(runSequenceTask.isEnabled() == false)
    {
      runSequenceTask.enable();
       bild_count = 0;
    }
    else
    {
      Serial.println(F("runSequenceTask is enabled"));
    }
    

    // end function and go an layer back
   // LCDML.FUNC_goBackToMenu(1);      // leave this function

    // Disable the screensaver for this function until it is closed
   // LCDML.FUNC_disableScreensaver();

  }

  if (LCDML.FUNC_close())    // ****** STABLE END *********
  {
        // start thread 
    if(runSequenceTask.isEnabled() == true)
    {
      runSequenceTask.disable();
    }
    else
    {
      Serial.println(F("runSequenceTask is disabled"));
    }
  }
}
