// Copyright (c) Janghun LEE. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef QUEUE_MESSAGE_H
#define QUEUE_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
#include "esp_log.h"
#include "stdlib.h"
#include "string.h"

typedef struct MESSAGE {
  char *text;
  struct MESSAGE *next;
} Message;

typedef struct MESSAGE_QUEUE {
  Message *front;
  Message *rear;
  int count;
} MessageQueue;

esp_err_t queue_message_init(void);
esp_err_t queue_message_add_message(const char *text);
char *queue_message_get_message(void);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_MESSAGE_H */