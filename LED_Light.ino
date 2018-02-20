#define BLUELED  4
#define REDLED    5

#define PWMOUT1   12
#define PWMOUT2   13

void setup(void)
{
    pinMode(BLUELED,OUTPUT);        
    pinMode(REDLED,OUTPUT);
}


//void loop(void)
//{
//    digitalWrite(BLUELED,HIGH);   
//    digitalWrite(REDLED,HIGH);
//    delay(200);
//
//    digitalWrite(BLUELED,LOW);    
//    digitalWrite(REDLED,LOW);
//    delay(200);     
//}

void loop(void)
{
    for(uint32_t i=0;i<256;i++)
    {
       analogWrite(PWMOUT1,i);     
       analogWrite(PWMOUT2,i);    
       delay(40);
    }
    
    for(uint32_t i=256;i>0;i--)
    {
       analogWrite(PWMOUT1,i);     
       analogWrite(PWMOUT2,i);    
       delay(40);
    }        
}
