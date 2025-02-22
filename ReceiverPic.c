#include <16F877A.h>
#fuses HS, NOWDT, NOPUT, NOLVP, NOCPD, NOPROTECT
#use delay(clock=40000000)  // Set to your clock frequency
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)  // Configure UART

// LCD module connections
#define LCD_ENABLE_PIN PIN_D2
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>  // Include the LCD driver

// Function to initialize the LCD
void initialize_LCD() {
   lcd_init();            // Initialize LCD
   lcd_putc('\f');        // Clear the screen
   lcd_gotoxy(1, 1);      // Set cursor to first line
}

// Function to display a character on the LCD
void display_char(char c) {
   lcd_gotoxy(1, 1);      // Set cursor to first line
   lcd_putc("Switch Status:"); // Print label
   lcd_gotoxy(1, 2);      // Set cursor to second line
   lcd_putc(c);           // Display the received character
}

void main() {
   char received_char;

   set_tris_b(0xFF);  // Set PORTB as input (for UART communication)
   set_tris_d(0x00);  // Set PORTD as output for LCD

   initialize_LCD();  // Initialize the LCD

   while(TRUE) {
      if (kbhit()) { // Check if there is data in the RX buffer
         received_char = getc();  // Read received character
         
         lcd_gotoxy(1, 1);  // Set cursor to first line
         lcd_putc("Switch Status:"); // Print label
         lcd_gotoxy(1, 2);  // Set cursor to second line
         lcd_putc(received_char);  // Display received status
      }
      
      delay_ms(100); // Small delay to prevent overloading the CPU
   }
}

