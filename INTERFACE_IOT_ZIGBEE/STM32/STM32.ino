void setup()

{

pinMode(PC13, OUTPUT);

Serial.begin(9600);
}

void loop() {

if (Serial.available())

{

int state = Serial.parseInt();

if (state == 1)

{

digitalWrite(PC13, HIGH);



}

if (state == 2)

{

digitalWrite(PC13, LOW);


}

}

}
