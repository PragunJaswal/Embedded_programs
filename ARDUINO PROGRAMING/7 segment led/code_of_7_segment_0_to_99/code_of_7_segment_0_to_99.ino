
int f = 13;
int g = 12;
int e = 11;
int d = 10;
int c = 9;
int b = 8;
int a = 7;

int de = 300;
int da = 200;
void print_zero(){
   digitalWrite(0, 1);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 0); //0
  }
  void print_one(){
  digitalWrite(0, 0);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);} //1

  void print_two(){
  digitalWrite(0, 1);
  digitalWrite(1, 1);
  digitalWrite(2, 0);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 0);
  digitalWrite(6, 1);} //2

  void print_three(){
  digitalWrite(0, 1);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 1);} //3
  
  void print_four(){
  digitalWrite(0, 0);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 1);} //4

  void print_five(){
  digitalWrite(0, 1);
  digitalWrite(1, 0);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 1);} //5

  void print_six(){
  digitalWrite(0, 1);
  digitalWrite(1, 0);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);} //6

  void print_seven(){
  digitalWrite(0, 1);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 0);
  digitalWrite(4, 0);
  digitalWrite(5, 0);
  digitalWrite(6, 0);} //7


  void print_eight(){
  digitalWrite(0, 1);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 1);
  digitalWrite(5, 1);
  digitalWrite(6, 1);} //8

  void print_nine(){
  digitalWrite(0, 1);
  digitalWrite(1, 1);
  digitalWrite(2, 1);
  digitalWrite(3, 1);
  digitalWrite(4, 0);
  digitalWrite(5, 1);
  digitalWrite(6, 1);} //2



  
  void print_0(){
   digitalWrite(f,0);
  digitalWrite(g, 1);
  digitalWrite(e, 1);
  digitalWrite(d, 1);
  digitalWrite(c, 1);
  digitalWrite(b, 1);
  digitalWrite(a, 1); //0
  }
 void print_1(){
   digitalWrite(a, 0);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);}  // 1
void print_2(){
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 0);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 0);}  // 2
void print_3(){
digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 0);}  // 3

  void print_4(){
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);}  // 4

  void print_5(){
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);}  // 5
 
  void print_6(){
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 1);}  // 6
 
  void print_7(){
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 0);
  digitalWrite(e, 0);
  digitalWrite(f, 0);
  digitalWrite(g, 0);}   // 7

  void print_8(){
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 1);
  digitalWrite(f, 1);
  digitalWrite(g, 1);}  // 8

  void print_9(){
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  digitalWrite(c, 1);
  digitalWrite(d, 1);
  digitalWrite(e, 0);
  digitalWrite(f, 1);
  digitalWrite(g, 1);} //9

void setup() {

  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);

  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
 
}

void loop()
{
  print_zero();
  
  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_one();
  delay(da);

print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_two();
  delay(da);
  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_three();
  delay(da);

  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_four();
  delay(da);

  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_five();
  delay(da);
  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_six();
  delay(da);

  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_seven();
  delay(da);

  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_eight();
  delay(da);

  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_nine();
  delay(da);

  print_0();
  delay(de);
  print_1();
 
  delay(de);
  print_2();
 
  delay(de);
  print_3();
 
  delay(de);
  print_4();
 
  delay(de);
  print_5();
 
  delay(de);
  print_6();
 
  delay(de);
  print_7();
 
  delay(de);
  print_8();
 
  delay(de);
  print_9();
 
  delay(de);
  
  print_0();

  print_zero();
  delay(da);
  

}
