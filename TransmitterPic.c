#include <16F877A.h>
#fuses HS, NOWDT, NOPUT, NOLVP, NOCPD, NOPROTECT
#use delay(clock=40000000)  // Set to your clock frequency
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)  // Configure UART

void main() {
   char switch_status;

   set_tris_b(0x01);  // Set RB0 as input (switch), others as output
   set_tris_c(0xBF);  // Set RC6 as output (UART TX), RC7 as input (UART RX)

   while(TRUE) {
      switch_status = input_b();  // Read PORTB status
      if (switch_status & 0x01) { // Check if RB0 bit is high (switch ON)
         putc('O');  // Send 'O' for ON
      } else {
         putc('F');  // Send 'F' for OFF
      }
      
      delay_ms(500); // Update status every 500 ms
   }
}

