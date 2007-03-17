#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define HISTO_WIDTH     128
#define HISTO_HEIGHT    50

void histogram_process();
void histogram_stop();
void histogram_restart();

extern unsigned char histogram[HISTO_WIDTH];
extern long exposition_thresh;
extern long under_exposed;
extern long over_exposed;

#endif
