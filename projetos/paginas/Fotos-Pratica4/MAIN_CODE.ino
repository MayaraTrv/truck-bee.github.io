//Defining  variable and the GPIO pin on Arduino
#define redPin 9
#define greenPin 10
#define  bluePin  11
#define buzzer 12

#define RPWM_Output 5// Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM) - amarelo ph
#define LPWM_Output 6 // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM) - laranja ph
#define button 2 // Arduind digital input for the main button

int last_bt_state = HIGH;
int aux = LOW;
unsigned long bt_last_time = 0;
unsigned long mtr_last_time = 0;
unsigned long TIME_MOTOR_ON = 30; //time in seconds

unsigned long red_last_time = millis();
int red_state = HIGH;

unsigned long green_last_time = 0;
int green_state = LOW;

unsigned long blue_last_time = 0;
int blue_state = LOW;

bool motor_on = false;

unsigned long deb_time = 50; //Debounce time

void setup() {
  Serial.begin(9600);
  //Defining the pins as OUTPUT
  pinMode(redPin,  OUTPUT);              
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);

  pinMode(button, INPUT);


  //Set the LED to white
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);

  digitalWrite(LPWM_Output, LOW);
  digitalWrite(RPWM_Output, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  turnOff();

}
void  loop() {

///////////////////////////////////MOTOR/////////////////////////////////////////////////////////////
  
  int bt_state = digitalRead(button);
  if (bt_state != last_bt_state)
  {
    bt_last_time = millis();
  }


  if ((!motor_on) && (millis() - bt_last_time > deb_time)) //When the debounce time is achived, turn on the motor
  {
    if (bt_state != aux)
    {
      aux = bt_state;
      if (aux == HIGH)
      {
        turnOn();
        mtr_last_time = millis();
      }
    }    
  }

  if ((motor_on) && (millis() - mtr_last_time> TIME_MOTOR_ON * 1000)) //After the time has passed, te motor turns off
  {
      turnOff();
  }
  last_bt_state = bt_state ;//Update button state

///////////////////////////////LED////////////////////////////////////////////////////////////////////
  if ((red_state == HIGH) && (millis() - red_last_time> 500)) //After the time has passed, the red  turns off and blue turns on
  {
      red_state = LOW;
      blue_state = HIGH;
      blue_last_time = millis();
  }
  if ((blue_state == HIGH) && (millis() - blue_last_time> 500)) //After the time has passed, the red  turns on and blue turns off
  {
    red_state = HIGH;
    blue_state = LOW;  
    red_last_time = millis();
  }

  digitalWrite (redPin, red_state);
  digitalWrite (bluePin, blue_state);
  digitalWrite (greenPin, green_state);
  if(motor_on)
  {
    digitalWrite (buzzer, red_state);
  }
}

////////////////////////////////////AUX FUNCTIONS////////////////////////////////////////////////

void turnOff()
{
  digitalWrite(LPWM_Output, LOW);
  digitalWrite(RPWM_Output, LOW);
  digitalWrite(LED_BUILTIN, LOW);
  motor_on = false;
  Serial.println("Turn OFF Motor");
}

void turnOn()
{
  digitalWrite(LPWM_Output, LOW);
  digitalWrite(RPWM_Output, LOW);
  analogWrite(RPWM_Output, 255);
  digitalWrite(LED_BUILTIN, HIGH);
  motor_on = true;
  Serial.println("Turn ON Motor");
}
