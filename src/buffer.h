#ifndef _BUFFER_H
#define _BUFFER_H

#include <Arduino.h>

// Macros por defecto
#ifndef LIST_LENGTH
#define LIST_LENGTH          32
#endif
#ifndef USER_NAME_LENGTH
#define USER_NAME_LENGTH     64
#endif
#ifndef PACKAGE_NAME_LENGTH
#define PACKAGE_NAME_LENGTH  64
#endif
#ifndef MAX_PACKAGES
#define MAX_PACKAGES         12
#endif

// Structs del buffer
typedef struct package {
  uint16_t item;
} package_t;

typedef struct node {
  char user[USER_NAME_LENGTH];
  uint8_t item_num;
  uint32_t time;
  package_t items[MAX_PACKAGES];
} node_t;

extern RTC_DATA_ATTR node_t buffer[LIST_LENGTH];
extern RTC_DATA_ATTR uint8_t buffer_idx;


void buffer_add_user(char *user_name);

void buffer_add_time(uint32_t time_unix);

void buffer_add_item(char *item_name);

void buffer_print_string(uint8_t idx);

void buffer_print_all(void);

void buffer_print_json(uint8_t idx);

void buffer_empty(void);

String buffer_get_items(uint8_t idx);

bool buffer_is_empty(void);

bool buffer_check_packages(void);

void buffer_fill_to_max();

#endif // _BUFFER_H