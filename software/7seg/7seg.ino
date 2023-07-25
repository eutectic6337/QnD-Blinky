const char message[] = "dc615 ... dEFcon31   ";
//"01234567789. abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

#define TOTAL_DIGITS 3
#define DIGIT_ON_ms 5
#define DIGIT_OFF_ms (DIGIT_ON_ms*2/3)
#define SCROLL_ms ((DIGIT_ON_ms+DIGIT_OFF_ms)*TOTAL_DIGITS*7)

#define DIGIT_ON_count 100
#define DIGIT_OFF_count 100
#define SCROLL_count 500


// go high to drive an N-channel MOSFET to connect cathode to 0V
#define SEGMENT_A_pin D10
#define SEGMENT_B_pin D5
#define SEGMENT_C_pin D3
#define SEGMENT_D_pin D2
#define SEGMENT_E_pin D0
#define SEGMENT_F_pin D8
#define SEGMENT_G_pin D1
#define SEGMENT_dp_pin D6

// go low to drive a P-channel MOSFET to connect anode to Vbatt
#define DIGIT_1_pin D4
#define DIGIT_2_pin D9
#define DIGIT_3_pin D7

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
} raw_7segment_map[] = {
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
  {'p',unavailable},
  {'q',A|B|C|F|G},
  {'r',E|G},
  {'s',unavailable},
  {'t',unavailable},
  {'u',C|D|E},
  {'v',B|F|G},
  {'w',unavailable},
  {'x',unavailable},
  {'y',B|C|D|F|G},
  {'z',unavailable},

  {'A',A|B|C|E|F|G},
  {'B',unavailable},
  {'C',unavailable},
  {'D',unavailable},
  {'E',A|D|E|F|G},
  {'F',A|E|F|G},
  {'G',A|C|D|E|F},
  {'H',B|C|E|F|G},
  {'I',unavailable},
  {'J',B|C|D|E},
  {'K',unavailable},
  {'L',D|E|F},
  {'M',unavailable},
  {'N',unavailable},
  {'O',A|B|F|G},
  {'P',A|B|E|F|G},
  {'Q',unavailable},
  {'R',unavailable},
  {'S',unavailable},
  {'T',unavailable},
  {'U',A|B|C|D|E|F},
  {'V',unavailable},
  {'W',unavailable},
  {'X',unavailable},
  {'Y',unavailable},
  {'Z',unavailable},
};

#if 1
#define DEBUG Serial.print
#define DEBUGf Serial.printf
#define DEBUGln Serial.println
#else
#define DEBUG (void)
#define DEBUGf (void)
#define DEBUGln (void)
#endif

