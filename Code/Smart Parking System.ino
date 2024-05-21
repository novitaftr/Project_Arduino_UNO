#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int LDR = A0; 
const int LDR1 = A1;
int pos = 0;
int rate;
int rate1;
int LED1 = 12;
int jumlah = 0;

//inisiasi PING (KODE A)
const int trigPinA = 9;
const int echoPinA = 8;
long durationA;
int distanceA;

//inisiasi PING (KODE B)
const int trigPinB = 13;
const int echoPinB = 10;
long durationB;
int distanceB;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(LED1,OUTPUT);;
  myservo.attach(11);

  //LCD
  lcd.print("PARKIR OTOMATIS"); // mencetak string
  lcd.setCursor(0,1); // mengatur cursor posisi pencetakan
  lcd.print("BERBASIS ARDUINO UNO"); // mencetak string-dengan arduino
  delay(2000); // waktu jeda 2 detik
  lcd.clear(); // membersihkan LCD
  lcd.setCursor(0,0);
  lcd.print("P1 TDK");
  lcd.setCursor(7,0);
  lcd.print("P2 TDK ");
  lcd.setCursor(0,1);
  lcd.print("TERDAPAT = 0 ");
  
  //PING (KODE A)
  pinMode(trigPinA,OUTPUT);
  pinMode(echoPinA, INPUT);
  
   //PING(KODE B)
  pinMode(trigPinB,OUTPUT);
  pinMode(echoPinB, INPUT);
  }

void loop(){
  //PING A
  digitalWrite(trigPinA,LOW);
  delayMicroseconds(2500);

  digitalWrite(trigPinA, HIGH);
  delayMicroseconds(2500);
  digitalWrite(trigPinA,LOW);

  durationA = pulseIn(echoPinA,HIGH);
  distanceA = durationA*0.034/2;
  Serial.println(distanceA);

//PING B
  digitalWrite(trigPinB,LOW);
  delayMicroseconds(2500);

  digitalWrite(trigPinB, HIGH);
  delayMicroseconds(2500);
  digitalWrite(trigPinB,LOW);

  durationB = pulseIn(echoPinB,HIGH);
  distanceB = durationB*0.034/2;
  //Serial.println(distanceB);

 if(distanceA < 4){
    jumlah++;
    cetak(jumlah);
    for(pos=0; pos <= 90; pos +=1){
      myservo.write(pos);
      delay(50);
    }
 }
 
 if(distanceB < 4){
    jumlah--;
    cetak(jumlah);
    for(pos=0; pos <= 90; pos +=1){
      myservo.write(pos);
      delay(50);
    }
 }
  rate = analogRead(LDR);
  rate1= analogRead(LDR1);

  if(rate < 19){
    digitalWrite(LED1, HIGH);
    lcd.setCursor(0,0);
    lcd.print("P1 ADA");
    delay(100);
  }
  
  if(rate > 20){
    digitalWrite(LED1, LOW);
    lcd.setCursor(0,0);
    lcd.print("PI TDK");
    delay(100);
  }
  
  if(rate1 < 19){
    digitalWrite(LED1, HIGH);
    lcd.setCursor(7,0);
    lcd.print("P2 ADA");
    delay(100);
  }

  if(rate1 > 20){
    digitalWrite(LED1,LOW);
    lcd.setCursor(7,0);
    lcd.print("P2 TDK");
    delay(100);
  }
}

void cetak(int jumlah){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P1 TDK");
  lcd.setCursor(7,0);
  lcd.print("P2 TDK ");
  lcd.setCursor(0,1);
  lcd.print("TERDAPAT = ");
  lcd.setCursor(11,1);
  lcd.print(jumlah);
}

