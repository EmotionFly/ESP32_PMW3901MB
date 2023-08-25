## 硬件连接

| Name         | Pin      |
| ------------ | -------- |
| SPI_MISO_PIN | GPIO12   |
| SPI_MOSI_PIN | GPIO13   |
| SPI_SCK_PIN  | GPIO14   |
| SPI_CS_PIN   | GPIO15   |


## 编译命令

1、获取esp-idf库的环境
  . $HOME/esp/esp-idf/export.sh

2、编译代码
  make gtr_pmw3901

3、下载代码
  make upload

4、查看运行结果
  make monitor_rc

5、清除代码
  make clean_rc
  会把构建输出的文件从构建目录中删除，从而清理整个项目。下次构建时会强制“重新完整构建”这个项目。清理时，不会删除 CMake 配置输出及其他文件。
  make fullclean
  会将整个 build 目录下的内容全部删除，包括所有 CMake 的配置输出文件。下次构建项目时，CMake 会从头开始配置项目。请注意，该命令会递归删除构建目录下的所有文件，请谨慎使用。项目配置文件不会被删除。


## ESP32_VL53L3CX

Development of the VL53L3CX Distance Sensor on the ESP32 DEVKIT V1 Development Board.