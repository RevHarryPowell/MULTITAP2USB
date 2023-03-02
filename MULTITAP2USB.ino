#include "HID-Project.h"

/*
  SNES Multitap to USB adapter
  Developed for and tested on Seeduino Xiao SAMD21

  SNES multitap pinout:
               ________________
              | 0 0 0 0 | 0 0 0 ) 
               ----------------      
                + C L D   D M G
                V L A A   A U N
                  K T T   T X D
                    C A   A 
                    H 0   1


  NOTE: BY DEFAULT, ONLY 3 HID GAMEPADS WILL BE CREATED
  TO GET 4 GAMEPADS, CDC SERIAL MUST BE DESABLED ON THE ARDUINO
  add "#define CDC_DISABLED" and comment out "#define CDC_ENABLED" in C:\Users\<USER>\AppData\Local\Arduino15\packages\<BRAND>\hardware\<CONTROLLER>\<VERSION>\cores\arduino\USB\USBDesc.h
  >this will disable the serial port. To upload a new sketch, first put the board into bootloader mode (usually RESET x2).
  >to re-enable serial, undo the changes to USBDesc.h, put the board into bootloader mode, then upload any sketch
*/

// bit positions of each controller button in the status register
const int B_BUTTON               = 0;
const int Y_BUTTON               = 1;
const int SELECT_BUTTON          = 2;
const int START_BUTTON           = 3;
const int UP_BUTTON              = 4;
const int DOWN_BUTTON            = 5;
const int LEFT_BUTTON            = 6;
const int RIGHT_BUTTON           = 7;
const int A_BUTTON               = 8;
const int X_BUTTON               = 9;
const int LSHOULDER_BUTTON       = 10;
const int RSHOULDER_BUTTON       = 11;

const int latchDelay  = 12;  // latch pulse width in microseconds (SNES spec = 12)
const int clockDelay  = 6;   // clock pulse width in microseconds (SNES spec = 6)

// SNES Pins
const int snesClock       = 7;      // SNES multitap clock pin
const int snesLatch       = 8;      // SNES multitap latch pin
const int snesData0       = 5;      // SNES multitap data0 pin
const int snesData1       = 2;      // SNES multitap data1 pin
const int snesMux         = 3;      // SNES multitap multiplex pin

int pad2Register;           // SNES controller 2 button states. 0=pressed 1=released
int pad3Register;           // SNES controller 3 button states
int pad4Register;           // SNES controller 4 button states
int pad5Register;           // SNES controller 5 button states
 

void setup(){

  // configure pins
  pinMode(snesData0, INPUT);
  pinMode(snesData1, INPUT);
  pinMode(snesMux, OUTPUT);
  pinMode(snesClock, OUTPUT);
  pinMode(snesLatch, OUTPUT);

  digitalWrite(snesClock, LOW);      // SNES control lines idle low
  digitalWrite(snesLatch, LOW);
  digitalWrite(snesMux, HIGH);

  //Initialize HID gamepads
  Gamepad1.begin();
  Gamepad2.begin();
  Gamepad3.begin();
  Gamepad4.begin();
}

void loop(){
  readSNES();
  writeSNES1();
  writeSNES2();
  writeSNES3();
  writeSNES4();
}



void readSNES(){
  digitalWrite(snesMux, HIGH);            // Set mux pin high to read controllers 2 and 3

  digitalWrite(snesLatch, HIGH);          // latch pulse 
  delayMicroseconds(latchDelay);
  digitalWrite(snesLatch, LOW);
  
  for (int x = 0; x < 12; x++) {                        // read in the 12 controller buttons that were latched
    bitWrite(pad2Register, x, digitalRead(snesData0));  // store the current controller 2 button state on the data input into the register
    bitWrite(pad3Register, x, digitalRead(snesData1));  // store the current controller 3 button state on the data input into the register
    digitalWrite(snesClock, HIGH);                      // generate a clock pulse to bring the next button to the data input
    delayMicroseconds(clockDelay);
    digitalWrite(snesClock, LOW);                    
  }

  digitalWrite(snesMux, LOW);             // Set mux pin low to read controllers 4 and 5

  for (int x = 0; x < 12; x++) {                        // read in the 12 controller buttons that were latched
    bitWrite(pad4Register, x, digitalRead(snesData0));  // store the current controller 4 button state on the data input into the register
    bitWrite(pad5Register, x, digitalRead(snesData1));  // store the current controller 5 button state on the data input into the register
    digitalWrite(snesClock, HIGH);                      // generate a clock pulse to bring the next button to the data input
    delayMicroseconds(clockDelay);
    digitalWrite(snesClock, LOW);                    
  }
}

