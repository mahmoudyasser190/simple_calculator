/* 
 * File:   application.c
 * Author: Ahmed.Elghafar
 * https://www.linkedin.com/in/ahmedabdelghafarmohammed/
 * Created on November 28, 2020, 8:43 PM
 */

#include "application.h"

void calc_1(uint8 first_num[],uint8 second_num[],uint32 *number_1, uint32 *number_2,uint8 operation,uint32 *result);


uint8 keypad_value='\0';
uint8 number1;
uint8 column_1=0;
uint8 operation=0;
uint8 first_num[4];
uint8 second_num[4];
uint32 num_1=0;
uint32 num_2=0;
uint32 result=0;
uint8 str[5]={0};
Std_ReturnType ret = E_NOT_OK;
int main()
{ 
    

    application_intialize();
    ret=lcd_8bit_send_string(&lcd,"SIMPLE CALCULATOR:");
    
        
        
    
    while(1)
    {
         keypad_value='\0';
         column_1=0;
         operation=0;
         
        
        while(1)
        {
            do 
        {
            ret=keypad_get_value(&keypad_obj,&keypad_value);
            __delay_ms(200);
        }
        while('\0'==keypad_value);
        if('#'==keypad_value)
        {
            uint8 counter_1=0;
            ret=lcd_8bit_send_command(&lcd,_LCD_CLEAR);
            __delay_ms(200);
            ret=lcd_8bit_send_string(&lcd,"SIMPLE CALCULATOR:");
            column_1=0;
            for(counter_1=0;counter_1<4;counter_1++)
            {
                first_num[counter_1]='\0';
                second_num[counter_1]='\0';
            }
            
            continue;
            
        }
        if(('+'==keypad_value)||('-'==keypad_value)||('*'==keypad_value)||('/'==keypad_value))
        {
            operation=keypad_value;
           
            ret=lcd_8bit_send_char_data_pos(&lcd,2,column_1+1,keypad_value);
            column_1++;
            break;
        }
         
                
                first_num[column_1]=keypad_value;
                column_1++;
                ret=lcd_8bit_send_char_data_pos(&lcd,2,column_1,keypad_value);
                keypad_value='\0';

        }
        keypad_value='\0';
        uint8 counter_2=0;
        while(1)
        {
             do 
        {
            ret=keypad_get_value(&keypad_obj,&keypad_value);
            __delay_ms(200);
        }
        while('\0'==keypad_value);
        if('#'==keypad_value)
        {
            uint8 counter_3;
            ret=lcd_8bit_send_command(&lcd,_LCD_CLEAR);
            __delay_ms(100);
            ret=lcd_8bit_send_string(&lcd,"SIMPLE CALCULATOR:");
            column_1=0;
            for(counter_3=0;counter_3<4;counter_3++)
            {
                first_num[counter_3]='\0';
                second_num[counter_3]='\0';
            }
            break;
        }
        if('='== keypad_value)
        {
             
              calc_1(first_num, second_num, &num_1, &num_2, operation,&result);
            
            sprintf(str,"%d",result);
            ret=lcd_8bit_send_string_pos(&lcd,3,1,str);
            
        }
        second_num[counter_2]=keypad_value;
        counter_2++;
        column_1++;
        ret=lcd_8bit_send_char_data_pos(&lcd,2,column_1,keypad_value);
         keypad_value='\0';
        }
    }
    return (EXIT_SUCCESS);
}
void application_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}

void calc_1(uint8 first_num[],uint8 second_num[],uint32 *number_1, uint32 *number_2,uint8 operation,uint32 *result)
{
    
    uint8 counter=0;
    
    
    for(counter=0;counter<4;counter++)
    {
        first_num[counter]-='0';
        second_num[counter]-='0';
    }
   
    
    *number_1=first_num[0]*1000+first_num[1]*100+first_num[2]*10+first_num[3];
    *number_2=second_num[0]*1000+second_num[1]*100+second_num[2]*10+second_num[3];
    switch(operation)
    {
        case '+' :*result=*number_1 + *number_2;break;
        case '-' :*result=*number_1 - *number_2;break;
        case '*' :*result=*number_1 * *number_2;break;
        case '/' :*result=*number_1 / *number_2;break;
        default:break;
    }

}



