/*
Nintendo Switch Fightstick - Proof-of-Concept

Based on the LUFA library's Low-Level Joystick Demo
	(C) Dean Camera
Based on the HORI's Pokken Tournament Pro Pad design
	(C) HORI

This project implements a modified version of HORI's Pokken Tournament Pro Pad
USB descriptors to allow for the creation of custom controllers for the
Nintendo Switch. This also works to a limited degree on the PS3.

Since System Update v3.0.0, the Nintendo Switch recognizes the Pokken
Tournament Pro Pad as a Pro Controller. Physical design limitations prevent
the Pokken Controller from functioning at the same level as the Pro
Controller. However, by default most of the descriptors are there, with the
exception of Home and Capture. Descriptor modification allows us to unlock
these buttons for our use.
*/

/** \file
 *
 *  Main source file for the Joystick demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#include <LUFA/Drivers/Peripheral/Serial.h>
#include "Joystick.h"

uint8_t target = RELEASE;
uint16_t command;

void parseLine(char *line)
{
	char t[8];
	char c[16];
	sscanf(line, "%s %s", t, c);
	if (strcasecmp(t, "Button") == 0)
	{
		target = Button;
		printf("\r\nButton OK\r\n");
	}
	else if (strcasecmp(t, "LX") == 0)
	{
		target = LX;
		printf("\r\nLX OK\r\n");
	}
	else if (strcasecmp(t, "LY") == 0)
	{
		target = LY;
	}
	else if (strcasecmp(t, "RX") == 0)
	{
		target = RX;
	}
	else if (strcasecmp(t, "RY") == 0)
	{
		target = RY;
	}
	else if (strcasecmp(t, "HAT") == 0)
	{
		target = HAT;
	}
	else
	{
		target = RELEASE;
		printf("\r\nRELEASE OK\r\n");
	}

	if (strcasecmp(c, "Y") == 0)
	{
		command = SWITCH_Y;
	}
	else if (strcasecmp(c, "B") == 0)
	{
		command = SWITCH_B;
	}
	else if (strcasecmp(c, "A") == 0)
	{
		command = SWITCH_A;
	}
	else if (strcasecmp(c, "X") == 0)
	{
		command = SWITCH_X;
	}
	else if (strcasecmp(c, "L") == 0)
	{
		command = SWITCH_L;
	}
	else if (strcasecmp(c, "R") == 0)
	{
		command = SWITCH_R;
	}
	else if (strcasecmp(c, "ZL") == 0)
	{
		command = SWITCH_ZL;
	}
	else if (strcasecmp(c, "ZR") == 0)
	{
		command = SWITCH_ZR;
	}
	else if (strcasecmp(c, "SELECT") == 0)
	{
		command = SWITCH_SELECT;
	}
	else if (strcasecmp(c, "START") == 0)
	{
		command = SWITCH_START;
	}
	else if (strcasecmp(c, "LCLICK") == 0)
	{
		command = SWITCH_LCLICK;
	}
	else if (strcasecmp(c, "RCLICK") == 0)
	{
		command = SWITCH_RCLICK;
	}
	else if (strcasecmp(c, "HOME") == 0)
	{
		command = SWITCH_HOME;
	}
	else if (strcasecmp(c, "CAPTURE") == 0)
	{
		command = SWITCH_CAPTURE;
	}
	else if (strcasecmp(c, "RELEASE") == 0)
	{
		command = SWITCH_RELEASE;
	}
	else if (strcasecmp(c, "MIN") == 0)
	{
		command = STICK_MIN;
	}
	else if (strcasecmp(c, "MAX") == 0)
	{
		command = STICK_MAX;
	}
	else if (strcasecmp(c, "TOP") == 0)
	{
		command = HAT_TOP;
	}
	else if (strcasecmp(c, "TOP_RIGHT") == 0)
	{
		command = HAT_TOP_RIGHT;
	}
	else if (strcasecmp(c, "RIGHT") == 0)
	{
		command = HAT_RIGHT;
	}
	else if (strcasecmp(c, "BOTTOM_RIGHT") == 0)
	{
		command = HAT_BOTTOM_RIGHT;
	}
	else if (strcasecmp(c, "BOTTOM") == 0)
	{
		command = HAT_BOTTOM;
	}
	else if (strcasecmp(c, "BOTTOM_LEFT") == 0)
	{
		command = HAT_BOTTOM_LEFT;
	}
	else if (strcasecmp(c, "LEFT") == 0)
	{
		command = HAT_LEFT;
	}
	else if (strcasecmp(c, "TOP_LEFT") == 0)
	{
		command = HAT_TOP_LEFT;
	}
	else if (strcasecmp(c, "CENTER") == 0)
	{
		if (target == HAT)
		{
			command = HAT_CENTER;
		}
		else
		{
			command = STICK_CENTER;
		}
	}
	else
	{
		target = RELEASE;
	}
}

#define MAX_BUFFER 32
char b[MAX_BUFFER];
uint8_t l = 0;
//监听ttl RX的输入
ISR(USART1_RX_vect)
{
	char c = fgetc(stdin);
	if (Serial_IsSendReady())
	{
		printf("%c", c);
	}
	if (c == '\r')
	{
		//判断RX输入的是什么内容
		parseLine(b);
		l = 0;
		memset(b, 0, sizeof(b));
		// printf("\r\nOK\r\n");
	}
	else if (c != '\n' && l < MAX_BUFFER)
	{
		b[l++] = c;
		
	}
}

// Main entry point.
int main(void)
{
	//初始化com端口
	Serial_Init(9600, false);
	Serial_CreateStream(NULL);

	sei();
	//等待com信号
	while(Serial_IsCharReceived()==false)
	{

	}
	// char c = fgetc(stdin);
	// Serial_SendString("111");
	// Serial_SendString(c);
	// Serial_SendString("\r\n");
	Serial_SendString("Welcome switch joystick!\r\n");
	// printf("Welcome switch joystick!\r\n");

	UCSR1B |= (1 << RXCIE1);

	// We'll start by performing hardware and peripheral setup.
	//初始化硬件
	SetupHardware();
	// We'll then enable global interrupts for our use.
	//中断
	GlobalInterruptEnable();
	// Once that's done, we'll enter an infinite loop.
	//进入一个死循环
	for (;;)
	{
		// We need to run our task to process and deliver data for our IN and OUT endpoints.
		//处理硬件的输入输出
		HID_Task();
		// We also need to run the main USB management task.
		//usb任务管理
		USB_USBTask();
	}
}

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware(void)
{
	// We need to disable watchdog if enabled by bootloader/fuses.
	//禁用看门狗
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	// We need to disable clock division before initializing the USB hardware.
	//禁用时钟
	clock_prescale_set(clock_div_1);
	// We can then initialize our hardware and peripherals, including the USB stack.

	#ifdef ALERT_WHEN_DONE
	// Both PORTD and PORTB will be used for the optional LED flashing and buzzer.
	#warning LED and Buzzer functionality enabled. All pins on both PORTB and \
PORTD will toggle when printing is done.
	DDRD  = 0xFF; //Teensy uses PORTD
	PORTD =  0x0;
                  //We'll just flash all pins on both ports since the UNO R3
	DDRB  = 0xFF; //uses PORTB. Micro can use either or, but both give us 2 LEDs
	PORTB =  0x0; //The ATmega328P on the UNO will be resetting, so unplug it?
	#endif


	PORTD |= (1<< PD3);


	// The USB stack should be initialized last.
	//usb初始化
	USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void)
{
	// We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void)
{
	// We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	// We setup the HID report endpoints.
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_OUT_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE, 1);

	// We can read ConfigSuccess to indicate a success or failure at this point.
}

// Process control requests sent to the device from the USB host.
//usb发送控制请求
void EVENT_USB_Device_ControlRequest(void)
{
	// We can handle two control requests: a GetReport and a SetReport.
	switch (USB_ControlRequest.bRequest)
	{
	// GetReport is a request for data from the device.
	case HID_REQ_GetReport:
		if (USB_ControlRequest.bmRequestType == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE))
		{
			// We'll create an empty report.
			USB_JoystickReport_Input_t JoystickInputData;
			// We'll then populate this report with what we want to send to the host.
			GetNextReport(&JoystickInputData);
			// Since this is a control endpoint, we need to clear up the SETUP packet on this endpoint.
			Endpoint_ClearSETUP();
			// Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
			Endpoint_Write_Control_Stream_LE(&JoystickInputData, sizeof(JoystickInputData));
			// We then acknowledge an OUT packet on this endpoint.
			Endpoint_ClearOUT();
		}

		break;
	case HID_REQ_SetReport:
		if (USB_ControlRequest.bmRequestType == (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE))
		{
			// We'll create a place to store our data received from the host.
			USB_JoystickReport_Output_t JoystickOutputData;
			// Since this is a control endpoint, we need to clear up the SETUP packet on this endpoint.
			Endpoint_ClearSETUP();
			// With our report available, we read data from the control stream.
			Endpoint_Read_Control_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData));
			// We then send an IN packet on this endpoint.
			Endpoint_ClearIN();
		}

		break;
	}
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void)
{
	// If the device isn't connected and properly configured, we can't do anything here.
	//判断有usb有没有连接
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

	// We'll start with the OUT endpoint.
	//检查JOYSTICK 的输出端 [即switch向芯片发数据]
	Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
	// We'll check to see if we received something on the OUT endpoint.
	//确定是否收到数据
	if (Endpoint_IsOUTReceived())
	{
		// If we did, and the packet has data, we'll react to it.
		//判断一下是否能读取到数据
		if (Endpoint_IsReadWriteAllowed())
		{
			// We'll create a place to store our data received from the host.
			//新那家一个 JoystickOutputData 来用存放收到的数据对象
			USB_JoystickReport_Output_t JoystickOutputData;
			// We'll then take in that data, setting it up in our storage.
			//把数据写入到对象
			Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL);
			// At this point, we can react to this data.
			// However, since we're not doing anything with this data, we abandon it.
			//还可以对数据做其它操作
		}
		// Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
		//清除OUT数据
		Endpoint_ClearOUT();
	}

	// We'll then move on to the IN endpoint.
	//检查JOYSTICK 的输入端 [即芯片向switch发数据]
	Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
	// We first check to see if the host is ready to accept data.
	//确定是否有数据输入
	if (Endpoint_IsINReady())
	{
		// We'll create an empty report.
		USB_JoystickReport_Input_t JoystickInputData;
		// We'll then populate this report with what we want to send to the host.
		//获取要要输入的数据
		GetNextReport(&JoystickInputData);
		// Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
		Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL);
		// We then send an IN packet on this endpoint.
		//清除输入点
		Endpoint_ClearIN();

		/* Clear the report data afterwards */
		// memset(&JoystickInputData, 0, sizeof(JoystickInputData));
	}
}

// Prepare the next report for the host.
void GetNextReport(USB_JoystickReport_Input_t *const ReportData)
{
	/* Clear the report contents */
	memset(ReportData, 0, sizeof(USB_JoystickReport_Input_t));
	ReportData->LX = STICK_CENTER;
	ReportData->LY = STICK_CENTER;
	ReportData->RX = STICK_CENTER;
	ReportData->RY = STICK_CENTER;
	ReportData->HAT = HAT_CENTER;
	ReportData->Button |= SWITCH_RELEASE;

	switch (target)
	{
	case Button:
		ReportData->Button |= command;
		break;
	case LX:
		ReportData->LX = command;
		break;
	case LY:
		ReportData->LY = command;
		break;
	case RX:
		ReportData->RX = command;
		break;
	case RY:
		ReportData->RY = command;
		break;
	case HAT:
		ReportData->HAT = command;
		break;
	case RELEASE:
	default:
		ReportData->LX = STICK_CENTER;
		ReportData->LY = STICK_CENTER;
		ReportData->RX = STICK_CENTER;
		ReportData->RY = STICK_CENTER;
		ReportData->HAT = HAT_CENTER;
		ReportData->Button |= SWITCH_RELEASE;
		break;
	}
}
// vim: noexpandtab
