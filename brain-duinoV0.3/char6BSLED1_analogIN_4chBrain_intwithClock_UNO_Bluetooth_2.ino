
/* 
char6BSLED1_analogIN_4chBrain_intwithClock_HMD

for Arduino pro mini / use program with Arduino Nano

Serial.begin(230400);  
max 512 Hz
set to 512 Hz
masahiro kahata
*/

/*
analogReference(DEFAULT, INTERNAL, INTERNAL1V1, INTERNAL2V56, or EXTERNAL)

Warning

Don't use anything less than 0V or more than 5V for external reference voltage on the AREF pin! 
If you're using an external reference on the AREF pin, you must set the analog reference to EXTERNAL before calling analogRead(). 
Otherwise, you will short together the active reference voltage (internally generated) and the AREF pin, 
possibly damaging the microcontroller on your Arduino board.
Alternatively, you can connect the external reference voltage to the AREF pin through a 5K resistor, 
allowing you to switch between external and internal reference voltages. 
Note that the resistor will alter the voltage that gets used as the reference because there is an internal 32K resistor on the AREF pin. 
The two act as a voltage divider, so, for example, 2.5V applied through the resistor will yield 2.5 * 32 / (32 + 5) = ~2.2V at the AREF pin.
*/

/*
  String length() 
 
 Examples of how to use length() in a String. 
 Open the Serial Monitor and start sending characters to see the results.
 
 created 1 Aug 2010
 by Tom Igoe
 
 http://arduino.cc/en/Tutorial/StringLengthTrim
 
 This example code is in the public domain.
*/
 
/*
 http://letsmakerobots.com/node/28278
 
Timer Overflow:
Timer overflow means the timer has reached is limit value. When a timer overflow interrupt occurs, the timer overflow bit TOVx will be set in the interrupt flag register TIFRx. When the timer overflow interrupt enable bit TOIEx in the interrupt mask register TIMSKx is set, the timer overflow interrupt service routine ISR(TIMERx_OVF_vect)  will be called.

 Output Compare Match:
When a output compare match interrupt occurs, the OCFxy flag will be set in the interrupt flag register TIFRx . When the output compare interrupt enable bit OCIExy in the interrupt mask register TIMSKx is set, the output compare match interrupt service ISR(TIMERx_COMPy_vect) routine will be called.

Timer Input Capture:
When a timer input capture interrupt occurs, the input capture flag bit ICFx will be set in the interrupt flag register TIFRx. When the input capture interrupt enable bit  ICIEx in the interrupt mask register TIMSKx is set, the timer input capture interrupt service routine ISR(TIMERx_CAPT_vect) will be called.

PWM and timer
There is fixed relation between the timers and the PWM capable outputs. When you look in the data sheet or the pinout of the processor these PWM capable pins have names like OCRxA, OCRxB or OCRxC (where x means the timer number 0..5). The PWM functionality is often shared with other pin functionality. 
The Arduino has 3Timers and 6 PWM output pins. The relation between timers and PWM outputs is:
Pins 5 and 6: controlled by timer0
Pins 9 and 10: controlled by timer1
Pins 11 and 3: controlled by timer2
*/

//timer interrupts
//by Amanda Ghassaei
//June 2012
//http://www.instructables.com/id/Arduino-Timer-Interrupts/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

//
//  http://arduino.cc/playground/Code/Timer1
//

//timer setup for timer0, timer1, and timer2.
//For arduino uno or any board with ATMEL 328/168.. diecimila, duemilanove, lilypad, nano, mini...

//this code will enable all three arduino timer interrupts.
//timer0 will interrupt at 2kHz
//timer1 will interrupt at 1Hz
//timer2 will interrupt at 8kHz

//storage variables
boolean toggle0 = 0;
boolean toggle1 = 0;
boolean toggle2 = 0;

//
int timeX =0;
//
//
String txtMsg = "";                         // a string for incoming text
int lastStringLength = txtMsg.length();     // previous length of the String

