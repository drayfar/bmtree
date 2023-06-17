#include <Adafruit_NeoPixel.h>

#define STRIP_COUNT 21
#define TRUNK_COUNT 3
#define LEAF_COUNT 18
#define PIXELS_PER_LEAF 60
#define PIXELS_PER_TRUNK 300

Adafruit_NeoPixel leaf0(PIXELS_PER_LEAF, 22, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf1(PIXELS_PER_LEAF, 23, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf2(PIXELS_PER_LEAF, 24, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf3(PIXELS_PER_LEAF, 25, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf4(PIXELS_PER_LEAF, 26, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf5(PIXELS_PER_LEAF, 27, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel trunk0(PIXELS_PER_TRUNK, 28, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel leaf6(PIXELS_PER_LEAF, 29, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf7(PIXELS_PER_LEAF, 30, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf8(PIXELS_PER_LEAF, 31, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf9(PIXELS_PER_LEAF, 33, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf10(PIXELS_PER_LEAF, 34, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf11(PIXELS_PER_LEAF, 37, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel trunk1(PIXELS_PER_TRUNK, 38, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel leaf12(PIXELS_PER_LEAF, 41, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf13(PIXELS_PER_LEAF, 42, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf14(PIXELS_PER_LEAF, 45, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf15(PIXELS_PER_LEAF, 46, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf16(PIXELS_PER_LEAF, 49, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leaf17(PIXELS_PER_LEAF, 50, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel trunk2(PIXELS_PER_TRUNK, 53, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel strips[STRIP_COUNT] = {
    leaf0,
    leaf1,
    leaf2,
    leaf3,
    leaf4,
    leaf5,
    trunk0,
    leaf6,
    leaf7,
    leaf8,
    leaf9,
    leaf10,
    leaf11,
    trunk1,
    leaf12,
    leaf13,
    leaf14,
    leaf15,
    leaf16,
    leaf17,
    trunk2,
};

Adafruit_NeoPixel leaves[LEAF_COUNT] = {
    leaf0,
    leaf1,
    leaf2,
    leaf3,
    leaf4,
    leaf5,
    leaf6,
    leaf7,
    leaf8,
    leaf9,
    leaf10,
    leaf11,
    leaf12,
    leaf13,
    leaf14,
    leaf15,
    leaf16,
    leaf17,
};

Adafruit_NeoPixel trunks[TRUNK_COUNT] = {trunk0, trunk1, trunk2};

int brightness = 1;

void setup()
{
  for (int i = 0; i < STRIP_COUNT; i++)
  {
    // Configure the pin for output
    strips[i].begin();
    // Set brightness to 10%ish (out of 255)
    strips[i].setBrightness(brightness * 0.1 * 255);
    // Transmit data in RAM to the strip
    // strips[i].fill(getColor(colors[i * 2][0], colors[i * 2][1], colors[i * 2][2]));
    strips[i].show();
    // Serial.begin(2400);
  }

  pinMode(7, INPUT);
  digitalWrite(7, HIGH);
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
}

int offset = 0;
int buttonDelay0 = 0;
int buttonDelay1 = 0;
int mode = 0;

void loop()
{

  int buttonState0 = digitalRead(7);
  if (buttonState0 == LOW && buttonDelay0 == 0)
  {
    buttonDelay0 = 2;
    switch (brightness)
    {
    case 1:
      brightness = 3;
      break;
    case 3:
      brightness = 5;
      break;
    case 5:
      brightness = 7;
      break;
    default:
      brightness = 1;
      break;
    }
    for (int i = 0; i < STRIP_COUNT; i++)
    {
      strips[i].setBrightness(brightness * 255 * 0.1);
    }
  }

  int buttonState1 = digitalRead(8);
  if (buttonState1 == LOW && buttonDelay1 == 0)
  {
    buttonDelay1 = 2;
    switch (mode)
    {
    case 0:
      mode = 1;
      break;
    case 1:
      mode = 2;
      break;
    case 2:
      mode = 3;
      break;
    case 3:
      mode = 4;
      break;
    case 4:
      mode = 5;
      break;
    case 5:
      mode = 6;
      break;
    default:
      mode = 0;
      break;
    }
  }

  if (buttonDelay0 > 0)
  {
    buttonDelay0--;
  }
  if (buttonDelay1 > 0)
  {
    buttonDelay1--;
  }

  switch (mode)
  {
  case 0:
    treeMode();
    break;
  case 1:
    rainbowMode(1);
    break;
  case 2:
    rainbowMode(10);
    break;
  case 3:
    rainbowMode(20);
    break;
  case 4:
    wholeRainbowMode(1);
    break;
  case 5:
    wholeRainbowMode(5);
    break;
  case 6:
    wholeRainbowMode(10);
    break;
  default:
    treeMode();
    break;
  }
}

void wholeRainbowMode(int speed)
{
  uint32_t color = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(offset % 65535, 255U, getValueWithBrightness(255)));
  for (int i = 0; i < STRIP_COUNT; i++)
  {
    strips[i].fill(color);
    strips[i].show();
  }

  offset += 100 * speed;
}

void rainbowMode(int speed)
{
  for (int i = 0; i < STRIP_COUNT; i++)
  {
    strips[i].rainbow((offset + i * 200) % 65535);
    strips[i].show();
  }

  offset += 500 * speed;
}

const uint16_t greenHueMin = 12000;
const uint16_t greenHueMax = 28000;
const uint16_t greenHueSpread = greenHueMax - greenHueMin;
const uint16_t brownHue = 7500;
const uint8_t brownValMin = 0.45 * 255U;
const uint8_t brownValMax = 255U;
const uint8_t brownValSpread = brownValMax - brownValMin;
float treeOffsetMultiplier = 0;
int direction = 1;

uint8_t getValueWithBrightness(uint8_t val)
{
  switch (brightness)
  {
  case 1:
    return val * 0.5;
    break;
  case 3:
    return val * 0.6;
    break;
  case 5:
    return val * 0.7;
    break;
  case 7:
    return val * 0.8;
    break;
  default:
    return val;
  }
}

void treeMode()
{
  if (treeOffsetMultiplier >= 1)
  {
    treeOffsetMultiplier = 1;
    direction = -1;
  }

  if (treeOffsetMultiplier <= 0)
  {
    treeOffsetMultiplier = 0;
    direction = 1;
  }

  int midpoint = 60 * treeOffsetMultiplier;

  for (int i = 0; i < LEAF_COUNT; i++)
  {
    for (int j = 0; j < PIXELS_PER_LEAF; j++)
    {
      int distance = abs(midpoint - j);
      uint16_t hue = distance == 0 ? greenHueMax : greenHueMax - ((distance / float(PIXELS_PER_LEAF)) * greenHueSpread);
      uint8_t val = getValueWithBrightness(255U);
      uint32_t color = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(hue, 255U, val));
      leaves[i].setPixelColor(j, color);
    }
    leaves[i].show();
  }

  for (int i = 0; i < TRUNK_COUNT; i++)
  {
    for (int j = 0; j < PIXELS_PER_TRUNK; j++)
    {
      int distance = abs(midpoint - j);
      uint16_t hue = brownHue;
      uint8_t val = distance == 0 ? brownValMax : brownValMax - ((distance / float(PIXELS_PER_TRUNK)) * brownValSpread);
      val = getValueWithBrightness(val);
      uint32_t color = Adafruit_NeoPixel::gamma32(Adafruit_NeoPixel::ColorHSV(hue, 255U, val));
      trunks[i].setPixelColor(j, color);
    }

    trunks[i].show();
  }

  treeOffsetMultiplier += 0.05 * direction;
}