/**
  *********************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   RT-Thread 3.0 + STM32 �̼�������
  *********************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� STM32F429��ս�� ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  **********************************************************************
  */ 
 
/*
*************************************************************************
*                             ������ͷ�ļ�
*************************************************************************
*/ 
#include "board.h"
#include "rtthread.h"


/*
*************************************************************************
*                               ����
*************************************************************************
*/
/* �����߳̿��ƿ� */
static rt_thread_t test_thread = RT_NULL;

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);

void LCD_Test(void);

/*
*************************************************************************
*                             main ����
*************************************************************************
*/
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
    /* 
	 * ������Ӳ����ʼ����RTTϵͳ��ʼ���Ѿ���main����֮ǰ��ɣ�
	 * ����component.c�ļ��е�rtthread_startup()����������ˡ�
	 * ������main�����У�ֻ��Ҫ�����̺߳������̼߳��ɡ�
	 */
	
	test_thread =                          /* �߳̿��ƿ�ָ�� */
    rt_thread_create( "test",              /* �߳����� */
                      test_thread_entry,   /* �߳���ں��� */
                      RT_NULL,             /* �߳���ں������� */
                      512,                 /* �߳�ջ��С */
                      3,                   /* �̵߳����ȼ� */
                      20);                 /* �߳�ʱ��Ƭ */
                   
    /* �����̣߳��������� */
   if (test_thread != RT_NULL)
        rt_thread_startup(test_thread);
    else
        return -1;
}

/*
*************************************************************************
*                             �̶߳���
*************************************************************************
*/

static void test_thread_entry(void* parameter)
{	
  while (1)
  {
    LED1_ON;
    rt_thread_delay(500);   /* ��ʱ500��tick */
    rt_kprintf("test_thread running,LED1_ON\r\n");
    
    LED1_OFF;     
    rt_thread_delay(500);   /* ��ʱ500��tick */		 		
    rt_kprintf("test_thread running,LED1_OFF\r\n");
  }
}


/*���ڲ��Ը���Һ���ĺ���*/
void LCD_Test(void)
{
	static uint8_t testCNT=0;
	char dispBuff[100];
	
	testCNT++;
	
	/*ʹ�ò�͸��ǰ����*/
	LCD_SetLayer(LCD_FOREGROUND_LAYER);  
  LCD_SetTransparency(0xff);
	
  LCD_Clear(LCD_COLOR_BLACK);	/* ��������ʾȫ�� */

	/*����������ɫ������ı�����ɫ(�˴��ı�������ָLCD�ı����㣡ע������)*/
  LCD_SetColors(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	
	/*ѡ�����壬ʹ����Ӣ����ʾʱ��������Ӣ��ѡ���16*24�����壬
	*���������С��24*24�ģ���Ҫ��������������������ģ*/
	/*�������ֻ��Ӣ������������*/
  LCD_SetFont(&Font16x24); 	

	LCD_DisplayStringLineEx(0,5,16,16,(uint8_t* )"����F429 16*16 ",0);
 	LCD_DisplayStringLine_EN_CH(LINE(1),(uint8_t* )"����F429 24*24 ");
	LCD_DisplayStringLineEx(0,50,32,32,(uint8_t* )"����F429 32*32 ",0);
	LCD_DisplayStringLineEx(0,82,48,48,(uint8_t* )"����F429 48*48 ",0);

	#if 1
	/*ʹ��c��׼��ѱ���ת�����ַ���*/
	sprintf(dispBuff,"��ʾ��������: testCount = %d ",testCNT);
	LCD_ClearLine(LINE(7));
	
	/*Ȼ����ʾ���ַ������ɣ���������Ҳ����������*/
	LCD_DisplayStringLine_EN_CH(LINE(7),(uint8_t* )dispBuff);


  /* ��ֱ�� */
  LCD_SetTextColor(LCD_COLOR_BLUE);
  
	LCD_ClearLine(LINE(8));
  LCD_DisplayStringLine_EN_CH(LINE(8),(uint8_t* )"����:");
  
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
  LCD_DrawUniLine(50,250,750,250);  
  LCD_DrawUniLine(50,300,750,300);
  
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  LCD_DrawUniLine(300,250,400,400);  
  LCD_DrawUniLine(600,250,600,400);
  
  rt_thread_delay(500);   /* ��ʱ500��tick */
  
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
  
  
  /*������*/
  LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
  LCD_DisplayStringLine_EN_CH(LINE(8),(uint8_t* )"������:");
	
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
  LCD_DrawRect(200,250,200,100);
	
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  LCD_DrawRect(350,250,200,50);
	
	LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_DrawRect(200,350,50,200);
  
  rt_thread_delay(500);   /* ��ʱ500��tick */
  
  
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
  

  /*������*/
  LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine_EN_CH(LINE(8),(uint8_t* )"������:");

 	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
  LCD_DrawFullRect(200,250,200,100);
	
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  LCD_DrawFullRect(350,250,200,50);
	
	LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
  LCD_DrawFullRect(200,350,50,200);
  
  rt_thread_delay(500);   /* ��ʱ500��tick */
  
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
	
  /* ��Բ */
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine_EN_CH(LINE(8),(uint8_t* )"��Բ:");
  
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_RED);
  LCD_DrawCircle(200,350,50);
	
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_GREEN);
  LCD_DrawCircle(350,350,75);
  
  rt_thread_delay(500);   /* ��ʱ500��tick */
  
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);


  /*���Բ*/
	LCD_SetTextColor(LCD_COLOR_BLUE);
	LCD_ClearLine(LINE(8));
	LCD_DisplayStringLine_EN_CH(LINE(8),(uint8_t* )"���Բ:");
  
	LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
  LCD_DrawFullCircle(300,350,50);
	
	LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  LCD_DrawFullCircle(450,350,75);
  
  rt_thread_delay(500);   /* ��ʱ500��tick */
  
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
	
	LCD_ClearLine(LINE(8));

//���ֲ���Ч�����л������󣬲��Ƽ�ʹ�á�һ�㱳�����ʹ��ARGB��ʽ����ɫ�����		
//	/*͸��Ч�� ǰ�������*/
//	{
//		LCD_SetTextColor(LCD_COLOR_BLUE);
//		LCD_ClearLine(LINE(8));
//		LCD_DisplayStringLine_EN_CH(LINE(8),(uint8_t* )"˫��͸��Ч����");
//		
//		/*����ǰ���㲻͸����*/
//		LCD_SetLayer(LCD_FOREGROUND_LAYER); 	
//		LCD_SetTransparency(200);
//		
//		/*��ǰ����һ����ɫԲ*/
//		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(400,350,75);
//	
//	}
//	
//	/*͸��Ч�� ���������*/
//	{		
//		/*���ñ����㲻͸��*/
//		LCD_SetLayer(LCD_BACKGROUND_LAYER); 	
//		LCD_SetTransparency(0xff);
//		LCD_Clear(LCD_COLOR_BLACK);

//		/*�ڱ�����һ����ɫԲ*/
//		LCD_SetColors(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(450,350,75);
//		
//		/*�ڱ�����һ����ɫԲ*/
//		LCD_SetColors(LCD_COLOR_BLUE,LCD_COLOR_BLACK);
//		LCD_DrawFullCircle(350,350,75);
//	}
  
  rt_thread_delay(500);   /* ��ʱ500��tick */
	
	LCD_SetColors(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
  LCD_DrawFullRect(0,200,LCD_PIXEL_WIDTH,LCD_PIXEL_HEIGHT-200);
	#endif

}
/********************************END OF FILE****************************/
