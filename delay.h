void timer2_init(void);
void delay_microsec(unsigned long);

void timer2_init()
{
	TIM2_CR1 = 0b00000100;
	TIM2_SR1 = 0x00;
	TIM2_PSCR = 0x04;
	TIM2_ARRH = 0xff;
	TIM2_ARRL = 0xff;
}
void delay_microsec(unsigned long time)
{
	int i;
	unsigned int temp1 = time / 65535;
	if(temp1)
	{
		unsigned int temp2 = 65536 - (time % 65535);
		for(i = 0; i<temp1; i++)
		{
			TIM2_CNTR = 0x00;
			TIM2_CR1 |= (1<<0);
			while(!(TIM2_SR1 & 0x01));
			TIM2_CR1 &= ~(1<<0);
			TIM2_SR1 = 0x00;
		}
		
		TIM2_CNTR = temp2;
		TIM2_CR1 |= (1<<0);
		while(!(TIM2_SR1 & 0x01));
		TIM2_SR1 |= (1<<0);
		TIM2_CR1 &= ~(1<<0);
	}
	else
	{
		TIM2_CNTR = 65536 - time;
		TIM2_CR1 |= (1<<0);
		while(!(TIM2_SR1 & 0x01));
		TIM2_SR1 |= (1<<0);
		TIM2_CR1 &= ~(1<<0);
	}
}