#include <pebble.h>

static Window *s_main_window;
static bool s_animate_window = false;

static AppMessageResult trigger_screenshot() {
  DictionaryIterator *out;
  AppMessageResult result = app_message_outbox_begin(&out);
  dict_write_cstring(out, MESSAGE_KEY_TakeScreenshot, "1");
  result = app_message_outbox_send();
  return result;
}

static void inbox_received_handler(DictionaryIterator *iter, void *context) {
  Tuple *ready_tuple = dict_find(iter, MESSAGE_KEY_JSReady);
  if (ready_tuple) {
    // PebbleKit JS is ready! Safe to send messages
    trigger_screenshot();
  }
  Tuple *done_tuple = dict_find(iter, MESSAGE_KEY_Done);
  if (done_tuple) {
    exit_reason_set(APP_EXIT_ACTION_PERFORMED_SUCCESSFULLY);
    window_stack_remove(s_main_window, s_animate_window);
  }
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
}

static void main_window_unload(Window *window) {
}

static void init(void) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(256, 256);
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, s_animate_window);
}

static void deinit(void) {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}