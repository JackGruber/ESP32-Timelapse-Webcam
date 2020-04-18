#include "Arduino.h"
#include "camera.h"
#include "esp_camera.h"
#include "pins_camera.h"
#include "Pref.h"

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
  
  #if defined(CAMERA_MODEL_M5STACK_WIDE)
    camera_sensor->set_vflip(s, 1);
    camera_sensor->set_hmirror(s, 1);
  #endif

  return true;
}

bool CameraLoadSettings(void)
{
  sensor_t *s = esp_camera_sensor_get();
  PrefInit();
  
  if(s->set_framesize(s, (framesize_t) PrefLoadInt("framesize", 10, false))) { return false; }
  if(s->set_quality(s, PrefLoadInt("quality", 10, false))) { return false; }
  if(s->set_contrast(s, PrefLoadInt("contrast", 0, false))) { return false; }
  if(s->set_brightness(s, PrefLoadInt("brightness", 0, false))) { return false; }
  if(s->set_saturation(s, PrefLoadInt("saturation", 0, false))) { return false; }
  if(s->set_gainceiling(s, (gainceiling_t) PrefLoadInt("gainceiling", 0, false))) { return false; }
  if(s->set_colorbar(s, PrefLoadInt("colorbar", 0, false))) { return false; }
  if(s->set_whitebal(s, PrefLoadInt("awb", 1, false))) { return false; }
  if(s->set_gain_ctrl(s, PrefLoadInt("agc", 1, false))) { return false; }
  if(s->set_exposure_ctrl(s, PrefLoadInt("aec", 1, false))) { return false; }
  if(s->set_hmirror(s, PrefLoadInt("hmirror", 0, false))) { return false; }
  if(s->set_vflip(s, PrefLoadInt("vflip", 0, false))) { return false; }
  if(s->set_agc_gain(s, PrefLoadInt("agc_gain", 0, false))) { return false; }
  if(s->set_aec2(s, PrefLoadInt("aec2", 0, false))) { return false; }
  if(s->set_aec_value(s, PrefLoadInt("aec_value", 168, false))) { return false; }
  if(s->set_dcw(s, PrefLoadInt("dcw", 1, false))) { return false; }
  if(s->set_bpc(s, PrefLoadInt("bpc", 0, false))) { return false; }
  if(s->set_wpc(s, PrefLoadInt("wpc", 1, false))) { return false; }
  if(s->set_raw_gma(s, PrefLoadInt("raw_gma", 1, false))) { return false; }
  if(s->set_lenc(s, PrefLoadInt("lenc", 1, false))) { return false; }
  if(s->set_special_effect(s, PrefLoadInt("special_effect", 0, false))) { return false; }
  if(s->set_wb_mode(s, PrefLoadInt("wb_mode", 0, false))) { return false; }
  if(s->set_awb_gain(s, PrefLoadInt("awb_gain", 1, false))) { return false; }
  if(s->set_ae_level(s, PrefLoadInt("ae_level", 0, false))) { return false; }
  if(s->set_sharpness(s, PrefLoadInt("sharpness", 0, false))) { return false; }

  PrefEnd();
  return true;
}

bool CameraSaveSettings(void)
{
  sensor_t *s = esp_camera_sensor_get();
  PrefInit();

  PrefSaveInt("framesize", s->status.framesize,false);
  PrefSaveInt("quality", s->status.quality,false);
  PrefSaveInt("contrast", s->status.contrast,false);
  PrefSaveInt("brightness", s->status.brightness,false);
  PrefSaveInt("saturation", s->status.saturation,false);
  PrefSaveInt("gainceiling", s->status.gainceiling,false);
  PrefSaveInt("colorbar", s->status.colorbar,false);
  PrefSaveInt("awb", s->status.awb,false);
  PrefSaveInt("agc", s->status.agc,false);
  PrefSaveInt("aec", s->status.aec,false);
  PrefSaveInt("hmirror", s->status.hmirror,false);
  PrefSaveInt("vflip", s->status.vflip,false);
  PrefSaveInt("agc_gain", s->status.agc_gain,false);
  PrefSaveInt("aec2", s->status.aec2,false);
  PrefSaveInt("aec_value", s->status.aec_value,false);
  PrefSaveInt("dcw", s->status.dcw,false);
  PrefSaveInt("bpc", s->status.bpc,false);
  PrefSaveInt("wpc", s->status.wpc,false);
  PrefSaveInt("raw_gma", s->status.raw_gma,false);
  PrefSaveInt("lenc", s->status.lenc,false);
  PrefSaveInt("special_effect", s->status.special_effect,false); 
  PrefSaveInt("wb_mode", s->status.wb_mode,false);  
  PrefSaveInt("awb_gain", s->status.awb_gain,false);  
  PrefSaveInt("ae_level", s->status.ae_level,false);  
  PrefSaveInt("sharpness", s->status.sharpness,false);  

  PrefEnd();
  return true;
}
