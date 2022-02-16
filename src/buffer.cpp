#include "buffer.h"

void buffer_add_user(char *user_name)
{
  strncpy(buffer[buffer_idx].user, user_name, USER_NAME_LENGTH);
  buffer[buffer_idx].item_num = 0;
  log_d("ADDED USER: %s IN INDEX %d", user_name, buffer_idx);
}

void buffer_add_time(uint32_t time_unix){
  buffer[buffer_idx].time = time_unix;
  log_d("ADDED TIME %d TO USER %d", time_unix, buffer_idx);
}

void buffer_add_item(char *item_name)
{
  uint8_t i_num = buffer[buffer_idx].item_num;
  char string[PACKAGE_NAME_LENGTH];
  strncpy(string, item_name, USER_NAME_LENGTH);  
  bool next = false;
  char * token = strtok(string, "/");
  while( token != NULL ) { // Check every token until it reads "info" -> next token is ID
    if(next){
        token = strtok(NULL, "/");
        break;
    }
    token = strtok(NULL, "/");
    if(strstr(token, "info") != NULL){
        next = true;
    }
  }
  buffer[buffer_idx].items[i_num].item = atoi(token);
  log_d("ADDED ITEM N°%d: %d TO USER: %s IN INDEX %d", 
        i_num, 
        buffer[buffer_idx].items[i_num].item, 
        buffer[buffer_idx].user, 
        buffer_idx);
  buffer[buffer_idx].item_num++;
}

void buffer_print_string(uint8_t idx) {
  node_t node = buffer[idx];
  if(node.user != NULL) {
    log_d("\nUSER N°%d: %s", idx, node.user);
    log_d("TIME: %d", node.time);
    log_d("ITEM NUMBER: %d", node.item_num);
    log_d("ITEMS: ");
    for(uint8_t i = 0; i < node.item_num; i++) {
      log_d("%d: %d", i, node.items[i].item);
    }
  }
  else {
    log_e("ERROR: INDEX POINTS TO EMPTY USER");
  }
}

void buffer_print_all(void) {
  for(uint8_t i = 0; i < LIST_LENGTH; i++) {
    if(buffer[i].item_num != 0) {  // TODO: change to detect user string
      buffer_print_string(i);
    }
    else {
      break;
    }
  }
}

void buffer_print_json(uint8_t idx, char* value) {
  node_t node = buffer[idx];
  if(node.user != NULL) {
    strncpy(value, node.user, strlen(node.user));
    strcat(value, ", [");
    for(uint8_t i = 0; i < node.item_num; i++) {
      char id_str[5];
      sprintf(id_str, "%d",node.items[i].item);
      strncat(value, id_str, 5);
      if(i != node.item_num - 1) {
        strcat(value, ", ");
      }
    }
    strcat(value, "]");
    log_d("value: %s\n", value);
  }
  else {
    log_e("ERROR: INDEX POINTS TO EMPTY USER");
  }
}

void buffer_empty(void) {
  for(uint8_t i = 0; i < buffer_idx; i++) {
    buffer[i] = (node_t){0};
  }
  buffer_idx = 0;
  log_d("Buffer deleted successfully");
}

String buffer_get_items(uint8_t idx) {
  node_t node = buffer[idx];
  String value = "";
  if(node.user != NULL) {
    value += "[\"";
    for(uint8_t i = 0; i < node.item_num; i++) {
      //value += "info/";
      value += String(node.items[i].item);
      if(i != node.item_num - 1) {
        value += "\",\"";
      }
    }
    value += "\"]";
    log_d("value: %s\n", value);
  }
  else {
    log_e("ERROR: INDEX POINTS TO EMPTY USER");
  }
  return value;
}

bool buffer_is_empty(void) {
  // If first element exists, then buffer is not empty
  node_t node = buffer[0];
  if(node.user != NULL) {
    log_d("Buffer is not empty!");
    return false;
  }
  log_d("Buffer is empty");
  return true;
}

bool buffer_check_packages(void) {
  // If at least one user has packages, then buffer must be uploaded
  for(uint8_t i = 0; i < buffer_idx; i++) {
    node_t node = buffer[i];
    if(node.item_num != 0) {
      // Returns true if at least one user has packages registered in buffer
      log_d("There are valid packages in buffer");
      return true;
    }
  }
  log_d("There are no packages registered in buffer");
  return false;
}

// Función para testeo de envío de datos.
void buffer_fill_to_max(){
  buffer_empty();
  buffer_idx = LIST_LENGTH;
  for(uint8_t i = 0; i < LIST_LENGTH; i++){
    strncpy(buffer[i].user, "Nombre para testeo en Redefine", USER_NAME_LENGTH);
    buffer[i].item_num = 12;
    buffer[i].time = 0;
    for(uint8_t j = 0; j < MAX_PACKAGES; j++){
      buffer[i].items[j].item = 64000;
    }
  }
}
