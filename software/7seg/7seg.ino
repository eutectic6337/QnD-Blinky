const char message[] = "dc615 ... dEFcon31   ";

/* 7seg

  A  
 F B
  G
 E C
  D dp */
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
void populate_7segment_map(void)
{
  for (int i= 0; i<sizeof(rawmap)/sizeof(raw_7segment_map[0]); i++) {
    cached_7segment_map[raw_7segment_map[i].c] = raw_7segment_map[i].segments;
  }
}
unsigned char map(char c)
{
  return cached_7segment_map[(unsigned char)c];
}


#undefine A
#undefine B
#undefine C
#undefine D
#undefine E
#undefine F
#undefine G
#undefine dp

void setup() {
  // put your setup code here, to run once:
  populate_7segment_map();

}

void loop() {
  // put your main code here, to run repeatedly:

}
