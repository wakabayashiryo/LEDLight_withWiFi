#define BLUELED  4
#define REDLED    5

#define PWMOUT1   12
#define PWMOUT2   13

void setup(void)
{
    pinMode(BLUELED,OUTPUT);        
    pinMode(REDLED,OUTPUT);

    analogWrite(PWMOUT1,0x00);
    analogWrite(PWMOUT2,0x00);
}

//    digitalWrite(BLUELED,HIGH);   
//    digitalWrite(REDLED,HIGH);
//    analogWrite(PWMOUT1,i);    max value 0xFF  
//    analogWrite(PWMOUT2,i);    

void loop(void)
{

  
}

