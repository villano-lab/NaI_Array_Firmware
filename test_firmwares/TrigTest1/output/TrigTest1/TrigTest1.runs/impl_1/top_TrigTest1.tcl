# 
# Report generation script generated by Vivado
# 

proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000

start_step init_design
set ACTIVE_STEP init_design
set rc [catch {
  create_msg_db init_design.pb
  create_project -in_memory -part xc7s25csga225-1
  set_property design_mode GateLvl [current_fileset]
  set_param project.singleFileAddWarning.threshold 0
  set_property webtalk.parent_dir C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.cache/wt [current_project]
  set_property parent.project_path C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.xpr [current_project]
  set_property ip_output_repo C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.cache/ip [current_project]
  set_property ip_cache_permissions {read write} [current_project]
  set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
  add_files -quiet C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.runs/synth_1/top_TrigTest1.dcp
  read_ip -quiet C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.srcs/sources_1/ip/clk_125MHZ/clk_125MHZ.xci
  read_ip -quiet C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.srcs/sources_1/ip/FTDI_FIFOs/FTDI_FIFOs.xci
  read_ip -quiet C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.srcs/sources_1/ip/main_clk_gen/main_clk_gen.xci
  read_xdc C:/OpenHardware/UserProject/NaI_Array_Firmware/test_firmwares/TrigTest1/output/TrigTest1/TrigTest1.srcs/constrs_1/imports/HDL/SCIDK_constraints.xdc
  link_design -top top_TrigTest1 -part xc7s25csga225-1
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
  unset ACTIVE_STEP 
}

start_step opt_design
set ACTIVE_STEP opt_design
set rc [catch {
  create_msg_db opt_design.pb
  opt_design 
  write_checkpoint -force top_TrigTest1_opt.dcp
  create_report "impl_1_opt_report_drc_0" "report_drc -file top_TrigTest1_drc_opted.rpt -pb top_TrigTest1_drc_opted.pb -rpx top_TrigTest1_drc_opted.rpx"
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
  unset ACTIVE_STEP 
}

start_step place_design
set ACTIVE_STEP place_design
set rc [catch {
  create_msg_db place_design.pb
  implement_debug_core 
  place_design 
  write_checkpoint -force top_TrigTest1_placed.dcp
  create_report "impl_1_place_report_io_0" "report_io -file top_TrigTest1_io_placed.rpt"
  create_report "impl_1_place_report_utilization_0" "report_utilization -file top_TrigTest1_utilization_placed.rpt -pb top_TrigTest1_utilization_placed.pb"
  create_report "impl_1_place_report_control_sets_0" "report_control_sets -verbose -file top_TrigTest1_control_sets_placed.rpt"
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
  unset ACTIVE_STEP 
}

start_step route_design
set ACTIVE_STEP route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force top_TrigTest1_routed.dcp
  create_report "impl_1_route_report_drc_0" "report_drc -file top_TrigTest1_drc_routed.rpt -pb top_TrigTest1_drc_routed.pb -rpx top_TrigTest1_drc_routed.rpx"
  create_report "impl_1_route_report_methodology_0" "report_methodology -file top_TrigTest1_methodology_drc_routed.rpt -pb top_TrigTest1_methodology_drc_routed.pb -rpx top_TrigTest1_methodology_drc_routed.rpx"
  create_report "impl_1_route_report_power_0" "report_power -file top_TrigTest1_power_routed.rpt -pb top_TrigTest1_power_summary_routed.pb -rpx top_TrigTest1_power_routed.rpx"
  create_report "impl_1_route_report_route_status_0" "report_route_status -file top_TrigTest1_route_status.rpt -pb top_TrigTest1_route_status.pb"
  create_report "impl_1_route_report_timing_summary_0" "report_timing_summary -max_paths 10 -file top_TrigTest1_timing_summary_routed.rpt -rpx top_TrigTest1_timing_summary_routed.rpx -warn_on_violation "
  create_report "impl_1_route_report_incremental_reuse_0" "report_incremental_reuse -file top_TrigTest1_incremental_reuse_routed.rpt"
  create_report "impl_1_route_report_clock_utilization_0" "report_clock_utilization -file top_TrigTest1_clock_utilization_routed.rpt"
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  write_checkpoint -force top_TrigTest1_routed_error.dcp
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
  unset ACTIVE_STEP 
}

start_step write_bitstream
set ACTIVE_STEP write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  set_property XPM_LIBRARIES {XPM_CDC XPM_FIFO XPM_MEMORY} [current_project]
  catch { write_mem_info -force top_TrigTest1.mmi }
  write_bitstream -force top_TrigTest1.bit -bin_file
  catch {write_debug_probes -quiet -force top_TrigTest1}
  catch {file copy -force top_TrigTest1.ltx debug_nets.ltx}
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
  unset ACTIVE_STEP 
}
