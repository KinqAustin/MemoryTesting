#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

class Vector2() 
{
  public:
    uint16_t X;
    uint16_t Y;

    Vector2() 
    {
      
    }
}

struct DataEntry 
{
  String File_ID;
  uint16_t Size;
  uint16_t Start_Address;

  uint16_t Data;

};

// Pins

uint16_t WE = 22;

uint16_t D0 = 23;
uint16_t D1 = 24;
uint16_t D2 = 25;
uint16_t D3 = 26;

uint16_t Ad0 = 27;
uint16_t Ad1 = 28;
uint16_t Ad2 = 29;
uint16_t Ad3 = 30;
uint16_t Ad4 = 31;
uint16_t Ad5 = 32;
uint16_t Ad6 = 33;
uint16_t Ad7 = 34;
uint16_t Ad8 = 35;
uint16_t Ad9 = 36;

// Configurations 

uint16_t MemorySize = 1024;
uint16_t Address = 27;

const uint16_t AddressSize = 32;
const uint16_t SlotSize = 4;

uint16_t BinaryAddress[AddressSize];
uint16_t RetrievedData[SlotSize];

uint16_t* decimalToBinary(uint16_t add, uint16_t Size) 
{
  uint16_t* binary = new uint16_t[Size];
  Serial.println("--Converting--");

  for (uint16_t i = 0; i < Size; i++)
  {
    binary[i] = add % 2;
    Serial.println(binary[i]);
    add = add / 2;
  }

  return binary;
}

void StoreMemory(uint16_t* binary) 
{
  WriteEnable(true);

  digitalWrite(D0, binary[0]);
  digitalWrite(D1, binary[1]);
  digitalWrite(D2, binary[2]);
  digitalWrite(D3, binary[3]);
}

void ReadMemory() 
{

}

void WriteEnable(bool Enable) 
{
  if (Enable == true) 
  {
    digitalWrite(WE, LOW);
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
  }
  else 
  {
    digitalWrite(WE, HIGH);
    pinMode(D0, INPUT);
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
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

  uint16_t* SavedData = decimalToBinary(5, SlotSize);
  Serial.println("Showing Result Values: ");
  for (int i = 0; i < SlotSize; i++) 
  {
    Serial.println(SavedData[i]);
  }

  StoreMemory(SavedData);

  Serial.println("Wrote to Memory");
  WriteEnable(false);
  
  delay(1000);
  
  Serial.println("Reading Memory: ");
  Serial.print(digitalRead(D0));
  Serial.print(digitalRead(D1));
  Serial.print(digitalRead(D2));
  Serial.print(digitalRead(D3));

  delete [] SavedData;
  
}

void loop() 
{}




/*
 -- SAVED CODE --

 WriteEnable(true);
  delay(500);

  digitalWrite(Ad0, LOW);
  digitalWrite(Ad2, LOW);
  digitalWrite(Ad4, HIGH);

  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
  digitalWrite(D3, 0);

  Serial.println("Wrote to Memory");
  delay(500);
  WriteEnable(false);
  delay(500);
  Serial.println("Reading Memory: ");
  Serial.print(digitalRead(D0));
  Serial.print(digitalRead(D1));
  Serial.print(digitalRead(D2));
  Serial.print(digitalRead(D3));
  */
