#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define HISTO_WIDTH         128
#define HISTO_HEIGHT        50

#define HISTO_MODE_LINEAR   0
#define HISTO_MODE_LOG      1

#define HISTO_R             0
#define HISTO_G             1
#define HISTO_B             2
#define HISTO_RGB           3
#define HISTO_Y             4


void histogram_process();
void histogram_stop();
void histogram_restart();
extern void histogram_set_mode(unsigned int mode);
extern void histogram_set_main(unsigned int main);

extern unsigned char histogram[5][HISTO_WIDTH];
extern long exposition_thresh;
extern long under_exposed;
extern long over_exposed;
extern long histo_magnification;

#endif
