// Бинарное представление азбуки Морзе (5 бит на символ)
// Формат: LLLL L (4 бита - длина кода, 1 бит - первый символ)
const uint8_t morseCodes[] PROGMEM = {
  0b00010, // A (.-)    0001 0
  0b10100, // B (-...)  1010 0
  0b10110, // C (-.-.)  1011 0
  0b01100, // D (-..)   0110 0
  0b00001, // E (.)     0000 1
  0b10101, // F (..-.)  1010 1
  0b01110, // G (--.)   0111 0
  0b10000, // H (....)  1000 0
  0b01000, // I (..)    0100 0
  0b10011, // J (.---)  1001 1
  0b01101, // K (-.-)   0110 1
  0b10010, // L (.-..)  1001 0
  0b00110, // M (--)    0011 0
  0b00101, // N (-.)    0010 1
  0b00111, // O (---)   0011 1
  0b10011, // P (.--.)  1001 1
  0b10111, // Q (--.-)  1011 1
  0b01010, // R (.-.)   0101 0
  0b01001, // S (...)   0100 1
  0b00011, // T (-)     0001 1
  0b01001, // U (..-)   0100 1
  0b10001, // V (...-)  1000 1
  0b01011, // W (.--)   0101 1
  0b10101, // X (-..-)  1010 1
  0b10111, // Y (-.--)  1011 1
  0b01101  // Z (--..)  0110 1
};

// Параметры сигналов
const int DOT_DURATION = 1000;  // Длительность точки (мс)
const int DASH_DURATION = 3 * DOT_DURATION; // Длительность тире
const int SYMBOL_PAUSE = DOT_DURATION; // Пауза между символами
const int LETTER_PAUSE = 3 * DOT_DURATION; // Пауза между буквами
const int WORD_PAUSE = 5 * DOT_DURATION; // Пауза между словами

void setup() {
  pinMode(13, OUTPUT);
}

void playSymbol(bool isDash) {
  digitalWrite(13, HIGH); 
  delay(isDash ? DASH_DURATION : DOT_DURATION);
  digitalWrite(13, LOW); 
  delay(SYMBOL_PAUSE);
}

void playLetter(char letter) {
  if (letter >= 'A' && letter <= 'Z') {
    uint8_t code = pgm_read_byte(&morseCodes[letter - 'A']);
    uint8_t length = code >> 1; // Первые 4 бита - длина кода
    bool firstSymbol = code & 0x01; // Последний бит - первый символ
    
    for (uint8_t i = 0; i < length; i++) {
      bool isDash = (i == 0) ? firstSymbol : !firstSymbol;
      playSymbol(isDash);
    }
  }
  delay(LETTER_PAUSE - SYMBOL_PAUSE); // Компенсируем последнюю паузу
}

void playText(const char* text) {
  while (*text) {
    if (*text == ' ') {
      delay(WORD_PAUSE - LETTER_PAUSE);
    } else {
      playLetter(toupper(*text));
    }
    text++;
  }
}

void loop() {
  playText("HELLO WORLD");
  delay(5000);
}