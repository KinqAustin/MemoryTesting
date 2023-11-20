#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct DataEntry 
{
  String File_ID;
  int Size;
  int Start_Address;

  int Data;

};

// Pins

int WE = 22;

int D0 = 23;
int D1 = 24;
int D2 = 25;
int D3 = 26;

int Ad0 = 27;
int Ad1 = 28;
int Ad2 = 29;
int Ad3 = 30;
int Ad4 = 31;
int Ad5 = 32;
int Ad6 = 33;
int Ad7 = 34;
int Ad8 = 35;
int Ad9 = 36;

// Configurations 

int MemorySize = 1024;
int Address = 27;
int BinaryAddress[10];

int* decimalToBinary(int add) 
{
  static int newAddress[10];

  for (int i = 9; i >= 0; i--)
  {
    int v = (add >> i) & 1;
    newAddress[9 - i] = v;
  }

  return newAddress;

}

int* retrieveData(DataEntry& dataEntry)  
{

  int loc = dataEntry.Start_Address;
  int size = dataEntry.Size;

  int retrievedData[size];

  setLocation(loc);
  SetMode(true);

  retrievedData[0] = digitalRead(D0);
  retrievedData[1] = digitalRead(D1);
  retrievedData[2] = digitalRead(D2);
  retrievedData[3] = digitalRead(D3);

  Serial.print("Reading Pin and Size: ");
  Serial.println(sizeof(retrievedData) / sizeof(int));
  Serial.println(digitalRead(D0));
  Serial.println(digitalRead(D1));
  Serial.println(digitalRead(D2));
  Serial.println(digitalRead(D3));

  return retrievedData;

}

void setLocation(int location) 
{
  int* Data_Address = decimalToBinary(location);

  digitalWrite(Ad0, Data_Address[0]);
  digitalWrite(Ad1, Data_Address[1]);
  digitalWrite(Ad2, Data_Address[2]);
  digitalWrite(Ad3, Data_Address[3]);
  digitalWrite(Ad4, Data_Address[4]);
  digitalWrite(Ad5, Data_Address[5]);
  digitalWrite(Ad6, Data_Address[6]);
  digitalWrite(Ad7, Data_Address[7]);
  digitalWrite(Ad8, Data_Address[8]);
  digitalWrite(Ad9, Data_Address[9]);

}

void storeData(int location, DataEntry& dataEntry) 
{
  dataEntry.Start_Address = location;
  int* Data = decimalToBinary(dataEntry.Data);

  setLocation(location);

  if (ceil(sizeof(Data) / sizeof(int)) > 4) 
  {
  }
  else 
  {
    digitalWrite(D0, Data[0]);
    digitalWrite(D1, Data[1]);
    digitalWrite(D2, Data[2]);
    digitalWrite(D3, Data[3]);
  }
}

void SetMode(bool Read) 
{
  if (Read == true) 
  {
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);

    digitalWrite(WE, HIGH);
  }
  else 
  {
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);

    digitalWrite(WE, LOW);
  }
}

void setup() 
{
  Serial.begin(9600);

  pinMode(WE, OUTPUT);

  pinMode(Ad0, OUTPUT);
  pinMode(Ad1, OUTPUT);
  pinMode(Ad2, OUTPUT);
  pinMode(Ad3, OUTPUT);
  pinMode(Ad4, OUTPUT);
  pinMode(Ad5, OUTPUT);
  pinMode(Ad6, OUTPUT);
  pinMode(Ad7, OUTPUT);
  pinMode(Ad8, OUTPUT);
  pinMode(Ad9, OUTPUT);

  SetMode(false);

  DataEntry newData;
  newData.Data = 10;
  newData.Size = 4;
  newData.Start_Address = 1;

  storeData(1, newData);
  Serial.println("Stored Data");

  delay(1000);

  int* retrievedData = retrieveData(newData);
  Serial.println("Retrieved Data: ");
  for (int i = 0; i < 4; i++) 
  {
    Serial.println(retrievedData[i]);
  }

}

void loop() 
{

}

