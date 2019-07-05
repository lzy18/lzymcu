/**
  ******************************************************************************
  * @file    Thread_NeckControl.c
  * @author  ������
  * @version V1.0
  * @date    2018.3.5
  * @brief   ����ļ�ʵ�ֻ�����������ת����������ĵ���
  ******************************************************************************
  * @attention
   �������裺
   1.����ʱ���ȿ��Ʋ������������ұ�ˢ�ۣ��ú���±�ˢ�ۣ��ٷ�����ɨ��֮��ʼִ����ɨ·��
   2.����ʱ���������
  *
  ******************************************************************************
  */

/* USER CODE BEGIN */
/* Includes ------------------------------------------------------------------*/
#include "soft.h"
#include "stdlib.h"
/* Define --------------------------------------------------------------------*/
#define     KP              0.6     //8     PIDϵ��
#define     KI              0.0002    //30
#define     KD              0.001    //150

/* Variables -----------------------------------------------------------------*/
RAP  l_vr, r_vr, fan1, fan2;     //���������

/* Private variables */


/* Function prototypes -------------------------------------------------------*/

/* Private function prototypes */


/* Hook prototypes */

/**
   * @brief PID����
   * @param rap: ����ָ����Ϣ
   * @param ring ����״̬��Ϣ
   * @retval None
   * @note  ���ټ�������ٴ�С������ٶȣ��������� �������ȶ��Ժ͵��ٷ�Χ������Ӱ�����аڶ�
   */
void PIDSpeedController(RAP * rap)
{
    float ec = 0;


    if((rap->rap == 0) && (rap->duty == 0))  // ��ֹ״̬
    {
        return;
    }


    if((rap->velocity == 0) && (fabs(rap->duty) > 2000))   //�����ӵ�Դ����û��ʱ�������
    {
        return;
    }

    rap->ek[2] = rap->ek[1];
    rap->ek[1] = rap->ek[0];


    rap->ek[0] = rap->rap - rap->velocity;    //����Ŀ���ٶȲ�


    ec = KP * rap->ek[0] + rap->integral * KI * rap->integral + KD * (rap->ek[0] - rap->ek[1]); //PIDλ���ͱ���ʽ


    if(rap->rap == 0)   //����������ͣʱ���ٱ�����С�����⣬������һ���ļ��ٶ�ֱ����ȫֹͣ
    {
        if(ec > 0)
        {
            ec = 400;
        }
        else if(ec < 0)
        {
            ec = -400;
        }
    }

    ec = ec + rap->duty;    //����PID


    if(ec > MAX_DUTY)    //����������
    {
        ec = MAX_DUTY;
    }
    else if(ec < -MAX_DUTY)
    {
        ec = -MAX_DUTY;
    }

    rap->duty = ec;     //���ٺ����


}

/**
   * @brief    ��ʼ�������ֵĽṹ����
   * @param    None
   * @param    None
   *
   * @retval   None
   */
void InitRap(RAP * rap)
{
    u8 i = 0;
    for(i = 0; i < sizeof(RAP); i++)
    {
        *((u8*)rap + i) = 0;
    }
}




/* USER CODE END */