const int ledPin1 =  2;      // the number of the LED pin
const int ledPin2 =  4;      // the number of the LED pin
const int ledPin3 =  7;      // the number of the LED pin
const int ledPin4 =  8;      // the number of the LED pin
const int ledPin5 =  12;      // the number of the LED pin
const int ledPin6 =  13;      // the number of the LED pin
const int ledPinPCM7 =  3;      // the number of the LED pin
const int ledPinPCM8 =  5;      // the number of the LED pin
const int ledPinPCM9 =  6;      // the number of the LED pin
const int ledPinPCM10 =  9;      // the number of the LED pin
const int ledPinPCM11 =  10;      // the number of the LED pin
const int ledPinPCM12 =  11;      // the number of the LED pin

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 3; // Analog output pin that the LED is attached to
const int analogInPin2 = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPin2 = 5; // Analog output pin that the LED is attached to
const int analogInPin3 = A2;  // Analog input pin that the potentiometer is attached to
const int analogOutPin3 = 6; // Analog output pin that the LED is attached to
const int analogInPin4 = A3;  // Analog input pin that the potentiometer is attached to
const int analogOutPin4 = 9; // Analog output pin that the LED is attached to
const int analogInPin5 = A4;  // Analog input pin that the potentiometer is attached to
const int analogOutPin5 = 10; // Analog output pin that the LED is attached to
const int analogInPin6 = A5;  // Analog input pin that the potentiometer is attached to
const int analogOutPin6 = 11; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int sensorValue2 = 0;        // value read from the pot
int outputValue2 = 0;        // value output to the PWM (analog out)
int sensorValue3 = 0;        // value read from the pot
int outputValue3 = 0;        // value output to the PWM (analog out)
int sensorValue4 = 0;        // value read from the pot
int outputValue4 = 0;        // value output to the PWM (analog out)
int sensorValue5 = 0;        // value read from the pot
int outputValue5 = 0;        // value output to the PWM (analog out)
int sensorValue6 = 0;        // value read from the pot
int outputValue6 = 0;        // value output to the PWM (analog out)

String channel1 = "abc";
String channel2 = "abc";
String channel3 = "abc";
String channel4 = "abc";
String channel5 = "abc";
String channel6 = "abc";
String zeroChar = "0";

int afterReciveSerial = 0;


void setup() {
  // open the serial port:
//  Serial.begin(38400);
//   Serial.begin(9600);
//    Serial.begin(115200);  
        Serial.begin(230400);  
        
        //
        // 10 Aug2014
        //
        analogReference(EXTERNAL);
        
        
        
    // set the digital pin as output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);  
  pinMode(ledPin3, OUTPUT);  
  pinMode(ledPin4, OUTPUT);  
  pinMode(ledPin5, OUTPUT);  
  pinMode(ledPin6, OUTPUT);  
  pinMode(ledPinPCM7, OUTPUT);  
  pinMode(ledPinPCM8, OUTPUT);  
  pinMode(ledPinPCM9, OUTPUT);  
  pinMode(ledPinPCM10, OUTPUT);  
  pinMode(ledPinPCM11, OUTPUT);  
  pinMode(ledPinPCM12, OUTPUT);  
  
  cli();//stop interrupts

//set timer0 interrupt at 1024Hz : OCR0A = 243.14;// = (16*10^6) / (1024*64) - 1 (must be <256)  
//set timer0 interrupt at 1200Hz : OCR0A = 208.33;// = (16*10^6) / (1200*64) - 1 (must be <256)
//set timer0 interrupt at 2kHz : OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  TCCR0A = 0;// set entire TCCR2A register to 0
  TCCR0B = 0;// same for TCCR2B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 243;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS11 and CS10 bits for 64 prescaler
  TCCR0B |= (1 << CS11) | (1 << CS10);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
 

//set timer1 interrupt at 1Hz : OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
//set timer1 interrupt at 128Hz : OCR1A = 121.0703;// = (16*10^6) / (128*1024) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 60.35;// = (16*10^6) / (256*1024) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 975.56;// = (16*10^6) / (256*64) - 1 (must be <65536)

//set timer1 interrupt at 128Hz : OCR1A = 15624;// = (16*10^6) / (128*8) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
//set timer1 interrupt at 512Hz : OCR1A = 3905.25;// = (16*10^6) / (512*8) - 1 (must be <65536)
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments

//     OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
          OCR1A = 3905.25;// = (16*10^6) / (512*8) - 1 (must be <65536)
  //        OCR1A = 3986; // = (16*10^6) / (503*8) - 1 (must be <65536) // it is good
 //           OCR1A = 1952.625;// = (16*10^6) / (1024*8) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
//  TCCR1B |= (1 << CS12) | (1 << CS10);  
  
    // Set CS11 and CS10 bits for 64 prescaler
//  TCCR1B |= (1 << CS11) | (1 << CS10);   

  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);   
  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

 /*
//set timer2 interrupt at 8kHz : OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
//set timer2 interrupt at 8kHz : OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS11 bit for 8 prescaler
  TCCR2B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
 */

