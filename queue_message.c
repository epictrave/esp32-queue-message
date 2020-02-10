// Copyright (c) Janghun LEE. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "queue_message.h"

static MessageQueue *queue = NULL;
static const char *TAG = "queue message";

esp_err_t queue_message_init(void) {
  if (queue != NULL) {
    ESP_LOGE(TAG, "Queue is already initialized.");
    return ESP_ERR_INVALID_STATE;
  } else {
    queue = (MessageQueue *)malloc(sizeof(MessageQueue));
    queue->front = queue->rear = NULL;
    queue->count = 0;
    return ESP_OK;
  }
}

esp_err_t queue_message_add_message(const char *text) {
  if (queue == NULL) {
    ESP_LOGE(TAG,
             "Queue is not initialized. please execute queue_message_init().");
    return ESP_ERR_INVALID_STATE;
  }
  Message *new_message = (Message *)malloc(sizeof(Message));
  new_message->next = NULL;
  new_message->text = (char *)malloc(sizeof(char) * (strlen(text) + 1));
  strncpy(new_message->text, text, strlen(text) + 1);
  if (queue->count == 0) {
    queue->front = new_message;
  } else {
    queue->rear->next = new_message;
  }
  queue->rear = new_message;
  queue->count++;
  return ESP_OK;
}

char *queue_message_get_message(void) {
  if (queue == NULL) {
    ESP_LOGE(TAG,
             "Queue is not initialized. please execute queue_message_init().");
    return NULL;
  }
  if (queue->count == 0) {
    return NULL;
  }
  Message *message = queue->front;
  char *text = (char *)malloc(sizeof(char) * (strlen(message->text) + 1));
  strncpy(text, message->text, strlen(message->text) + 1);
  queue->front = message->next;
  free(message->text);
  free(message);
  queue->count--;
  return text;
}