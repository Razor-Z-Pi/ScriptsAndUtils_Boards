void setup() {
  pinMode(13, OUTPUT);
}

// Массив с кодами Морзе для каждой буквы (A-Z)
const char* arr[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};

void playMorse(char s) {
  if (s == '.') 
  {
      digitalWrite(13, HIGH);  
      delay(1000);          
      digitalWrite(13, LOW);   
  } 
  else if (s == '-') 
  {
      digitalWrite(13, HIGH);  
      delay(2000);         
      digitalWrite(13, LOW);
      delay(1000);  
  }
}

void Letter(char letter) {
  if (letter >= 'A' && letter <= 'Z') 
  {
      const char* code = arr[letter - 'A'];  // Получаем код Морзе для буквы
      for (int i = 0; code[i] != '\0'; i++) 
      {
        playMorse(code[i]);
      }
  }
}

void playMorseText(const char* text) {
  for (int i = 0; text[i] != '\0'; i++) 
  {
      if (text[i] == ' ') 
      {
        delay(5000);
      } 
      else 
      {
        Letter(toupper(text[i]));
      }
  }
}

void loop() {
  const char* message = "HELLO WORLD";
  playMorseText(message);
}