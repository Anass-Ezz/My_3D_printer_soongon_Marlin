
#include "mini.h"
#include "../gcode/queue.h"

#if BOTH(SOONGON_MINI_SECTION_CODE, SOONGON_Z_LIMIT_TEST)

namespace sg_mini
{
  static void z_limit_test_key_function(uint8_t press_mode);

  static volatile bool is_key_press = false;
  static volatile bool is_long_key_press = false;

  MINI_KEY_T z_limit_test_key = {0, 0,  0,  0,  0, BTN_PRINT, z_limit_test_key_function };

  void mini_key_z_limit_test_check()
  {
    mini_key_check(z_limit_test_key);
  }

  void mini_key_z_limit_test_process(void)
  {
    if(is_key_press)
    {
      if(queue.has_commands_queued())
      {
        queue.clear();
      }
      queue.enqueue_now_P(PSTR("G28 Z0"));
      is_key_press = false;
    } else if(is_long_key_press)
    {
      if(queue.has_commands_queued())
      {
        queue.clear();
      }
      queue.enqueue_now_P(PSTR("G92 Z0"));
      queue.enqueue_now_P(PSTR("G1 Z1"));
      queue.enqueue_now_P(PSTR("M84 Z"));
      is_long_key_press = false;
    }
  }

  static void z_limit_test_key_function(uint8_t press_mode)
  {
    switch (press_mode)
    {
    case KEY_SHORT_PRESS:
      is_key_press = true;
      is_long_key_press = false;
      break;

    case KEY_LONG_PRESS:
      is_key_press = false;
      is_long_key_press = true;
      break;

    default:
      is_key_press = false;
      is_long_key_press = false;
      break;
    }
  }
}

#endif


