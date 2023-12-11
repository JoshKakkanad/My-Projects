// correct wire to cut is black

int brown = 12, white = 8, black = 7, green = 4;
int valBrown, valWhite, valBlack, valGreen;
int status = 1;

void setup() {
    Serial.begin(9600);
    pinMode(brown, INPUT);
    pinMode(white, INPUT);
    pinMode(black, INPUT);
    pinMode(green, INPUT);    
}

void loop() {
    
    if (status) {
        valBrown = digitalRead(brown);
        valWhite = digitalRead(white);
        valBlack = digitalRead(black);
        valGreen = digitalRead(green);
        char output[100];
        sprintf(output, "brown: %d, white: %d. black: %d, green: %d", valBrown, valWhite, valBlack, valGreen);
        Serial.println(output);
        delay(1000);
        // if (valBrown == 1 && valWhite == 1 && valBlack == 1 && valGreen == 1) {
        //     Serial.println("bomb ticking");
        //     delay(150);
        // }
        // else if (valBrown == 0 || valWhite == 0 || valGreen == 0) {
        //     Serial.println("exploded!");
        //     output = "output: exploded!";
        //     delay(150);
        //     status = 0;
        // }
        // else if (valBlack == 0) {
        //     Serial.println("correct!");
        //     output = "output: correct!";
        //     delay(150);
        //     status = 0;
        // }    
    }
    else {
        //Serial.println(output);
        delay(150);
    }

    
}
