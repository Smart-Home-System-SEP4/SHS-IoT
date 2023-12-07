#include "includes.h"
#include "periodic_task.h"
#include "pc_comm.h"
#include "display.h"
#include "leds.h"
#include "servo.h"


void func_a(){
//static uint16_t i = -10;
//display_int(i++);

pc_comm_send_string_blocking("!!!!!!!!!!!!!!!!!!!!!");
}

void func_b(){
    static uint8_t state = 0;
    if (state==0)
    {
        servo(50);
        state = 1;
    }
    else {
        servo(100);
        state = 0;
    }
    

}

void func_c(){

sei();
pc_comm_send_string_blocking("   _______________                        |*\\_/*|________\n"
"  |  ___________  |     .-.     .-.      ||_/-\\_|______  |\n"
"  | |           | |    .****. .****.     | |           | |\n"
"  | |   0   0   | |    .*****.*****.     | |   0   0   | |\n"
"  | |     -     | |     .*********.      | |     -     | |\n"
"  | |   \\___/   | |      .*******.       | |   \\___/   | |\n"
"  | |___     ___| |       .*****.        | |___________| |\n"
"  |_____|\\_/|_____|        .***.         |_______________|\n"
"    _|__|/ \\|_|_.............*.............._|________|_\n"
"   / ********** \\                          / ********** \\\n"
" /  ************  \\                      /  ************  \\\n"
"--------------------                    --------------------\n");

}

int main(void)
{

    //display_init();
    leds_init();
    pc_comm_init(9600, ((void *)0));
    
    
    periodic_task_init_a(func_a, 3300);
    //periodic_task_init_b(func_b, 5000);
     periodic_task_init_c(func_c, 1000);
while (1)
{
    
   
   
}

   


    return 0;
}
