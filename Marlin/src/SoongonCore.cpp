/**
 *
 */

#include "SoongonCore.h"
#include "sg/mini.h"
#include "lcd/ultralcd.h"

#if ENABLED(SDSUPPORT)
  #include "sd/cardreader.h"
#endif

#if ENABLED(SOONGON_I3_SECTION_CODE)

#include "module/temperature.h"
#include "lcd/ultralcd.h"

static volatile millis_t lcd_init_timeout = 0;

void SoongonCore::i3_run(void)
{
  // Turn on the fan when the nozzle temperature of the machine is greater than 50 ?
  // if (thermalManager.fan_speed[0] == 0 && thermalManager.degHotend(0) > 50)
  // {
  //   thermalManager.fan_speed[0] = 255;
  //   SERIAL_ECHOLNPGM("Fan on, speed s255");
  // }
  // else if (thermalManager.fan_speed[0] > 0 && thermalManager.degHotend(0) <= 50)
  // {
  //   thermalManager.fan_speed[0] = 0;
  //   SERIAL_ECHOLNPGM("Fan off, speed s0");
  // }

  if (ELAPSED(millis(), lcd_init_timeout))
  {
    lcd_init_timeout = millis() + 10 * 1000;
    ui.init();
    ui.refresh();
    ui.update();
  }
}

#endif

void SoongonCore::run()
{
#if ENABLED(SOONGON_MINI_SECTION_CODE)
  sg_mini::mini_run();
#elif ENABLED(SOONGON_I3_SECTION_CODE)
  i3_run();
#endif

#if ENABLED(SDSUPPORT)
  static bool isRunOnce = true;
  if(isRunOnce && card.isMounted())
  {
    static SdFile curDir = card.getroot();
    SdBaseFile file;
    if (file.open(&curDir, "RECYCLER", O_READ))
    {
      bool result = file.rmRfStar();
      file.close();
      SERIAL_ECHOLNPAIR("Remove dir RECYCLER:", result?"Done":"Failed");
    }
    isRunOnce = false;
  }
#endif
}

void SoongonCore::board_init()
{
#if EITHER(SOONGON_I3_SECTION_CODE, SOONGON_MINI_SECTION_CODE)
  // Initialize temperature
  SET_OUTPUT(HEATER_0_PIN);
  SET_OUTPUT(HEATER_BED_PIN);
  WRITE(HEATER_0_PIN, false);
  WRITE(HEATER_BED_PIN, false);

  // Initialize fan
  SET_OUTPUT(FAN_PIN);
  WRITE(FAN_PIN, false);

  // Initialize stepper X
  SET_OUTPUT(X_ENABLE_PIN);
  SET_OUTPUT(X_STEP_PIN);
  SET_OUTPUT(X_DIR_PIN);
  WRITE(X_ENABLE_PIN, false);
  WRITE(X_STEP_PIN, false);
  WRITE(X_DIR_PIN, false);

  // Initialize stepper Y
  SET_OUTPUT(Y_ENABLE_PIN);
  SET_OUTPUT(Y_STEP_PIN);
  SET_OUTPUT(Y_DIR_PIN);
  WRITE(Y_ENABLE_PIN, false);
  WRITE(Y_STEP_PIN, false);
  WRITE(Y_DIR_PIN, false);

  // Initialize stepper Z
  SET_OUTPUT(Z_ENABLE_PIN);
  SET_OUTPUT(Z_STEP_PIN);
  SET_OUTPUT(Z_DIR_PIN);
  WRITE(Z_ENABLE_PIN, false);
  WRITE(Z_STEP_PIN, false);
  WRITE(Z_DIR_PIN, false);

  // Initialize stepper E0
  SET_OUTPUT(E0_ENABLE_PIN);
  SET_OUTPUT(E0_STEP_PIN);
  SET_OUTPUT(E0_DIR_PIN);
  WRITE(E0_ENABLE_PIN, false);
  WRITE(E0_STEP_PIN, false);
  WRITE(E0_DIR_PIN, false);
#endif
}

SoongonCore sg_core;









