/*FH*************************************************************************
* Name: spiInit
* Parameters: -
* Return value: -
* Description: init SPI as master for use with SSI
*****************************************************************************/
#include <avr/io.h>
#include <SPI.h>
/*FH*************************************************************************
* Name: readSSI_SPI
* Parameters: -
* Return value: value read from SSI
* Description: read a 25 Bit SSI word using the SPI interface
*****************************************************************************/
long unsigned int spiReadSSI( void )
{
byte u8byteCount;
byte u8data;
long unsigned int u32result = 0;
for (u8byteCount=0; u8byteCount<4; u8byteCount++)
{
// send a dummy byte, read the result
SPDR = 0xFF; // send 0xFF as dummy
u32result <<= 8; // left shift the result so far
//while ( (SPSR & (1 << SPIF)) == 0); // wait until transfer complete
u8data = SPDR; // read data from SPI register
u32result |= u8data; // and ‘or’ it with the result word
}
u32result >>= 7; // throw aways the LSBs
return u32result;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE1));
 Serial.println(spiReadSSI());
  SPI.endTransaction();
  delay(100);
 
}
