/*
 * Project AnalogTest pwn cycling for testing
 * Description:
 * Author:
 * Date:
 */

#include"Particle.h"
#include"Nextion.h"
#include"math.h"

SYSTEM_THREAD(ENABLED);

USARTSerial& nexSerial = Serial1;

#define DEBUG_SERIAL_ENABLE
#define dbSerial Serial
#define CLOUD_UPDATE_INTERVAL 60000
#define PWM_FREQ 500

int pmp = A5;
unsigned long lastcloudupdate = 0;
unsigned long lastchange=0;

char buffer[100] = {0};

NexNumber n1 = NexNumber(0, 4, "n1");
NexButton b0 = NexButton (0, 5, "b0");
NexDSButton bt0 = NexDSButton(0, 6, "bt0");

NexTouch *nex_listen_list[] = 
{ 
  &b0, 
  &bt0, 
  &n1, 
  NULL
};

//void b0PushCallback(void *ptr) {}

void b0PopCallback(void *ptr) 
{
  //dbSerial.println("b0PopCallback");

  uint32_t screenset = 0;
  int controlset = 0;
  
  n1.getValue(&screenset);
  
  //dbSerial.printlnf("Screen Set: %d", screenset);

  controlset=int(screenset*255/100);
  
  //dbSerial.printlnf("Control Set: %d", controlset);

  analogWrite(pmp, controlset, PWM_FREQ);
}

void bt0PushCallback(void *ptr) 
{
  //dbSerial.println("btoPushCallback");
  //dbSerial.println("AUTOMATIC");
}

void bt0PopCallback(void *ptr) 
{
  //dbSerial.println("btoPopCallback");
  //dbSerial.println("MANUAL");
}

void setup() 
{
  //dbSerial.begin(9600);
  //delay(100);

  nexSerial.begin(9600);
  delay(100);

  nexInit();
  delay(100);

  //b0.attachPush(b0PushCallback, &b0);
  b0.attachPop(b0PopCallback, &b0);
  bt0.attachPush(bt0PushCallback, &bt0);
  bt0.attachPop(bt0PopCallback, &bt0);

  //dbSerial.println("Touch Listen Set Up");

  pinMode(pmp, OUTPUT);

  //lastcloudupdate=millis();   
}

void loop() 
{
  nexLoop(nex_listen_list);

  //if( (millis() - lastcloudupdate) > CLOUD_UPDATE_INTERVAL)
  //{
    //lastchange = int(lastcloudupdate));
    //dbSerial.printlnf("No Change in: %d", lastchange);
    //lastcloudupdate=millis();
  //} 
}