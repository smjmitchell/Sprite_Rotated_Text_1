// This example plots a rotated Sprite to the screen using the pushRotated()
// function. It is written for a 240 x 320 TFT screen.

// Two rotation pivot points must be set, one for the Sprite and one for the TFT
// using setPivot(). These pivot points do not need to be within the visible screen
// or Sprite boundary.

// When the Sprite is rotated and pushed to the TFT with pushRotated(angle) it will be
// drawn so that the two pivot points coincide. This makes rotation about a point on the
// screen very simple. The rotation is clockwise with increasing angle. The angle is in
// degrees, an angle of 0 means no Sprite rotation.

// The pushRotated() function works with 1, 4, 8 and 16-bit per pixel (bpp) Sprites.

// The original Sprite is unchanged so can be plotted again at a different angle.

// Optionally a transparent colour can be defined, pixels of this colour will
// not be plotted to the TFT.

// For 1 bpp Sprites the foreground and background colours are defined with the
// function spr.setBitmapColor(foregroundColor, backgroundColor).

// For 4 bpp Sprites the colour map index is used instead of the 16-bit colour
// e.g. spr.setTextColor(5); // Green text in default colour map
// See "Transparent_Sprite_Demo_4bit" example for default colour map details

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();           // TFT object

TFT_eSprite spr = TFT_eSprite(&tft); // Sprite object

// =======================================================================================
// Setup
// =======================================================================================

void setup()   {
  Serial.begin(250000); // Debug only

  tft.begin();  // initialize
  tft.setRotation(0);

  Serial.println("Font Height and Width");
  Serial.println(tft.fontHeight(4));
  Serial.println(tft.textWidth(4));  
}

// =======================================================================================
// Loop
// =======================================================================================

void loop() {
  
  int xw = tft.width()/2;   // xw, yh is middle of screen
  int yh = tft.height()/2;

  showMessage("Transparent rotations");
  tft.fillCircle(xw, yh, 70, TFT_DARKGREY); // Draw a filled circle

  tft.setPivot(xw, yh);         // Set pivot to middle of screen
  drawX(xw, yh);                // Show where pivot is
  
  //spr.deleteSprite();

  spr.setColorDepth(8);         // Create a 8bpp Sprite
  spr.createSprite(40, 30);     // Create a new Sprite 40x30
  spr.setPivot(20, 70);         // Set Sprite pivot at 20,80

  spr.setTextColor(TFT_RED);    // Red text in Sprite
  spr.setTextDatum(MC_DATUM);   // Middle centre datum

  int num = 1;

  for (int16_t angle = 30; angle <= 360; angle += 30)
  {
    spr.fillSprite(TFT_BLACK);         // Clear the Sprite
    spr.drawNumber(num, 20, 15, 4);    // Plot number, in Sprite at 20,15 and with font 4
    spr.pushRotated(angle, TFT_BLACK); // Plot rotated Sprite, black being transparent
    num++;
  }

  spr.setTextColor(TFT_WHITE);    // White text in Sprite
  spr.setPivot(-75, 15);          // Set Sprite pivot at -75,15

  for (int16_t angle = -90; angle < 270; angle += 30)
  {
    spr.fillSprite(TFT_BLACK);           // Clear the Sprite
    spr.drawNumber(angle+90, 20, 15, 4); // Plot number, in Sprite at 20,15 and with font 4
    spr.pushRotated(angle, TFT_BLACK);   // Plot rotated Sprite, black being transparent
    num++;
  }
  
  delay(8000);  // Pause so we see it

  spr.deleteSprite();

}

// =======================================================================================
// Draw an X centered on x,y
// =======================================================================================

void drawX(int x, int y)
{
  tft.drawLine(x-5, y-5, x+5, y+5, TFT_WHITE);
  tft.drawLine(x-5, y+5, x+5, y-5, TFT_WHITE);
}

// =======================================================================================
// Show a message at the top of the screen
// =======================================================================================

void showMessage(String msg)
{
  // Clear the screen areas
  tft.fillRect(0, 0, tft.width(), 20, TFT_BLACK);
  tft.fillRect(0, 20, tft.width(), tft.height()-20, TFT_BLUE);

  uint8_t td = tft.getTextDatum(); // Get current datum

  tft.setTextDatum(TC_DATUM);      // Set new datum

  tft.drawString(msg, tft.width()/2, 2, 2); // Message in font 2

  tft.setTextDatum(td); // Restore old datum
}

// =======================================================================================
