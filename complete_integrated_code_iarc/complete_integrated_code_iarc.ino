//oled setup
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
//pins
#define sclk 47
#define mosi 45
#define cs   39
#define rst  43
#define dc   41
//color definition
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

const int en_right=7, en_left=2, rightPin_1 = 6,rightPin_2 = 5,leftPin_1 = 4,leftPin_2 = 3;
int ir[6];
// setup for node
int nodal_line=0,central_black=0,white_space=0,f=0,t=0,j;
// all white decision
int right_line=0;
//setup for check point
int interval = 800;
int previous_time=0, current_time,check_point=0;

//setup for ultrasonic

const int echo_r = 25, trig_r = 23 ,gnd_r = 27, echo_l = 53, trig_l = 51,vcc_l= 49, echo_f = 31, trig_f = 33,gnd_f = 29,vcc_f = 35;
int D_right, D_left, D_front;
char wall_side;
float duration_right, duration_left, duration_front;

// setup for distance calculation

int timer_on =0, timer_reading=0, timer_final=0;

//motor functions
void forward (int left_speed , int right_speed)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);
    digitalWrite (rightPin_1,HIGH);
    digitalWrite (rightPin_2,LOW);
    digitalWrite (leftPin_1,LOW);
    digitalWrite (leftPin_2,HIGH);
  } 
  
void backward (int left_speed , int right_speed)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,LOW);
    digitalWrite (rightPin_2,HIGH);
    digitalWrite (leftPin_1,HIGH);
    digitalWrite (leftPin_2,LOW);
  } 
  
void right_turn (int left_speed , int right_speed, int delay_time)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,LOW);
    digitalWrite (rightPin_2,HIGH);
    digitalWrite (leftPin_1,LOW);
    digitalWrite (leftPin_2,HIGH);
    delay (delay_time);
  } 
  
void left_turn (int left_speed , int right_speed, int delay_time)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,HIGH);
    digitalWrite (rightPin_2,LOW);
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
  
  //wall following functions
  
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

  
void setup()
{
  
  // motor setup
  pinMode (rightPin_1, OUTPUT);
  pinMode (rightPin_2, OUTPUT);
  pinMode (leftPin_1, OUTPUT);
  pinMode (leftPin_2, OUTPUT);
  pinMode (en_right, OUTPUT);
  pinMode (en_left, OUTPUT);
  
  //oled begin
  display.begin();
  
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

}
  
