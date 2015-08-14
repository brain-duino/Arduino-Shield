#include <SPI.h>
#include <AD7173.h>





void setup() {
    /* initiate serial communication */
//    Serial.begin(115200);
          Serial.begin(230400);
 //         Serial.begin(460800);
    /* initiate ADC, return true if device ID is valid */
     AD7173.init();
    /* reset ADC registers to the default state */
     AD7173.reset();
    
  
	/* set ADC configuration */
	/* enable channel 0 and channel 1 and connect each to 2 analog inputs for bipolar input */
	/* CH0 - CH15 */
	/* AIN0 - AIN16, REF_POS, REF_NEG, TEMP_SENSOR_POS, TEMP_SENSOR_NEG */
// 	AD7173.enable_channel(CH0, true, AIN0, AIN1);
// 	AD7173.enable_channel(CH1, true, AIN2, AIN3);
//   	AD7173.enable_channel(CH0, true, AIN4, AIN5);
//  	AD7173.enable_channel(CH1, true, AIN6, AIN7);   
//  	AD7173.enable_channel(CH0, true, AIN8, AIN9);
// 	AD7173.enable_channel(CH1, true, AIN10, AIN11); 
   	AD7173.enable_channel(CH0, true, AIN12, AIN13);
  	AD7173.enable_channel(CH1, true, AIN14, AIN15); 
//   	AD7173.enable_channel(CH0, true, AIN12);
//  	AD7173.enable_channel(CH1, true, AIN14); 
 
    /* set the ADC filter samplingrate to 1007 Hz*/
    /* SPS_1, SPS_2, SPS_5, SPS_10, SPS_16, SPS_20, SPS_50, SPS_60, SPS_100, SPS_200 */
    /* SPS_381, SPS_504, SPS_1007, SPS_2597, SPS_5208, SPS_10417, SPS_15625, SPS_31250 */
     AD7173.set_filter_speed(FILTER0, SPS_1007);
     

  
    /* set the ADC setup coding to BIPLOAR output*/
    /* BIPOLAR_CODED_OUTPUT, UNIPOLAR_CODED_OUTPUT */
     AD7173.set_setup_coding(SETUP0, BIPOLAR);
//    AD7173.set_setup_coding(SETUP0, UNIPOLAR);
 
         /* set the ADC data mode */
    /* CONTINUOUS_READ_MODE, SINGLE_CONVERSION_MODE, CONTINUOUS_CONVERSION_MODE */
//               AD7173.set_data_mode(CONTINUOUS_READ_MODE);   
              AD7173.set_data_mode(CONTINUOUS_CONVERSION_MODE);     
  
   
    
    /* wait for ADC */
    delay(10);
     timerSet();
}


