#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <Servo.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo ServoLeft; //membuat objek servo

int count = 0; 
int sensor=6;  
int buzzer=2;
uint64_t timeloop = 0; 
uint64_t timeout = 100000;
void setup() {
  // put your setup code here, to run once: 
Serial.begin(9600);  
pinMode(6, INPUT_PULLUP);   
pinMode(2, OUTPUT);
ServoLeft.attach(13); //servo terhubung pada pin 13
ServoLeft.writeMicroseconds(1500); //kondisi awal servo
//Serial.println("Silahkan Masukkan Koin Anda"); 
// delay(1000);
  lcd.begin(); 
  lcd.setCursor(0,0);
  lcd.print("SELAMAT DATANG"); 
  delay(1500);  
  lcd.setCursor(0,1);
  lcd.print("VENDING MACHINE"); 
  delay(1500); 
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly: 
  lcd.setCursor(0,0);
  lcd.print("Jumlah Koin :"); 

  timeloop = 0;
  //koin terdeteksi
 if (digitalRead(sensor) == LOW) {  
   delay(7); //tunggu 20ms
    if (digitalRead(sensor) == LOW) { //apabila koin masih terdeteksi 
       while (digitalRead(sensor) == LOW && timeloop++ <= timeout); //selama koin masih terdeteksi dan kurang dari timeout 
       if(timeloop >= timeout) {  //jika lebih dari time out 
        //peringatan error
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("DETEKSI ERROR");  
        digitalWrite(buzzer,HIGH);
        delay(500);  
        digitalWrite(buzzer,LOW); 
        delay(100);  
        digitalWrite(buzzer,HIGH);
        delay(500);  
        digitalWrite(buzzer,LOW); 
        delay(100); 
        digitalWrite(buzzer,HIGH);
        delay(500);  
        digitalWrite(buzzer,LOW);

        //action 
       /* lcd.clear(); 
        lcd.setCursor(4,0); 
        lcd.print("AKTIFKAN");
        lcd.setCursor(2,1);
        lcd.print("MODE MEKANIK"); 
        delay(500);  
        ServoLeft.writeMicroseconds(2600); 
        delay(1000); 
        ServoLeft.writeMicroseconds(1500); 
        delay(1000);  */  

        //kembali ke menu hitung
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print("Jumlah Koin :");
        lcd.setCursor(0,1);  
        lcd.print(count);  
        lcd.setCursor(3,1); 
        lcd.print("KOIN");  
        
        
       }   
       
       //else { //jika tidak lebih dari timeout
        count++;  
        Serial.println(digitalRead(sensor));  
        lcd.setCursor(0,1);  
        lcd.print(count);  
        lcd.setCursor(3,1); 
        lcd.print("KOIN");  
         
       }
        
    }
 }
