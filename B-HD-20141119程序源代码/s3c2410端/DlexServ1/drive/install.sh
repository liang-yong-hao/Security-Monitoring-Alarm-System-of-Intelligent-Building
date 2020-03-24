insmod magic_gpio.ko
mknod /dev/gpio c 234 0
insmod magic_irst.ko
mknod /dev/irst c 246 0
insmod magic_sht11_driver.ko
mknod /dev/sht11 c 238 0
insmod s3c2410-adc.ko
mknod /dev/adc c 250 0 

