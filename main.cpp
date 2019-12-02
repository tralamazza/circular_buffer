#include <iostream>
#include <cstdint>
#include "circularBuffer.hpp"

using namespace std;

//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     readBufferComplete
// 
// Function: Read and print the complete circular buffer until it is empty. 
//           If buffer is empty nothing will be printed.
//
// Param:    void
// Return:   void
//
//**********************************************************************************
void readBufferComplete(void)
{
  uint8_t item; 
  cout<<endl<<"Reading circular complete buffer<uint8_t>[5]. "<<endl<<endl;    
  while (circularBuffer<uint8_t,5>::get(item))
  {
      cout<<"Reading "<<item<<endl;
  }
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     readBufferOneItem
// 
// Function: Read one item from buffer. If buffer is empty nothing will be printed.
//
// Param:    void
// Return:   void
//
//**********************************************************************************
void readBufferOneItem(void)
{
  uint8_t item; 
  cout<<endl<<"Reading circular one item from buffer<uint8_t>[5]. "<<endl<<endl;    
  if (circularBuffer<uint8_t,5>::get(item))
  {
      cout<<"Reading "<<item<<endl;
  }
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     putOverwriteTest
// 
// Function: Write numberOfItems from character A to buffer. Use override.
//
// Param:    int numberOfItems
// Return:   void
//
//**********************************************************************************
void putOverwriteTest(int numberOfItems)
{
  cout<<endl<<"Put overwrite " << numberOfItems << " values buffer<uint8_t>[5]."<<endl<<endl;;
  numberOfItems = numberOfItems + 65;     //start from character A
  
  for (uint8_t i=65; i<numberOfItems; i++) 
  {
    circularBuffer<uint8_t,5>::put_overwrite(i);
    cout<<"Putting "<<i<<endl;
  }

  
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     putDiscardTest
// 
// Function: Write numberOfItems from character A to buffer. Use discard.
//
// Param:    int numberOfItems
// Return:   void
//
//**********************************************************************************
void putDiscardTest(int numberOfItems)
{
  cout<<endl<<"Put discard " << numberOfItems << " values buffer<uint8_t>[5]."<<endl<<endl;;
  
  numberOfItems = numberOfItems + 65;     //start from character A
  
  for (uint8_t i=65; i<numberOfItems; i++) 
  {
    circularBuffer<uint8_t,5>::put_discard(i);
    cout<<"Putting "<<i<<endl;
  }
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     putDiscardTest
// 
// Function: Alternate putDiscardTest and putOverwriteTest.
//
// Param:    void
// Return:   void
//
//**********************************************************************************
void alternateTest(void)
{
  putOverwriteTest(1);
  putDiscardTest(1);
  putOverwriteTest(3);
  putDiscardTest(3);
  readBufferOneItem();
  putOverwriteTest(5);
  putDiscardTest(5);
  readBufferOneItem();
  putOverwriteTest(10);
  readBufferOneItem();
  putDiscardTest(10);
}
//**********************************************************************************
// Author:   Sascha Heinisch
// Date:     28.11.2019
// Name:     putDiscardTest
// 
// Function: Main function for circular buffer test.
//
// Param:    void
// Return:   int
//
//**********************************************************************************
int main(void)
{
      
  putOverwriteTest(10);
  readBufferComplete(); 
  putOverwriteTest(8);
  readBufferComplete();

  putDiscardTest(10);
  readBufferComplete();
  
  alternateTest();
  readBufferComplete();

  return 0;    
}