sei();//allow interrupts

}

ISR(TIMER0_COMPA_vect){// set timer0 interrupt at 1024Hz
  if ( afterReciveSerial == 0 )  {
//   runLED();
  }
}

ISR(TIMER1_COMPA_vect){ // timer1 interrupt at 256Hz

    send4Data();
}

   /*
ISR(TIMER2_COMPA_vect){//timer1 interrupt 8kHz toggles ledPin1 : pin 2
//generates pulse wave of frequency 8kHz/2 = 4kHz (takes two cycles for full wave- toggle high then toggle low)
// pin 5 connect to digital filter
  if (toggle2){
    digitalWrite(ledPin1,HIGH); 
    toggle2 = 0;
  }
  else{
    digitalWrite(ledPin1,LOW);
    toggle2 = 1;
  }
}
 */

void loop() {
/*
 
    if (Serial.available() > 0) {
     int inChar = Serial.read();
 
//  Serial.println(inChar);
 
    afterReciveSerial = 1;
    
      if ( inChar =='A' ) // 1
         digitalWrite(ledPinPCM7, HIGH);
      if ( inChar =='a' )
          digitalWrite(ledPinPCM7, LOW);

      if ( inChar =='B' ) // 2
        digitalWrite(ledPinPCM8, HIGH);
      if (  inChar =='b' )
        digitalWrite(ledPinPCM8, LOW);

      if ( inChar =='C' ) // 3
         digitalWrite(ledPinPCM9, HIGH);
      if (  inChar =='c' )
        digitalWrite(ledPinPCM9, LOW);


      if (  inChar =='D' ) // 4
        digitalWrite(ledPinPCM10, HIGH);
      if (  inChar =='d' )
         digitalWrite(ledPinPCM10, LOW);

      if  (  inChar =='E' ) // 5
        digitalWrite(ledPinPCM11, HIGH);
      if (  inChar =='e' )
         digitalWrite(ledPinPCM11, LOW);

      if (  inChar =='F' ) // 6
        digitalWrite(ledPinPCM12, HIGH);
      if (  inChar =='f' )
         digitalWrite(ledPinPCM12, LOW);


 if (  inChar =='0' )
          setSampleSpeed(120);

 if (  inChar =='1' )
          setSampleSpeed(240);

 if (  inChar =='2' )
          setSampleSpeed(480);

 if (  inChar =='5' )
          setSampleSpeed(128);

 if (  inChar =='6' )
          setSampleSpeed(256);

 if (  inChar =='7' )
          setSampleSpeed(512);



    }
    
    
    delay(10);
    */
}


