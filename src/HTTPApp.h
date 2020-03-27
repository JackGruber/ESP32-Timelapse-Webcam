#pragma once
#ifndef _HTTPAPP_H
#define _HTTPAPP_H

#include <Arduino.h>
#include "esp_http_server.h"

static size_t jpg_encode_stream(void *arg, size_t index, const void *data, size_t len);
static esp_err_t capture_handler(httpd_req_t *req);
static esp_err_t startLapseHandler(httpd_req_t *req);
static esp_err_t stopLapseHandler(httpd_req_t *req);
static esp_err_t streamHandler(httpd_req_t *req);
static esp_err_t cmd_handler(httpd_req_t *req);
static esp_err_t status_handler(httpd_req_t *req);
static esp_err_t index_handler(httpd_req_t *req);
void startCameraServer();

#endif