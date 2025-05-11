#include "../include/vga.h"

uint16 column = 0;
uint16 line = 0;
uint16* const vga = (uint16* const)0xb8000;
const uint16 defaultColor = (COLOR8_WHITE << 8) | (COLOR8_BLACK << 12);
uint16 currentColor;

void Reset(){
       line = 0;
       column = 0;
       currentColor = defaultColor;

       for(uint16 y = 0; y < height; y++){
              for(uint16 x = 0; x < width; x++){
                     vga[y * width + x] = ' ' | defaultColor;
              }
       }
}

void newLine(){
       if(line < height - 1){
              line++;
              column = 0;
       }else{
              scrollUp();
              column = 0;
       }
}

void scrollUp(){
       for(uint16 y = 0; y < height; y++){
              for(uint16 x = 0; x < width; x++){
                     vga[(y-1) * width + x] = vga[y*width+x];
              }
       }

       for(uint16 x = 0; x < width; x++){
              vga[(height-1) * width + x] = ' ' | currentColor;
       }
}

void print(const char* s){
       while(*s){
              switch(*s){
                     case '\n':
                            newLine();
                            break;
                     case '\r':
                            column = 0;
                            break;
                     case '\t':
                            if(column == width){
                                   newLine();
                            }
                            uint16 tabLen = 4 - (column % 4);
                            while(tabLen != 0){
                                   vga[line * width + (column++)] = ' ' | currentColor;
                                   tabLen--;
                            }
                            break;
                     default:
                            if(column == width){
                                   newLine();
                            }

                            vga[line * width + (column++)] = *s | currentColor;
                            break;
              }
              s++;
       }
}