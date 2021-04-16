#include "./hardware.h"
#include <SPI.h>     
#include "font.h"

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

void Hardware::PrintSymbol(int x_pos, int y_pos, const uint8_t *logo){
  lcd.drawBitmap(x_pos * 9, y_pos * 10, logo, 9, 10, BLACK);
}

void Hardware::PrintSmallNumeric(int x_pos, int y_pos, int value, uint16_t color, int length) {
  int char_w = 4, char_h = 5;
  int digitsShift = 0, currentValue = 0, maxRange = 3;
  int debug = value == 42;
  for (int i = 1; i <= maxRange; i++) {
    int p = pow(10, i);
    currentValue = (value % p) / (p / 10);
    value = value - currentValue;
    if ((length - i) < 0) continue;
    if (!(currentValue == 0 && i == 3)) // don't print on leading 0 for hundred
      lcd.drawBitmap(x_pos + (char_w * ((length - digitsShift) - 1)) - (i < 3 && length == 3), y_pos, numericFont[currentValue], char_w, char_h, color);
    digitsShift += 1;
  }
}

void Hardware::DrawScreen(const uint8_t* logo) {
  lcd.drawBitmap(0, 0, logo, 84, 48, BLACK);
}

void Hardware::DrawBox(int x, int y, int w, int h, uint16_t color) {
  lcd.fillRect(x, y, w, h, color);
}

int Hardware::isPressed(int prev, int curr){
  if(prev == curr) return 0;
  if(prev > curr) return -1;
  return 1;
}

int Hardware::IsRightPressed() {  
  return isPressed(previous.right, current.right) == -1;
}

int Hardware::IsLeftPressed() {  
  return isPressed(previous.left, current.left) == -1;
}

int Hardware::IsMiddlePressed() {  
  return isPressed(previous.middle, current.middle) == -1;
}

int Hardware::IsDebugPressed() {
  return isPressed(previous.debug, current.debug) == -1;
}

int Hardware::IsResetPressed() {
  return isPressed(previous.reset, current.reset) == -1;
}

int Hardware::HasPotChanged() {
  return previous.pot != current.pot;
}

float Hardware::GetPositionFromPot(float scale) {
  // log, resistor biased +5 top
  return (1024 * exp(log(((float)current.pot / 1024)))) / (1024 / scale);
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
