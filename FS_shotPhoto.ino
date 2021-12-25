void shotPhoto() {

long warte = g_wartezeit_value * 1000;
  
  if (DEBUG) {
    Serial.println("mache Foto: ");
    Serial.print("Wartezeit: ");
    Serial.println(warte);
  }
  
  
  delay(warte);
  digitalWrite(focusPin, HIGH);
  delay(50);
  digitalWrite(shutterPin, HIGH);
  delay(100);
  digitalWrite(focusPin, LOW);
  delay(10);
  digitalWrite(shutterPin, LOW);



}
