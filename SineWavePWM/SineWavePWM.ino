/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2018 Bolder Flight Systems
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the "Software"), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, 
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or 
* substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
* Description: this program will output a sine wave on all 8 channels of the 
* Teensy PWM Backpack (http://bolderflight.com/products/teensy/pwm). The
* sine amplitude will be set to make the servo travel across its entire range
* and the excitation frequency will be 1 Hz.
*/

/* Redefine the pin numbers to match the PWM Backpack numbering */
const unsigned int PWM[8] = {20,21,22,23,5,6,10,9};
/* PWM update frequency, 50 Hz */
const unsigned int Freq = 50;
/* PWM update period */
const unsigned int Period_us = 1000000 / Freq;
/* PWM resolution */
const unsigned int PWM_Resolution = 16;
/* Time, ms */
elapsedMillis time_ms;

void setup()
{
  /* Serial for printing the command */
  Serial.begin(115200);
  while (!Serial && time_ms < 5000) {}
  /* setting the analog frequency to 50 Hz and resolution to 16 bit */
  for (unsigned int i = 0; i < sizeof(PWM) / sizeof(unsigned int); ++i) {
    analogWriteFrequency(PWM[i], Freq);
    analogWriteResolution(PWM_Resolution);
  }
}

void loop()
{
  /* 1 Hz sine wave */
  float Cmd = sinf(2.0f * M_PI * time_ms / 1000.0f);
  /* Scale from +/- 1 to a range of 1000 us to 2000 us */
  Cmd = Cmd * 500.0f + 1500.0f;
  /* Command channels */
  for (unsigned int i = 0; i < sizeof(PWM) / sizeof(unsigned int); ++i) {
    analogWrite(PWM[i],Cmd / Period_us * powf(2,PWM_Resolution));
  }
  /* Print command */
  Serial.println(Cmd);
  /* Run at 50 Hz for better printing */
  delay(20);
}