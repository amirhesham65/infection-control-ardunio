/*
 *   INFO
 *    - Infection Control Bed
 *    - Authors:
 *      - Amir Hesham Khalil
 *      - Ali Tarek Atef
 *      - Ali Sherif Badran
 *      - Youssef Ashraf Mohamed
 *      - Hesham Tamer Mohamed
 *      - Muhannad Abdallah Abdallah
 *   
 *    
 * 
 *   BACKGROUND
 *   - Spread of COVID-19 occurs via airborne parricels and droplets.
 *   - People who are infected with COVID an release particles and droplets of respiratory fluids that contain the SARS CoV-2 virus into the air when they exhale.
 *   - The problem is that a person can be exposed by an infected person coughing or speaking near them.
 *   - They can also be exposed by inhaling aerosol particles that are spreading away from the infected person.
 *   - Transmission of COVID-19 from inhalation of virus in the air can occur at distances greater than six feet (182.88 cm ~ 180 cm)
 *   
 *   SOLUTION
 *   
 *   - This project will help in reducing rates of infection of the coronavirus through the following steps:
 *       - The patient's bed is surrounded by two ultrasonic sensors from the right and the left directions
 *       - If at least one ultrasonic sesnor detected a minumimum distance of 10cm between the patient's bed and the nearest person in the room an LED at the same direction will light up
 *       - Furthermore, once an LED lights up, the buzzer (piezo speaker) will send a sound signal of 2500Hz for half a second until the distance increases. 
 *       
 *       P.S: a scale of 18cm-to-1cm was used while taking measurements for the prototype.
 */


int ultrasonicL[3] = {3, 4, 2};
int ultrasonicR[3] = {6, 7, 5};
int speaker = 10;
int maxAllowedRange = 10;

// Calculating the distance based on radiation duration
float getDistanceOf(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  return 340 * (duration / 2) * (1e-4);
}

void setup() {
  // Setting up the Trigs
  pinMode(ultrasonicL[0], OUTPUT);
  pinMode(ultrasonicR[0], OUTPUT);

  // Setting up the Echos
  pinMode(ultrasonicL[1], INPUT);
  pinMode(ultrasonicR[1], INPUT);

  // Setting up the LEDs
  pinMode(ultrasonicL[2], OUTPUT);
  pinMode(ultrasonicR[2], OUTPUT);

  // Setting up the Speaker
  pinMode(speaker, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // initializing LEDS
  digitalWrite(ultrasonicL[2], LOW);
  digitalWrite(ultrasonicR[2], LOW);


  // Getting the distance of BOTH ultrasonic sensors
  float distL = getDistanceOf(ultrasonicL[0], ultrasonicL[1]);
  Serial.println(distL);

  float distR = getDistanceOf(ultrasonicR[0], ultrasonicR[1]);
  Serial.println(distR);

  
  // Check minimum constraints
  if (distL <= maxAllowedRange) {
    digitalWrite(ultrasonicL[2], HIGH), tone(speaker, 2500, 500);
  }

  if (distR <= maxAllowedRange) {
    digitalWrite(ultrasonicR[2], HIGH), tone(speaker, 2500, 500);
  }
  
  delay(200);
}
