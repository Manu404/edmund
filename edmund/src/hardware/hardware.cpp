   
#include "./hardware.h"
#include "../ui/font.h"
#include "rotary.h"

// ----------------------------------------------------
McpProvider* global_mcp;
Rotary rotary = Rotary(5, 6);
int global_encoder_value = 0;

void rte() {
  if (!global_mcp) return;
  if (!global_mcp->IsReady()) return;
  unsigned char result = rotary.process(global_mcp->digitalRead(1), global_mcp->digitalRead(2));
  if (result == DIR_CW) {
    global_encoder_value++;
  }
  else if (result == DIR_CCW) {
    global_encoder_value--;
  }
}
// ---------------------------------------------------- 

Hardware::Hardware():
  stateArray{ new ESPFlash<GameState>("/currentGame") },
  lcd{ new Adafruit_PCD8544(D0, D1, D3, D4, D2) },
  mcp_provider{ new McpProvider() },
  pinMapping{ PinMapping() },
  wire{ TwoWire() }{
}

Hardware::Hardware(Adafruit_PCD8544* _lcd, McpProvider* _mcp, ESPFlash<GameState>* _stateArray, PinMapping _mapping, TwoWire _wire) :
  stateArray(_stateArray),
  lcd(_lcd),
  mcp_provider{ _mcp },
  pinMapping(_mapping),
  wire(_wire) {
}

void Hardware::Initialize(){
  Serial.begin(SERIAL_SPEED);  
  Serial.println("init.");

  attachInterrupt(0, rte, CHANGE);
  global_mcp = mcp_provider;

  initScreen();
  initInputs();  
}

void Hardware::initInputs(){  
  mcp_provider->Initialize(D5, D6);
  mcp_provider->setupInterruptPinMode(pinMapping.DT, INPUT, CHANGE);
  mcp_provider->setupInterruptPinMode(pinMapping.CLK, INPUT, CHANGE);
  pinMode(pinMapping.pot, INPUT);
}

// https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
UIState Hardware::getState(){ 

  current_encoder_value = global_encoder_value;
  int direction = previous_encoder_value - current_encoder_value;
  previous_encoder_value = current_encoder_value;

  int middle = 0;
  float pot = analogRead(pinMapping.pot);
  int left = 0;
  int right = 0;

  return UIState 
  { 
    right,
    middle,
    left,
    pot, 
    left * right,    
    left * right * middle * (pot > 1020) * current.debug,
    direction
  };
}

void Hardware::initScreen(){
  lcd->begin();
  lcd->setContrast(0x7f);
  lcd->setBias(0x7f);
}

void Hardware::Print(String m){
  lcd->print(m);
}

void Hardware::PrintLine(String m){
  lcd->println(m);
}

void Hardware::PrintSymbol(int x_pos, int y_pos, const uint8_t *logo){
  lcd->drawBitmap(x_pos * 9, y_pos * 10, logo, 9, 10, BLACK);
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
      lcd->drawBitmap(x_pos + (char_w * ((length - digitsShift) - 1)) - (i < 3 && length == 3), y_pos, numericFont[currentValue], char_w, char_h, color);
    digitsShift += 1;
  }
}

void Hardware::DrawScreen(const uint8_t* logo) {
  lcd->drawBitmap(0, 0, logo, 84, 48, BLACK);
}

void Hardware::DrawBox(int x, int y, int w, int h, uint16_t color) {
  lcd->fillRect(x, y, w, h, color);
}

int Hardware::isPressed(int prev, int curr){
  return (prev == curr) ? (prev > curr ? -1 : 1) : 0;
}

int Hardware::IsEncoderTurnedRight() {
  return current.rotary_direction < 0;
}

int Hardware::IsEncoderTurnedLeft() {
  return current.rotary_direction > 0;
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

int Hardware::GetEncoderDelta() {
  return current.rotary_direction;
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
  return String(current.left) + String(current.middle) + String(current.right) + "|" + String(current.pot) + "|" + String(frameDuration) + "ms.";
}

void Hardware::clear(){
  lcd->clearDisplay();
}

void Hardware::display() {
  lcd->display();
}

void Hardware::BeginFrame(){
  frameStart = millis();
  clear();
  refreshInputs();
}

void Hardware::EndFrame() {
  display();  
  frameDuration = (millis() - frameStart);
  if(frameDuration < FRAME_DURATION_MS)
    delay(FRAME_DURATION_MS - frameDuration);
}

void Hardware::SaveStateToSpiff(const GameState& state){
  stateArray->set(state);
}

GameState Hardware::LoadStateFromSpiff(){
  return stateArray->get();
}
