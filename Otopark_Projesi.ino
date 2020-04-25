#include "Hx711.h"   //kütüphanelerimizi tanımladık
#include<Servo.h>
Servo motor;    

// (dt, sck)
Hx711 scale(A0,A1); 
Hx711 scale2(A2,A3);


int trigPin=7;   // hcsr04 ün trig pini
int echoPin=6;   // hcsr04 ün echo pinlerini tanımladık.
int santimetre;
int sure;

void MesafeSensoru() // kod kalabalıgı olmaması adına method oluşturdum. ve bu method da Santimetre işlemlerini yaptırdım.
{
 digitalWrite(trigPin, LOW);       
 delayMicroseconds(2);       
//------------
 digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
//------------
digitalWrite(trigPin,LOW);
sure=pulseIn(echoPin,HIGH); 
santimetre=(sure/2)/29.1;  
}

void setup() {
  motor.attach(8);  // servo pini 
  pinMode(trigPin,OUTPUT); // uzaklık sensörünün pinlerini tanımladık.
  pinMode(echoPin,INPUT);
  Serial.begin(115200); //serial porttan degiştirmeyi unutma.
  
}

void loop() {
 float park1=scale.getGram();  // loadcell den aldığımız veriyi(gramı) park1 degerinin içine attık.
 float park2=scale2.getGram();
 MesafeSensoru(); // mesafe sensörü methodunu çagırdık.
 

//------- 


if(park1<5 || park2<5 && santimetre<10) // kontrol işlemlerimiz park1 veya park2 boş ise ve santimetre 10 dan küçükse kapı açılacak.
{
  Serial.println("++++  !! Açılıyor!!  ++++");
   motor.write(90);
   delay(3000);
   motor.write(0);
 }
else if(park1>5 && park2>5 && santimetre>10) //  park1 ve park2 dolu ise ve santimetre 10 dan büyükse kapı açılmayacak.
{
 Serial.println("++++  !!  AÇILAMAZ !  ++++");
      motor.write(0);
  delay(3000);
 }
 

}
