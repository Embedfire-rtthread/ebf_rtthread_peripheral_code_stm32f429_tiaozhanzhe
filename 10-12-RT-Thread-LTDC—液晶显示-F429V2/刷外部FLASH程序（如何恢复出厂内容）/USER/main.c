/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ���ڴ�SD�����������ļ���FLASH�Ĺ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
/**
  ******************************************************************************
  *                              ͷ�ļ�
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./Bsp/led/bsp_led.h" 
#include "./Bsp/usart/bsp_debug_usart.h"
#include "ff.h"
#include "./fatfs/drivers/fatfs_flash_spi.h"
#include "aux_data.h"



/**
  ******************************************************************************
  *                              �������
  ******************************************************************************
  */
extern FATFS sd_fs;													/* Work area (file system object) for logical drives */
extern FATFS flash_fs;

//Ҫ���Ƶ��ļ�·������aux_data.c�޸�
extern char src_dir[];
extern char dst_dir[];


/*
*********************************************************************************************************
* Description : ��ʼ��BL8782 wifiģ��ʹ�����ţ����ر�ʹ��
* Argument(s) : none.
* Return(s)   : none.
*********************************************************************************************************
*/
static void BL8782_PDN_INIT(void)
{
  /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOB, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOB,GPIO_Pin_13);  //����WiFiģ��
}
/*
*********************************************************************************************************
* Description : ��ʼ��KEY1
* Argument(s) : none.
* Return(s)   : none.
*********************************************************************************************************
*/
static void KEY1_INIT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	/*��������GPIO�ڵ�ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  /*ѡ�񰴼�������*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
  /*��������Ϊ����ģʽ*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; 
  /*�������Ų�����Ҳ������*/
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	/* ���������ٶ� */
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz;
  /*ʹ������Ľṹ���ʼ������*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/**
  * @brief  ������
  * @param  ��
  * @retval ��
	* @note    ��ȡSD��XBF�ֿ��ļ�(eg.xinsongti25.xbf)������д��SPI Flash���ļ�ϵͳ
	*          �����С�
  */
int main(void)
{
  FRESULT res = FR_OK;
  
	BL8782_PDN_INIT();
	/* ��ʼ��LED */
  LED_GPIO_Config();
  KEY1_INIT();

  /* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
  Debug_USART_Config();
  TM_FATFS_FLASH_SPI_disk_initialize();
  
  res = FR_DISK_ERR;
       
  //����SD��
  res = f_mount(&sd_fs,SD_ROOT,1);

  //����ļ�ϵͳ����ʧ�ܾ��˳�
  if(res != FR_OK)
  {
    BURN_ERROR("f_mount ERROR!������������SD��Ȼ�����¸�λ������!");
    LED_RED;
    while(1);
  }    
    
  printf("\r\n ��һ��KEY1��ʼ��д�ֿⲢ�����ļ���FLASH�� \r\n"); 
  printf("\r\n ע��ò������FLASH��ԭ���ݻᱻɾ������ \r\n"); 

  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0);
  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1); 

  printf("\r\n ���ڽ�����Ƭ������ʱ��ܳ��������ĵȺ�...\r\n");
  SPI_FLASH_BulkErase();   
  //��¼���ݵ�flash�ķ��ļ�ϵͳ����    
  res = burn_file_sd2flash(burn_data,AUX_MAX_NUM); 
  
  if(res == FR_OK)
  {
    printf("\r\n\r\n\r\n"); 

    //�����ļ���FLASH���ļ�ϵͳ����
    copy_file_sd2flash(src_dir,dst_dir);
    if(res == FR_OK)
    {
      printf("\r\n ���������ѳɹ����Ƶ�FLASH������ \r\n");  
      LED_GREEN;
    }
    else
    {
      printf("\r\n �����ļ���FLASHʧ��(�ļ�ϵͳ����)���븴λ���ԣ��� \r\n"); 
    }
  }
  else
  {
    printf("\r\n �������ݵ�FLASHʧ��(���ļ�ϵͳ����)���븴λ���ԣ��� \r\n"); 
  }
  
  


  
  while(1);


}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
