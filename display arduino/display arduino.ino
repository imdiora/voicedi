#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char *players[]={
"John", 
"Marie", 
"Bob", 
"Richard", 
"Michael", 
"Madeleine", 
"Samuel", 
"Michelle", 
"Jennifer", 
"Claire", 
};

long player;

int val1 = 0;
int BUTTON1 = 13;

void setup() {
  lcd.begin(16, 2);
  pinMode(BUTTON1, INPUT);
}

void loop() {
  lcd.setCursor(0,1);
  lcd.print(millis() / 1000);
  val1 = digitalRead(BUTTON1);
  unsigned long seed=seedOut(50);
  randomSeed(seed);
  if (val1 == HIGH) {
    for (int i=0;i<1;++i) {
      player = (random(sizeof(players)/sizeof(char*)));
      lcd.setCursor(0, 0);
      lcd.print(players[player]);
      delay(5000);
      lcd.clear();
    }
  }
  else
  {
    return;
  }
}

unsigned int bitOut(void) {
  static unsigned long firstTime=1, prev=0;
  unsigned long bit1=0, bit0=0, x=0, port=0, limit=10;
  if (firstTime) {
    firstTime=0;
    prev=analogRead(port);
  }
  while (limit--) {
    x=analogRead(port);
    bit1=(prev!=x?1:0);
    prev=x;
    x=analogRead(port);
    bit0=(prev!=x?1:0);
    prev=x;
    if (bit1!=bit0)
      break;
  }
  return bit1;
}

unsigned long seedOut(unsigned int noOfBits) {
  unsigned long seed=0;
  for (int i=0;i<noOfBits;++i)
    seed = (seed<<1) | bitOut();
  return seed;
}
