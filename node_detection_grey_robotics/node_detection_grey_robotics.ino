int nodal_line=0,central_black=0,white_space=0,f=0,t=0,j;
void setup ()
{
  Serial.begin(9600);
}
void loop ()
{
  // ir 0 is attached to A0, ir 1 to A1 and so on...
  int ir[6];
  ir [0] = analogRead(A5);
  ir [1] = analogRead(A4);
  ir [2] = analogRead(A3);
  ir [3] = analogRead(A2);
  ir [4] = analogRead(A1);
  ir [5] = analogRead(A0);
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
       (ir [0] <300 && ir [1] <300 && iirr [2] >500 && ir [3] <300 && ir [4] <300 && ir [5] <300) || 
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
        Serial.println("false node");
        Serial.print("no. of false node = ");
        Serial.println(f);
      }
    }
  
  if (nodal_line==1 && white_space==1) //when bot crosses nodal line and then finds white space (true node) 
    {
      for (j;j<1;j++)
      {
         t++;
         Serial.println("true node");
         Serial.print("no. of true nodes = ");
         Serial.println (t);

      }
    }
    
}
