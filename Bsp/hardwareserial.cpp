#include "hardwareserial.h"

USART_TypeDef*  SERIAL_USART[SERIALn] = {RIKI_SERIAL1, RIKI_SERIAL2, RIKI_SERIAL3};
GPIO_TypeDef*   SERIAL_PORT[SERIALn] = {RIKI_SERIAL1_GPIO_PORT, RIKI_SERIAL2_GPIO_PORT, RIKI_SERIAL3_GPIO_PORT}; 
const uint32_t  SERIAL_USART_CLK[SERIALn] = {RIKI_SERIAL1_CLK, RIKI_SERIAL2_CLK, RIKI_SERIAL3_CLK};
const uint32_t  SERIAL_PORT_CLK[SERIALn] = {RIKI_SERIAL1_GPIO_CLK, RIKI_SERIAL2_GPIO_CLK, RIKI_SERIAL3_GPIO_CLK};
const uint16_t  SERIAL_TX_PIN[SERIALn] = {RIKI_SERIAL1_TX_PIN, RIKI_SERIAL2_TX_PIN, RIKI_SERIAL3_TX_PIN}; 
const uint16_t  SERIAL_RX_PIN[SERIALn] = {RIKI_SERIAL1_RX_PIN, RIKI_SERIAL2_RX_PIN, RIKI_SERIAL2_RX_PIN}; 
const uint16_t  SERIAL_IRQn[SERIALn] = {RIKI_SERIAL1_IRQ, RIKI_SERIAL2_IRQ, RIKI_SERIAL3_IRQ};
const uint16_t  SERILA_NVIC[SERIALn] = {RIKI_SERIAL1_NVIC, RIKI_SERIAL2_NVIC, RIKI_SERIAL3_NVIC};

static uint8_t rxbuf[RXBUF_SIZE];        
static ring_buffer rb1_recv;  
static ring_buffer rb2_recv;  
static ring_buffer rb3_recv;  

void HardwareSerial::begin(uint32_t baud)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
    
	if(this->Serial == SERIAL1) {
		RCC_APB2PeriphClockCmd(SERIAL_USART_CLK[this->Serial]|SERIAL_PORT_CLK[this->Serial], ENABLE);	
	} else {
		RCC_APB1PeriphClockCmd(SERIAL_USART_CLK[this->Serial], ENABLE); 
		RCC_APB2PeriphClockCmd(SERIAL_PORT_CLK[this->Serial], ENABLE); 
	}
	//USART_TX   
	GPIO_InitStructure.GPIO_Pin = SERIAL_TX_PIN[this->Serial];        	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	 	 
	GPIO_Init(SERIAL_PORT[this->Serial], &GPIO_InitStructure);

	//USART_RX	 
	GPIO_InitStructure.GPIO_Pin = SERIAL_RX_PIN[this->Serial];           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(SERIAL_PORT[this->Serial], &GPIO_InitStructure);  

	USART_InitStructure.USART_BaudRate	 = baud;				
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits 	 = USART_StopBits_1;	
	USART_InitStructure.USART_Parity	 = USART_Parity_No;		
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	USART_Init(SERIAL_USART[this->Serial], &USART_InitStructure); 				

	NVIC_InitStructure.NVIC_IRQChannel = SERIAL_IRQn[this->Serial];       
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SERILA_NVIC[this->Serial];		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);						   
	//USART_ITConfig(SERIAL_USART[this->Serial], USART_IT_TXE, ENABLE);
	USART_ITConfig(SERIAL_USART[this->Serial], USART_IT_RXNE, ENABLE);

	USART_Cmd(SERIAL_USART[this->Serial], ENABLE);

	/** init ringbuf **/ 
	if(this->Serial == SERIAL1)
		rb_init(&rb1_recv, sizeof(rxbuf), rxbuf); 
	if(this->Serial == SERIAL2)
		rb_init(&rb2_recv, sizeof(rxbuf), rxbuf); 
	if(this->Serial == SERIAL3)
		rb_init(&rb3_recv, sizeof(rxbuf), rxbuf); 
}

uint32_t HardwareSerial::available(void)
{
	if(this->Serial == SERIAL1)
		return rb_full_count(&rb1_recv);
	if(this->Serial == SERIAL2)
		return rb_full_count(&rb2_recv);
	if(this->Serial == SERIAL3)
		return rb_full_count(&rb3_recv);

	return 0;

}

uint8_t HardwareSerial::read(void)
{
	while(!this->available())
		;
	if(this->Serial == SERIAL1)
		return rb_remove(&rb1_recv);
	if(this->Serial == SERIAL2)
		return rb_remove(&rb2_recv);
	if(this->Serial == SERIAL3)
		return rb_remove(&rb3_recv);

	return 0;
}

uint32_t HardwareSerial::write(uint8_t ch)
{
	USART_SendData(SERIAL_USART[this->Serial], ch);
	while(USART_GetFlagStatus(SERIAL_USART[this->Serial], USART_FLAG_TXE) == RESET); 
	
	return 1;
}

void HardwareSerial::flush()
{
	if(this->Serial == SERIAL1)
		rb_reset(&rb1_recv);
	if(this->Serial == SERIAL2)
		rb_reset(&rb2_recv);
	if(this->Serial == SERIAL3)
		rb_reset(&rb3_recv);
}

void HardwareSerial::print(const char *format, ...)
{
	va_list args;
	char buf[256];
	va_start (args, format);
	vsprintf (buf, format, args);       
	va_end (args);    
	putstr(buf);

}

void HardwareSerial::putstr(const char *str)
{
	int i;
	for(i = 0; i < strlen(str); i++){	
		write(str[i]);
	}
}

#ifdef __cplusplus
extern "C" {
#endif

void USART1_IRQHandler(void)
{
	unsigned char data;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		data = USART_ReceiveData(USART1);
		rb_push_insert(&rb1_recv, data);        
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
void USART2_IRQHandler(void)
{
	unsigned char data;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
		data = USART_ReceiveData(USART2);
		rb_push_insert(&rb2_recv, data);        
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

void USART3_IRQHandler(void)
{
	unsigned char data;
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
		data = USART_ReceiveData(USART3);
		rb_push_insert(&rb3_recv, data);        
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
}
#ifdef __cplusplus
}
#endif
