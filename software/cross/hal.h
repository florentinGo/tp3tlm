/********************************************************************
 * Copyright (C) 2009, 2012 by Verimag                              *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

/*!
  \file hal.h
  \brief Harwdare Abstraction Layer : implementation for MicroBlaze
  ISS.


*/
#ifndef HAL_H
#define HAL_H

#include <stdint.h>


/* Dummy implementation of abort(): dereference a NULL pointer */
#define abort() ((*(int *)NULL) = 0)

/* TODO : implementer ces primitives pour la compilation croisée */
//#define read_mem(a)     abort()
//#define write_mem(a,d)  abort()
#define wait_for_irq()  abort()
#define cpu_relax()     abort()

#define microblaze_enable_interrupts() /* Not needed, we always
					* activate interrupts */

uint32_t read_mem(uint32_t addr){
	volatile uint32_t *ptr = addr;
	return *ptr;
}

void write_mem(uint32_t addr, uint32_t data){
	volatile uint32_t *ptr = addr;
	*ptr = data;
}
/* printf is disabled, for now ... */
#define printf our_print

void our_print(char* str){
	int i;
	for(i = 0; str[i] != '\0' ; i++){
		write_mem(UART_BASEADDR + 0x04, str[i]);
	}
}

#endif /* HAL_H */