void loop()  
  {
    ir [0] = analogRead(A5);
    ir [1] = analogRead(A4);
    ir [2] = analogRead(A3);
    ir [3] = analogRead(A2);
    ir [4] = analogRead(A1);
    ir [5] = analogRead(A0);
    
     // check_point
    current_time = millis();
  // if all black, update previous_time to current time
    if ((ir [0] >700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] >700))
    previous_time=current_time;
 if(current_time - previous_time >= interval)
  {
    if (previous_time <= current_time + 100 && previous_time >= current_time-100)
     check_point++;
  }
 
 // line_following
    if ( check_point == 1 ||check_point == 4 )
 {
    // straight forward ** "WBWWBW BBWWBB" WWBBWW BBBBBB
    if (  (ir [0] <700 && ir [1] >700 && ir [2] <700 && ir [3] <700 && ir [4] >700 && ir [5] <700) ||
          (ir [0] >700 && ir [1] >700 && ir [2] <700 && ir [3] <700 && ir [4] >700 && ir [5] >700) ||
          (ir [0] <700 && ir [1] <700 && ir [2] >700 && ir [3] >700 && ir [4] <700 && ir [5] <700) ||
          (ir [0] >700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] >700)) 
          {
            forward (200,232);
          }
     
     //slight slight left ** "BBWWBW" WWBWWW 
     else if ( (ir [0] >700 && ir [1] >700 && ir [2] <700 && ir [3] <700 && ir [4] >700 && ir [5] <700) ||
               (ir [0] <700 && ir [1] <700 && ir [2] >700 && ir [3] <700 && ir [4] <700 && ir [5] <700)  )
          
          {
            forward (0,255);
            //forward (50,255);
            //forward (150,255);
            //forward (200,248);
          }
     
     //slight left moving forward ** "BBWBBW" WBBWWW WBWWWW
     else if ( (ir [0] >700 && ir [1] >700 && ir [2] <700 && ir [3] >700 && ir [4] >700 && ir [5] <700) ||
               (ir [0] <700 && ir [1] >700 && ir [2] >700 && ir [3] <700 && ir [4] <700 && ir [5] <700) ||
               (ir [0] <700 && ir [1] >700 && ir [2] <700 && ir [3] <700 && ir [4] <700 && ir [5] <700) )
             {
               left_turn (20,255,0);
             }
          
      // **WBBBWW
           
      //more left moving forward ** BBWWWW
     else if ( (ir [0] >700 && ir [1] >700 && ir [2] <700 && ir [3] <700 && ir [4] <700 && ir [5] <700) )
      
              {
                left_turn (120,255,0);
              }
       // more more left BWWWWW
      else if ( (ir [0] >700 && ir [1] <700 && ir [2] <700 && ir [3] <700 && ir [4] <700 && ir [5] <700))
           {
                left_turn (200,255,0);
              }
              
      // slight slight right ** "WBWWBB" WWWBWW
      else if ( (ir [0] <700 && ir [1] >700 && ir [2] <700 && ir [3] <700 && ir [4] >700 && ir [5] >700) ||
                (ir [0] <700 && ir [1] <700 && ir [2] <700 && ir [3] >700 && ir [4] <700 && ir [5] <700))
      {
        forward (255,00);
      }
      
     //slight right moving forward ** "WBBWBB" WWWBBW WWWWBW
    else if (  (ir [0] <700 && ir [1] >700 && ir [2] >700 && ir [3] <700 && ir [4] >700 && ir [5] >700) ||
               (ir [0] <700 &&  ir [1] <700 && ir [2] <700 && ir [3] >700 && ir [4] >700 && ir [5] <700) ||
               (ir [0] <700 && ir [1] <700 && ir [2] <700 && ir [3] <700 && ir [4] >700 && ir [5] <700) )
             
             {
               right_turn (255 , 30,0);
               
             }
          
      //**WWBBBW
           
      //more right moving forward ** WWWWBB
     else if ( (ir [0] <700 && ir [1] <700 && ir [2] <700 && ir [3] <700 && ir [4] >700 && ir [5] >700) )
      
              {
                right_turn (255,120,0);
              }
              
     //more more right moving forward ** WWWWWB
     else if ( (ir [0] <700 && ir [1] <700 && ir [2] <700 && ir [3] <700 && ir [4] <700 && ir [5] >700) )
      
               {
                 //right_turn (255,200,0);
                 //forward (255,00);
                 //forward (255,50);
                 //forward (255,100);
                //forward (255,145);
                right_turn (255,200,0);
              }
                
     //turn left  ** BBBWWW BBBBWW BBBBBW
     else if ( (ir [0] >700 && ir [1] >700 && ir [2] >700 && ir [3] <700 && ir [4] <700 && ir [5] <700) ||
               (ir [0] >700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] <700 && ir [5] <700) ||
               (ir [0] >700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] <700) )
           
             {
                left_turn (180,232,375);
             }
           
     //turn right -- but LEFT HAND RULE says no right turn, so bot goes straight ** WWWBBB WWBBBB WBBBBB
     else if ( (ir [0] <700 && ir [1] <700 && ir [2] <700 && ir [3] >700 && ir [4] >700 && ir [5] >700) ||
          (ir [0] <700 && ir [1] <700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] >700) ||
          (ir [0] <700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] >700) )
          
          {
            forward (200,232);
            right_line == 1;
          }
                   
     //120 degree turns, follow left **WBBBBW WWBBBW WBBBWW
     else if ( (ir [0] <700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] <700) ||
               (ir [0] <700 && ir [1] <700 && ir [2] >700 && ir [3] >700 && ir [4] >700 && ir [5] <700) ||
               (ir [0] <700 && ir [1] >700 && ir [2] >700 && ir [3] >700 && ir [4] <700 && ir [5] <700) )
               
               {
                 forward (0,255);
               }
               
     //for only **WWWWWW
      if ( (ir [0] <700 && ir [1] <700 && ir [2] <700 && ir [3] <700 && ir [4] <700 && ir [5] <700) )
          {
            if (nodal_line ==0)
            {
              if (right_line == 1)
              right_turn (250,255,390);
              else
              left_turn (180,232,375);
            }
              else if (nodal_line ==1)
               forward (200,232);
               
          }
               right_line=0;
               
               // NODE DETECTION
   if(central_black==1||white_space==1)
   {
    if ( (ir [0] <300 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] <300) ||
         (ir [0] >500 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] >500) ||
         (ir [0] >500 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] <300) ||
         (ir [0] <300 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] >500) ||
         (ir [0] >500 && ir [1] >500 && ir [2] <300 && ir [3] >500 && ir [4] >500 && ir [5] <300) ||
         (ir [0] <300 && ir [1] >500 && ir [2] >500 && ir [3] <300 && ir [4] >500 && ir [5] >500) )
                                                                                                               //line before any node
      {
        nodal_line =!nodal_line;
        central_black=0;
        white_space=0;
        j=0;
      }
   }
    
  if ( (ir [0] <300 && ir [1] <300 && ir [2] >500 && ir [3] >500 && ir [4] <300 && ir [5] <300) || 
       (ir [0] <300 && ir [1] <300 && ir [2] >500 && ir [3] <300 && ir [4] <300 && ir [5] <300) || 
       (ir [0] <300 && ir [1] <300 && ir [2] <300 && ir [3] >500 && ir [4] <300 && ir [5] <300) )
                                                                                                                // central black line
    {
     central_black=1;
    }
  if (ir[1]<300 && ir[2]<300 && ir[3]<300 && ir[4]<300 && ir[5]<300 && ir[0]<300)
     {
      white_space=1; // central white line (true node)
    }
    
  if (nodal_line==1 && central_black==1) //when bot crosses nodal line and then finds black line (false node) 
    {
      for (j;j<1;j++)
      {
        
        f++;
        display.fillScreen(BLACK);
        display.setCursor(0,0);
        display.setTextColor(RED);
        display.setTextSize(2);
        display.println("false\nnode");
        display.setTextColor(BLUE);
        display.setTextSize(2);
        display.print(f);
        
      }
    }
  
  if (nodal_line==1 && white_space==1) //when bot crosses nodal line and then finds white space (true node) 
    {
      for (j;j<1;j++)
      {
         t++;
        display.fillScreen(BLACK);
        display.setCursor(0,0);
        display.setTextColor(GREEN);
        display.setTextSize(2);
        display.println("true\nnode");
        display.setTextColor(BLUE);
        display.setTextSize(2);
        display.print(t);
      }
    }
 }

