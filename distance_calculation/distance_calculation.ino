int timer_on =0, timer_reading=0, timer_final=0;
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
         t++;
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
        
