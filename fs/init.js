load('api_hcsr04.js');
load('api_config.js');
load('api_timer.js');
load('api_sys.js');

/* Create HC-SR04 sensor instance */
let hcsr04 = HCSR04.create(Cfg.get('app.hcsr04.trigger_pin'),
  Cfg.get('app.hcsr04.echo_pin'));

/* Set timer for reading distance */
Timer.set(Cfg.get('app.measure_interval'), Timer.REPEAT, function(sensor) {
  let dist = sensor.getDistance();
  Sys.usleep(50); // 5 milliseconds
  let distAvg = sensor.getAvgDistance(Cfg.get('app.hcsr04.avg_attempts'));

  if (!isNaN(dist) && !isNaN(distAvg)) {
    print('Distance (mm):',  dist, '(avg.', distAvg,
      '| discrepancy', (dist - distAvg), ')');
  } else if (!isNaN(dist)) {
    print('Distance (mm):', dist);
  } else if (!isNaN(distAvg)) {
    print('Distance (mm): avg.', distAvg);
  } else {
    print('Distance (mm): error reading distance');
  }
}, hcsr04);