#include "Arduino.h"
#include "camera.h"
#include "esp_camera.h"
#include "pins_camera.h"


bool CameraInit(void)
{
  camera_config_t camera_config = {
    .pin_pwdn  = PIN_CAM_PWDN,
    .pin_reset = PIN_CAM_RESET,
    .pin_xclk = PIN_CAM_XCLK,
    .pin_sscb_sda = PIN_CAM_SIOD,
    .pin_sscb_scl = PIN_CAM_SIOC,

    .pin_d7 = PIN_CAM_D7,
    .pin_d6 = PIN_CAM_D6,
    .pin_d5 = PIN_CAM_D5,
    .pin_d4 = PIN_CAM_D4,
    .pin_d3 = PIN_CAM_D3,
    .pin_d2 = PIN_CAM_D2,
    .pin_d1 = PIN_CAM_D1,
    .pin_d0 = PIN_CAM_D0,
    .pin_vsync = PIN_CAM_VSYNC,
    .pin_href = PIN_CAM_HREF,
    .pin_pclk = PIN_CAM_PCLK,

    //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_JPEG,//YUV422,GRAYSCALE,RGB565,JPEG
    .frame_size = FRAMESIZE_UXGA,//QQVGA-QXGA Do not use sizes above QVGA when not JPEG

    .jpeg_quality = 12, //0-63 lower number means higher quality
    .fb_count = 1 //if more than one, i2s runs in continuous mode. Use only with JPEG
  };

  
  //init with high specs to pre-allocate larger buffers
  if (psramFound())
  {
    Serial.println("PSRAM found");
    camera_config.frame_size = FRAMESIZE_UXGA;
    camera_config.jpeg_quality = 10;
    camera_config.fb_count = 2;
  }
  else
  {
    Serial.println("No PSRAM found");
    camera_config.frame_size = FRAMESIZE_SVGA;
    camera_config.jpeg_quality = 12;
    camera_config.fb_count = 1;
  }


  //power up the camera if PWDN pin is defined
  if(PIN_CAM_PWDN != -1)
  {
    pinMode(PIN_CAM_PWDN, OUTPUT);
    digitalWrite(PIN_CAM_PWDN, LOW);
  }


  // camera init
  esp_err_t err = esp_camera_init(&camera_config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return false;
  }

  sensor_t *camera_sensor = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (camera_sensor->id.PID == OV3660_PID)
  {
    camera_sensor->set_vflip(camera_sensor, 1);      //flip it back
    camera_sensor->set_brightness(camera_sensor, 1);  //up the blightness just a bit
    camera_sensor->set_saturation(camera_sensor, -2); //lower the saturation
  }
  //drop down frame size for higher initial frame rate
  camera_sensor->set_framesize(camera_sensor, FRAMESIZE_QVGA);
  
  #if defined(CAMERA_MODEL_M5STACK_WIDE)
    camera_sensor->set_vflip(s, 1);
    camera_sensor->set_hmirror(s, 1);
  #endif

  return true;
}
