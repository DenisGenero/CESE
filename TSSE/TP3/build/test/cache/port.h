



void APISysInit();

void SystemClock_Config(void);

void MX_GPIO_Init(void);

void MX_DMA_Init(void);

void MX_TIM1_Init(void);

void MX_SPI1_Init(void);

void MX_USART3_UART_Init(void);



void uartInit();

uint8_t uartReceiveString();

void uartSendString(uint8_t *pstring);



_Bool 

    uartNewData();





_Bool 

    SPIRead(uint8_t reg, uint8_t *data, uint8_t length);



_Bool 

    SPIWrite(uint8_t reg, uint8_t command);