void send4Data() {
 txtMsg = "";


  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
//  outputValue = map(sensorValue, 0, 1023, 0, 255);  
outputValue =  sensorValue;        

         
   sensorValue2 = analogRead(analogInPin2);            
  // map it to the range of the analog out: 
//    outputValue2 = map(sensorValue2, 60, 690, 0, 255);  
outputValue2 = sensorValue2;
  // change the analog out value:
//  if (outputValue2<0) outputValue2=0;
//   analogWrite(ledPinPCM11, outputValue2);  
  
//    sensorValue3 = 0;            
     sensorValue3 = analogRead(analogInPin3);            
  // map it to the range of the analog out:
 //   outputValue3 = map(sensorValue3, 60, 690, 0, 255); 
outputValue3 =  sensorValue3;
  // change the analog out value:
//  if (outputValue3<0) outputValue3=0;
//   analogWrite(ledPinPCM12, outputValue3);  
  
//      sensorValue4 = 0;            
       sensorValue4 = analogRead(analogInPin4);            
  // map it to the range of the analog out:  
//    outputValue4 = map(sensorValue4, 60, 690, 0, 255);  
outputValue4 = sensorValue4;
  // change the analog out value:
//  if (outputValue4<0) outputValue4=0;
//   analogWrite(ledPinPCM10, outputValue4);  
   
  // print the results to the serial monitor:  
channel1 = String(  outputValue, HEX );
channel2 = String(  outputValue2, HEX );
channel3 = String(  outputValue3, HEX );
channel4 = String(  outputValue4, HEX );

if (channel1.length() == 1) {
    Serial.print(zeroChar);
  Serial.print(zeroChar);
}
if (channel1.length() == 2)
  Serial.print(zeroChar);
    
  Serial.print(channel1);      
  Serial.print("\t");     
 
  if (channel2.length() ==1)  {
  Serial.print(zeroChar);
  Serial.print(zeroChar);
  }
 if (channel2.length() ==2)
  Serial.print(zeroChar);
  
  Serial.print(channel2);   
  Serial.print("\t");    

if (channel3.length() ==1) {
  Serial.print(zeroChar);
    Serial.print(zeroChar);
}
if (channel3.length() ==2)
  Serial.print(zeroChar);
  
  Serial.print(channel3); 
  Serial.print("\t");      

if (channel4.length() ==1) {
  Serial.print(zeroChar);  
  Serial.print(zeroChar);  
}
if (channel4.length() ==2)
  Serial.print(zeroChar);  
  
  Serial.print(channel4);  
//  Serial.println(channel4); 
  
  Serial.print("\r");  
}


 void runLED()  {
   
    // :CH0BS1=24: // G
 // :CH0BS2=24: // B
 // :CH0BS3=24: // R
 // :CH1BS1=24: // G
 // :CH1BS2=24: // B
 // :CH1BS3=24: // R
    

// R : 

// analogWrite(ledPinPCM7, 255); // red
// analogWrite(ledPinPCM8, 0); // blue
// analogWrite(ledPinPCM9, 0); // green

      if ( (timeX>=0) && (timeX<100) )
        digitalWrite(ledPinPCM7, HIGH);
      else if ( (timeX>=100) && (timeX<200) )
         digitalWrite(ledPinPCM7, LOW);

      if ( (timeX>=100) && (timeX<200) )
        digitalWrite(ledPinPCM8, HIGH);
      else if ( (timeX>=200) && (timeX<300) )
         digitalWrite(ledPinPCM8, LOW);

      if ( (timeX>=200) && (timeX<300) )
        digitalWrite(ledPinPCM9, HIGH);
      else if ( (timeX>=300) && (timeX<400) )
         digitalWrite(ledPinPCM9, LOW);

      if ( (timeX>=300) && (timeX<400) )
        digitalWrite(ledPinPCM10, HIGH);
      else if ( (timeX>=400) && (timeX<500) )
         digitalWrite(ledPinPCM10, LOW);

      if  ( (timeX>=400) && (timeX<500) )
        digitalWrite(ledPinPCM11, HIGH);
      else if ( (timeX>=500) && (timeX<600) )
         digitalWrite(ledPinPCM11, LOW);

      if ( (timeX>=500) && (timeX<600) )
        digitalWrite(ledPinPCM12, HIGH);
      else if ( (timeX>=0) && (timeX<100) )
         digitalWrite(ledPinPCM12, LOW);

    timeX = timeX+1;
    if ( timeX > 600 ) timeX=0;
}

void setSampleSpeed(int sampleN)  {
  cli();//stop interrupts

//set timer1 interrupt at 1Hz : OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
//set timer1 interrupt at 128Hz : OCR1A = 121.0703;// = (16*10^6) / (128*1024) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 60.35;// = (16*10^6) / (256*1024) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 975.56;// = (16*10^6) / (256*64) - 1 (must be <65536)

//set timer1 interrupt at 128Hz : OCR1A = 15624;// = (16*10^6) / (128*8) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
//set timer1 interrupt at 512Hz : OCR1A = 3905.25;// = (16*10^6) / (512*8) - 1 (must be <65536)
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments

switch (sampleN)  {
  case 120: 
  OCR1A = 16665.7;// = (16*10^6) / (120*8) - 1 (must be <65536)
  break;
    case 240: 
  OCR1A = 8332.3;// = (16*10^6) / (240*8) - 1 (must be <65536)
  break;
    case 480: 
  OCR1A = 4165.7;// = (16*10^6) / (480*8) - 1 (must be <65536)
  break;
    case 128: 
  OCR1A = 15624;// = (16*10^6) / (128*8) - 1 (must be <65536)
  break;
    case 256: 
  OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
  break;
    case 512: 
  OCR1A = 3905.25;// = (16*10^6) / (512*8) - 1 (must be <65536)
  break;
  default:
  OCR1A = 16665.7;// = (16*10^6) / (120*8) - 1 (must be <65536)
}


//    OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
//        OCR1A = 3905.25;// = (16*10^6) / (512*8) - 1 (must be <65536)
 //           OCR1A = 1952.625;// = (16*10^6) / (1024*8) - 1 (must be <65536) : not work
 
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
//  TCCR1B |= (1 << CS12) | (1 << CS10);  
  
    // Set CS11 and CS10 bits for 64 prescaler
//  TCCR1B |= (1 << CS11) | (1 << CS10);   

  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);   
  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


sei();//allow interrupts

}


