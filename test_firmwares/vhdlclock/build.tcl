


set script_path [ file dirname [ file normalize [ info script ] ] ]
set outputDir $script_path/vivado
set artDir $script_path/output
file mkdir $outputDir
file mkdir $artDir

set outfile1 [open "${artDir}/content.xml" w+]   

puts $outfile1 "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
puts $outfile1 "<OPENHARDWARE>"
puts $outfile1 "   <SUPPORTED_PLATFORM>"
puts $outfile1 "       <GUID0>36F7FF8D-4166-4517-81D2-60182B95C7C3</GUID0>"
puts $outfile1 "       <MODEL>A</MODEL>"
puts $outfile1 "   </SUPPORTED_PLATFORM>"
puts $outfile1 "   <FPGA>"
puts $outfile1 "       <version>2024.02.06.25</version>"
puts $outfile1 "       <filename>top_vhdlclock.bin</filename>"
puts $outfile1 "   </FPGA>"
puts $outfile1 "   <HWJSON>"
puts $outfile1 "       <filename>RegisterFile.json</filename>"
puts $outfile1 "   </HWJSON>"
puts $outfile1 "</OPENHARDWARE>"

close $outfile1


create_project vhdlclock $outputDir -part XC7S25CSGA225-1 -force
set_property source_mgmt_mode None [current_project]
set_property target_language VHDL [current_project]
set_property XPM_LIBRARIES {XPM_CDC XPM_MEMORY XPM_FIFO} [current_project]



add_files -force ./pcores/clk_125MHZ.xci
add_files -force ./pcores/FTDI_FIFOs.xcix
add_files -force ./pcores/main_clk_gen.xci
add_files -force ./top_vhdlclock.vhd
add_files -force ./pcores/ftdi245.vhd
add_files -force ./pcores/ftdi245_cdc.vhd
add_files -force ./pcores/i2c_master_scidk_config.vhd
add_files -force ./pcores/md5.vhd
add_files -force ./pcores/scidk_internal_i2c_manager.vhd
add_files -force ./pcores/security.vhd
add_files -force ./pcores/spi93lc56_16bit.vhd
add_files -force ./pcores/U2_UserHDL_Clock_Tx.vhd
add_files -force ./pcores/U3_UserHDL_Serial_Tx.vhd
add_files -force ./pcores/U4_UserHDL_Serial_Rx.vhd
add_files -force -fileset constrs_1 ./SCIDK_constraints.xdc
import_files -force -norecurse
import_files -fileset constrs_1 -force -norecurse ./SCIDK_constraints.xdc


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

update_ip_catalog -rebuild



set_property Top top_vhdlclock [current_fileset]

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

file copy -force $outputDir/vhdlclock.runs/impl_1/top_vhdlclock.bin $artDir/top_vhdlclock.bin
file copy -force $script_path/RegisterFile.json $artDir/RegisterFile.json
if { [catch { exec rm $artDir/vhdlclock.niu  } msg] } {
puts "No niu file present to be deleted"
}

exec zip -j $artDir/vhdlclock.niu $artDir/RegisterFile.json $artDir/top_vhdlclock.bin $artDir/content.xml

exit





