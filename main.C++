#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

Servo servo;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};

Keypad kp = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pirPin = 8;
bool systemAwake = false;

unsigned long lastActivity = 0;
const unsigned long timeout = 5000;

char correctPass[] = "1234";
int number = sizeof(correctPass) - 1;
char pass[sizeof(correctPass) - 1];
int i = 0, counter = 0;

bool door = 1;

void setup(){
    servo.attach(12);
    pinMode(pirPin, INPUT);
    lcd.init();
    lcd.noBacklight();
    servo.write(0);
}

void loop(){
    bool motionDetected = (digitalRead(pirPin) == HIGH);
    if (motionDetected){
        lastActivity = millis();
    }

    if (door ==1){
        if (motionDetected && !systemAwake){
            systemAwake = true;
            lcd.backlight();
            lcd.setCursor(0, 0);
            lcd.print("Insira a senha: ");
            lcd.setCursor(0, 1);
        } else if (systemAwake && (millis() - lastActivity > timeout)) {
            systemAwake = false;
            lcd.clear();
            lcd.noBacklight();
            i = 0;
        }
    }
    if (systemAwake){
        char key = kp.getKey();
        if (key){
            lastActivity = millis();
        }
        if (door == 0){
            if (key == 'C'){
                servo.write(0);
                i = counter = 0;
                door = 1;
                systemAwake = false;
                lcd.clear();
                lcd.noBacklight();
            }
        } else {
            if (key >= '0' && key <= '9'){
                lcd.print('*');
                pass[i] = key;
                i++;
            } else if (key == 'D'){
                if (i == number){
                    for (int j = 0; j < number; j++){
                        if (pass[j] == correctPass[j]) counter++;
                    } if (counter == number){
                        correct();
                    } else {wrong();}
                } else {wrong();}
            }
        }
    }
}

void wrong(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senha incorreta!    ");
    lcd.setCursor(0, 1);
    lcd.print("  Tente novamente!  ");
    delay(2000);
    i = 0;
    counter = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("insira a senha: ");
    lcd.setCursor(0, 1);
    lastActivity = millis();
}

void correct(){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Senha correta!   ");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("A porta abriu!");
    lcd.setCursor(0, 1);
    lcd.print("<C> Para fechar.");
    servo.write(90);
    delay(1000);
    i = 0;
    counter = 0;
    door = 0;
    lastActivity = millis();
}