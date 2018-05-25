/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */




/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */




/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */
/*******************************************************************************
 *
 * Function     : unsigned int uiUpdateCrc( unsigned char ser_data, unsigned int crc )
 * PreCondition : None
 * Input        : None
 * Output       : None
 * Side Effects : None
 * Overview     : CCIT 16 XMODEM CRC Calculator
 * Note         : None
 *
 ******************************************************************************/
unsigned short UpdateCrc( unsigned char ser_data, unsigned short crc )//CCIT 16 XMODEM
{
    crc = (unsigned short)(crc >> 8) | (crc << 8);
    crc ^= ser_data;
    crc ^= (unsigned short)(crc & 0xff) >> 4;
    crc ^= (crc << 8) << 4;
    crc ^= ((crc & 0xff) << 4) << 1;
    return crc;
}

void Add_Data_To_Buffer(volatile unsigned char* buffer, volatile unsigned char* bufferWriteIdentifier, unsigned char bufferSize, unsigned char data)
{
    buffer[*bufferWriteIdentifier] = data;
    ++*bufferWriteIdentifier;
    if(*bufferWriteIdentifier == bufferSize)
    {
        *bufferWriteIdentifier = 0;
    }
}


unsigned char Get_Data_From_Buffer(volatile unsigned char* buffer, volatile unsigned char* bufferReadIdentifier, unsigned char bufferSize)
{
    unsigned char value;

    value = buffer[*bufferReadIdentifier];
    ++*bufferReadIdentifier;
    if(*bufferReadIdentifier == bufferSize)
    {
        *bufferReadIdentifier = 0;
    }
    return value;
}


/* *****************************************************************************
 End of File
 */
