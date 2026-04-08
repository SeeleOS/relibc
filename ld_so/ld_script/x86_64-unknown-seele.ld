SECTIONS {
  .eh_frame_hdr : {
    PROVIDE_HIDDEN(__eh_frame_hdr_start = .);
    *(.eh_frame_hdr)
    *(.eh_frame_entry .eh_frame_entry.*)
    PROVIDE_HIDDEN(__eh_frame_hdr_end = .);
  }

  .eh_frame : {
    PROVIDE_HIDDEN(__eh_frame_start = .);
    KEEP(*(.eh_frame))
    *(.eh_frame.*)
    PROVIDE_HIDDEN(__eh_frame_end = .);
  }
} INSERT BEFORE .gcc_except_table;
