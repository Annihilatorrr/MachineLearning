#pragma once
void mutableToUpper(char* text);
void mutableToLower(char* text);
void mutableFilter(char* text);
void mutableDeleteSpace(char* text);
bool isNumber(char* text);
bool isLetter(char* text);
void mutableEncoderCesar(char* text, int step);
void mutableDecoderCesar(char* text, int step);
void mutableEncoderXor(char* text, char* key);
void mutableDecoderXor(char* text, char* key);