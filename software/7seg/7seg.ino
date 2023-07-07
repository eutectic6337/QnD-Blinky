const char message[] = "dc615 ... dEFcon31   ";

const char alphabet[] =
  "0123456789"
  "._-~=\|/?[]"
  "abcdefghijklmnopqrstuvwxyz"
  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

const unsigned map[] =
//"0123456789"
  A|B|C|D|E|F,  //0
  B|C,//1
  A|B|D|E|G,//2
  A|B|C|D|G,//3
  B|C|F|G,//4
  A|C|D|F,//5
  A|C|D|E|F|G,//6
  A|B|C,//7
  A|B|C|D|E|F|G,//8
  A|B|C|D|F|G,//9
//"._-~=\|/?[]"
  dp,//.
  D,//_
  G,//-
  A,//~
  D|G,//=
  B|E|G,//backslash
  E|F,//|
  F|G|C,///
  A|B|E|G,//?
  A|D|E|F,//[
  A|B|C|D,//]
//"abcdefghijklmnopqrstuvwxyz"
  unavailable,//a
  C|D|E|F|G,//b
  D|E|G,//c
  B|C|D|E|G,//d
  A|B|C|D|F|G,//e
  A|E|F|G,//f
  unavailable,//g 9
  C|E|F|G,//h
  C,//i
  unavailable,//j
  unavailable,//k
  E|F,//l
  unavailable,//m
  C|E|G,//n
  C|D|E|G,//o
  unavailable,//p P
  A|B|C|F|G,//q
  E|G,//r
  unavailable,//s 5
  unavailable,//t
  C|D|E,//u
  unavailable,//v u
  unavailable,//w
  unavailable,//x H
  B|C|D|F|G,//y
  unavailable,//z 2
//"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  A|B|C|E|F|G,//A
  unavailable,//B 8
  unavailable,//C [
  unavailable,//D 0
  A|D|E|F|G,//E
  A|E|F|G,//F
  unavailable,//G
  B|C|E|F|G,//H
  unavailable,//I l,1
  B|C|D|E,//J
  unavailable,//K
  D|E|F,//L
  unavailable,//M
  unavailable,//N
  unavailable,//O 0
  A|B|E|F|G,//P
  unavailable,//Q
  unavailable,//R A
  unavailable,//S 5
  unavailable,//T
  A|B|C|D|E|F,//U
  unavailable,//V U
  unavailable,//W
  unavailable,//X H
  unavailable,//Y
  unavailable,//Z 2
};
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

}

void loop() {
  // put your main code here, to run repeatedly:

}
