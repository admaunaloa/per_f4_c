## ALOHA!
This project is a hardware abstraction (HAL) library for F4 micro-controller peripherals written in C.  
  
The advantages of this libary are:
* Faster execution
* Smaller size
* Interrupt and thread safe register manipulation
* Type safe consistent API interface
* It can co-exist with other HAL libraries

Typical GPIO peripheral functions have up to 50% shorter execution time combined with a up to 40% smaller footprint.  
Bitband technology is used extensively and implicit.  
This library gives existing bare-metal projects a performance boost, it unleashes the full power of the peripherals hardware.  

### Bitband
This technique is excellently explained by: [Martin Hubacek](http://www.martinhubacek.cz/arm/advanced-arm-cortex-tips/bit-banding---fast-and-safe-bit-manipulation)

## USAGE
Three examples. The first two GPIO get and set, the third is an interrupt handler.  

### GPIO GET
```c++
    #include "per_gpio.h"
   
    #define bsp_user_button_1() (per_gpio_c_in(PER_GPIO_PIN_13))

    // Get status of the button input
    bool button_state = per_gpio_in(bsp_user_button_1());
```

### GPIO SET
```c++
    #include "per_gpio.h"
   
    #define bsp_gpio_led_green() (per_gpio_b_out(PER_GPIO_PIN_0))

    // Enable the green LED
    per_gpio_set_out(bsp_gpio_led_green(), true);
```

### IRQ
```c++
    #include "per_tim_gp.h"

    void TIM3_IRQHandler(void)
    {
        // Read and clear the Timer _ GeneralPurpose _ Update Interrupt Flag	
        if (per_tim_gp_rdclr_uif(per_tim_gp_3()))
        {
            // user code to handle interrupt reason
            // ...
        }
    }
```

### TRY IT OUT
1. Copy the libraries F4, F439ZI and Bsp_example in an existing project, F439ZI supports most other types too,
1. Add the directories F4/inc F439ZI/inc and Bsp_example  to the include directories of the project/makefile.
1. Copy the lines of the GPIO get example above to an existing source file.
1. Modify PER_GPIOC and PER_GPIO_PIN_13 to a valid GPIO input.
1. Compile
1. Test  

## SYNTAX
For each peripheral bit the possible get and set functions are provided.
The syntax is
1. **per_**      Peripheral library prefix
1. **_usart_**   Peripheral type USART
1. **_ue**       Peripheral field name as in the manual. UE is Usart Enable.
1. **(...)**     Function  

Example:
```c++
    bool per_usart_ue(per_usart_t* )           // returns the value of the Usart Enable bit.
    void per_usart_set_ue(per_usart_t* , bool) // modifies the value of Usart Enable bit.
```

The per_usart_t pointers are provided in a function format
```c++
    per_usart_t* per_usart_1(void)
    per_usart_t* per_usart_2(void)
	...  
```

Enabling USART3 comes down to:
```c++
    per_usart_set_ue(per_usart_3(), true);  
```

This set UE example results in a minimal number of assembly instructions because
both functions are inlined and bitband is used. Both functions also make it
type-safe and they enable features such as zero-cost error checking.

## DEVELOPMENT STATUS (apr 2021)
Supported peripherals
* 100% ADC, DMA, SPI, USART, GPIO, I2C, TIM_AD, TIM_GP, DES, RCC, FLASH, PWR
* 50%  SYS_CFG
* 20%  ETH

Status generics
* 100% BITBAND, LOGGING

## STRUCTURE
The library consists the following layers:

### generic type definitions
In per_bit_f4.h generic field types are provided. The types are available per access rule and per bit size.
For example per_bit_rw1_t is a 1 bit size read and write peripheral field.

### generic functions for each generic type
In per_bit_f4.h generic functions are provided. Each function accesses one specific field type.
For example per_bit_rw1_set(..., ...) sets one specific bit.

### peripheral specific structure
Each peripheral has a specific structure defining all the internal fields with size, type and position. It is assembled from the generic types.
per_usart_f4.h shows an example of this.
```c++
    typedef struct
    {
        per_bit_rw1_t Ue; ///< USART enable
        per_bit_rw2_t Stop; ///< STOP bits
        per_bit_rw8_t Psc; ///< Pre-scaler value
    } per_usart_per_t;	
```

Each single line defines six properties of the specific peripheral field for the compiler.  
* The type **per_bit_rw1_t** provides both the bit size and the access rules.  
* The position in the containing struct provides the register address, the bit offset in the register and also the bitband address.  
* The name of the containing struct provides a small scope.  

Compare this with alternatives that require calculations with magic numbers and global scoped names.
These first three layers are very powerfull and they allow to define a complete new peripheral with minimal errors and in minimal time. 

### peripheral field specific functions
Each peripheral field has specific functions to access this field.  
If relevant an enum is provided to interpret the value of the field correctly.
per_usart_f4.h shows examples of this.
```c++
    /// USART enable get
    static per_inline bool per_usart_ue(const per_usart_t* const usart)
    {
        return per_bit_rw1(&usart->Per->Ue);
    }

    /// USART enable set
    static per_inline void per_usart_set_ue(const per_usart_t* const usart, bool val)
    {
        per_bit_rw1_set(&usart->Per->Ue, val);
    }
```

### peripheral variants
Peripherals have variations that are handled by include files in the F4xxx/inc directory.
Variants are for example the UART and USART. also the F407 has six UART/USARTS while the F439 has eight of these.
These variants are handled with a descriptor structure for each specific peripheral.  
This descriptor structure contains
* a pointer to the real peripheral structure
* enums that define the variant
* function pointers to get the base frequency
* error logging enums  

The prevention of functions accessing non-suporting peripheral variants is done with a zero-cost check.
If the variant is correct the compiler will optimise it out, if(0), if the variant is wrong, if(1) the linker will report this non existing function.
```c++
    if (usart->Uart)
    {
        per_log_err_function_not_supported();
    }
```
An example is F439/inc/per_usart.h.

### peripheral descriptor functions
Access to the peripheral descriptors is done via functions that return this descriptor.  
This function interface is consistent for all peripherals and it is future proof, for simple GPIO it is implemented as a define, for complex peripherals it is implemented as a function.
For example **per_usart_1()**.

## inline
All the layers are provided in header files and inline functions. This allows the compiler to resolve all constants and optimise this all to a minimum size executable with fast execution times.
The use of inline functions makes the API consistent and type safe.  

## debug logging
Runtime debug logging is provided in bsp_dep.c. This file contains a call-back function that is called from the per_... files in case of a runtime fault.
A default log implementation captures this errors. It is up to the user to adapt and extend this file. 

## dependencies
There are only a few external dependencies. All dependencies are accessed and wrapped via the per_dep.* and bsp_dep.* files.  
These files allow the user to adapt the library to other development enviroments.

## exceptions
There are a few hardware peripheral registers that are better accessed by register instead of bitband.
The specific functions for this register handle this implicitly. Examples of this are TIMx_SR and USARTx_DR

## compilation
The library can coexist with other HAL libraries. Just add the directories to the project.
Note: the F439ZI is also good for other F4 types, it provides all possible peripherals.
Add the include libraries: F4/inc, F439ZI/inc, Nucleo/inc
If required, compile the files: per_bit.c, per_gpio.c, per_dep.c and bsp_dep.c  

## THE END
If you have any tips, remarks, questions or suggestions please send an email.  
Developing more efficient software can decrease energy consumption, decrease carbon footprint and help our planet :-)  
