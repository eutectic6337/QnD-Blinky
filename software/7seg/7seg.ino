const char message[] = "dc615 ... dEFcon31   ";

#define TOTAL_DIGITS 3
#define DIGIT_ON_ms 100
#define SCROLL_ms 200

// go high to drive an N-channel MOSFET to connect cathode to 0V
#define SEGMENT_A_pin 11
#define SEGMENT_B_pin 6
#define SEGMENT_C_pin 4
#define SEGMENT_D_pin 3
#define SEGMENT_E_pin 1
#define SEGMENT_F_pin 9
#define SEGMENT_G_pin 2
#define SEGMENT_dp_pin 7

// go low to drive a P-channel MOSFET to connect anode to Vbatt
#define DIGIT_1_pin 5
#define DIGIT_2_pin 10
#define DIGIT_3_pin 8

/* 7seg

  A  
 F B
  G
 E C
  D dp */
#define none 0
#define A 0x01
#define B 0x02
#define C 0x04
#define D 0x08
#define E 0x10
#define F 0x20
#define G 0x40
#define dp 0x80
#define unavailable A|D|G

const struct {
  char c;
  unsigned char segments;
} raw_7segment_map[] =
  {'0', A|B|C|D|E|F},
  {'1', B|C},
  {'2',A|B|D|E|G},
  {'3',A|B|C|D|G},
  {'4',B|C|F|G},
  {'5',A|C|D|F},
  {'6',A|C|D|E|F|G},
  {'7',A|B|C},
  {'8',A|B|C|D|E|F|G},
  {'9',A|B|C|D|F|G},

  {' ',none},

  {'.',dp},
  {'_',D},
  {'-',G},
  {'~',A},
  {'=',D|G},
  {'\\',B|E|G},
  {'|',E|F},
  {'/',F|G|C},
  {'?',A|B|E|G},
  {'[',A|D|E|F},
  {']',A|B|C|D},

  {'a',unavailable},
  {'b',C|D|E|F|G},
  {'c',D|E|G},
  {'d',B|C|D|E|G},
  {'e',A|B|C|D|F|G},
  {'f',A|E|F|G},
  {'g 9',unavailable},
  {'h',C|E|F|G},
  {'i',C},
  {'j',unavailable},
  {'k',unavailable},
  {'l',E|F},
  {'m',unavailable},
  {'n',C|E|G},
  {'o',C|D|E|G},
  {'p P',unavailable},
  {'q',A|B|C|F|G},
  {'r',E|G},
  {'s 5',unavailable},
  {'t',unavailable},
  {'u',C|D|E},
  {'v u',B|F|G},
  {'w',unavailable},
  {'x H',unavailable},
  {'y',B|C|D|F|G},
  {'z 2',unavailable},

  {'A',A|B|C|E|F|G},
  {'B 8',unavailable},
  {'C [',unavailable},
  {'D 0',unavailable},
  {'E',A|D|E|F|G},
  {'F',A|E|F|G},
  {'G',unavailable},
  {'H',B|C|E|F|G},
  {'I l,1',unavailable},
  {'J',B|C|D|E},
  {'K',unavailable},
  {'L',D|E|F},
  {'M',unavailable},
  {'N',unavailable},
  {'O 0',A|B|F|G},
  {'P',A|B|E|F|G},
  {'Q',unavailable},
  {'R A',unavailable},
  {'S 5',unavailable},
  {'T',unavailable},
  {'U',A|B|C|D|E|F},
  {'V U',unavailable},
  {'W',unavailable},
  {'X H',unavailable},
  {'Y',unavailable},
  {'Z',unavailable},
};