void timerSet() {
      
    
  cli();//stop interrupts
 

//set timer1 interrupt at 128Hz : OCR1A = 15624;// = (16*10^6) / (128*8) - 1 (must be <65536)
//set timer1 interrupt at 256Hz : OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
//set timer1 interrupt at 512Hz : OCR1A = 3905.25;// = (16*10^6) / (512*8) - 1 (must be <65536)
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments

//     OCR1A = 15624;// = (16*10^6) / (128*8) - 1 (must be <65536)
 //      OCR1A = 7811.5;// = (16*10^6) / (256*8) - 1 (must be <65536)
            OCR1A = 3905.25; // = (16*10^6) / (512*8) - 1 (must be <65536)
 //        OCR1A = 3966; // = (16*10^6) / (503*8) - 1 (must be <65536)


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




ISR(TIMER1_COMPA_vect){ // timer1 interrupt at 512 Hz
          sendData();
}
 



 
  long data;
  int data1, data2, data3, data4;
  int countD;
  int dataX;
 byte value0[3];
 byte value1[3];
 byte value2[3];  
 byte value3[3]; 
  
void  sendData() {
  /*
    dataX = (data1-511)*2;
    if ( dataX <0 ) dataX=0;
     if ( dataX > 0x3ff ) dataX=0x3ff;
       Serial.print(String(dataX, HEX));
        Serial.write(0x09);  

    dataX = (data2-511)*2;
    if ( dataX <0 ) dataX=0;
     if ( dataX > 0x3ff ) dataX=0x3ff;
        Serial.print(String(dataX, HEX));
        Serial.write(0x09);

       Serial.print(200);
       Serial.write(0x09);
         
        
        Serial.print(200);
        Serial.write(0x0D);
 
 
*/
 
 
 /*
Serial.print( value0[0], HEX );    Serial.print( value0[1], HEX );    Serial.print( value0[2], HEX );
        Serial.write(0x09);  

 Serial.print( value1[0], HEX );    Serial.print( value1[1], HEX );    Serial.print( value1[2], HEX );
 
        Serial.write(0x09);
        
          Serial.print( value2[0], HEX );   //   Serial.print( value2[1], HEX );    Serial.print( value2[2], HEX );
        Serial.write(0x09);
   
        
          Serial.print( value3[0], HEX );    // Serial.print( value3[1], HEX );    Serial.print( value3[2], HEX );
        Serial.write(0x0D);

*/  

 

  HEXprint(value0[0]);  HEXprint(value0[1]);  HEXprint(value0[2]);
  Serial.write(0x09);  
  
  HEXprint(value1[0]);  HEXprint(value1[1]);  HEXprint(value1[2]);
  Serial.write(0x09);   
  
 
  
  
  Serial.print( 0 );   //   Serial.print( value2[1], HEX );    Serial.print( value2[2], HEX );
        Serial.write(0x09);
   
        
          Serial.print( 0 );    // Serial.print( value3[1], HEX );    Serial.print( value3[2], HEX );
        Serial.write(0x0D);
 
 
  
  /*
  HEXprint(value0[0]);  HEXprint(value0[1]);  HEXprint(value0[2]);
  Serial.write(0x09);  
  
  HEXprint(value1[0]);  HEXprint(value1[1]);  HEXprint(value1[2]);
  Serial.write(0x09);   
  
  HEXprint(value2[0]);  // HEXprint(value2[1]);  HEXprint(value2[2]);
  Serial.write(0x09); 
  
    HEXprint(value3[0]);  // HEXprint(value3[1]);  HEXprint(value3[2]);
  Serial.write(0x0D); 
   */
}


void HEXprint(byte inVal)  {
  if ( inVal >= 16 ) {
    Serial.print( inVal, HEX );
  }
   else {
     Serial.print( 0 );
     Serial.print( inVal, HEX );
   }
   
}
 
  
  
void  getData() {
      byte value[3];
   long dataA;
 
   while (DATA_READY);     // wait for ready to go low
   while (!DATA_READY);  // wait for ready to go high
  
   //   if (DATA_READY) {
          AD7173.get_data(value);


   //      dataA = (value[0] << 2) | (value[1] & 0x03);
     //      dataA = ((unsigned long)value[2] << 16) | ((unsigned long)value[1] << 8) | value[0];
        countD = countD + 1;
 //     }
 

    if ( countD==1 ) {
      data1=dataA;
      value0[0]=value[0];
      value0[1]=value[1];
      value0[2]=value[2];
    }

     if ( countD==2 ) {
       data2=dataA;
      value1[0]=value[0];
      value1[1]=value[1];
      value1[2]=value[2];
     }
     
     if ( countD==3 ) {
       data2=dataA;
      value2[0]=value[0];
      value2[1]=value[1];
      value2[2]=value[2];
     }

     if ( countD==4 ) {
       data2=dataA;
      value3[0]=value[0];
      value3[1]=value[1];
      value3[2]=value[2];
     }
     
     if ( countD>=2) {
       countD=0;

     }


}


void loop() {
    getData();
 }
