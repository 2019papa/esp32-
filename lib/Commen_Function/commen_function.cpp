#include <Arduino.h>
#include "My_Advance_Motot.h"
#include "commen_function.h"
#include "my_key.h"
#include "my_led.h"

#include "Trigger.h"
#include "my_timer.h"

#include <stdio.h>
#include <stdlib.h>
#include "double_direct_chain.h"
#include "dynamic_chain.h"


void array_slice(int *source_arr,int *storage_arr,int start,int end) 
{
    int len=end-start+1;

    for (int i = start; i < len; i++) {
        storage_arr[i]=source_arr[i];
    }

}

