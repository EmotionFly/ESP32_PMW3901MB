idf_component_register(SRCS "pmw3901.c"
                       INCLUDE_DIRS "include"
                       REQUIRES deck_digital
                       REQUIRES deck_spi
                       REQUIRES esp32_bridge)
