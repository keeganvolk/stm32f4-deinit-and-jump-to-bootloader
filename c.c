/* USER CODE BEGIN 4 */
void jumpToBootloader(void){
	void (*jump)(void);
	volatile uint32_t bootAddy=0x1FFF0000; //set boot address, if MCU is F7 set to 0x1FF00000
  /* disable all peripherals here, including CAN */



	// all peripheral settings must be set to their default states
	// to avoid interruptions when system is in boot mode

	HAL_RCC_DeInit(); //set clock to default state
	HAL_DeInit();
	SysTick->CTRL=0; //disable systick timer, set to default values
	SysTick->LOAD=0;
	SysTick->VAL=0;
	//__disable_irq(); //disable interrupts
	SYSCFG->MEMRMP = 0x01; //remap system memory, ***for F7 change MEMRMP to CFGR1***
	/*for (i=0;i<5;i++) //clear interrupt, enable register and interrupt pending register
		{
			NVIC->ICER[i]=0xFFFFFFFF;
			NVIC->ICPR[i]=0xFFFFFFFF;
		}*/
	//__enable_irq(); //re-enable interrupts
	jump = (void (*)(void)) (*((uint32_t *)(bootAddy + 4))); //set jump to bootloader address+4
	__set_MSP(*(uint32_t *)bootAddy); //set MSP to bootloader stack
	jump(); //call the function to do the jump
};
/* USER CODE END 4 */
