#include "mgos.h"
#include "mgos_timers.h"
#include "mgos_sys_config.h"
#include "mgos_hcsr04.h"


static void my_timer_cb(void *arg) {
  struct mgos_hcsr04 *sensor = (struct mgos_hcsr04 *)arg;
  
  float dist = mgos_hcsr04_get_distance(sensor);
  mgos_msleep(5);
  float dist_avg = mgos_hcsr04_get_distance_avg(sensor,
    mgos_sys_config_get_app_hcsr04_avg_attempts(), -1);

  if (!isnan(dist) && !isnan(dist_avg)) {
    LOG(LL_INFO, ("Distance (mm): %.2lf (avg. %.2lf | discrepancy %.2lf)",
      dist, dist_avg, (dist - dist_avg)));
  } else if (!isnan(dist)) {
    LOG(LL_INFO, ("Distance (mm): %.2lf", dist));
  } else if (!isnan(dist_avg)) {
    LOG(LL_INFO, ("Distance (mm): avg. %.2lf", dist_avg));
  } else {
    LOG(LL_INFO, ("Distance (mm): error reading distance"));
  }
}

enum mgos_app_init_result mgos_app_init(void) {
  /* Create HC-SR04 sensor instance */
  struct mgos_hcsr04 *hcsr04 = mgos_hcsr04_create(
    mgos_sys_config_get_app_hcsr04_trigger_pin(),
    mgos_sys_config_get_app_hcsr04_echo_pin());
  if (hcsr04 == NULL) return MGOS_APP_INIT_ERROR;  
  
  /* Set timer for reading distance */
  mgos_set_timer(mgos_sys_config_get_app_measure_interval(),
    MGOS_TIMER_REPEAT, my_timer_cb, hcsr04);

  return MGOS_APP_INIT_SUCCESS;
}
