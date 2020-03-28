#pragma once
#ifndef _HTTPAPP_H
#define _HTTPAPP_H

#include <Arduino.h>
#include "esp_http_server.h"

static size_t HTTPAppJPGEncodeStream(void *arg, size_t index, const void *data, size_t len);
static esp_err_t HTTPAppHandlerCaptureJPG(httpd_req_t *req);
static esp_err_t HTTPAppHandlerStartLapse(httpd_req_t *req);
static esp_err_t HTTPAppHandlerStopLapse(httpd_req_t *req);
static esp_err_t HTTPAppHandlerStream(httpd_req_t *req);
static esp_err_t HTTPAppHandlerCMD(httpd_req_t *req);
static esp_err_t HTTPAppHandlerStatus(httpd_req_t *req);
static esp_err_t HTTPAppHandlerIndex(httpd_req_t *req);
void HTTPAppStartCameraServer();

#endif