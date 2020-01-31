const int ledGreen = 11;
const int ledYellow = 12;
const int ledRed = 13;
const int button = 2;
const int changeDelay = 5000;   // number of milliseconds between swapping from red->green or back if button hasn't caused override
const int midChange = 1000;     // number of milliseconds between changes light is red->yellow->green or vice-versa

int buttonPresses = 0;          // number of times the button has been pressed (simulating cars pulling up)
char currentLight = 'R';        // the current light that is on (red or green)

unsigned long lastChangeTime = 0;     // the time that the light last changed G->R || R->G
unsigned long currentTime = 0;        // the time this iteration of the loop started
unsigned long lastMidChange = 0;      // the time the last transitional change occurred
unsigned long lastDebounceTime = 0;   // the last time the button was toggled
unsigned long debounceDelay = 100;     // milliseconds to account debounce time on button presses


void setup() {
  Serial.begin(9600);

  for (int ledPin = 11; ledPin <=13; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
  pinMode(button, INPUT);
  digitalWrite(ledRed, HIGH);  // starts with Red Light
}

void loop() {

  currentTime = millis();

  if (digitalRead(button) == HIGH && millis() - lastDebounceTime > debounceDelay) {
    buttonPresses++;
    lastDebounceTime = millis();
  }

  if (currentTime - lastChangeTime > changeDelay || buttonPresses == 3) {
    currentLight = lightChange();
    if (buttonPresses == 3) {
      buttonPresses = 0;
    }
    lastChangeTime = millis();
  }
  Serial.print("Button Presses: ");
  Serial.println(buttonPresses);
}

char lightChange() {
  if (currentLight == 'R') {
    digitalWrite(ledRed, LOW);
    lastMidChange = millis();
    while (lastMidChange + midChange >= millis()) {
      digitalWrite(ledYellow, HIGH);
    }
    digitalWrite(ledYellow, LOW);
    lastMidChange = millis();
    digitalWrite(ledGreen, HIGH);
    return 'G';
  }
  else if (currentLight == 'G') {
    digitalWrite(ledGreen, LOW);
    lastMidChange = millis();
    while (lastMidChange + midChange >= millis()) {
      digitalWrite(ledYellow, HIGH);
    }
    digitalWrite(ledYellow, LOW);
    lastMidChange = millis();
    digitalWrite(ledRed, HIGH);
    return 'R';
  }
}
