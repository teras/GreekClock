#pragma once
#define KEY_BLACK 0
#define KEY_FROM 1
#define KEY_TO 2
#define KEY_LANGFORMAL 3

void registerConfig(void);

int getFromTime();

int getToTime();

int getLangFormal();

void updateBack(void);
