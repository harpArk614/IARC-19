const int en_right=7, en_left=2, rightPin_1 = 6,rightPin_2 = 5,leftPin_1 = 4,leftPin_2 = 3;
int ir[6];
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
  
void left_turn (int left_speed , int right_speed, int delay_time)
  {
    analogWrite (en_right, right_speed);
    analogWrite (en_left, left_speed);    
    digitalWrite (rightPin_1,LOW);
    digitalWrite (rightPin_2,HIGH);
    digitalWrite (leftPin_1,LOW);
    digitalWrite (leftPin_2,HIGH);
    delay (delay_time);
  } 
  
void right_turn (int left_speed , int right_speed, int delay_time)
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
  
void setup()
{
  
  // motot setup
  pinMode (rightPin_1, OUTPUT);
  pinMode (rightPin_2, OUTPUT);
  pinMode (leftPin_1, OUTPUT);
  pinMode (leftPin_2, OUTPUT);
  pinMode (en_right, OUTPUT);
  pinMode (en_left, OUTPUT);
  
}
  
void loop()
  {
    ir [0] = analogRead(A5);
    ir [1] = analogRead(A4);
    ir [2] = analogRead(A3);
    ir [3] = analogRead(A2);
    ir [4] = analogRead(A1);
    ir [5] = analogRead(A0);
    // straight forward ** WWBBWW WWBWWW WWWBWW
    if ( (ir [0] <500 && ir [1] <500 && ir [2] >500 && ir [3] >500 && ir [4] <500 && ir [5] <500) || 
         (ir [0] <500 && ir [1] <500 && ir [2] >500 && ir [3] <500 && ir [4] <500 && ir [5] <500) || 
         (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] >500 && ir [4] <500 && ir [5] <500) )
          
          {
            forward (255,255);
          }
     
     //slight left moving forward ** WBBWWW WBWWWW
     else if ( (ir [0] <500 && ir [1] >500 && ir [2] >500 && ir [3] <500 && ir [4] <500 && ir [5] <500) ||
               (ir [0] <500 && ir [1] >500 && ir [2] <500 && ir [3] <500 && ir [4] <500 && ir [5] <500) )
                       {
               forward (240,255);
             }
          
      // **WBBBWW
           
      //more left moving forward ** BWWWWW BBWWWW
      else if ( (ir [0] >500 && ir [1] <500 && ir [2] <500 && ir [3] <500 && ir [4] <500 && ir [5] <500) ||
                (ir [0] >500 && ir [1] >500 && ir [2] <500 && ir [3] <500 && ir [4] <500 && ir [5] <500) )
      
              {
                forward (220,255);
              }
          
     //slight right moving forward ** WWWBBW WWWWBW
     else if ( (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] >500 && ir [4] >500 && ir [5] <500) ||
               (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] <500 && ir [4] >500 && ir [5] <500) )
             
             {
               forward (255,240);
             }
          
      //**WWBBBW
           
      //more right moving forward ** WWWWWB WWWWBB
      else if ( (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] <500 && ir [4] <500 && ir [5] >500) ||
                (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] <500 && ir [4] >500 && ir [5] >500) )
      
              {
                forward (255,220);
              }
                
     //turn left  ** BBBWWW BBBBWW BBBBBW BBBBBB
     else if ( (ir [0] >500 && ir [1] >500 && ir [2] >500 && ir [3] <500 && ir [4] <500 && ir [5] <500) ||
               (ir [0] >500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] <500 && ir [5] <500) ||
               (ir [0] >500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] <500) ||
               (ir [0] >500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] >500) )
           
             {
                left_turn (0,255,00);
             }
           
     //turn right -- but LEFT HAND RULE says no right turn, so bot goes straight ** WWWBBB WWBBBB WBBBBB
     else if ( (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] >500 && ir [4] >500 && ir [5] >500) ||
          (ir [0] <500 && ir [1] <500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] >500) ||
          (ir [0] <500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] >500) )
          
          {
            forward (255,255);
            //for right turn only **WWWWWW
            if ( (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] <500 && ir [4] <500 && ir [5] <500) )
              right_turn (255,255,00);
          }
          
     // LEFT HAND RULE -- turning left ** WWWWWW // WWWWWW ONLY IF NODAL LINE=0 INCLUDE LATERRR
     else if ( (ir [0] <500 && ir [1] <500 && ir [2] <500 && ir [3] <500 && ir [4] <500 && ir [5] <500) ||
          (ir [0] >500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] >500) )
          
          {
            left_turn (255,255,00);
            
          }
     //move forward through nodes ** WBWWBW BBWWBB BBWWBW WBWWBB BBWBBW WBBWBB
     else if ( (ir [0] <500 && ir [1] >500 && ir [2] <500 && ir [3] <500 && ir [4] >500 && ir [5] <500) ||
          (ir [0] >500 && ir [1] >500 && ir [2] <500 && ir [3] <500 && ir [4] >500 && ir [5] >500) ||
          (ir [0] >500 && ir [1] >500 && ir [2] <500 && ir [3] <500 && ir [4] >500 && ir [5] <500) ||
          (ir [0] <500 && ir [1] >500 && ir [2] <500 && ir [3] <500 && ir [4] >500 && ir [5] >500) ||
          (ir [0] >500 && ir [1] >500 && ir [2] <500 && ir [3] >500 && ir [4] >500 && ir [5] <500) ||
          (ir [0] <500 && ir [1] >500 && ir [2] >500 && ir [3] <500 && ir [4] >500 && ir [5] >500) )
          
          {
            forward (255,255);
          } 
          
     //120 degree turns, follow left **WBBBBW WWBBBW WBBBWW
     else if ( (ir [0] <500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] <500) ||
               (ir [0] <500 && ir [1] <500 && ir [2] >500 && ir [3] >500 && ir [4] >500 && ir [5] <500) ||
               (ir [0] <500 && ir [1] >500 && ir [2] >500 && ir [3] >500 && ir [4] <500 && ir [5] <500) )
               
               {
                 forward (220,255);
               }

  }
  
  
