void setup() {
  Serial.begin(9600);
  delay(3000);
}

void JSONexpert(int num) {
    Serial.print("{");
    Serial.print(" 't':");
    Serial.print(num);
    Serial.print(",");
    Serial.print(" 'id':");
    Serial.print("'termometr'");
    Serial.println("}");
};

void loop() {
  //Serial.read();
    int rnd = random(25000, 30000);
    JSONexpert(rnd);
    delay(1000);
}
