'''apport package hook for i-nex


Author: eloaders <eloaders@yahoo.com>
'''

from apport.hookutils import *


def add_info(report):
    report['CrashDB'] = 'inex'
    attach_file_if_exists(report, '/sys/bus/acpi/devices/LNXTHERM:00/thermal_zone/temp', 'ThermalZone')
    attach_file_if_exists(report, '/proc/acpi/battery/BAT1/info', 'BAT1_Info')
    attach_file_if_exists(report, '/proc/acpi/battery/BAT0/info', 'BAT0_Info')
    attach_file_if_exists(report, '/proc/cpuinfo', 'CpuInfo')
    attach_file_if_exists(report, '/etc/timezone', 'TimeZone')
    
    attach_root_command_outputs(report,
        {'lsusb': 'lsusb',
	 'lspci': 'lspci',
	 'lshal': 'lshal',
	 'lshw': 'lshw',
	 'UnameA': 'uname -a',
	 'LsSysBlock': 'ls /sys/block/ | grep sd',
	 'Glxinfo': 'glxinfo',
	 'Xdpyinfo': 'xdpyinfo',
	 'Xrandr': 'xrandr',
	 'UsbDevicesInBus': 'ls /sys/bus/usb/devices/*/* | grep manufacturer | grep [0-9]',
         'CurrentDmesg': 'dmesg',
	 'FreeM': 'free -m',
	 'SwaponS': 'swapon -s'})
