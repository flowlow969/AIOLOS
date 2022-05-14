
void sendToPi(String& s){
  Serial.println(s);
}

void myDebug(String s){
  #ifdef MYDEBUG
  Serial.print(s);
  #endif
}
