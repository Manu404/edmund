#include "./hardware.h"

Hardware::Hardware(){
}

void Hardware::Initialize(){
  Serial.begin(SERIAL_SPEED);  
  Serial.println("init.");
  initScreen();
  initInputs();  
}

void Hardware::initInputs(){  
  pinMode(mapping.left, INPUT);
  pinMode(mapping.middle, INPUT);
  pinMode(mapping.right, INPUT);
  pinMode(mapping.pot, INPUT);
}

UIState Hardware::getState(){ 
  int left = digitalRead(mapping.left);
  int right = digitalRead(mapping.right);
  int middle = digitalRead(mapping.middle);
  float pot = analogRead(mapping.pot);
  
  return UIState 
  { 
    right,
    middle,
    left,
    pot, 
    left * right,    
    left * right * middle * (pot > 1020) * current.debug
  };
}

void Hardware::initScreen(){
  lcd.begin();
  lcd.setContrast(0x7f);
  lcd.setBias(0x7f);
}

void Hardware::Print(String m){
  lcd.print(m);
}

void Hardware::PrintLine(String m){
  lcd.println(m);
}

void Hardware::DrawSymbol(int x_pos, int y_pos, const uint8_t *logo){
  lcd.drawBitmap(x_pos * 9, y_pos * 10, logo, 9, 10, BLACK);
}

void Hardware::DrawNumeric(int x_pos, int y_pos, const uint8_t* logo) {
  lcd.drawBitmap(x_pos, y_pos, logo, 4, 5, BLACK);
}

void Hardware::DrawNumericWhite(int x_pos, int y_pos, const uint8_t* logo) {
  lcd.drawBitmap(x_pos, y_pos, logo, 4, 5, WHITE);
}

void Hardware::DrawScreen(const uint8_t* logo) {
  lcd.drawBitmap(0, 0, logo, 84, 48, BLACK);
}

int Hardware::isPressed(int prev, int curr){
  if(prev == curr) return 0;
  if(prev > curr) return -1;
  return 1;
}

int Hardware::IsRightPressed(){  
  return isPressed(previous.right, current.right) == -1;
}

int Hardware::IsLeftPressed(){  
  return isPressed(previous.left, current.left) == -1;
}

int Hardware::IsMiddlePressed(){  
  return isPressed(previous.middle, current.middle) == -1;
}

int Hardware::IsDebugPressed(){
  return isPressed(previous.debug, current.debug) == -1;
}

int Hardware::IsResetPressed(){
  return isPressed(previous.reset, current.reset) == -1;
}

int Hardware::HasPotChanged(){
  return previous.pot != current.pot;
}

float Hardware::GetPositionFromPot(float scale){
  float currentPos = (log(current.pot) - 1.39) / (5 / scale);
  if(currentPos > scale) currentPos = scale - 1;
  if(currentPos < 0) currentPos = 0.00f;
  return currentPos;
}

void Hardware::refreshInputs(){
  previous = current;  
  current = getState();
}

String Hardware::GetDebugLine(){
  return String(current.left) + String(current.middle) + String(current.right) + "|" + String(current.pot) + "|" + String(this->frameDuration) + "ms.";
}

void Hardware::clear(){
  lcd.clearDisplay();
}

void Hardware::display() {
  lcd.display();
}

void Hardware::BeginFrame(){
  this->frameStart = millis();
  this->clear();
  refreshInputs();
}

void Hardware::EndFrame() {
  this->display();  
  this->frameDuration = (millis() - this->frameStart);
  if(this->frameDuration < FRAME_DURATION_MS)
    delay(FRAME_DURATION_MS - this->frameDuration);
}

void Hardware::SaveStateToSpiff(GameState& state){
  stateArray.set(state);
}

GameState Hardware::LoadStateFromSpiff(){
  return stateArray.get();
}
