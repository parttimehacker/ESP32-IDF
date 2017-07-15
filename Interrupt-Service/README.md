Simplified interface to the interrupt service logic. 

Method: initialize an interrupt handler service. 

xQueueHandle initialize_interrupt(
  uint32_t gpio_pin,
  gpio_mode_t int_mode,
  gpio_pullup_t pull_up,
  gpio_pulldown_t pull_down,
  gpio_int_type_t int_type );

I use a PIR sensor to generate a single interrupt for test purposes.
