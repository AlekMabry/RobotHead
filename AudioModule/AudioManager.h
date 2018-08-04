#include "pocketsphinx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

#ifndef MODELDIR
#define MODELDIR "/usr/local/share/pocketsphinx/model/"
#endif

class AudioManager {
  ps_decoder_t *ps;
  cmd_ln_t *config;
  FILE *fh;
  char const *hyp, *uttid;
  int16 buf[512];
  int rv;
  int32 score;

  //private:
    //MicrophoneHot();

  public:
    AudioManager();
    void DecodeBuffer();
};
