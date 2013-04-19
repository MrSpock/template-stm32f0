template-stm32f0
================

STM32F0 bare metal template with heap support

I've spend days to make proper linker file that will work perfectly and gives ability to use stdio.h functions.
Lower workhorse of printf,sprintf etc is using heap to move data and most of templates  I found did't have this function.

Code is based on work Hussam Al-Hertani (http://hertaville.com) and his blog posts. Thank you.


New target in Makegile was added - "make load" for flashing STM32F0DISCOVERY board


