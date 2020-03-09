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

typedef enum { MESSAGE, REPORT } PayloadType;
typedef struct QUEUE_PAYLOAD {
  char *text;
  PayloadType type;
  struct MESSAGE *next;
} Payload;

typedef struct QUEUE {
  Payload *front;
  Payload *rear;
  int count;
} Queue;

esp_err_t queue_init(void);
esp_err_t queue_add_message(const char *text);
Payload *queue_get_payload(void);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_MESSAGE_H */