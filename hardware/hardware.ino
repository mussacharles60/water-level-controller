

#define TRIG_PIN 9
#define ECHO_PIN 10

#define GREEN_LED A1
#define RED_LED A2

#define RELAY_PIN A3

long duration;
int distance;

int tank_height = 100;
int full_unit = 10;
int low_unit = tank_height - full_unit;

bool tank_was_empty = false;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  Serial.begin(9600);

  digitalWrite(GREEN_LED, 0);
  digitalWrite(RED_LED, 0);
  digitalWrite(RELAY_PIN, 0);
}

void loop() {
  // Clears the TRIG_PIN
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the TRIG_PIN on HIGH state for 10 micro seconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= full_unit) {
    tank_was_empty = false;
    digitalWrite(GREEN_LED, 1);
    digitalWrite(RED_LED, 0);
    digitalWrite(RELAY_PIN, 0);
  }
  else if (distance > full_unit && distance < low_unit) {
    digitalWrite(GREEN_LED, 0);
    if (tank_was_empty) {
      digitalWrite(RED_LED, 1);
      digitalWrite(RELAY_PIN, 1);
    } else {
      digitalWrite(RED_LED, 0);
      digitalWrite(RELAY_PIN, 0);
    }
  }
  else if ( distance >= low_unit) {
    tank_was_empty = true;
    digitalWrite(GREEN_LED, 0);
    digitalWrite(RED_LED, 1);
    digitalWrite(RELAY_PIN, 1);
  }
}