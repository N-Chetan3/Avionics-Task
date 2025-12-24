const int motorPin1=5; 
const int motorPin2=6; 
const int enablePin=9;
const int potPin=A0;
const int encoderChA=2;
const int encoderChB=3;

bool positionReached = false;

const int potThreshold = 5; 
int  potValue=0;
int prevPot=0;
int  motorPWM=128;

int en_pulse_count = 0;
float gearRatio=180.0;
float encoderPPR=12.0;
float actualAngle=0;
float setAngle=0;

long timeStamp=0;
long timeElapsed=0; 
int sampleRate=50;

double error=0;
double error_I=0;
double error_D=0;
double past_error=0;
const float Kp = 4;
const float Ki = 1;
const float Kd=0.1;

void setup()
{
  
  pinMode(encoderChA, INPUT_PULLUP);  
  attachInterrupt(digitalPinToInterrupt(encoderChA), encoderA_SR, RISING);
  pinMode(encoderChB, INPUT_PULLUP);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  Serial.begin(9600);  
}

void loop()
{
  
  potValue=analogRead(A0); 
  if (abs(potValue - prevPot) > potThreshold)
{

  en_pulse_count = 0;
  actualAngle = 0;

  error_I = 0;
  past_error = 0;

  positionReached = false;
  prevPot = potValue;
}

  setAngle=map(potValue,0,1023,+180,-180); 
  

  timeElapsed=millis()-timeStamp;
  if (timeElapsed >= sampleRate)
  {
    if (!positionReached)
{
  getAngle();
  computePID();
}
else
{
  motorPWM = 0;
}

    timeStamp=millis();
  }
   if (motorPWM > 0)
   {
     MotorCCW(0,abs(motorPWM));
   }
  
   else if (motorPWM < 0)
   {
     MotorCW(0,abs(motorPWM));
   }
  
  Serial.print("setAngle:");
  Serial.print(setAngle);
  Serial.print("\t");
  Serial.print("Motor PWM:");
  Serial.print(abs(motorPWM));
  Serial.print("\t");
  Serial.print("error: ");
  Serial.print(error);
  Serial.print("  Actual Angle: ");
  Serial.println(actualAngle);
  Serial.print("\t");
  delay(20);
 }

void computePID()
{
    error=setAngle- actualAngle; 
    error_I=error_I + error; 
    error_D= past_error- error;
    past_error=error;
    
    if (abs(error_I) > 5)
    {  
      error_I=0;
    }
    motorPWM=Kp*error+ Ki*error_I + Kd*error_D;
 
      
    if (motorPWM >= 255)
    {
      motorPWM=255;
    }
    
    else if (motorPWM <= -255)
    {
      motorPWM=-255;
    }  
     
   if (abs(error) < 0.25)
   {
    	motorPWM=0;
        positionReached = true;
	}
  prevPot=potValue;
}

  
void encoderA_SR()
{   
   if (digitalRead(encoderChB)==HIGH)
   {
    en_pulse_count++; 
   }
   else 
   {
    en_pulse_count--;
   }

 }

void getAngle()
{  
   
   actualAngle= (float)en_pulse_count*360/(encoderPPR*gearRatio);
    
   if (abs(actualAngle) >=200)
   {
     actualAngle=0;
     en_pulse_count=0;
   }
      
 }

void MotorCCW(int dir, int pwm)
{
  digitalWrite(motorPin1, dir);
  analogWrite(motorPin2, pwm);
}


void MotorCW(int dir, int pwm)
{
  digitalWrite(motorPin2, dir);
  analogWrite(motorPin1, pwm);
}

void MotorStop()
{
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  delay(20);
}


