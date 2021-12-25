void shotPhoto() {

long warte = g_wartezeit_value * 1000;
  
  if (DEBUG) {
    Serial.println("mache Foto: ");
    Serial.print("Wartezeit: ");
    Serial.println(warte);
  }
  
  
  delay(warte);
  digitalWrite(FOCUS_PIN, HIGH);
  delay(100);
  digitalWrite(SHUTTER_PIN, HIGH);
  delay(300);
  digitalWrite(SHUTTER_PIN, LOW);
  delay(100);
  digitalWrite(FOCUS_PIN, LOW);



}
