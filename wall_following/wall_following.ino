//oled
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
//oled pins
#define sclk 47
#define mosi 45
#define cs   39
#define rst  43
#define dc   41
// Color definitions
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);
//ir array
int ir[6];
//ultrasonic pins
const int echo_r = 25, trig_r = 23 ,gnd_r = 27, echo_l = 53, trig_l = 51,vcc_l= 49, echo_f = 31, trig_f = 33,gnd_f = 29,vcc_f = 35;
const int en_right=7, en_left=2, rightPin_1 = 6,rightPin_2 = 5,leftPin_1 = 4,leftPin_2 = 3;
int D_right, D_left, D_front, circular_patch=0;
char wall_side;
float duration_right, duration_left, duration_front;
void forward (int left_speed , int right_speed)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);
    digitalWrite (rightPin_1,HIGH);
    digitalWrite (rightPin_2,LOW);
    digitalWrite (leftPin_1,HIGH);
    digitalWrite (leftPin_2,LOW);
  } 
  
void backward (int left_speed , int right_speed)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,LOW);
    digitalWrite (rightPin_2,HIGH);
    digitalWrite (leftPin_1,LOW);
    digitalWrite (leftPin_2,HIGH);
  } 
  
void left_turn (int left_speed , int right_speed, int delay_time)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,HIGH);
    digitalWrite (rightPin_2,LOW);
    digitalWrite (leftPin_1,LOW);
    digitalWrite (leftPin_2,HIGH);
    delay (delay_time);
  } 
  
void right_turn (int left_speed , int right_speed, int delay_time)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,LOW);
    digitalWrite (rightPin_2,HIGH);
    digitalWrite (leftPin_1,HIGH);
    digitalWrite (leftPin_2,LOW);
    delay (delay_time);
  } 
  
void stop_ ()
  {    
    digitalWrite (rightPin_1,HIGH);
    digitalWrite (rightPin_2,HIGH);
    digitalWrite (leftPin_1,HIGH);
    digitalWrite (leftPin_2,HIGH);
  }
  
void setup()
{
  
  // motot setup
  pinMode (rightPin_1, OUTPUT);
  pinMode (rightPin_2, OUTPUT);
  pinMode (leftPin_1, OUTPUT);
  pinMode (leftPin_2, OUTPUT);
  pinMode (en_right, OUTPUT);
  pinMode (en_left, OUTPUT);
  //ultrasonic setup
    pinMode (echo_r, INPUT);
  pinMode (trig_r, OUTPUT);
  pinMode (echo_l, INPUT);
  pinMode (trig_l, OUTPUT);
  pinMode (echo_f, INPUT);
  pinMode (trig_f, OUTPUT);
  pinMode (gnd_r, OUTPUT);
  digitalWrite (gnd_r, LOW);
  pinMode (vcc_l, OUTPUT);
  digitalWrite (vcc_l, HIGH); 
  pinMode (gnd_f, OUTPUT);
  digitalWrite (gnd_f, LOW);
  pinMode (vcc_f, OUTPUT);
  digitalWrite (vcc_f, HIGH); 

 
 //oled
display.begin();
Serial.begin (9600);
  
}

void check_uss (char side)
{
  if ( side == 'l' )
  {
    // Clears the trigPin
    digitalWrite(trig_l, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig_l, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_l, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration_left = pulseIn(echo_l, HIGH);
    // Calculating the D
    D_left = duration_left*0.034/2;
  }
  
    else if ( side == 'r' )
  {
    // Clears the trigPin
    digitalWrite(trig_r, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig_r, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_r, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration_right = pulseIn(echo_r, HIGH);
    // Calculating the D
    D_right= duration_right*0.034/2;
  }
  
    else if ( side == 'f' )
  {
    // Clears the trigPin
    digitalWrite(trig_f, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trig_f, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_f, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration_front = pulseIn(echo_f, HIGH);
    // Calculating the D
    D_front= duration_front*0.034/2;
  }
  
}
  
void wall_following (char wall_side)
  {
    if ( wall_side == 'L' )
      {
       
       // left wall following
       check_uss('l');
       check_uss('f');
       //deviates from wall
       if(D_left > 7 && D_left < 10)
       {
         forward (180,200);
       }
      
       //deviate more from wall
       else if (D_left > 10 && D_left <30)
       {
         forward (160,200);
       }
      
       // perfect following
       else if (D_left > 5 && D_left<7)
       {
        forward (200,200);
       }
       // goes closer to wall
       else if (D_left <5 )
       {
         forward (200,180);
       }
      
       //left turn
       else if (D_left > 30)
       {
         forward ( 50,200);
       }
      
       //right turn
       else if (D_left<30 && D_front < 7)
       {
         right_turn (200,200,500);
       }
       
       //crossing boundary
       if ( ir[0]>500 || ir[1]>500 )
       {
         forward (200,160);
       }

     }
     
     else if ( wall_side == 'R')
     {
       // right wall following
       check_uss('r');
       check_uss('f');
       //deviates from wall
       if(D_right > 7 && D_right < 10)
       {
         forward (200,180);
       }
      
       //deviate more from wall
       else if (D_right > 10 && D_right <30)
       {
         forward (200,160);
       }
      
       // perfect following
       else if (D_right > 5 && D_right<7)
       {
        forward (200,200);
       }
       // goes closer to wall
       else if (D_right <5 )
       {
         forward (180,200);
       }
      
       //right turn
       else if (D_right > 30)
       {
         forward ( 200,50);
       }
      
       //left turn
       else if (D_right<30 && D_front < 7)
       {
         left_turn (200,200,500);
       }
       
       //crossing boundary
       if ( ir[4]>500 || ir[5]>500 )
       {
         forward (160,200);
       }

     }
  }
     
      void loop ()
      {
        //ir values
          ir[0] = analogRead(A5);
          ir[1] = analogRead(A4);
          ir[2] = analogRead(A3);
          ir[3] = analogRead(A2);
          ir[4] = analogRead(A1);
          ir[5] = analogRead(A0);
        if ( ir[0]>500 && ir[1]>500 && ir[2]>500 && ir[3]>500 && ir[4]>500 && ir[5]>500 )
        {
          check_uss ('r');
          check_uss ('l');
           if (D_right < 30 || D_left<30)
             circular_patch = 1;
           else 
             circular_patch = 0;
        }
         if (circular_patch==1)
         {
           if (D_right < D_left)
             wall_side = 'R';
             
           else if (D_right > D_left)
             wall_side = 'L';
         }
         else
           wall_side = 'N';
         
         //follow respective wall
         wall_following (wall_side);
         Serial.print (D_right);
         
      }
      
       
      
      
