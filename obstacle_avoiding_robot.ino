// Obstacle-Avoiding Robot with Ultrasonic Sensor and L298 Motor Driver

// Pin definitions
const int trigPin = 11;
const int echoPin = 10;

const int IN1 = 2; // Left motor forward
const int IN2 = 3; // Left motor backward
const int IN3 = 4; // Right motor forward
const int IN4 = 5; // Right motor backward

long duration;
long distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  distance = getDistance();

  if (distance > 10) {
    moveForward();
  } else {
    // Obstacle detected: back up and rotate until clear
    do {
      moveBackward();
      delay(400);
      stopMotors();
      delay(200);
      rotateRight();
      delay(400);
      stopMotors();
      delay(200);
      distance = getDistance();
    } while (distance <= 10 && distance != -1);

    // Path is clear, move forward
    moveForward();
  }
}

// Measure distance using ultrasonic sensor
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // 20ms timeout
  if (duration == 0) {
    Serial.println("No echo received!");
    return -1; // No echo
  }
  long dist = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(dist);
  return dist;
}

// Motor control functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void rotateRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