void enable_digit_1(void)
{
  digitalWrite(DIGIT_1_pin, LOW);
  DEBUG("digit 1 low;");
}
void disable_digit_1(void)
{
  digitalWrite(DIGIT_1_pin, HIGH);
  DEBUG("digit 1 high;");
}
void enable_digit_2(void)
{
  digitalWrite(DIGIT_2_pin, LOW);
  DEBUG("digit 2 low;");
}
void disable_digit_2(void)
{
  digitalWrite(DIGIT_2_pin, HIGH);
  DEBUG("digit 2 high;");
}
void enable_digit_3(void)
{
  digitalWrite(DIGIT_3_pin, LOW);
  DEBUG("digit 3 low;");
}
void disable_digit_3(void)
{
  digitalWrite(DIGIT_3_pin, HIGH);
  DEBUG("digit 3 high;");
}
void send_segments_to_display(unsigned char segments)
{
  if (segments & A) {
    digitalWrite(SEGMENT_A_pin, HIGH);
    DEBUG("sA high;");
  } else {
    digitalWrite(SEGMENT_A_pin, LOW);
    DEBUG("sA low;");
  }
  if (segments & B) {
    digitalWrite(SEGMENT_B_pin, HIGH);
    DEBUG("sB high;");
  } else {
    digitalWrite(SEGMENT_B_pin, LOW);
    DEBUG("sB low;");
  }
  if (segments & C) {
    digitalWrite(SEGMENT_C_pin, HIGH);
    DEBUG("sC high;");
  } else {
    digitalWrite(SEGMENT_C_pin, LOW);
    DEBUG("sC low;");
  }
  if (segments & D) {
    digitalWrite(SEGMENT_D_pin, HIGH);
    DEBUG("sD high;");
  } else {
    digitalWrite(SEGMENT_D_pin, LOW);
    DEBUG("sD low;");
  } if (segments & E) {
    digitalWrite(SEGMENT_E_pin, HIGH);
    DEBUG("sE high;");
  } else {
    digitalWrite(SEGMENT_E_pin, LOW);
    DEBUG("sE low;");
  }
  if (segments & F) {
    digitalWrite(SEGMENT_F_pin, HIGH);
    DEBUG("sF high;");
  } else {
    digitalWrite(SEGMENT_F_pin, LOW);
    DEBUG("sF low;");
  }
  if (segments & G) {
    digitalWrite(SEGMENT_G_pin, HIGH);
    DEBUG("sG high;");
  } else {
    digitalWrite(SEGMENT_G_pin, LOW);
    DEBUG("sG low;");
  }
  if (segments & dp) {
    digitalWrite(SEGMENT_dp_pin, HIGH);
    DEBUG("dp high;");
  } else {
    digitalWrite(SEGMENT_dp_pin, LOW);
    DEBUG("dp low;");
  }
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
unsigned char permuted_7segment_map[256];
void setup_7segment_map(void)
{
  for (unsigned i= 0; i<sizeof(raw_7segment_map)/sizeof(raw_7segment_map[0]); i++) {
    unsigned segments = raw_7segment_map[i].segments;
    permuted_7segment_map[raw_7segment_map[i].c] = segments;
    send_segments_to_display(segments);
    enable_digit_1();
    delay(DIGIT_ON_ms);
    disable_digit_1();
    delay(DIGIT_OFF_ms);
    enable_digit_2();
    delay(DIGIT_ON_ms);
    disable_digit_2();
    delay(DIGIT_OFF_ms);
    enable_digit_3();
    delay(DIGIT_ON_ms);
    disable_digit_3();
    delay(DIGIT_OFF_ms);
  }
}

const unsigned message_length = sizeof(message)/sizeof(message[0]) -1;
unsigned message_index(unsigned i)
{
  return i % message_length;
}

unsigned char message_to_display[TOTAL_DIGITS];
unsigned char segments_to_display[TOTAL_DIGITS];
unsigned next_char_to_display;
void setup_segment_display(void)
{
  message_to_display[0] = message[0];
  segments_to_display[0] = permuted_7segment_map[message_to_display[0]];
  message_to_display[1] = message[1];
  segments_to_display[1] = permuted_7segment_map[message_to_display[1]];
  message_to_display[2] = message[2];
  segments_to_display[2] = permuted_7segment_map[message_to_display[2]];
  next_char_to_display = 3;
}
void scroll_message(void)
{
  DEBUGf("scroll from [%.3s]", message_to_display);
  message_to_display[0] = message_to_display[1];
  segments_to_display[0] = segments_to_display[1];
  message_to_display[0] = message_to_display[2];
  segments_to_display[1] = segments_to_display[2];
  next_char_to_display = message_index(next_char_to_display + 1);
  message_to_display[2] = message[next_char_to_display];
  segments_to_display[2] = permuted_7segment_map[message_to_display[2]];
  DEBUGf(" to [%.3s]\n", message_to_display);
}

void setup() {
  Serial.begin(9600);
  setup_output_pins();
  setup_7segment_map();
  setup_segment_display();
}


unsigned display_digit_1 = DIGIT_ON_count;
unsigned display_digit_2 = 0;
unsigned display_digit_3 = 0;
unsigned digits_off = 0;
unsigned scroll = SCROLL_count;

void loop() {
  if (Serial.available() > 0) {
    Serial.read();
    Serial.println("github.com/eutectic6337/QnD-Blinky.git");
  }
  if (display_digit_1) {
    DEBUG("1.");
    disable_digit_2();
    disable_digit_3();
    enable_digit_1();
    send_segments_to_display(segments_to_display[0]);
    if (--display_digit_1 == 0) {
      display_digit_2 = DIGIT_ON_count;
    }
  }
  if (display_digit_2) {
    DEBUG("2.");
    disable_digit_1();
    disable_digit_3();
    enable_digit_2();
    send_segments_to_display(segments_to_display[1]);
    if (--display_digit_2 == 0) {
      display_digit_3 = DIGIT_ON_count;
    }
  }
  if (display_digit_3) {
    DEBUG("3.");
    disable_digit_1();
    disable_digit_2();
    enable_digit_3();
    send_segments_to_display(segments_to_display[2]);
    if (--display_digit_3 == 0) {
      digits_off = DIGIT_OFF_count;
    }
  }
  if (digits_off) {
    DEBUG("0.");
    enable_digit_1();
    enable_digit_2();
    enable_digit_3();
    send_segments_to_display(0);
    if (--digits_off == 0) {
      display_digit_1 = DIGIT_ON_count;
    }
  }

  if (--scroll == 0) {
    scroll_message();
  }
}
