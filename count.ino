#include <LiquidCrystal.h>
# define num A1
# define operate A2
# define equals A3
# define next A4
# define wipe A5

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int count = 0;
int itemNum = 1;
int item1;
int item2;
int place = 0;
String opr[4] = {"/", "+", "-", "*"};
int i = 0;
bool now = true;
int whole;

void setup() {
  lcd.begin(16, 2);
  lcd.print(count);
  pinMode(num, OUTPUT);
  pinMode(operate, OUTPUT);
  pinMode(next, OUTPUT);
  pinMode(equals, OUTPUT);
  pinMode(wipe, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(num) == HIGH) {
    if (now == false) {
     now = true;
     place++;
     Serial.println(item1 + opr[i]+ item2);
    }
    if (count < 9) {
     count++; 
     delay(200);
    } else {
     count = 0; 
     delay(200);
    }
    Serial.println(item1 + opr[i]+ item2 + count);
    lcd.setCursor(place, 0);
    lcd.print(count);
  }
    
  if (digitalRead(next) == HIGH) {
    proceed();
    lcd.setCursor(place, 0);
    lcd.print(count);
  }
  
  if (digitalRead(operate) == HIGH) {
    operant();
  }
  
  if (digitalRead(equals) == HIGH) {
    equal();
    delay(500);
  }
  
  if (digitalRead(wipe) == HIGH) {
    reset();
    delay(500);
  }

}
 
void proceed() {
 if (itemNum == 1) {
      item1 = item1 * 10;
      item1 += count++;
      count = 0;
      place++;
      Serial.println(item1 + opr[i]+ item2);
      delay(300);
    } else {
      item2 = item2 * 10;
      item2 += count++;
      count = 0;
      place++;
      Serial.println(item1 + opr[i]+ item2);
      delay(300);
    } 
  
}

void operant() {
  if (now == true) {
    item1 = item1 * 10;
    item1 += count++;
    itemNum = 2;
    place++;
    now = false;
    Serial.println(item1);
  }
  count = 0;
  lcd.setCursor(place, 0);
  i++;
  lcd.print(opr[i]);
  if (i > 3) {i=0;}
  delay(300);
}

void equal() {
  item2 = item2 * 10;
  item2 += count++;
  
  switch(i) {
    case 1:
    whole = item1 + item2;
    break;
    
    case 2:
    whole = item1 - item2;
    break;
    
    case 3:
    whole = item1 * item2;
    break;
    
    case 0:
    whole = item1 / item2;
    break;
    
    default:
    lcd.setCursor(0, 8);
    lcd.print("err");
    
  }
  lcd.setCursor(0, 1);
  lcd.print(whole);
  
}

void reset() {
  count = 0;
  itemNum = 1;
  item1 = 0;
  item2 = 0;
  place = 0;
  i = 0;
  now = true;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(0);
  
}
