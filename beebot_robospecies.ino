
/**********************
 *declare DC motor pins 
 **********************/
int motorpin1_1 = 3;
int motorpin1_2 = 5;
int motorpin2_1 = 6;
int motorpin2_2 = 9;
/**********************
 * declare switches
 **********************/
int switch_left = 2;
int switch_right = 4;
int switch_forward = 7;
int switch_backward = 8;
int switch_go = 12;
int switch_Pause = 10;
int switch_clear = 11;

/***************************
 * declare global variables
 **************************/
 bool goRight = 0;
 bool goLeft = 0;
 bool goForward = 0;
 bool goBackward = 0;
 bool LeftStep = 0;
 bool RightStep = 0;
 bool ForwardStep = 0;
 bool ReverseStep = 0;
 bool GoStep = 0;
 bool PauseStep = 0;
 bool ClearStep = 0;
 bool motionFlag = 0;
 int Left_Count = 0;
 long int priorityValue[50];
 int i = 0;
 int switchFlag = 0;
 int steps = 0;
/***************
 * servo motor library call
 **************/

long int switchValue = 0;
/********************
 * function void setup 
 * All the declaration and pin defination is done in this
 *******************/
void setup() 
{
  Serial.begin(9600);
  pinMode(motorpin1_1,OUTPUT);
  pinMode(motorpin1_2,OUTPUT);
  pinMode(motorpin2_1,OUTPUT);
  pinMode(motorpin2_2,OUTPUT);
  
  pinMode(switch_left,INPUT);
  pinMode(switch_right,INPUT);
  pinMode(switch_forward,INPUT);
  pinMode(switch_backward,INPUT);
  pinMode(switch_go,INPUT);
  pinMode(switch_Pause,INPUT);
  pinMode(switch_clear,INPUT);
  
}// end of void setup()

void loop() 
{ 
  
  switchValue = readswitches();
  
  if(switchFlag == 1)
  {
    
    priorityValue[i] = switchValue;
    i++;
    steps = i;
    switchFlag = 0;
  }// end of for(int i = 0;i<8;i++)
  
  switch(switchValue)
  {
    case 1:
            Left();
            break;
    case 2:
            Right();
            break;
    case 3:
            Forward();
            break;
    case 4:
            Backward();
            break;
    case 5:
            Go();
            break;
    case 6:
            Pause();
            break;            
    case 7:
            Clear();
            break;
    default :
           break;    
    
  }// end of switch(switchValue)
  
delay(250);

}// end of void loop()

/********************************************
 * motion function is used to move the
 * mouse according to the given direction
 ********************************************/
void Motion(int x)
{
  while(motionFlag == 1)
  {
       switch(x)
  {
    case 1:
            goLeft = 1;
            Left();
            break;
    case 2:
            goRight = 1;
            Right();
            break;
    case 3:
            goForward = 1;
            Forward();
            break;
    case 4:
            goBackward = 1;
            Backward();
            break;
    
    default :
           break;    
    
  }// end of switch(switchValue)

  motionFlag = 0;
  }// end of while(1)
  
}// end of void motion(int x)

/**********************************************************
 * unsigned int readswitches() function is used to read switches
 * to set mouse movements and direction
 *************************************************************/
unsigned int readswitches()
{
  
  LeftStep = digitalRead(switch_left);
  RightStep = digitalRead(switch_right);
  ForwardStep = digitalRead(switch_forward);
  ReverseStep = digitalRead(switch_backward);
  GoStep = digitalRead(switch_go);
  PauseStep = digitalRead(switch_Pause);
  ClearStep = digitalRead(switch_clear);
  
  int x;
  
  if(LeftStep == 0)
  {
    switchFlag = 1;
    x = 1;
    
  }
  else if(RightStep == 0)
  {
    switchFlag = 1;
    x = 2;
    
  }
  else if(ForwardStep == 0)
  {
    switchFlag = 1;
    x = 3;
    
  }
  else if(ReverseStep == 0)
  {
    switchFlag = 1;
    x = 4;
  }
  else if(GoStep == 0)
  {
    switchFlag = 1;
    x = 5;
  }
  else if(PauseStep == 1)
  {
    switchFlag = 1;
    x = 6;
  }
  else if(ClearStep == 0)
  {
    switchFlag = 1;
    x = 7;
  }
  
  return x;
} // end of bool readswitches()

/**************************************
 * void left function to move left direction
 ***************************************/
void Left()
{
  
  if(goLeft == 1)
  {
    Serial.println("Moving Left");
    analogWrite(motorpin1_2,200);
    //analogWrite(motorpin2_2,200);
      delay(1500);
  }
  else
  Serial.println("Left");

  analogWrite(motorpin1_2,0);
}// end of void Left(int Left_count)

/**************************************
 * void Right function to move Right direction
 ***************************************/
void Right()
{
  
  if(goRight == 1)
  {
    Serial.println("Moving Right");
    analogWrite(motorpin2_2,200); 
      delay(1500);
  }
  else
  Serial.println("Right");

  analogWrite(motorpin2_2,0); 
}// end of void Right()

void Forward()
{
  
  if(goForward == 1)
  {
    Serial.println("Moving Forward");
    digitalWrite(motorpin1_1,HIGH);
    digitalWrite(motorpin2_1,HIGH);
    delay(1000);
  }
  else
  Serial.println("Forward");
  
    digitalWrite(motorpin1_1,LOW);
    digitalWrite(motorpin2_1,LOW); 
}
void Backward()
{
  
  if(goBackward == 1)
  {
    Serial.println("Moving Backward");
    digitalWrite(motorpin1_2,HIGH);
    digitalWrite(motorpin2_2,HIGH);
    motionFlag = 0;
    delay(1000);
  }
  else
  Serial.println("Backward");
  
    digitalWrite(motorpin1_2,LOW);
    digitalWrite(motorpin2_2,LOW);
}

void Go()
{
  i = 0;
  Serial.println("Go ");
    while(i<steps)
    {
      
      Serial.println(priorityValue[i]);
      int j = priorityValue[i];
      motionFlag = 1;
      Motion(j);
      i++;
      delay(150);     
     
    }
  
}
void Pause()
{
  
}

void Clear()
{
  steps = 0;
  
}

