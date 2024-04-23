#define DEBUG 0

#define BAUD_RATE 9600

#define THRESHOLD_DISTANCE_1 80
#define THRESHOLD_DISTANCE_2 80
#define THRESHOLD_DISTANCE_3 80


#define TFMINI_1_RX 18
#define TFMINI_1_TX 19

#define TFMINI_2_RX 22
#define TFMINI_2_TX 23

#define TFMINI_3_RX 27
#define TFMINI_3_TX 26


#include <Arduino.h>
#include <SoftwareSerial.h>   //header file of software serial port


SoftwareSerial Serial_1(TFMINI_1_RX, TFMINI_1_TX); //define software serial port name as Serial_1 and define pin2 as RX & pin3 as TX
SoftwareSerial Serial_2(TFMINI_2_RX, TFMINI_2_TX); //define software serial port name as Serial_1 and define pin2 as RX & pin3 as TX
SoftwareSerial Serial_3(TFMINI_3_RX, TFMINI_3_TX); //define software serial port name as Serial_1 and define pin2 as RX & pin3 as TX


int dist_1, dist_2, dist_3;                     //actual distance measurements of LiDAR
int strength_1, strength_2, strength_3;         //signal strength of LiDAR
int check_1, check_2, check_3;                  //save check value
int i_1, i_2, i_3;
int uart_1[9], uart_2[9], uart_3[9];            //save data measured by LiDAR
const int HEADER_1 = 0x59, HEADER_2 = 0x59, HEADER_3 = 0x59;      //frame header of data package
 
void checkDistance_1(){
  if (Serial_1.available())                //check if serial port has data input
  {
    if (Serial_1.read() == HEADER_1)        //assess data package frame header 0x59
    {
      uart_1[0] = HEADER_1;
      if (Serial_1.read() == HEADER_1)      //assess data package frame header 0x59
      {
        uart_1[1] = HEADER_1;
        for (i_1 = 2; i_1 < 9; i_1++)         //save data in array
        {
          uart_1[i_1] = Serial_1.read();
        }
        check_1 = uart_1[0] + uart_1[1] + uart_1[2] + uart_1[3] + uart_1[4] + uart_1[5] + uart_1[6] + uart_1[7];
        if (uart_1[8] == (check_1 & 0xff))        //verify the received data as per protocol
        {
          dist_1 = uart_1[2] + uart_1[3] * 256;     //calculate distance value
          strength_1 = uart_1[4] + uart_1[5] * 256; //calculate signal strength value
          
          
        }
      }
    }
  }
}

void checkDistance_2(){
  if (Serial_2.available())                //check if serial port has data input
  {
    if (Serial_2.read() == HEADER_2)        //assess data package frame header 0x59
    {
      uart_2[0] = HEADER_2;
      if (Serial_2.read() == HEADER_2)      //assess data package frame header 0x59
      {
        uart_2[1] = HEADER_2;
        for (i_2 = 2; i_2 < 9; i_2++)         //save data in array
        {
          uart_2[i_2] = Serial_2.read();
        }
        check_2 = uart_2[0] + uart_2[1] + uart_2[2] + uart_2[3] + uart_2[4] + uart_2[5] + uart_2[6] + uart_2[7];
        if (uart_2[8] == (check_2 & 0xff))        //verify the received data as per protocol
        {
          dist_2 = uart_2[2] + uart_2[3] * 256;     //calculate distance value
          strength_2 = uart_2[4] + uart_2[5] * 256; //calculate signal strength value
          
          
        }
      }
    }
  }
}

void checkDistance_3(){
  if (Serial_3.available())                //check if serial port has data input
  {
    if (Serial_3.read() == HEADER_3)        //assess data package frame header 0x59
    {
      uart_3[0] = HEADER_3;
      if (Serial_3.read() == HEADER_3)      //assess data package frame header 0x59
      {
        uart_3[1] = HEADER_3;
        for (i_3 = 2; i_3 < 9; i_3++)         //save data in array
        {
          uart_3[i_3] = Serial_3.read();
        }
        check_3 = uart_3[0] + uart_3[1] + uart_3[2] + uart_3[3] + uart_3[4] + uart_3[5] + uart_3[6] + uart_3[7];
        if (uart_3[8] == (check_3 & 0xff))        //verify the received data as per protocol
        {
          dist_3 = uart_3[2] + uart_3[3] * 256;     //calculate distance value
          strength_3 = uart_3[4] + uart_3[5] * 256; //calculate signal strength value

        }
      }
    }
  }
}

void processDistance(){
  static bool flag_1 = false;
  static bool flag_2 = false;
  static bool flag_3 = false;

  if (dist_1 > 0 && dist_1 < THRESHOLD_DISTANCE_1 ){
    if (!flag_1){flag_1 = true; Serial.println("L");}    
  } else { flag_1 = false;}

  if (dist_2 > 0 && dist_2 < THRESHOLD_DISTANCE_2 ){
    if (!flag_2){flag_2 = true; Serial.println("C");}    
  } else { flag_2 = false;}

  if (dist_3 > 0 && dist_3 < THRESHOLD_DISTANCE_3 ){
    if (!flag_3){flag_3 = true; Serial.println("R");}    
  } else { flag_3 = false;}

  if (DEBUG){Serial.println("L: " + String(flag_1) + "\t C: " + String(flag_2) + "\t R: " + String(flag_3));}
}

void debugData(){
  if (DEBUG){Serial.println("Dist 1: " + String(dist_1) + "\t Dist 2: " + String(dist_2) + "\t Dist 3: " + String(dist_3));}
  
}

void setup()
{
  Serial.begin(BAUD_RATE);         //set bit rate of serial port connecting Arduino with computer

  Serial_1.begin(115200);      //set bit rate of serial port connecting LiDAR with Arduino
  Serial_2.begin(115200);      //set bit rate of serial port connecting LiDAR with Arduino
  Serial_3.begin(115200);      //set bit rate of serial port connecting LiDAR with Arduino
}
 
 
void loop() {
  checkDistance_1();
  checkDistance_2();
  checkDistance_3();

  processDistance();
  // debugData();
}