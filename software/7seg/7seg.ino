const char message[] = "dc615 - dEFcon31   ";
//"01234567789. abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

#if 0
#define DEBUG Serial.print
#define DEBUGf Serial.printf
#define DEBUGln Serial.println
#else
#define DEBUG (void)
#define DEBUGf (void)
#define DEBUGln (void)
#endif

#define TOTAL_DIGITS 3

#define DIGIT_ON_count 1
#define DIGIT_OFF_count 11
#define SCROLL_count 150

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
  {'#',A|B|F|G},
  {'^',A|B|F},
  {'@',A|B|D|E|F|G|dp},
  {'&',A|C|D|E|F|G|dp},
  {'+',B|C|G},
  {'`',F|G},
  {'\'',B|G},  
  {'\\',F|G|C},
  {'|',E|F},
  {'/',B|E|G},
  {'!',B|C|dp},
  {'?',A|B|E|G},
  {'[',A|D|E|F},
  {']',A|B|C|D},
  {'(',A|F|G},
  {')',A|B|G},
  {'<',D|E|G},
  {'>',C|D|G},

  {'a',C|D|E|G},
  {'b',C|D|E|F|G},
  {'c',D|E|G},
  {'d',B|C|D|E|G},
  {'e',A|B|D|E|F|G},
  {'f',A|E|F|G},
  {'g',A|B|C|D|F|G},
  {'h',C|E|F|G},
  {'i',C},
  {'j',C|D},
  {'k',unavailable},
  {'l',E|F},
  {'m',A|D|E|F|G},//90deg cw
  {'n',C|E|G},
  {'o',C|D|E|G},
  {'p',A|B|E|F|G},
  {'q',A|B|C|F|G},
  {'r',E|G},
  {'s',A|C|D|F},
  {'t',D|E|F|G},
  {'u',C|D|E},
  {'v',B|F|G},
  {'w',A|B|C|D|G},//90deg cw
  {'x',unavailable},
  {'y',B|C|D|F|G},
  {'z',A|B|D|E|G},

  {'A',A|B|C|E|F|G},
  {'B',A|B|C|D|E|F|G},
  {'C',A|D|E|F},
  {'D',A|B|C|D|E|F},
  {'E',A|D|E|F|G},
  {'F',A|E|F|G},
  {'G',A|C|D|E|F},
  {'H',B|C|E|F|G},
  {'I',E|F},
  {'J',B|C|D|E},
  {'K',unavailable},
  {'L',D|E|F},
  {'M',unavailable},
  {'N',unavailable},
  {'O',A|B|C|D|E|F},
  {'P',A|B|E|F|G},
  {'Q',A|B|C|D|E|F|dp},
  {'R',A|B|E|F|G|dp},
  {'S',A|C|D|F},
  {'T',A|E|F},
  {'U',A|B|C|D|E|F},
  {'V',A|B|C|D|E|F},
  {'W',unavailable},
  {'X',unavailable},
  {'Y',B|C|F|G},
  {'Z',A|B|D|E|G},
};

