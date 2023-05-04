
#include "gd32vf103.h"
#include "usb_serial_if.h"
#include "usb_delay.h"

#include <stdlib.h>
#include <string.h>

#define USE_USB
#define USE_USB_PRINTF


int main(void)
{
    uint32_t count = 0;
    uint8_t usb_data_buffer[512] = {0};
    /* GD32VF103 contains dedicated hardware for USB. To make sending data to and from a computer
       the libraries in these examples includes a virtual com port driver. This lets the usb connection
       on the devboard appear as a serial device which makes communication with a PC fairly simple.
       
       This example will listen for input from a serial terminal and when it you press enter it will print
       back all it received in the same terminal.
       
       To test, connect the MCU-card to your computer and open a serial terminal (in platformIO press the icon in the bottom of the window)
       and start typing, then press enter. */
    configure_usb_serial();
    /* This sets up so that the MCU will show up as a virtual com port when connected over usb to a computer */
    
    /* If the controller has sucessfully been connected usb_serial_available() will return 1 */
	while(!usb_serial_available())usb_delay_1ms(100);
    
	usb_delay_1ms(1000);
    while(1){
        //Read new messages into buffer
		count = read_usb_serial(usb_data_buffer);
        if(count){
            //If message was received, echo back to sender
            printf("%s", usb_data_buffer);
            //Make sure that message is actually sent and not cached
            fflush(0);
        }
        usb_delay_1ms(10);
    }
}