#include <iostm8s003k3.h>
#include <string.h>
#include "lcd2x16.h"
#include "DataType.h"

int main( void ){
  LCD_Init();
  //LCDDisableBackLigth();
  LCDEnableBackLigth();
  LCDWriteString(0,1,"   TE AMO YISS  ");
  LCDWriteString(0,2,"  ERES MI VIDA  ");
  while(1){
  }
}
