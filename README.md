## ALOHA!
This project is a hardware abstraction (HAL) library for F4 series micro-controller peripherals written in C.  
The advantages of this libary are:
* Faster execution (2x)
* Smaller size (1/2)
* Interrupt and thread safe register manipulation
* Type safe consistent API interface
* It can co-exist with another HAL library

Tests on typical GPIO peripheral functions showed 50% shorter execution time and 50% smaller footprint.  
Bitband technology is used extensively to maximise performance and to minimise footprint.
These figures can easily be verified by executing instructions under the chapter TEST below.
This library is ideally to give existing bare-metal projects a performance boost.

### Bitband
This technique is excellently explained by: [Martin Hubacek](http://www.martinhubacek.cz/arm/advanced-arm-cortex-tips/bit-banding---fast-and-safe-bit-manipulation)

## USAGE
Two examples. The first one is a GPIO set output, the second is an interrupt handler.
### GPIO
```c++
    #include "per_gpio.h"
   
    // Definition of green LED
    static per_inline const per_gpio_out_t* const bsp_gpio_led_green(void)
    {
        static const per_gpio_out_t gpio =
        {
            .Per = PER_GPIOB,
            .Pin = PER_GPIO_PIN_0,
        };
        return &gpio;
    }
	

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

## TEST
1. Add the include libraries F4/inc and F439ZI/inc to an existing project.
1. Add the code below to a source file.
1. Compile it with -O3.
1. Note the size of the executable.
1. Replace per_gpio_set_out() with a comparable function from another HAL library.
1. Compile
1. Compare the size of the executable.  

```c++
    #include "per_gpio.h"
	
   
    // Single definition of green LED
    static per_inline const per_gpio_out_t* const bsp_gpio_led_green(void)
    {
        // Replace PER_GPIOB and PER_GPIO_PIN_0 with valid port and pin values or an output
        static const per_gpio_out_t gpio =
        {
            .Per = PER_GPIOB,
            .Pin = PER_GPIO_PIN_0,
        };
        return &gpio;
    }
	
	
	
    // Make a variable value here. Replace dots by some non const value.
    bool value = ...;

    // Enable the green LED
    per_gpio_set_out(bsp_gpio_led_green(), value);
```

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

## DEVELOPMENT STATUS (feb 2021)
Status of peripheral code
* 100% ADC, DMA, SPI, USART, GPIO, TIM_AD, TIM_GP, DES 
* 50%  PWR, RCC, SYS_CFG
* 10%  ETH

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
This function interface is future proof and it is consistent for all peripherals.
For example **per_usart_1(void)**. The functions limit the scope the desciptor structure.  

## inline
All the layers are provided in header files and inline functions. This allows the compiler to resolve all constants and optimise this all to a minimum size executable with fast execution times.
The use of inline functions makes the API consistent and type safe.  

## debug logging
Runtime debug logging is provided in bsp_dep.c. This file contains a call-back function that is called from the per_... files in case of a runtime fault.
A default log implementation captures this errors. It is up to the user to adapt and extend this file. 

## exceptions
There are a few hardware peripheral registers that are better or faster accessed by register instead of bitband.
The specific functions for this register handle this implicitly. An example of this is TIMx_SR.  

## COMPILATION
The library can coexist with other HAL libraries. Just add the directories to the project.
Note: the F439ZI is also good for other F4 types, it provides all possible peripherals.
Add the include libraries: F4/inc, F439ZI/inc, Nucleo/inc
If required, compile the files: per_bit.c, per_gpio.c, per_dep.c and bsp_dep.c  

## THE END
If you have any tips, remarks, questions and suggestions please send an email.  
Developing more efficient software can decrease energy consumption, decrease CO2 exhaust and help our planet :-)  
