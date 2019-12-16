#include <FastLED.h>
#include "BluetoothSerial.h"
#define LED_PIN     4
#define NUM_LEDS    48
BluetoothSerial ESP_BT;
char incoming;
int RGBSize=3;
    char set[]={'0','0','0'};
    int RGBSet[]={0,0,0};
    //int usedCellsIndex=0;
    int setIndex=0;
    int RGBSetIndex=0;    
    CRGB leds[NUM_LEDS];
    void setup() 
    {
      Serial.begin(9600); //Start Serial monitor in 9600
      ESP_BT.begin("ESP32_LED_Tester"); //Name of your Bluetooth Signal
      Serial.println("Bluetooth Device is Ready to Pair");
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
      
    }

    void endOfSetCleanUp()
    {

            if(setIndex == 2)
            {
              set[2]=set[1];
              set[1]=set[0];
              set[0]='0';
              //this is probably faster if just did bit shifting
            }
            else if(setIndex == 1)
            {
              set[2]=set[0];
              set[1]='0';
              set[0]='0';
            }
            Serial.print("Complete Set "); Serial.print(RGBSetIndex);Serial.print(":");Serial.print(set[0]);Serial.print(",");Serial.print(set[1]);Serial.print(",");Serial.println(set[2]);
            sscanf(set,"%d", &RGBSet[RGBSetIndex]);
            RGBSetIndex++;
            for(int i=0;i<RGBSize;i++)
            {
              set[i]='0';
            }
            
            setIndex=0;
    }

    
    void loop() {

      //format R,G,B ex. 225,225,225
      if (ESP_BT.available()) //Check if we receive anything from Bluetooth
      {
        incoming = ESP_BT.read(); //Read what char we recevive
        Serial.print("CHAR Received:"); Serial.print(incoming);Serial.println("|");
        if(incoming == '\n')
        {
          Serial.println("In Here");
          if(RGBSetIndex>0)
          {
            endOfSetCleanUp();
            Serial.print("RGB:");Serial.print(RGBSet[0]);Serial.print(",");Serial.print(RGBSet[1]);Serial.print(",");Serial.println(RGBSet[2]);
            Serial.print("TURN LEDS ON");
            for(int i=0;i<NUM_LEDS;++i)
            {
              leds[i] = CRGB(RGBSet[0], RGBSet[1], RGBSet[2]);
              FastLED.show();
              delay(500);  //DO I WANT THIS?
            }
          }
          RGBSetIndex=0;
        }
        else if(incoming == ',')
        {
            endOfSetCleanUp();
        }
        else
        {
          set[setIndex]=incoming;  
          setIndex++;
        }
      }
    }
      /*for(int i=0;i<NUM_LEDS;++i)
      {
      leds[i] = CRGB(100, 100, 0);
      FastLED.show();
      delay(500);  
      }*/
