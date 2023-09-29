//ID Number
int cntUp = 15;    //Stops counting up when it reaches this value
int cntDown = 16; //Stops counting down when it reaches this value

//pin state of the LEDs in the 7 segment display from digits 0-9
int digit[10] =
{0b1000000, 
 0b1111001, 
 0b0100100, 
 0b0110000, 
 0b0011001, 
 0b0010010, 
 0b0000010, 
 0b1111000, 
 0b0000000, 
 0b0010000};

//button controls
int b1state0 = 1;
int b2state0 = 1;
int b1state1, b2state1;

int b1 = 12;//count down button
int b2 = 11;//count up button

//counter controls
int countstate = cntDown - 1;//initial value
int ones, tens;
int spd = 2900;//about 1 seconds per count
int rep = spd;

void setup()
{
    for (int i = 2; i < 11; i++)
    {
    pinMode(i, OUTPUT);
    }
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);
}

void count(int num)
{
    for (int i = 2; i <= 8; i++)
    {
    digitalWrite(i, bitRead(digit[num], i - 2));
    }
}

void loop()
{
    while (1 == 1)//waiting for toggle input
    {
        digitalWrite(9, 0);
        digitalWrite(10, 1);
        count(cntDown%10);
        delay(10);
        digitalWrite(9, 1);
        digitalWrite(10, 0);
        count(cntDown/10);
        delay(10);
        b1state1 = digitalRead(b1);
        if(b1state1 == 1 && b1state0 == 0)
        {
            b1state0 = b1state1;
            goto countdown;
        }
        b1state0 = b1state1;
    }
    countup:
    while (1 == 1)
    {
        tens = countstate / 10;
        ones = countstate % 10;
        while (rep > 0)
        {
            digitalWrite(9, 0);
            digitalWrite(10, 1);
            count(ones);
            delay(10);
            digitalWrite(9, 1);
            digitalWrite(10, 0);
            count(tens);
            delay(10);
            b1state1 = digitalRead(b1);
        if(b1state1 == 1 && b1state0 == 0)
        {
            b1state0 = b1state1;
            goto countdown;
        }
            b1state0 = b1state1;
            rep = rep - 1;
        }
        rep = spd;
        if(countstate != cntUp)
        {
            countstate = countstate + 1;
        }
        if(countstate > 16)
        {
            countstate = 0;
        }
    }
    countdown:
    while (1 == 1)
    {
        tens = countstate / 10;
        ones = countstate % 10;
        while (rep > 0)
        {
            digitalWrite(9, 0);
            digitalWrite(10, 1);
            count(ones);
            delay(10);
            digitalWrite(9, 1);
            digitalWrite(10, 0);
            count(tens);
            delay(10);
            b2state1 = digitalRead(b2);
        if(b2state1 == 1 && b2state0 == 0)
        {
            b2state0 = b2state1;
            goto countup;
        }
            b2state0 = b2state1;
            rep = rep - 1;
        }
        rep = spd;
        if(countstate != cntDown)
        {
            countstate = countstate - 1;
        }
        if(countstate < 0)
        {
            countstate = 16;
        }
    }
}
