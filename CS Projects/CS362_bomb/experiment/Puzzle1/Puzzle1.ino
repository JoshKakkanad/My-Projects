/*
THIS CODE IS NOT TESTED YET
*/


const int led1 = 10;
const int led2 = 13;
const int button1 = 6;
const int button2 = 7;
const int button3 = 8;
const int button4 = 9;
const int interval = 25;
unsigned long prevMillis = 0;

int answerArray[4];
int correctAnswer[4] = {3,0,2,1};
int count = 0;

int button1State, button2State,
    button3State, button4State;

int buttonStatus1, buttonStatus2, 
    buttonStatus3, buttonStatus4;

int ledCycleCount = 0;
unsigned long ledTime = 0;
const long ledInterval = 1000;


void ledCycle () {

    int cycleNum = ledCycleCount % 6;

    //int correctAnswer[4] = {3,0,1,2};
    if (cycleNum == 0) {

        //display 3
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
    } else if (cycleNum == 1) {

        //display 0
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
    } else if (cycleNum == 2) {

        //display 1
        digitalWrite(led1, HIGH);
        digitalWrite(led2, LOW);
    } else if (cycleNum == 3) {

        //display 2
        digitalWrite(led1, LOW);
        digitalWrite(led2, HIGH);
    } else if (cycleNum == 4) {
        
        // empty to reset and not confuse player
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
    } else if (cycleNum == 5) {
        
        //empty to reset and not confuse player
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
    }
    //Serial.println(cycleNum);
    ledCycleCount++;
}

void checkAnswer () {
    for (int i = 0; i < 4; i++) {
        if (answerArray[i] == correctAnswer[i]) {
            continue;
        } else {
            //serial communicate failure
            Serial.println("Failed");
            return;
        }
    }
    //serial communicate success and open box
    Serial.println("Success");
    return;
}

void checkButtonInput (int button) {
    int index = count % 4;

    switch (button) {
        case 6:
            answerArray[index] = 0;
            break;
        case 7:
            answerArray[index] = 1;
            break;
        case 8:
            answerArray[index] = 2;
            break;
        case 9:
            answerArray[index] = 3;
            break;
    }

    count++;
    if (index == 3) {
        checkAnswer();
    }
}

void brooklynDebounce (int buttonState, int *buttonStatus, int button) {
    buttonState = digitalRead(button);

    if (buttonState != *buttonStatus) {
        if (buttonState == HIGH) {
            checkButtonInput(button);
        }
    }
    *buttonStatus = buttonState;
}


void setup() {
  // put your setup code here, to run once:
    pinMode(button1, INPUT);
    pinMode(button2, INPUT);
    pinMode(button3, INPUT);
    pinMode(button4, INPUT);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    Serial.begin(9600);
    buttonStatus1 = digitalRead(button1);
    buttonStatus2 = digitalRead(button2);
    buttonStatus3 = digitalRead(button3);
    buttonStatus4 = digitalRead(button4);
}

void loop() {
  // put your main code here, to run repeatedly:
    unsigned long currentMillis = millis();
    if (currentMillis - prevMillis > interval) {
        brooklynDebounce(button1State, &buttonStatus1, button1);
        brooklynDebounce(button2State, &buttonStatus2, button2);
        brooklynDebounce(button3State, &buttonStatus3, button3);
        brooklynDebounce(button4State, &buttonStatus4, button4);
        prevMillis = currentMillis;
    }
    if (currentMillis - ledTime > ledInterval) {
        ledCycle();
        ledTime = currentMillis;
        //Serial.println(ledTime);
    }
}
