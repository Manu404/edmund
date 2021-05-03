#include "gmock/gmock.h"
#include "outputapi.h"

class MockIPCD8544Api : public Edmund::Hardware::IPCD8544Api {
 public:
  ~MockIPCD8544Api() { }
  MOCK_METHOD0(begin, void());
  MOCK_METHOD0(initDisplay, void());
  MOCK_METHOD1(setRotation, void(byte v));
  MOCK_METHOD1(setContrast, void(byte c));
  MOCK_METHOD1(setBias, void(byte b));
  MOCK_METHOD1(setClockDivider, void(byte d));
  MOCK_METHOD1(print, void(String m));
  MOCK_METHOD1(println, void(String m));
  MOCK_METHOD5(drawChar, void(int16_t x, int16_t y, unsigned char c, int16_t fgcolor, int16_t bgcolor));
  MOCK_METHOD6(drawBitmap, void(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color));
  MOCK_METHOD6(drawNumericBitmap, void(int16_t x, int16_t y, int n, int16_t w, int16_t h, uint16_t color));
  MOCK_METHOD5(drawRect, void(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color));
  MOCK_METHOD5(fillRect, void(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color));
  MOCK_METHOD7(getTextBounds, void(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h));
  MOCK_METHOD2(setCursor, void(int16_t x, int16_t y));
  MOCK_METHOD1(setTextColor, void(uint16_t c));
  MOCK_METHOD0(clearDisplay, void());
  MOCK_METHOD0(display, void());
  MOCK_METHOD0(useSmallFont, void());
  MOCK_METHOD0(useMonoBoldFont, void());
};

class MockedPCD8544Api : public Edmund::Hardware::IPCD8544Api {
  private:  
    MockIPCD8544Api* lcd;
  public:
    MockedPCD8544Api() : lcd(new MockIPCD8544Api()) { }        
    MockedPCD8544Api(MockIPCD8544Api* api) : lcd(api) { }
    ~MockedPCD8544Api(){
      delete(lcd);
    }
    
    void begin() { lcd->begin(); }
    void initDisplay() { lcd->initDisplay(); }
    void setRotation(byte v) { lcd->setRotation(v); }
    void setContrast(byte c) { lcd->setContrast(c); }
    void setBias(byte b) { lcd-> setBias(b); }
    void setClockDivider(byte d) { lcd->setClockDivider(d); }
    void print(String m) { lcd->print(m); }
    void println(String m) { lcd->println(m); }
    void drawChar(int16_t x, int16_t y, unsigned char c, int16_t fgcolor, int16_t bgcolor) { lcd->drawChar(x, y, c, fgcolor, bgcolor); }
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) { lcd->drawBitmap(x, y, bitmap, w, h, color); }
    void drawNumericBitmap(int16_t x, int16_t y, int n, int16_t w, int16_t h, uint16_t color) { lcd->drawNumericBitmap(x, y, n, w, h, color); }
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { lcd->drawRect(x, y, w, h, color); }
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) { lcd->fillRect(x, y, w, h, color); }
    void getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, uint16_t *w, uint16_t *h) { lcd->getTextBounds(str, x, y, x1, y1, w, h); }
    void setCursor(int16_t x, int16_t y) { lcd->setCursor(x, y); }
    void setTextColor(uint16_t c) { lcd->setTextColor(c); }
    void clearDisplay() { lcd->clearDisplay(); }
    void display() { lcd->display(); }
    void useSmallFont() { lcd->useSmallFont(); }
    void useMonoBoldFont() { lcd->useMonoBoldFont(); }
};

class MockIOutputDevice : public Edmund::Hardware::IOutputDevice {
 public:
  MOCK_CONST_METHOD1(Print, void(String m));
  MOCK_CONST_METHOD3(Print, void(String m, int x, int y));
  MOCK_CONST_METHOD1(PrintLine, void(String m));
  MOCK_CONST_METHOD3(DrawSymbol, void(int x, int y, const uint8_t* logo));
  MOCK_CONST_METHOD1(DrawScreen, void(const uint8_t* screen));
  MOCK_CONST_METHOD5(DrawBox, void(int x, int y, int w, int h, uint16_t color));
  MOCK_CONST_METHOD5(DrawBorder, void(int x, int y, int w, int h, uint16_t color));
  MOCK_CONST_METHOD2(DrawScreen, void(const uint8_t* logo, int x));
  MOCK_CONST_METHOD5(DrawLogo, void(int x, int y, int w, int h, const uint8_t* logo));
  MOCK_CONST_METHOD4(PrintLineCentered, void(const String& buf, int x, int y, uint16_t color));
  MOCK_CONST_METHOD5(PrintNumberSmall, void(int x, int y, int value, uint16_t color, int minLength));
  MOCK_CONST_METHOD5(PrintNumberLarge, void(int x, int y, int value, uint16_t color, int minLength));
  MOCK_CONST_METHOD0(GetScreenWidth, int());
  MOCK_CONST_METHOD0(GetScreenHeigt, int());
  MOCK_METHOD0(initScreen, void());
  MOCK_CONST_METHOD0(clear, void());
  MOCK_CONST_METHOD0(display, void());
  MOCK_CONST_METHOD0(beginFrame, void());
  MOCK_CONST_METHOD0(endFrame, void());
};