#include <pebble.h>

static GBitmap *s_bitmap;
static Window *s_main_window;
static BitmapLayer *s_bitmap_layer;
static TextLayer *s_text_layer;


#ifndef PBL_DISPLAY_WIDTH
#define PBL_DISPLAY_WIDTH 200
#endif

#define ANIMATE_WINDOW true

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
    vibes_short_pulse();
    exit_reason_set(APP_EXIT_ACTION_PERFORMED_SUCCESSFULLY);
    window_stack_remove(s_main_window, ANIMATE_WINDOW);
  }
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  #define TW 160
  s_text_layer = text_layer_create(PBL_IF_ROUND_ELSE(GRect((bounds.size.w - TW) / 2, bounds.size.h / 3 * 2 + 15, TW, 20), GRect(0, bounds.size.h - 30, bounds.size.w, 20)));
  text_layer_set_text(s_text_layer, "Taking A Screenshot...");
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
  text_layer_set_background_color(s_text_layer, GColorWhite);

  s_bitmap_layer = bitmap_layer_create(GRect(0, 0, PBL_DISPLAY_WIDTH, PBL_DISPLAY_WIDTH));
  bitmap_layer_set_compositing_mode(s_bitmap_layer, GCompOpSet);
  bitmap_layer_set_bitmap(s_bitmap_layer, s_bitmap);

  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
  gbitmap_destroy(s_bitmap);
  bitmap_layer_destroy(s_bitmap_layer);
}

static void init(void) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(256, 256);

  s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_MISTER_KUN);
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload,
  });
  window_stack_push(s_main_window, ANIMATE_WINDOW);
}

static void deinit(void) {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}