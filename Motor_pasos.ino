#include <SPI.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_GFX.h>


#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

#define Bob1 2
#define Bob2 3
#define Bob3 4
#define Bob4 5
long i = 50;
int pasos[4] = {B1000, B0100, B0010, B0001};
int paso = 0;
bool green = false;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
double tiem = 0;
double velo = 5;
long tiempomil = 0;
long tiempomilt = 0;
double tiempouso = 0;
int btt = 0;
bool primer1 = true;
bool primer2 = true;
bool esc = false;


void setup() {
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.fillScreen(ST77XX_BLACK);
  attachInterrupt( 2, Btt, FALLING);
  pinMode(Bob1, OUTPUT);
  pinMode(Bob2, OUTPUT);
  pinMode(Bob3, OUTPUT);
  pinMode(Bob4, OUTPUT);
  
}
//Vmax = 14.64
void loop() {
    
    if(btt==0){
    velo = 5;
    tiem = (60/(32*64*velo));
    tiem = tiem *1000000;
    primer1 = true;
    primer2 = true;
    }

    if(btt==1){  
      if(primer1){
        tiempomil = millis();
        primer1 = false;
        esc=false;
      }
    tiempomilt = millis();
    tiempomilt = tiempomilt - tiempomil;
    tiempouso = tiempomilt/1000;
    if(tiempouso>5){
      tiempouso = 5;
      if(!esc){
      tft.println("max");   
      esc=true;
      }   
    }
    velo = 5 + (115.68*(tiempouso/60));
    tiem = (60/(32*64*velo));
    tiem = tiem *1000000;    
    }  

    if(btt==2){  
      if(primer2){
        tiempomil = millis();
        primer2 = false;
        esc=false;
      }
    tiempomilt = millis();
    tiempomilt = tiempomilt - tiempomil;
    tiempouso = tiempomilt/1000;
    if(tiempouso>5){
      tiempouso = 5;
      btt=0;
      if(!esc){
      tft.println("min");       
      esc=true;
      }
    }
    velo = 14.64 - (115.68*(tiempouso/60));
    tiem = (60/(32*64*velo));
    tiem = tiem *1000000;    
    }  

    Paso(paso);
    delayMicroseconds(tiem);
    paso++;
    if(paso>3){
      paso=0;
    }                                            
    }    


void Btt(){
        btt++;
        if(btt>2){
          btt=0;
        }
}

void Paso(int paso){
    digitalWrite(Bob1, bitRead(pasos[paso],0));
    digitalWrite(Bob2, bitRead(pasos[paso],1));
    digitalWrite(Bob3, bitRead(pasos[paso],2));
    digitalWrite(Bob4, bitRead(pasos[paso],3));
  }

//min delay 1820
