#include <stdio.h>

#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"

#pragma import(__use_no_semihosting_swi)

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

#if !(defined(__ICCARM__) && (__VER__ >= 6010000))
struct __FILE {
    uint16_t handle; /* Add whatever you need here */
};
#endif
FILE __stdout;
FILE __stdin;

enum { r0, r1, r2, r3, r12, lr, pc, psr};

void stackDump(uint32_t stack[])
{
	printf("r0  = 0x%x\n", stack[r0]);
	printf("r1  = 0x%x\n", stack[r1]);
	printf("r2  = 0x%x\n", stack[r2]);
	printf("r3  = 0x%x\n", stack[r3]);
	printf("r12 = 0x%x\n", stack[r12]);
	printf("lr  = 0x%x\n", stack[lr]);
	printf("pc  = 0x%x\n", stack[pc]);
	printf("psr = 0x%x\n", stack[psr]);
} 

void Hard_Fault_Handler(uint32_t stack[])
{     
	printf("In Hard Fault Handler\n");

	stackDump(stack);

	while(1);
}

/**
 * @brief    This HardFault handler is implemented to support semihost
 *
 * @param    None
 *
 * @returns  None
 *
 * @details  This function is implement to support semihost message print.
 *
 */
__asm int32_t HardFault_Handler(void)
{

    MOV     R0, LR
    LSLS    R0, #29               //; Check bit 2
    BMI     SP_is_PSP             //; previous stack is PSP
    MRS     R0, MSP               //; previous stack is MSP, read MSP
    B       SP_Read_Ready
SP_is_PSP
    MRS     R0, PSP               //; Read PSP

SP_Read_Ready
    LDR     R1, [R0, #24]         //; Get previous PC
    LDRH    R3, [R1]              //; Get instruction
    LDR     R2, =0xBEAB           //; The sepcial BKPT instruction
    CMP     R3, R2                //; Test if the instruction at previous PC is BKPT
    BNE     HardFault_Handler_Ret //; Not BKPT

    ADDS    R1, #4                //; Skip BKPT and next line
    STR     R1, [R0, #24]         //; Save previous PC

    BX      LR                    //; Return
HardFault_Handler_Ret

    /* TODO: Implement your own hard fault handler here. */
    MOVS    r0, #4 
    MOV     r1, LR 
    TST     r0, r1 
    BEQ     Stack_Use_MSP 
    MRS     R0, PSP ;stack use PSP 
    B       Get_LR_and_Branch 
Stack_Use_MSP 
    MRS     R0, MSP ; stack use MSP 
Get_LR_and_Branch 
    MOV     R1, LR ; LR current value 
    LDR     R2,=__cpp(Hard_Fault_Handler) 
    BX      R2                  
				 
    B       .

    ALIGN
}

/**
  * @brief  Write a char to debug console.
  * @param  ch The character sent to debug console
  * @return None
  */
void SendChar(int ch)
{
	ITM_SendChar(ch);
}

/**
  * @brief  Read a char from debug console.
  * @param  None
  * @return Received character from debug console
  * @note   This API waits until UART debug port or semihost input a character
  */
char GetChar(void)
{
	while (ITM_CheckChar() != 1) __NOP();  
	return (ITM_ReceiveChar()); 
}

volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;

/*---------------------------------------------------------------------------------------------------------*/
/* C library retargetting                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void _ttywrch(int ch)
{
    SendChar(ch);
}

int fputc(int ch, FILE *f)
{
    SendChar(ch);
    return ch;
}

int fgetc(FILE *f)
{
    return (GetChar());
}


int ferror(FILE *f)
{
    return EOF;
}

int __backscape()
{
	return 0;
}

void _sys_exit(int return_code)
{
label:
    goto label;  /* endless loop */
}

