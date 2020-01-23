load('api_hcsr04.js');
load('api_config.js');
load('api_timer.js');

/* Create HC-SR04 sensor instance */
let hcsr04 = HCSR04.create(Cfg.get('app.hcsr04.trigger_pin'),
  Cfg.get('app.hcsr04.echo_pin'));

/* Set timer for reading distance */
Timer.set(Cfg.get('app.measure_interval'), Timer.REPEAT, function(sensor) {
  let d = sensor.getDistance();
  print('Distance: ', (isNaN(d) ? 'error reading distance' : d));
}, hcsr04);