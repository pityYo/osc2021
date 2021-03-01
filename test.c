#include "uart.h"
#include "system.h"
#include <stdio.h>

int compare(const char *a, const char *b){
    if(!(*a | *b)) return 0;
    return (*a != *b)? *a - *b : compare(++a, ++b);

}
void start_message(){
    uart_puts("------------------------\r\n");
    uart_puts("= Welcome to Raspi3 B+ =\r\n");
    uart_puts("= Author: Yuan-Yu Wu   =\r\n");
    uart_puts("------------------------\r\n");
 
}
void show_commands(){
    uart_puts("[Command] | [Description]\r\n");
    uart_puts(" help     |  print all available commands\r\n");
    uart_puts(" hello    |  print Hello World\r\n");
    uart_puts(" reboot   |  reboot raspi3\r\n");
}
int main(void){
    uart_init();
    start_message();
    uart_puts("$ ");
    char str[1024], c; 
    int idx = 0;
    while(1){
        c = uart_get();
	str[idx++] = c;
	uart_send(c);
	if(c == '\n' || c == EOF){
	    str[idx - 1] = '\0';
	    if(compare(str, "hello") == 0)
	    	uart_puts("Hello World\n");
	    else if(compare(str, "help") == 0)
                show_commands();
	    else if(compare(str, "reboot") == 0){
		uart_puts("reboot ....\r\n");
                reset(0);
		//start_message();
	    }
	    idx = 0;
	    uart_puts("$ ");
	}

    }
    
    return 0;
}