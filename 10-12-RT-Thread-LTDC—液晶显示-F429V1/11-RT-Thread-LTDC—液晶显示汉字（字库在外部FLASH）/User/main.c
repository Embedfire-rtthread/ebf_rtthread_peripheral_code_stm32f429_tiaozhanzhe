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
void Printf_Charater(void);
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
	/*ʹ�ô�����ʾ���ʹ����ģ��������λ���鿴*/
	Printf_Charater();
  while (1)
  {
    LCD_Test();
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

 	LCD_DisplayStringLine_EN_CH(LINE(1),(uint8_t* )"����5.0Ӣ��Һ����������");
	LCD_DisplayStringLine_EN_CH(LINE(2),(uint8_t* )"�ֱ���:800x480 ����");
  LCD_DisplayStringLine_EN_CH(LINE(3),(uint8_t* )"������:5����ݴ�����");
  LCD_DisplayStringLine_EN_CH(LINE(4),(uint8_t* )"ʹ��STM32-LTDCֱ������,�����ⲿҺ��������");
	LCD_DisplayStringLine_EN_CH(LINE(5),(uint8_t* )"֧��RGB888/565,24λ��������");
  LCD_DisplayStringLine_EN_CH(LINE(6),(uint8_t* )"������ʹ��IIC��������");
	
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


}




/*"��"�ַ�����ģ*/ 	  
unsigned char charater_matrix[] =    
{ 
0x00,0x80,0x10,0x90,0x08,0x98,0x0C,0x90,0x08,0xA0,0x00,0x80,0x3F,0xFC,0x00,0x04,   
0x00,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x04,0x3F,0xFC,0x00,0x04,0x00,0x00  
};   
  
/**
  * @brief  ʹ�ô�������λ����ӡ��ģ
	*					��ʾ��ģ��ʾԭ��
  * @retval ��
  */
void Printf_Charater(void)   
{   
	int i,j;   
	unsigned char kk; 
  
	/*i�����м���*/
  for ( i=0;i<16;i++)   
	{   
		/*j����һ�ֽ������ݵ���λ����*/
		/*һ�����صĵ�һ���ֽ�*/
    for(j=0; j<8; j++)   
    {      
			/*һ������λһ������λ�ش���*/
      kk = charater_matrix[2*i] << j ;  //����Jλ          
			if( kk & 0x80)     
			{   
				printf("*"); //������λΪ1�����*�ţ���ʾ�ʼ�
			}   
			else  
			{   
				printf(" "); //������λΪ0������ո񣬱�ʾ�հ�  
			}   
    }   
		/*һ�����صĵڶ����ֽ�*/
    for(j=0; j<8; j++)   
		{              
      kk = charater_matrix[2*i+1] << j ;  //����Jλ   
       
			if( kk & 0x80)         
			{   
				printf("*"); //������λΪ1�����*�ţ���ʾ�ʼ�   
			}   
			else  
			{   
				printf(" "); //������λΪ0������ո񣬱�ʾ�հ� 
			}   
		}         
    printf("\n");    //�����һ�����أ����� 
	}   
	printf("\n\n"); 		//һ����������
}   


/********************************END OF FILE****************************/
