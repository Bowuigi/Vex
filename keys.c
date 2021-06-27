/* A simple yet very useful key handler */
#ifndef KEYS_C
#define KEYS_C

struct key_trigger {
	int keycode;
	void (*trigger)(void *data);
};

void handle_keys(struct key_trigger keys,int keys_length) {
  for(int i = 0; i < keys_length; i++) {
    if(c == keys[i].keycode) {
      keys[i].trigger( /* data */);
    }
  }
}
#endif /* KEYS_C */

