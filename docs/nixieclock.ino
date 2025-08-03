#include <MD_DS1307.h>
#include <Wire.h>
// Pin definitions for controlling the Nixie tubes
#define A1 3
#define B1 4
#define C1 5
#define D1 6
#define A2 7
#define B2 8
#define C2 9
#define D2 10
#define A3 11
#define B3 12
#define C3 13
#define D3 14
#define A4 15
#define B4 16
#define C4 2
#define D4 1
#define pot A3 // Potentiometer pin (not used in the code)
// Arrays of pins for convenient control
char A[4] = {A4, A3, A2, A1};
char B[4] = {B4, B3, B2, B1};
char C[4] = {C4, C3, C2, C1};
char D[4] = {D4, D3, D2, D1};

// Variables for storing digits and time
int zero;
int one;
int two;
int three;
int hour;
int minute;
void setup() {
// Set control pins as outputs
pinMode(A1, OUTPUT);
pinMode(B1, OUTPUT);
pinMode(C1, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(B2, OUTPUT);
pinMode(C2, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(A3, OUTPUT);
pinMode(B3, OUTPUT);
pinMode(C3, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(A4, OUTPUT);
pinMode(B4, OUTPUT);
pinMode(C4, OUTPUT);
pinMode(D4, OUTPUT);
pinMode(pot, INPUT); // Potentiometer as input (unused)
 // Initially turn off all digits on the tubes (set pins HIGH
for (char i = 0; i < 4; i++) {
digitalWrite(A[i], HIGH);
digitalWrite(B[i], HIGH);
digitalWrite(C[i], HIGH);
digitalWrite(D[i], HIGH);
}
 // Initialize RTC module
if (!RTC.isRunning())
RTC.control(DS1307_CLOCK_HALT, DS1307_OFF);
Serial.begin(9600);
}
void loop() {
RTC.readTime(); // Read current time from RTC
hour = RTC.h;
minute = RTC.m;

 // Calculate digits to be displayed
zero = (hour / 10) % 10;
one = hour % 10;
two = (minute / 10) % 10;
three = minute % 10;
 // Debug output to serial port
Serial.println(hour);
Serial.println(minute);
Serial.println(zero);
Serial.println(one);
Serial.println(two);
Serial.println(three);
offAll(); // Turn off all digits
 // Display digits on respective tubes
writenumber(0, zero);
writenumber(1, one);
writenumber(2, two);
writenumber(3, three);
delay(1000); // Refresh every second
}
// Function to display digit b on tube with index a
void writenumber(int a, int b) {
switch (b) {
case 0:
digitalWrite(A[a], LOW);
digitalWrite(B[a], LOW);
digitalWrite(C[a], LOW);
digitalWrite(D[a], LOW);
break;
case 1:
digitalWrite(A[a], HIGH);
digitalWrite(B[a], LOW);
digitalWrite(C[a], LOW);
digitalWrite(D[a], LOW);
break;
case 2:
digitalWrite(A[a], LOW);
digitalWrite(B[a], HIGH);
digitalWrite(C[a], LOW);
digitalWrite(D[a], LOW);
break;
case 3:
digitalWrite(A[a], HIGH);
digitalWrite(B[a], HIGH);
digitalWrite(C[a], LOW);
digitalWrite(D[a], LOW);
break;
case 4:
digitalWrite(A[a], LOW);
digitalWrite(B[a], LOW);
digitalWrite(C[a], HIGH);
digitalWrite(D[a], LOW);
break;
case 5:
digitalWrite(A[a], HIGH);
digitalWrite(B[a], LOW);
digitalWrite(C[a], HIGH);
digitalWrite(D[a], LOW);
break;
case 6:
digitalWrite(A[a], LOW);
digitalWrite(B[a], HIGH);
digitalWrite(C[a], HIGH);
digitalWrite(D[a], LOW);
break;
case 7:
digitalWrite(A[a], HIGH);
digitalWrite(B[a], HIGH);
digitalWrite(C[a], HIGH);
digitalWrite(D[a], LOW);
break;
case 8:
digitalWrite(A[a], LOW);
digitalWrite(B[a], LOW);
digitalWrite(C[a], LOW);
digitalWrite(D[a], HIGH);
break;
case 9:
digitalWrite(A[a], HIGH);
digitalWrite(B[a], LOW);
digitalWrite(C[a], LOW);
digitalWrite(D[a], HIGH);
break;
}
}
// Turns off the digit on tube with index a (sets all pins HIGH)
void off(int a) {
digitalWrite(A[a], HIGH);
digitalWrite(B[a], HIGH);
digitalWrite(C[a], HIGH);
digitalWrite(D[a], HIGH);

}
// Turns off all digits on all tubes//
void offAll() {
for (int i = 0; i < 4; i++) {
digitalWrite(A[i], HIGH);
digitalWrite(B[i], HIGH);
digitalWrite(C[i], HIGH);
digitalWrite(D[i], HIGH);
}
}