if (check_point == 2 || check_point == 3 )
{
    //check wall_side
        check_uss ('r');
        check_uss ('l');
           
        if (D_right < D_left)
        
            wall_side = 'R';
             
        else if (D_right > D_left)
     
            wall_side = 'L';
         
       //follow respective wall
       wall_following (wall_side);
       
}

// distance calculation

if (check_point == 4)
{
  if(central_black==1||white_space==1)
   {
    if ( (ir [0] <300 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] <300) ||
         (ir [0] >500 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] >500) ||
         (ir [0] >500 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] <300) ||
         (ir [0] <300 && ir [1] >500 && ir [2] <300 && ir [3] <300 && ir [4] >500 && ir [5] >500) ||
         (ir [0] >500 && ir [1] >500 && ir [2] <300 && ir [3] >500 && ir [4] >500 && ir [5] <300) ||
         (ir [0] <300 && ir [1] >500 && ir [2] >500 && ir [3] <300 && ir [4] >500 && ir [5] >500) )
                                                                                                               //line before any node
      {
        nodal_line =!nodal_line;
        central_black=0;
        white_space=0;
        j=0;
      }
   }
    
  if ( (ir [0] <300 && ir [1] <300 && ir [2] >500 && ir [3] >500 && ir [4] <300 && ir [5] <300) || 
       (ir [0] <300 && ir [1] <300 && ir [2] >500 && ir [3] <300 && ir [4] <300 && ir [5] <300) || 
       (ir [0] <300 && ir [1] <300 && ir [2] <300 && ir [3] >500 && ir [4] <300 && ir [5] <300) )
                                                                                                                // central black line
    {
     central_black=1;
    }
  if (ir[1]<300 && ir[2]<300 && ir[3]<300 && ir[4]<300 && ir[5]<300 && ir[0]<300)
     {
      white_space=1; // central white line (true node)
    }
  
  if (nodal_line==1 && white_space==1) //when bot crosses nodal line and then finds white space (true node) 
    {
      for (j;j<1;j++)
      {
         
         if ( timer_on == 0 )
         {
           timer_reading = millis();    //if timer was off when we detected a true node, start timer
           timer_on = 1;
         }
         else if ( timer_on == 1)
         {
           timer_final = timer_reading;   //stop timer 
           timer_on = 2;
         }
      }
    }
}
 
 // final_display 
 if (check_point ==5 )
 {
   stop_();
   
        display.fillScreen(BLACK);
        display.setCursor(0,0);
        display.setTextColor(YELLOW);
        display.setTextSize(2);
        display.println("FINISH");
        
        display.fillScreen(BLACK);
        display.setCursor(0,0);
        display.setTextColor(GREEN);
        display.setTextSize(2);
        display.println("true_node");
        display.setTextColor(BLUE);
        display.setTextSize(2);
        display.print(t);
        
        display.fillScreen(BLACK);
        display.setCursor(0,0);
        display.setTextColor(GREEN);
        display.setTextSize(2);
        display.println("distance");
        display.println(timer_final);
 }

  }
         