// Send commands to USB gamepad interface 1
void writeSNES1(){
  if (!bitRead(pad2Register, B_BUTTON)){
    Gamepad1.press(1);
  }
  else{
    Gamepad1.release(1);
  }
  if (!bitRead(pad2Register, Y_BUTTON)){
    Gamepad1.press(2);
  }
  else{
    Gamepad1.release(2);
  }
  if (!bitRead(pad2Register, SELECT_BUTTON)){
    Gamepad1.press(3);
  }
  else{
    Gamepad1.release(3);
  }
  if (!bitRead(pad2Register, START_BUTTON)){
    Gamepad1.press(4);
  }
  else{
    Gamepad1.release(4);
  }
  if (!bitRead(pad2Register, UP_BUTTON)){
    Gamepad1.yAxis(-32768);
  }
  else if (!bitRead(pad2Register, DOWN_BUTTON)){
    Gamepad1.yAxis(32767);
  }
  else{
    Gamepad1.yAxis(0);
  }
  if (!bitRead(pad2Register, LEFT_BUTTON)){
    Gamepad1.xAxis(-32768);
  }
  else if (!bitRead(pad2Register, RIGHT_BUTTON)){
    Gamepad1.xAxis(32767);
  }
  else{
    Gamepad1.xAxis(0);
  }
  if (!bitRead(pad2Register, A_BUTTON)){
    Gamepad1.press(5);
  }
  else{
    Gamepad1.release(5);
  }
  if (!bitRead(pad2Register, X_BUTTON)){
    Gamepad1.press(6);
  }
  else{
    Gamepad1.release(6);
  }
  if (!bitRead(pad2Register, LSHOULDER_BUTTON)){
    Gamepad1.press(7);
  }
  else{
    Gamepad1.release(7);
  }
  if (!bitRead(pad2Register, RSHOULDER_BUTTON)){
    Gamepad1.press(8);
  }
  else{
    Gamepad1.release(8);
  }

  Gamepad1.write();
}

// Send commands to USB gamepad interface 2
void writeSNES2(){
  if (!bitRead(pad3Register, B_BUTTON)){
    Gamepad2.press(1);
  }
  else{
    Gamepad2.release(1);
  }
  if (!bitRead(pad3Register, Y_BUTTON)){
    Gamepad2.press(2);
  }
  else{
    Gamepad2.release(2);
  }
  if (!bitRead(pad3Register, SELECT_BUTTON)){
    Gamepad2.press(3);
  }
  else{
    Gamepad2.release(3);
  }
  if (!bitRead(pad3Register, START_BUTTON)){
    Gamepad2.press(4);
  }
  else{
    Gamepad2.release(4);
  }
  if (!bitRead(pad3Register, UP_BUTTON)){
    Gamepad2.yAxis(-32768);
  }
  else if (!bitRead(pad3Register, DOWN_BUTTON)){
    Gamepad2.yAxis(32767);
  }
  else{
    Gamepad2.yAxis(0);
  }
  if (!bitRead(pad3Register, LEFT_BUTTON)){
    Gamepad2.xAxis(-32768);
  }
  else if (!bitRead(pad3Register, RIGHT_BUTTON)){
    Gamepad2.xAxis(32767);
  }
  else{
    Gamepad2.xAxis(0);
  }
  if (!bitRead(pad3Register, A_BUTTON)){
    Gamepad2.press(5);
  }
  else{
    Gamepad2.release(5);
  }
  if (!bitRead(pad3Register, X_BUTTON)){
    Gamepad2.press(6);
  }
  else{
    Gamepad2.release(6);
  }
  if (!bitRead(pad3Register, LSHOULDER_BUTTON)){
    Gamepad2.press(7);
  }
  else{
    Gamepad2.release(7);
  }
  if (!bitRead(pad3Register, RSHOULDER_BUTTON)){
    Gamepad2.press(8);
  }
  else{
    Gamepad2.release(8);
  }

  Gamepad2.write();
}