void enable_digit_1(void)
{
  digitalWrite(DIGIT_1_pin, LOW);
  //DEBUG("1");
}
void disable_digit_1(void)
{
  digitalWrite(DIGIT_1_pin, HIGH);
  //DEBUG("/1");
}
void enable_digit_2(void)
{
  digitalWrite(DIGIT_2_pin, LOW);
  //DEBUG("2");
}
void disable_digit_2(void)
{
  digitalWrite(DIGIT_2_pin, HIGH);
  //DEBUG("/2");
}
void enable_digit_3(void)
{
  digitalWrite(DIGIT_3_pin, LOW);
  //DEBUG("3");
}
void disable_digit_3(void)
{
  digitalWrite(DIGIT_3_pin, HIGH);
  //DEBUG("/3");
}
void send_segments_to_display(unsigned char segments)
{
  if (segments & A) {
    digitalWrite(SEGMENT_A_pin, HIGH);
    //DEBUG("A");
  } else {
    digitalWrite(SEGMENT_A_pin, LOW);
    //DEBUG("a");
  }
  if (segments & B) {
    digitalWrite(SEGMENT_B_pin, HIGH);
    //DEBUG("B");
  } else {
    digitalWrite(SEGMENT_B_pin, LOW);
    //DEBUG("b");
  }
  if (segments & C) {
    digitalWrite(SEGMENT_C_pin, HIGH);
    //DEBUG("C");
  } else {
    digitalWrite(SEGMENT_C_pin, LOW);
    //DEBUG("c");
  }
  if (segments & D) {
    digitalWrite(SEGMENT_D_pin, HIGH);
    //DEBUG("D");
  } else {
    digitalWrite(SEGMENT_D_pin, LOW);
    //DEBUG("d");
  } if (segments & E) {
    digitalWrite(SEGMENT_E_pin, HIGH);
    //DEBUG("E");
  } else {
    digitalWrite(SEGMENT_E_pin, LOW);
    //DEBUG("e");
  }
  if (segments & F) {
    digitalWrite(SEGMENT_F_pin, HIGH);
    //DEBUG("F");
  } else {
    digitalWrite(SEGMENT_F_pin, LOW);
    //DEBUG("f");
  }
  if (segments & G) {
    digitalWrite(SEGMENT_G_pin, HIGH);
    //DEBUG("G");
  } else {
    digitalWrite(SEGMENT_G_pin, LOW);
    //DEBUG("g");
  }
  if (segments & dp) {
    digitalWrite(SEGMENT_dp_pin, HIGH);
    //DEBUG("P");
  } else {
    digitalWrite(SEGMENT_dp_pin, LOW);
    //DEBUG("p");
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
  pinMode(DIGIT_1_pin, OUTPUT);
  digitalWrite(DIGIT_1_pin, HIGH);
  pinMode(DIGIT_2_pin, OUTPUT);
  digitalWrite(DIGIT_1_pin, HIGH);
  pinMode(DIGIT_3_pin, OUTPUT);
  digitalWrite(DIGIT_1_pin, HIGH);

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
}
unsigned char permuted_7segment_map[256];
void setup_7segment_map(void)
{
  for (unsigned i= 0; i<sizeof(raw_7segment_map)/sizeof(raw_7segment_map[0]); i++) {
    unsigned segments = raw_7segment_map[i].segments;
    permuted_7segment_map[raw_7segment_map[i].c] = segments;

    send_segments_to_display(segments);
    enable_digit_1();
    delay(1);
    enable_digit_2();
    delay(1);
    enable_digit_3();
    delay(1);

    disable_digit_1();
    delay(1);
    disable_digit_2();
    delay(1);
    disable_digit_3();
    delay(1);
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

  DEBUGf("message begins [%c%c%c]%02x%02x%02x(%u)\n",
    message_to_display[0], message_to_display[1], message_to_display[2],
    segments_to_display[0], segments_to_display[1], segments_to_display[2],
    next_char_to_display);
}
void scroll_message(void)
{
  DEBUGf("scroll from [%c%c%c]",
    message_to_display[0], message_to_display[1], message_to_display[2]);

  message_to_display[0] = message_to_display[1];
  segments_to_display[0] = segments_to_display[1];
  message_to_display[1] = message_to_display[2];
  segments_to_display[1] = segments_to_display[2];
  message_to_display[2] = message[next_char_to_display];
  segments_to_display[2] = permuted_7segment_map[message_to_display[2]];

  next_char_to_display = message_index(next_char_to_display + 1);

  DEBUGf(" to [%c%c%c]%02x%02x%02x(%u)\n",
    message_to_display[0], message_to_display[1], message_to_display[2],
    segments_to_display[0], segments_to_display[1], segments_to_display[2],
    next_char_to_display);
}

void setup() {
  Serial.begin(115200);
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
  //DEBUGf("0=%u,1=%u,2=%u,3=%u,s=%u\n", digits_off, display_digit_1, display_digit_2, display_digit_3, scroll);
  if (display_digit_1) {
    //DEBUG("1.");
    disable_digit_2();
    disable_digit_3();
    enable_digit_1();
    send_segments_to_display(segments_to_display[0]);
    delay(1);
    --display_digit_1;
    if (!display_digit_1) {
      display_digit_2 = DIGIT_ON_count;
    }
  }
  if (display_digit_2) {
    //DEBUG("2.");
    disable_digit_1();
    disable_digit_3();
    enable_digit_2();
    send_segments_to_display(segments_to_display[1]);
    delay(1);
    --display_digit_2;
    if (!display_digit_2) {
      display_digit_3 = DIGIT_ON_count;
    }
  }
  if (display_digit_3) {
    //DEBUG("3.");
    disable_digit_1();
    disable_digit_2();
    enable_digit_3();
    send_segments_to_display(segments_to_display[2]);
    delay(1);
    --display_digit_3;
    if (!display_digit_3) {
      digits_off = DIGIT_OFF_count;
    }
  }
  if (digits_off) {
    //DEBUG("0.");
    //enable_digit_1();
    //enable_digit_2();
    //enable_digit_3();
    send_segments_to_display(0);
    delay(1);
    disable_digit_1();
    disable_digit_2();
    disable_digit_3();
    --digits_off;
    if (!digits_off) {
      display_digit_1 = DIGIT_ON_count;
    }
  }

  if (scroll) {
    delay(1);
    --scroll;
    if (!scroll) {
      scroll_message();
      scroll = SCROLL_count;
    }
  }
}
