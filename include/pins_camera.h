// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER


#if defined(CAMERA_MODEL_WROVER_KIT)
    #define PIN_CAM_PWDN    -1
    #define PIN_CAM_RESET   -1
    #define PIN_CAM_XCLK    21
    #define PIN_CAM_SIOD    26
    #define PIN_CAM_SIOC    27

    #define PIN_CAM_D7      35
    #define PIN_CAM_D6      34
    #define PIN_CAM_D5      39
    #define PIN_CAM_D4      36
    #define PIN_CAM_D3      19
    #define PIN_CAM_D2      18
    #define PIN_CAM_D1       5
    #define PIN_CAM_D0       4
    #define PIN_CAM_VSYNC   25
    #define PIN_CAM_HREF    23
    #define PIN_CAM_PCLK    22

#elif defined(CAMERA_MODEL_ESP_EYE)
    #define PIN_CAM_PWDN    -1
    #define PIN_CAM_RESET   -1
    #define PIN_CAM_XCLK    4
    #define PIN_CAM_SIOD    18
    #define PIN_CAM_SIOC    23

    #define PIN_CAM_D7      36
    #define PIN_CAM_D6      37
    #define PIN_CAM_D5      38
    #define PIN_CAM_D4      39
    #define PIN_CAM_D3      35
    #define PIN_CAM_D2      14
    #define PIN_CAM_D1      13
    #define PIN_CAM_D0      34
    #define PIN_CAM_VSYNC   5
    #define PIN_CAM_HREF    27
    #define PIN_CAM_PCLK    25

#elif defined(CAMERA_MODEL_M5STACK_PSRAM)
    #define PIN_CAM_PWDN     -1
    #define PIN_CAM_RESET    15
    #define PIN_CAM_XCLK     27
    #define PIN_CAM_SIOD     25
    #define PIN_CAM_SIOC     23

    #define PIN_CAM_D7       19
    #define PIN_CAM_D6       36
    #define PIN_CAM_D5       18
    #define PIN_CAM_D4       39
    #define PIN_CAM_D3        5
    #define PIN_CAM_D2       34
    #define PIN_CAM_D1       35
    #define PIN_CAM_D0       32
    #define PIN_CAM_VSYNC    22
    #define PIN_CAM_HREF     26
    #define PIN_CAM_PCLK     21

#elif defined(CAMERA_MODEL_M5STACK_WIDE)
    #define PIN_CAM_PWDN     -1
    #define PIN_CAM_RESET    15
    #define PIN_CAM_XCLK     27
    #define PIN_CAM_SIOD     22
    #define PIN_CAM_SIOC     23

    #define PIN_CAM_D7       19
    #define PIN_CAM_D6       36
    #define PIN_CAM_D5       18
    #define PIN_CAM_D4       39
    #define PIN_CAM_D3        5
    #define PIN_CAM_D2       34
    #define PIN_CAM_D1       35
    #define PIN_CAM_D0       32
    #define PIN_CAM_VSYNC    25
    #define PIN_CAM_HREF     26
    #define PIN_CAM_PCLK     21

#elif defined(CAMERA_MODEL_AI_THINKER)
    #define PIN_CAM_PWDN     32
    #define PIN_CAM_RESET    -1
    #define PIN_CAM_XCLK      0
    #define PIN_CAM_SIOD     26
    #define PIN_CAM_SIOC     27

    #define PIN_CAM_D7       35
    #define PIN_CAM_D6       34
    #define PIN_CAM_D5       39
    #define PIN_CAM_D4       36
    #define PIN_CAM_D3       21
    #define PIN_CAM_D2       19
    #define PIN_CAM_D1       18
    #define PIN_CAM_D0        5
    #define PIN_CAM_VSYNC    25
    #define PIN_CAM_HREF     23
    #define PIN_CAM_PCLK     22

#else
    #error "Camera model not selected"
#endif