// Send commands to USB gamepad interface 3
void writeSNES3(){
  if (!bitRead(pad4Register, B_BUTTON)){
    Gamepad3.press(1);
  }
  else{
    Gamepad3.release(1);
  }
  if (!bitRead(pad4Register, Y_BUTTON)){
    Gamepad3.press(2);
  }
  else{
    Gamepad3.release(2);
  }
  if (!bitRead(pad4Register, SELECT_BUTTON)){
    Gamepad3.press(3);
  }
  else{
    Gamepad3.release(3);
  }
  if (!bitRead(pad4Register, START_BUTTON)){
    Gamepad3.press(4);
  }
  else{
    Gamepad3.release(4);
  }
  if (!bitRead(pad4Register, UP_BUTTON)){
    Gamepad3.yAxis(-32768);
  }
  else if (!bitRead(pad4Register, DOWN_BUTTON)){
    Gamepad3.yAxis(32767);
  }
  else{
    Gamepad3.yAxis(0);
  }
  if (!bitRead(pad4Register, LEFT_BUTTON)){
    Gamepad3.xAxis(-32768);
  }
  else if (!bitRead(pad4Register, RIGHT_BUTTON)){
    Gamepad3.xAxis(32767);
  }
  else{
    Gamepad3.xAxis(0);
  }
  if (!bitRead(pad4Register, A_BUTTON)){
    Gamepad3.press(5);
  }
  else{
    Gamepad3.release(5);
  }
  if (!bitRead(pad4Register, X_BUTTON)){
    Gamepad3.press(6);
  }
  else{
    Gamepad3.release(6);
  }
  if (!bitRead(pad4Register, LSHOULDER_BUTTON)){
    Gamepad3.press(7);
  }
  else{
    Gamepad3.release(7);
  }
  if (!bitRead(pad4Register, RSHOULDER_BUTTON)){
    Gamepad3.press(8);
  }
  else{
    Gamepad3.release(8);
  }

  Gamepad3.write();
}

// Send commands to USB gamepad interface 4
void writeSNES4(){
  if (!bitRead(pad5Register, B_BUTTON)){
    Gamepad4.press(1);
  }
  else{
    Gamepad4.release(1);
  }
  if (!bitRead(pad5Register, Y_BUTTON)){
    Gamepad4.press(2);
  }
  else{
    Gamepad4.release(2);
  }
  if (!bitRead(pad5Register, SELECT_BUTTON)){
    Gamepad4.press(3);
  }
  else{
    Gamepad4.release(3);
  }
  if (!bitRead(pad5Register, START_BUTTON)){
    Gamepad4.press(4);
  }
  else{
    Gamepad4.release(4);
  }
  if (!bitRead(pad5Register, UP_BUTTON)){
    Gamepad4.yAxis(-32768);
  }
  else if (!bitRead(pad5Register, DOWN_BUTTON)){
    Gamepad4.yAxis(32767);
  }
  else{
    Gamepad4.yAxis(0);
  }
  if (!bitRead(pad5Register, LEFT_BUTTON)){
    Gamepad4.xAxis(-32768);
  }
  else if (!bitRead(pad5Register, RIGHT_BUTTON)){
    Gamepad4.xAxis(32767);
  }
  else{
    Gamepad4.xAxis(0);
  }
  if (!bitRead(pad5Register, A_BUTTON)){
    Gamepad4.press(5);
  }
  else{
    Gamepad4.release(5);
  }
  if (!bitRead(pad5Register, X_BUTTON)){
    Gamepad4.press(6);
  }
  else{
    Gamepad4.release(6);
  }
  if (!bitRead(pad5Register, LSHOULDER_BUTTON)){
    Gamepad4.press(7);
  }
  else{
    Gamepad4.release(7);
  }
  if (!bitRead(pad5Register, RSHOULDER_BUTTON)){
    Gamepad4.press(8);
  }
  else{
    Gamepad4.release(8);
  }

  Gamepad4.write();
}
