    #include <FastLED.h>
    #include "BluetoothSerial.h"
    #define LED_PIN     4
    #define NUM_LEDS    48
    BluetoothSerial ESP_BT;
    char incoming;
    int RGBSize=3;
    char set[RGBSize]={'0','0','0'};
    int RGBSet[RGBSize]={0,0,0};
    int setIndex=0;
    int RGBSetIndex=0;    
    CRGB leds[NUM_LEDS];
    void setup() {
      Serial.begin(9600); //Start Serial monitor in 9600
      ESP_BT.begin("ESP32_LED_Tester"); //Name of your Bluetooth Signal
      Serial.println("Bluetooth Device is Ready to Pair");
      FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
      
    }
    void loop() {

      //format R,G,B ex. 225,225,225
      if (ESP_BT.available()) //Check if we receive anything from Bluetooth
      {
        incoming = ESP_BT.read(); //Read what we recevive
        Serial.print("Received:"); Serial.println(incoming);
        if(incoming == '\n')
        {
          if(RGBSetIndex>0)
          {
            for(int i=0;i<NUM_LEDS;++i)
            {
              leds[i] = CRGB(100, 100, 0);
              FastLED.show();
              delay(500);  
            }
          }
          RGBSetIndex=0;
        }
        else if(incoming == ',')
        {
            sscanf(set,"%d", RGBSet[RGBSetIndex]);
            RGBSetIndex++;
            set={'0','0','0'};
            setIndex=0;
        }
        else
        {
          set[RGBSize-setIndex]=incoming;
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
    }
