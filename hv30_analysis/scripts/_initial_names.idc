#include <idc.idc>
static makeNames1()
{
  MakeName(0x000f0000, "sys_partition_start");
  AutoMark(0x000f0000, AU_CODE );
  MakeName(0x000f0cb6, "sys_some_logger");
  AutoMark(0x000f0cb6, AU_CODE );
  MakeName(0x000f515e, "eventCreate_sys");
  AutoMark(0x000f515e, AU_CODE );
  MakeName(0x000f5aa4, "taskCreate_sys");
  AutoMark(0x000f5aa4, AU_CODE );
  MakeName(0x04048d84, "semCreate");
  AutoMark(0x04048d84, AU_CODE );

  MakeName(0x04048d9a, "eventCreate");
  AutoMark(0x04048d9a, AU_CODE );
  MakeName(0x0404905e, "init_task");
  AutoMark(0x0404905e, AU_CODE );
  MakeName(0x040490e4, "PANIC");
  AutoMark(0x040490e4, AU_CODE );
  MakeName(0x04049580, "init_create_events_tasks");
  AutoMark(0x04049580, AU_CODE );
  MakeName(0x040499fc, "init_task_super");
  AutoMark(0x040499fc, AU_CODE );
  MakeName(0x04049c98, "task_swp");

  AutoMark(0x04049c98, AU_CODE );
  MakeName(0x04049cba, "task_1294_vd");
  AutoMark(0x04049cba, AU_CODE );
  MakeName(0x04049cdc, "task_shell");
  AutoMark(0x04049cdc, AU_CODE );
  MakeName(0x04049eda, "task_osd");
  AutoMark(0x04049eda, AU_CODE );
  MakeName(0x0404a2ec, "memcpy_block");
  AutoMark(0x0404a2ec, AU_CODE );
  MakeName(0x0404a362, "memcmp");
  AutoMark(0x0404a362, AU_CODE );
  MakeName(0x0404a37e, "init_FR_program");
  AutoMark(0x0404a37e, AU_CODE );
  MakeName(0x0404a534, "init_root_TBR_reset_handler");
  AutoMark(0x0404a534, AU_CODE );
  MakeName(0x0404a7d6, "int_handler_2");
  AutoMark(0x0404a7d6, AU_CODE );
  MakeName(0x0404aaca, "intx6");
  AutoMark(0x0404aaca, AU_CODE );
  MakeName(0x0404cb5e, "sys_log");
  AutoMark(0x0404cb5e, AU_CODE );
  MakeName(0x040594c0, "cmd_debug_setup");
  AutoMark(0x040594c0, AU_CODE );
  MakeName(0x0405b86c, "shell_event");
  AutoMark(0x0405b86c, AU_CODE );
  MakeName(0x0405c4b8, "shell_kill");
  AutoMark(0x0405c4b8, AU_CODE );
  MakeName(0x040616f0, "shell_register");
  AutoMark(0x040616f0, AU_CODE );
  MakeName(0x04063234, "sys_log2");
  AutoMark(0x04063234, AU_CODE );
  MakeName(0x0411b8ba, "task_osd_loop");
  AutoMark(0x0411b8ba, AU_CODE );
  MakeName(0x041ff800, "TBR_LOCATION");

  MakeName(0x002c0000, "TBR_SYSTEM");
  MakeName(0x002c043c, "sys_cleanup_40000_42000");
  AutoMark(0x002c043c, AU_CODE );
  MakeName(0x002c04b0, "self_copy");
  AutoMark(0x002c04b0, AU_CODE );
  MakeName(0x002d49a8, "sys_2DB0E4to419C8");
  AutoMark(0x002d49a8, AU_CODE );
  MakeName(0x002d49c8, "sys_2D8114_to_100400");
  AutoMark(0x002d49c8, AU_CODE );
  MakeName(0x002d5018, "some_init");
  AutoMark(0x002d5018, AU_CODE );
}

static main()
{
}

