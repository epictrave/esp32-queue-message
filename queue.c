// Copyright (c) Janghun LEE. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "queue.h"

static Queue *queue = NULL;
static const char *TAG = "queue";

esp_err_t queue_init(void) {
  if (queue != NULL) {
    ESP_LOGE(TAG, "Queue is already initialized.");
    return ESP_ERR_INVALID_STATE;
  } else {
    queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->count = 0;
    return ESP_OK;
  }
}

esp_err_t queue_add(const char *text, PayloadType type) {
  if (queue == NULL) {
    ESP_LOGE(TAG, "Queue is not initialized. please execute queue_init().");
    return ESP_ERR_INVALID_STATE;
  }
  Payload *new_payload = (Payload *)malloc(sizeof(Payload));
  new_payload->next = NULL;
  new_payload->type = type;
  new_payload->text = (char *)malloc(sizeof(char) * (strlen(text) + 1));
  strncpy(new_payload->text, text, strlen(text) + 1);
  if (queue->count == 0) {
    queue->front = new_payload;
  } else {
    queue->rear->next = new_payload;
  }
  queue->rear = new_payload;
  queue->count++;
  return ESP_OK;
}

esp_err_t queue_add_message(const char *text, PayloadType type) {
  return queue_add(text, MESSAGE);
}

esp_err_t queue_add_report(const char *text, PayloadType type) {
  return queue_add(text, REPORT);
}
Payload *queue_get_payload(void) {
  if (queue == NULL) {
    ESP_LOGE(TAG,
             "Queue is not initialized. please execute queue_message_init().");
    return NULL;
  }
  if (queue->count == 0) {
    return NULL;
  }
  Payload *payload = queue->front;
  queue->front = payload->next;
  queue->count--;
  return payload;
}