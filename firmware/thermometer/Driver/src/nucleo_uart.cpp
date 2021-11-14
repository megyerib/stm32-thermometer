#include "nucleo_uart.h"

#define CLASS_NAME NucleoUart

const size_t RX_BUF_SIZE = 0;
const uint32_t BAUDRATE = 115200;
const uint32_t DMA_NVIC_PRIO = 1;
const uint32_t UART_NVIC_PRIO = 1;


#define UART_IRQ_HANDLER    USART2_IRQHandler
#define DMA_TX_IRQ_HANDLER  DMA1_Stream6_IRQHandler
#define DMA_RX_IRQ_HANDLER  DMA1_Stream5_IRQHandler

static DMA_UART_CFG uart_cfg =
{
	// Tx
	.txEnabled     = true,

	// Rx
	.rxEnabled     = false,
	.rxBuf         = nullptr,
	.rxBufSize     = RX_BUF_SIZE,

	// GPIO
	.gpioTxClkEn   = [](){__HAL_RCC_GPIOA_CLK_ENABLE();},
	.gpioTxPort    = GPIOA,
	.gpioTxPin     = GPIO_PIN_2,

	.gpioRxClkEn   = [](){__HAL_RCC_GPIOA_CLK_ENABLE();},
	.gpioRxPort    = GPIOA,
	.gpioRxPin     = GPIO_PIN_3,

	.gpioAf        = GPIO_AF7_USART2,

	// DMA
	.dmaClkEn      = [](){__HAL_RCC_DMA1_CLK_ENABLE();},

	.dmaTxStream   = DMA1_Stream6,
	.dmaTxChannel  = DMA_CHANNEL_4,
	.dmaTxIrq      = DMA1_Stream6_IRQn,
	.dmaTxNvicPrio = DMA_NVIC_PRIO,

	.dmaRxStream   = DMA1_Stream5,
	.dmaRxChannel  = DMA_CHANNEL_4,
	.dmaRxIrq      = DMA1_Stream5_IRQn,
	.dmaRxNvicPrio = DMA_NVIC_PRIO,

	// UART
	.uartClkEn     = [](){__HAL_RCC_USART2_CLK_ENABLE();},
	.uartInstance  = USART2,
	.uartBaudRate  = BAUDRATE,
	.uartIrq       = USART2_IRQn,
	.uartNvicPrio  = UART_NVIC_PRIO,
};

// Don't touch ---------------------------------------------------------------------------------------------------------

CLASS_NAME& CLASS_NAME::GetInstance()
{
	static CLASS_NAME instance;
	return instance;
}

CLASS_NAME::CLASS_NAME() : DmaUartF4(uart_cfg)
{

}

// Interrupt handlers --------------------------------------------------------------------------------------------------

extern "C" void DMA_RX_IRQ_HANDLER(void)
{
	CLASS_NAME::GetInstance().HandleDmaRxIrq();
}

extern "C" void DMA_TX_IRQ_HANDLER(void)
{
	CLASS_NAME::GetInstance().HandleDmaTxIrq();
}

extern "C" void UART_IRQ_HANDLER(void)
{
	CLASS_NAME::GetInstance().HandleUartIrq();
}

// End -----------------------------------------------------------------------------------------------------------------
