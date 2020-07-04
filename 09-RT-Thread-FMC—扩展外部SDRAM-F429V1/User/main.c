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

/*���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���*/
uint8_t testValue __attribute__((at(SDRAM_BANK_ADDR)));

/*
*************************************************************************
*                             ��������
*************************************************************************
*/
static void test_thread_entry(void* parameter);


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
  
  /*����������ʾ���ڶ�дSDRAM����*/
  LED_BLUE;
  
  /*��SDRAM���ж�д���ԣ����SDRAM�Ƿ�����*/
  if(SDRAM_Test()==1)
  {
		//�������� �̵���
    LED_GREEN;			  
  }
	else
	{
		//����ʧ�� �����
		LED_RED;
	}
	
	/*ָ�뷽ʽ����SDRAM*/
	{	
	 uint32_t temp;
	
	 printf("\r\nָ�뷽ʽ����SDRAM\r\n");
	/*��SDRAMд��8λ����*/
	 *( uint8_t*) (SDRAM_BANK_ADDR ) = (uint8_t)0xAA;
	 printf("\r\nָ�����SDRAM��д������0xAA \r\n");

	 /*��SDRAM��ȡ����*/
	 temp =  *( uint8_t*) (SDRAM_BANK_ADDR );
	 printf("��ȡ���ݣ�0x%X \r\n",temp);

	 /*д/�� 16λ����*/
	 *( uint16_t*) (SDRAM_BANK_ADDR+10 ) = (uint16_t)0xBBBB;
	 printf("ָ�����SDRAM��д������0xBBBB \r\n");
	 
	 temp =  *( uint16_t*) (SDRAM_BANK_ADDR+10 );
	 printf("��ȡ���ݣ�0x%X \r\n",temp);


	 /*д/�� 32λ����*/
	 *( uint32_t*) (SDRAM_BANK_ADDR+20 ) = (uint32_t)0xCCCCCCCC;
	 printf("ָ�����SDRAM��д������0xCCCCCCCC \r\n");	 
	 temp =  *( uint32_t*) (SDRAM_BANK_ADDR+20 );
	 printf("��ȡ���ݣ�0x%X \r\n",temp);

	}
	
	/*���Զ�λ��ʽ����SDRAM,���ַ�ʽ���붨���ȫ�ֱ���*/
	{
		testValue = 0xDD;
		printf("\r\n���Զ�λ����SDRAM��д������0xDD,��������0x%X,������ַΪ%X\r\n",testValue,(uint32_t )&testValue);	 
	}
	
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

/********************************END OF FILE****************************/
