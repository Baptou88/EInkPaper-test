// GxEPD2_HelloWorld.ino by Jean-Marc Zingg

// see GxEPD2_wiring_examples.h for wiring suggestions and examples
// if you use a different wiring, you need to adapt the constructor parameters!

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
#include <Arduino.h>

#define ENABLE_GxEPD2_GFX 1 
#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
//#include <GxEPD2_7C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// select the display class and display driver class in the following file (new style):

#include "GxEPD2_display_selection_new_style.h"

// or select the display constructor line in one of the following files (old style):
//#include "GxEPD2_display_selection.h"
//#include "GxEPD2_display_selection_added.h"

// alternately you can copy the constructor from GxEPD2_display_selection.h or GxEPD2_display_selection_added.h to here
// e.g. for Wemos D1 mini:
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEH0154D67

class Plot
{
private:
 
  int _xstep=50;
  int _data[10] ;
  int _margin = 5;
  int index = 0;
public:
  Plot(int x, int y);
  ~Plot();

  void draw(GxEPD2_GFX& display);
  void add(int y);
   int _x = 0;
  int _y = 0;
  int _width = 400;
  int _height = 160;

};

Plot::Plot(int x, int y)
{
  _x = x;
  _y = y;
}

Plot::~Plot()
{
}

void Plot::draw(GxEPD2_GFX& display )
{
  display.drawRect(_x - _margin, _y - _margin - _height, _width + _margin * 2 , _height + _margin *2, GxEPD_BLACK);
  display.drawLine(_x,_y,_x, _y - _height,GxEPD_BLACK);
  display.drawLine(_x,_y,_x + _width, _y , GxEPD_BLACK);
  display.drawCircle(_x,_y,_margin,GxEPD_RED);
  Serial.println(index);
  for (size_t i = 0; i < index; i++)
  {
    display.drawCircle(i*_xstep + _x, _y - _data[i],4,GxEPD_RED );

    if (i != 0)
    {
      display.drawLine(i*_xstep + _x, _y - _data[i], (i-1)*_xstep + _x, _y - _data[i-1] ,GxEPD_BLACK );
      
    }
    
  }
  
}

void Plot::add(int y)
{
  if (index > 10)
  {
    
  } else
  {
    _data[index] = y;
    index++;
  }
  
  
}

Plot graph(40,448);


const char HelloWorld[] = "Hello World!";
void helloWorld()
{
  Serial.println("Hello World fct !");
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  Serial.println("full window !");
  display.firstPage();
  Serial.println("first page");
  do
  {
    display.fillScreen(GxEPD_WHITE);
    Serial.println("fill screen");
    display.setCursor(x, y);
    display.print(HelloWorld);
    display.setCursor(x+60, y+60);
    display.drawLine(50,50,100,100,GxEPD_BLACK);
    Serial.println("print");
  }
  while (display.nextPage());
  Serial.println("sortie");
}

void helloWorld2()
{
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds("20", 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;

  display.setPartialWindow(tbx,tby,tbw,tbh);
  display.firstPage();
  do
  {
    //display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y + 30);
    display.print("20");
  }
  while (display.nextPage());
}

void helloWorlde()
{
  //Serial.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  //Serial.println("helloWorld done");
}
void showPartialUpdate()
{
  // some useful background
  helloWorlde();
  // use asymmetric values for test
  uint16_t box_x = 10;
  uint16_t box_y = 15;
  uint16_t box_w = 70;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + box_h - 6;
  float value = 13.95;
  uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  // show where the update box is
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
      //display.fillScreen(GxEPD_BLACK);
    }
    while (display.nextPage());
    delay(2000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    }
    while (display.nextPage());
    delay(1000);
  }
  //return;
  // show updates in the update box
  for (uint16_t r = 0; r < 4; r++)
  {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    for (uint16_t i = 1; i <= 10; i += incr)
    {
      display.firstPage();
      do
      {
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.setCursor(box_x, cursor_y);
        display.print(value * i, 2);
      }
      while (display.nextPage());
      delay(500);
    }
    delay(1000);
    display.firstPage();
    do
    {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    }
    while (display.nextPage());
    delay(1000);
  }
}

void testGraph(bool partialUpdate = false) {
  display.setRotation(0);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.setTextColor(GxEPD_RED);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  if (partialUpdate)
  {
    display.setPartialWindow(graph._x,graph._y-graph._height,graph._width,graph._height);
  } else
  {
    display.setFullWindow();
  }
  
  

  display.firstPage();

  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
    display.setCursor(x+60, y+60);
    display.drawLine(50,50,100,100,GxEPD_BLACK);

    graph.draw(display);
  }
  while (display.nextPage());
}
bool requiredUpdate = false;

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World !");
  graph.add(20);
  graph.add(50);
  graph.add(70);
  delay(5);
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  
  //helloWorld();
  //delay(100);
  //showPartialUpdate();

  testGraph();

  display.hibernate();
}


void loop() {
  if (Serial.available())
  {
    String test = Serial.readStringUntil('\n');
    int newVal = test.toInt();
    graph.add(newVal);
    requiredUpdate = true ;
    Serial.println("new Val: " + String(newVal));
  }
  
  if (requiredUpdate)
  {
    requiredUpdate = false;
    testGraph(true);
  }
  
  
};