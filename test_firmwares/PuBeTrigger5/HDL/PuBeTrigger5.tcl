set outputDir C:/OpenHardware/UserProject/PuBeTrigger5/output/PuBeTrigger5
file mkdir $outputDir
create_project PuBeTrigger5 C:/OpenHardware/UserProject/PuBeTrigger5/output/PuBeTrigger5 -part xc7z030fbg676-2 -force
set_property source_mgmt_mode None [current_project]
set_property target_language VHDL [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY XPM_FIFO} [current_project]
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/clk_wiz_0.xcix
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/clk_wiz_0.xcix
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/fifo_generator_0.xcix
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/fifo_generator_0.xcix
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/main_clock.xci
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/subpage_TriggerWindow.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/top_PuBeTrigger5.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/ADC1.v
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/ADC2.v
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/adcs_top.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/adcs_top.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/adc_interface.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/adc_interface.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/avalon_wrapper.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/avalon_wrapper.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/MCRateMeter.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/MCRateMeter.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/polinvert.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/polinvert.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/trigger_leading.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/trigger_leading.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/xlx_delay.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/xlx_delay.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/xlx_soft_gd.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/xlx_soft_gd.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/ZynqDesign_wrapper.vhd
add_files -force C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/ZynqDesign_wrapper.vhd
add_files -force -fileset constrs_1 C:/OpenHardware/UserProject/PuBeTrigger5/HDL/DT5560_pins.xdc
import_files -force -norecurse
import_files -fileset constrs_1 -force -norecurse C:/OpenHardware/UserProject/PuBeTrigger5/HDL/DT5560_pins.xdc
foreach ip [get_ips] {
upgrade_ip [get_ips $ip]
set ip_filename [get_property IP_FILE $ip]
set ip_dcp [file rootname $ip_filename]
append ip_dcp ".dcp"
set ip_xml [file rootname $ip_filename]
append ip_xml ".xml"
if {([file exists $ip_dcp] == 0) || [expr {[file mtime $ip_filename ] > [file mtime $ip_dcp ]}]} {
reset_target all $ip
file delete $ip_xml
generate_target all $ip
synth_ip $ip
}
}
set_property "ip_repo_paths" "[file normalize "C:/OpenHardware/UserProject/PuBeTrigger5/HDL/ip_repo"]"  [current_project]
update_ip_catalog -rebuild
source "C:/OpenHardware/UserProject/PuBeTrigger5/HDL/pcores/ZynqDesign.tcl"
set_property Top top_PuBeTrigger5 [current_fileset]
set obj [get_runs impl_1]
set obj_s [get_runs synth_1]
set_property -name "steps.write_bitstream.args.bin_file" -value "1" -objects $obj
if {[catch {
launch_runs synth_1 -jobs 32
wait_on_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs 32
wait_on_run impl_1
} errorstring]} {
Error "ABBA: $errorstring "
exit
}
exit
