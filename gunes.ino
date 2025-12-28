#include <Servo.h>

Servo horizontal; // Yatay servo
Servo vertical;   // Dikey servo

int servoh = 180;
int servov = 45;

int servohLimitHigh = 175;
int servohLimitLow  = 5;

int servovLimitHigh = 100;
int servovLimitLow  = 1;

// LDR pinleri
int ldrlt = A2; // Sol üst
int ldrrt = A3; // Sağ üst
int ldrld = A0; // Sol alt
int ldrrd = A1; // Sağ alt

void setup() {
  Serial.begin(9600);   // 🔴 EKSİKTİ
  horizontal.attach(9);
  vertical.attach(10);

  horizontal.write(servoh);
  vertical.write(servov);
  delay(2000);
}

void loop() {

  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);

  int dtime = 10;
  int tol = 90;

  int avt = (lt + rt) / 2; // Üst ortalama
  int avd = (ld + rd) / 2; // Alt ortalama
  int avl = (lt + ld) / 2; // Sol ortalama
  int avr = (rt + rd) / 2; // Sağ ortalama

  int dvert  = avt - avd;
  int dhoriz = avl - avr;

  // Debug çıktısı
  Serial.print("U:");
  Serial.print(avt);
  Serial.print(" A:");
  Serial.print(avd);
  Serial.print(" S:");
  Serial.print(avl);
  Serial.print(" R:");
  Serial.println(avr);

  // 🔼 Dikey servo kontrolü
  if (abs(dvert) > tol) {
    if (avt < avd) servov++;
    else           servov--;

    servov = constrain(servov, servovLimitLow, servovLimitHigh);
    vertical.write(servov);
  }

  // 🔄 Yatay servo kontrolü
  if (abs(dhoriz) > tol) {
    if (avl > avr) servoh--;
    else           servoh++;

    servoh = constrain(servoh, servohLimitLow, servohLimitHigh);
    horizontal.write(servoh);
  }

  delay(dtime);
}
