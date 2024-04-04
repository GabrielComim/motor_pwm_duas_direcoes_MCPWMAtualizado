#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/pulse_cnt.h"
#include "bdc_motor.h"
//#include "pid_ctrl.h"

#define DEBUG

#define TIMER_RESOLUTION 10000000                                //  tick = 0,1us
#define FREQUENCIA       100000
#define GPIO_HORARIO      26
#define GPIO_ANTI_HORARIO 27
#define DUTY_CYCLE        1  
#define DUTY_TICK_MAX       (TIMER_RESOLUTION / FREQUENCIA) // Valor máx. pode ser utilizado para configurar o duty cycle, in ticks.

void app_main(void)
{    
    bdc_motor_config_t motor_config;
    motor_config.pwm_freq_hz = FREQUENCIA;
    motor_config.pwma_gpio_num = GPIO_HORARIO;              // Definido pino de saída do pwm
    motor_config.pwmb_gpio_num = GPIO_ANTI_HORARIO;         // Definido pino de saída do pwm sentido reverso

    bdc_motor_mcpwm_config_t mcpwm_config;
    mcpwm_config.resolution_hz = TIMER_RESOLUTION;
    mcpwm_config.group_id = 0;    

    bdc_motor_handle_t motor = NULL;

    bdc_motor_new_mcpwm_device(&motor_config, &mcpwm_config, &motor);

    bdc_motor_enable(motor);        // Habilita o pwm
    //bdc_motor_forward(motor);     // Sentido do motor
    bdc_motor_reverse(motor);       // Sentido reverso do motor

    bdc_motor_set_speed(motor, 100);    // Configura a velocidade do motor através do valor do duty ticks
    /*
    while(true)
    {
        // O valor de duty cycle deve ser máx. o valor de DUTY_TICK_MAX
        for(int i = DUTY_TICK_MAX; i > 0; i--)
        {
            bdc_motor_set_speed(motor, i);
            vTaskDelay(pdMS_TO_TICKS(500));    
        } 
        
        for(int i = 0; i < DUTY_TICK_MAX; i++)
        {
            bdc_motor_set_speed(motor, i);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
    */
    //esp_timer_start_periodic();
}
