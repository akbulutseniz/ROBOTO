#include <Wire.h>

String message = "";

//Nem sensörü için tanımlar
#include <dht11.h>
#define dataPin 2 // Defines pin number to which the sensor is connected
dht11 DHT;  

//Motor ve motor sürücü için tanımlar
#define sagMotorHiz 11
#define solMotorHiz 6
#define sagMotorOn 10
#define sagMotorArka 12
#define solMotorOn 9
#define solMotorArka 8

//Mesafe sensörü için tanımlar
#define echoPin 5 //Ultrasonik sensörün echo pini Arduino'nun 12.pinine
#define trigPin 4
long sure, uzaklik; //süre ve uzaklık diye iki değişken tanımlıyoruz.
int maximumRange=50;
int minimumRange=0;


//Gaz sensörü için tanımlar
int esikDegeri = 200;            //Gaz eşik değerini belirliyoruz.    
int buzzerPin = 3;                 //Buzzerın takılacağı pin
int deger;  


void setup() {
     Serial.begin(9600); 
     Wire.begin(8);                /* join i2c bus with address 8 */
     Wire.onReceive(receiveEvent); /* register receive event */
     Wire.onRequest(requestEvent); /* register request event */
     pinMode(sagMotorHiz,OUTPUT);
     pinMode(solMotorHiz,OUTPUT);
     pinMode(sagMotorOn,OUTPUT);
     pinMode(sagMotorArka,OUTPUT);
     pinMode(solMotorOn,OUTPUT);
     pinMode(solMotorArka,OUTPUT);
     pinMode(buzzerPin,OUTPUT);
     pinMode(echoPin, INPUT);
     pinMode(trigPin, OUTPUT);
}

void loop() {
  if(message=="up"){
    ileri();
  }
  else if(message=="down"){
    geri();
  }
  else if(message=="left"){
    sag();
  }
  else if(message=="right"){
    sol();
  }
  else if(message=="stop"){
    dur();
  }
  else if(message=="gas"){
    while(true) gazSensoru();
  }
   else if(message=="humudity"){
    while(true) nemSensoru();
  }
  else if (message=="distance"){
      digitalWrite(trigPin, 1); //sensör pasif hale getirildi
      delayMicroseconds(1000);  
      digitalWrite(trigPin, 0); //Sensore ses dalgasının üretmesi için emir verildi
    
      sure = pulseIn(echoPin, 1); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
      uzaklik = (sure / 2) / 28.5; //ölçülen süre uzaklığa çevriliyor
      Serial.print("mesafe : ");
      Serial.println(uzaklik);
  }
  
}


String receiveEvent(int howMany) { 
  message="";
   while (0 <Wire.available()) {
      char c = Wire.read();      /* receive byte as a character */
      Serial.print(c);           /* print the character */
      message=message+c;
    }
 Serial.println();             /* to newline */
}

void requestEvent() {
 Wire.write("Hello NodeMCU");  /*send string on request */
}
boolean mesafe(){
  digitalWrite(trigPin, 1); //sensör pasif hale getirildi
  delayMicroseconds(1000);  
  digitalWrite(trigPin, 0); //Sensore ses dalgasının üretmesi için emir verildi

  sure = pulseIn(echoPin, 1); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = (sure / 2) / 28.5; //ölçülen süre uzaklığa çevriliyor
  if (uzaklik >30)
    return 0;
  else 
    return 1;
  
}

void engeldenKac(){
  digitalWrite(trigPin, 1); //sensör pasif hale getirildi
  delayMicroseconds(1000);  
  digitalWrite(trigPin, 0); //Sensore ses dalgasının üretmesi için emir verildi

  sure = pulseIn(echoPin, 1); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = (sure / 2) / 28.5; //ölçülen süre uzaklığa çevriliyor
  if (uzaklik < 30) // Uzaklık 15'den küçük ise,
  {
    geri();  // 150 ms geri git
    delay(150);
    sag();  // 250 ms sağa dön
    delay(250);
  }
  else {  // değil ise,
    ileri(); // ileri git
  }
}

void nemSensoru(){
      // Bir satır boşluk bırakıyoruz serial monitörde.
      Serial.println();
      // Sensörün okunup okunmadığını konrol ediyoruz. 
      // chk 0 ise sorunsuz okunuyor demektir. Sorun yaşarsanız
      // chk değerini serial monitörde yazdırıp kontrol edebilirsiniz.
      int chk = DHT.read(dataPin);
      // Sensörden gelen verileri serial monitörde yazdırıyoruz.
      Serial.print("Nem (%): ");
      Serial.println((float)DHT.humidity, 2);
    
      Serial.print("Sicaklik (Celcius): ");
      Serial.println((float)DHT.temperature, 2);
    
      Serial.print("Sicaklik (Fahrenheit): ");
      Serial.println(DHT.fahrenheit(), 2);
    
      Serial.print("Sicaklik (Kelvin): ");
      Serial.println(DHT.kelvin(), 2);
    
      // Çiğ Oluşma Noktası, Dew Point
      Serial.print("Cig Olusma Noktasi: ");
      Serial.println(DHT.dewPoint(), 2);
    
      // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.
      delay(2000);
}
void gazSensoru(){
  deger = analogRead(A0);           //Sensörden analog değer okuyoruz.
  if(deger > esikDegeri){           //Sensörden okunan değer eşik değerinden büyükse çalışır.
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(50);
    digitalWrite(buzzerPin, HIGH);
    delay(50);
  }
  else{                             //Sensörden okunan değer eşik değerinin altındaysa çalışır.
    digitalWrite(buzzerPin, LOW);
  }
  
    
}
void ileri(){
  if(!mesafe())
    engeldenKac();
  analogWrite(sagMotorHiz,200);
  digitalWrite(sagMotorOn ,1);
  digitalWrite(sagMotorArka,0);
  
  analogWrite(solMotorHiz,200);
  digitalWrite(solMotorOn,0);
  digitalWrite(solMotorArka,1);
}


void geri(){
  analogWrite(sagMotorHiz,255);
  digitalWrite(sagMotorOn ,0);
  digitalWrite(sagMotorArka,1);
  
  analogWrite(solMotorHiz,255);
  digitalWrite(solMotorOn,1);
  digitalWrite(solMotorArka,0);
}



void sag(){
  analogWrite(sagMotorHiz,0);
  digitalWrite(sagMotorOn ,0);
  digitalWrite(sagMotorArka,0);
  
  analogWrite(solMotorHiz,255);
  digitalWrite(solMotorOn,0);
  digitalWrite(solMotorArka,1);
}

void sol(){
  
  analogWrite(sagMotorHiz,255);
  digitalWrite(sagMotorOn ,1);
  digitalWrite(sagMotorArka,0);
  
  analogWrite(solMotorHiz,0);
  digitalWrite(solMotorOn,0);
  digitalWrite(solMotorArka,0);
  
}

void dur(){
  analogWrite(sagMotorHiz,0);
  digitalWrite(sagMotorOn ,0);
  digitalWrite(sagMotorArka,0);
  
  analogWrite(solMotorHiz,0);
  digitalWrite(solMotorOn,0);
  digitalWrite(solMotorArka,0);
}
