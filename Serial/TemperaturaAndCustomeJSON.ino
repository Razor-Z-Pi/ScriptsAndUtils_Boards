void setup() {
  Serial.begin(9600);
  delay(3000);
}

void JSONexpert(int num) {
    Serial.println("{");
    Serial.print(" 't':");
    Serial.print(num);
    Serial.println(",");
    Serial.print(" 'id':");
    Serial.println("'termometr'");
    Serial.println("}");
};

void loop() {
  //Serial.read();
    int rnd = random(25000, 30000);
    JSONexpert(rnd);
    delay(1000);
}