unsigned char cached_7segment_map[256];
void setup_7segment_map(void)
{
  for (int i= 0; i<sizeof(rawmap)/sizeof(raw_7segment_map[0]); i++) {
    cached_7segment_map[raw_7segment_map[i].c] = raw_7segment_map[i].segments;
  }
}
void setup_output_pins(void)
{
  pinMode(SEGMENT_A_pin, OUTPUT);
  digitalWrite(SEGMENT_A_pin, LOW);
  pinMode(SEGMENT_B_pin, OUTPUT);
  digitalWrite(SEGMENT_B_pin, LOW);
  pinMode(SEGMENT_C_pin, OUTPUT);
  digitalWrite(SEGMENT_C_pin, LOW);
  pinMode(SEGMENT_D_pin, OUTPUT);
  digitalWrite(SEGMENT_D_pin, LOW);
  pinMode(SEGMENT_E_pin, OUTPUT);
  digitalWrite(SEGMENT_E_pin, LOW);
  pinMode(SEGMENT_F_pin, OUTPUT);
  digitalWrite(SEGMENT_F_pin, LOW);
  pinMode(SEGMENT_G_pin, OUTPUT);
  digitalWrite(SEGMENT_G_pin, LOW);
  pinMode(SEGMENT_dp_pin, OUTPUT);
  digitalWrite(SEGMENT_dp_pin, LOW);

  pinMode(DIGIT_1_pin, OUTPUT);
  digitalWrite(DIGIT_1_pin, HIGH);
  pinMode(DIGIT_2_pin, OUTPUT);
  digitalWrite(DIGIT_1_pin, HIGH);
  pinMode(DIGIT_3_pin, OUTPUT);
  digitalWrite(DIGIT_1_pin, HIGH);
}
int send_to_display(char c, unsigned char pos)
{
  // all digits off
  digitalWrite(DIGIT_1_pin, HIGH);
  digitalWrite(DIGIT_2_pin, HIGH);
  digitalWrite(DIGIT_3_pin, HIGH);

  if(pos == 0 || pos > TOTAL_DIGITS) return 0;

  unsigned segments = cached_7segment_map[(unsigned char)c];

  if (segments & A) {
    digitalWrite(SEGMENT_A_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_A_pin, LOW);
  }
  if (segments & B) {
    digitalWrite(SEGMENT_B_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_B_pin, LOW);
  }
  if (segments & C) {
    digitalWrite(SEGMENT_C_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_C_pin, LOW);
  }
  if (segments & D) {
    digitalWrite(SEGMENT_D_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_D_pin, LOW);
  } if (segments & E) {
    digitalWrite(SEGMENT_E_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_E_pin, LOW);
  }
  if (segments & F) {
    digitalWrite(SEGMENT_F_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_F_pin, LOW);
  }
  if (segments & G) {
    digitalWrite(SEGMENT_G_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_G_pin, LOW);
  }
  if (segments & dp) {
    digitalWrite(SEGMENT_dp_pin, HIGH);
  } else {
    digitalWrite(SEGMENT_dp_pin, LOW);
  }

  if (pos == 1) {
    digitalWrite(DIGIT_1_pin, LOW);
  }
  else if (pos == 2) {
    digitalWrite(DIGIT_2_pin, LOW);
  }
  else {
    digitalWrite(DIGIT_3_pin, LOW);
  }

  return 1;
}

// now eliminate these troublesome macros
#undef none
#undef A
#undef B
#undef C
#undef D
#undef E
#undef F
#undef G
#undef dp
#undef unavailable

const unsigned message_length = sizeof(message)/sizeof(message[0]) -1;
unsigned message_index(unsigned i)
{
  return i % message_length;
}

void setup() {
  setup_7segment_map();
  setup_output_pins();
}

unsigned next_char_to_display = 0;
void loop() {
  for (unsigned i = 0; i < TOTAL_DIGITS; i++) {
    send_to_display(message[message_index(next_char_to_display + i)], i + 1);
    delay(DIGIT_ON_ms);
  }
  next_char_to_display = message_index(next_char_to_display + 1);
  send_to_display(0, 0);
  delay(SCROLL_ms);
}
