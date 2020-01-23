#include "mgos.h"
#include "mgos_timers.h"
#include "mgos_hcsr04.h"

static void my_timer_cb(void *arg) {
  struct mgos_hcsr04 *sensor = (struct mgos_hcsr04 *)arg;
  float distance = mgos_hcsr04_get_distance(sensor);
  if (distance != NAN)
    LOG(LL_INFO, ("Distance: %.2lf", distance));
  else
    LOG(LL_ERROR, ("Distance: error reading distance"));
}

enum mgos_app_init_result mgos_app_init(void) {
  /* Create HC-SR04 sensor instance */
  struct mgos_hcsr04 *hcsr04 = mgos_hcsr04_create(
    mgos_sys_config_app_hcsr04_trigger_pin_get(),
    mgos_sys_config_app_hcsr04_echo_pin_get());
  if (hcsr04 == NULL) return MGOS_APP_INIT_ERROR;  
  
  /* Set timer for reading distance */
  mgos_set_timer(mgos_sys_config_app_measure_interval_get(),
    MGOS_TIMER_REPEAT, my_timer_cb, hcsr04);

  return MGOS_APP_INIT_SUCCESS;
}
