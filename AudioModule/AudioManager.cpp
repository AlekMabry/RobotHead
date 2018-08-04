#include "AudioManager.h"

AudioManager::AudioManager() {
  config = cmd_ln_init(NULL, ps_args(), TRUE, "-hmm", MODELDIR "/en-us/en-us",
                                              "-lm", MODELDIR "/en-us/en-us.lm.bin",
                                              "-dict", MODELDIR "/en-us/cmudict-en-us.dict", NULL);

  if (config == NULL) {
    fprintf(stderr, "Failed to create a PocketSphinx config object, see log for details\n");
  }

  ps = ps_init(config);
  if (ps == NULL) {
    fprintf(stderr, "Failed to create a PocketSphinx recognizer, see log for details\n");
  }
}

void AudioManager::DecodeBuffer() {
  fh = fopen("goforward.raw", "rb");
  if (fh == NULL) {
    fprintf(stderr, "Unable to open PocketSphinx input buffer\n");
  }

  rv = ps_start_utt(ps);

  while (!feof(fh)) {
    size_t nsamp;
    nsamp = fread(buf, 2, 512, fh);
    rv = ps_process_raw(ps, buf, nsamp, FALSE, FALSE);
  }

  rv = ps_end_utt(ps);
  hyp = ps_get_hyp(ps, &score);
  printf("Recognized: %s\n", hyp);

  fclose(fh);
  ps_free(ps);
  cmd_ln_free_r(config);
}
