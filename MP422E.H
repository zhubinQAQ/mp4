//opem MP422E
extern "C" HANDLE __declspec(dllimport)  __stdcall MP422E_OpenDevice(long dev_num);
//close device
extern "C" long __declspec(dllimport)  __stdcall MP422E_CloseDevice(HANDLE hDevice);


//********************************************
//get board info
//model or type in *bStr
extern "C" long __declspec(dllimport)  __stdcall MP422E_Info(HANDLE hDevice,char *modle);



//----------------------------EEPROM------------------------------------------
//read  32byte , buffer must great 256
extern "C" long __declspec(dllimport)  __stdcall MP422E_EEPROM_Read(HANDLE hDevice,unsigned char *rbuf);

//write length=32
extern "C" long __declspec(dllimport)  __stdcall MP422E_EEPROM_Write(HANDLE hDevice, unsigned char *wbuf);

extern "C" long __declspec(dllimport)  __stdcall MP422E_EEPROM_S_Read(HANDLE hDevice,unsigned char *rbuf);

//write length=32
extern "C" long __declspec(dllimport)  __stdcall MP422E_EEPROM_S_Write(HANDLE hDevice, unsigned char *wbuf);


//---------------------------------------------------------------------------------------------
//AD
//sammode=0 normal scan AD mode/ =1 SH -burst mode
//trsl: =0 soft /=1 trig
//trpol:=0 rising edge / =1 falling edge
//clksl=0 inner adclk / =1 out clk
//clkpol=0 rsining edge / =1 falling edge 
//tdata:=50-65535 , AD cycle=0.1uS * tdata
//gain: 0-3 via 10/5/2.5/1.25V, 4-7 via B10/B5/B2.5/B1.25V 
//sidi=1 di input
extern "C" long __declspec(dllimport)  __stdcall MP422E_AD(HANDLE hDevice,
														   long stch,long endch,long gain,long sidi,
														   long sammode,long trsl,long trpol,long clksl,long clkpol,
														   long tdata);

extern "C" long __declspec(dllimport)  __stdcall MP422E_CAL(HANDLE hDevice);

//------------------------------------------------------------------------------------------
//polling if end of ad
// if fifo full return -1, else return read length, max length=512K word or =524288 words
// *fdata's length must >=524288
// return -1, fifo error of full, >=0 real read data length
//rdlen: user set data length to readm addata's size must > rdlen
//       rdlen>= MP422E_Poll's return value
extern "C" long __declspec(dllimport)  __stdcall MP422E_Read(HANDLE hDevice,long rdlen,long *addata);

//polling state 
//<0 fifo over error
//>=0 sam data length for user read
extern "C" long __declspec(dllimport)  __stdcall MP422E_Poll(HANDLE hDevice);



//stop
extern "C" long __declspec(dllimport)  __stdcall MP422E_StopAD(HANDLE hDevice1);


//convert data to voltage at mV
extern "C" double __declspec(dllimport) __stdcall MP422E_ADV(long adg,long addata);


//DI
extern "C" long __declspec(dllimport)  __stdcall MP422E_DI(HANDLE hDevice1);
//DO
extern "C" long __declspec(dllimport)  __stdcall MP422E_DO(HANDLE hDevice1,long data);

//-----------------------------------------------------------------------------------------------------
//DA
//set da out range
//g=0 10V / =1 B10v
extern "C" long __declspec(dllimport)  __stdcall MP422E_DA_Mode(HANDLE hDevice,long dag0,long dag1);
//set da data , data=0-4095
 //dach=0,1 sel DA channel 0,1
extern "C" long __declspec(dllimport)  __stdcall MP422E_DA(HANDLE hDevice,long dach,long dadata);



//---------------------------------------------------------------------------------------------------------
//run or start cnt ch
//cdata: initla cnt data
extern "C" long __declspec(dllimport)  __stdcall MP422E_CNT_Run(HANDLE hDevice, long cntch, long cdata);
//read data: cnt data cdata / timer data tdata
//return: <0 error / =0 cnt not over / =1 cnt over
extern "C" long __declspec(dllimport)  __stdcall MP422E_CNT_Read(HANDLE hDevice, long cntch,long *cdata, long *tdata);

///start pout and set out eb
//pch =0,1
//pmode: 0 PWM mode / 1 single pulse mode
//PWM mode: pdata0 cycle / padat1 high wideth
extern "C" long __declspec(dllimport)  __stdcall MP422E_PRun(HANDLE hDevice,long pch, long pmode,long pdata0, long pdata1);
//return out state, =1 out =1 / =0 out =0
extern "C" long __declspec(dllimport)  __stdcall MP422E_PState(HANDLE hDevice,long pch);
//stop pch and enable DO ch recover
extern "C" long __declspec(dllimport)  __stdcall MP422E_PEnd(HANDLE hDevice,long pch);
//set pulse out  data
extern "C" long __declspec(dllexport)  __stdcall MP422E_PSetData(HANDLE hDevice,long pch,long pdata0, long pdata1);





///////////////////////////////////////////////////////////////////////////////////////////////////////////
//profetional function
//read 8bit in by adress=adr
extern "C" long __declspec(dllimport)  __stdcall MP422E_inb(HANDLE hDevice,long adr);
//write 8bit data by adress=adr
extern "C" long __declspec(dllimport)  __stdcall MP422E_outb(HANDLE hDevice1,long adr,long data);


extern "C" long __declspec(dllimport)  __stdcall MP422E_BulkRead(HANDLE hDevice1,unsigned char *bdata,long rdl);
extern "C" long __declspec(dllimport)  __stdcall MP422E_ResetUSB(HANDLE hDevice1);

extern "C" long __declspec(dllimport)  __stdcall MP422E_RDCAL(HANDLE hDevice,unsigned long *caldata);
extern "C" long __declspec(dllimport)  __stdcall MP422E_WRCAL(HANDLE hDevice,unsigned long *caldata);
extern "C" long __declspec(dllimport)  __stdcall MP422E_WRUBUF(HANDLE hDevice,unsigned char *caldata);
extern "C" long __declspec(dllimport)  __stdcall MP422E_RDUBUF(HANDLE hDevice,unsigned char *caldata);

extern "C" long __declspec(dllimport) __stdcall MP422E_KFIFORD(HANDLE hDevice, long rdl , UCHAR *mdata);
extern "C" long __declspec(dllimport) __stdcall MP422E_KFIFOWR(HANDLE hDevice, long wl , UCHAR *mdata);
extern "C" long __declspec(dllimport) __stdcall MP422E_KFIFOPOLL(HANDLE hDevice, long *kfifolen, long *kfifoff, long *kfifost);
extern "C" long __declspec(dllimport) __stdcall MP422E_KFIFORESET(HANDLE hDevice);

extern "C" long __declspec(dllimport) __stdcall MP422E_EEPROM_CWR(HANDLE hDevice,long adr, long len , unsigned char *wdata);
extern "C" long __declspec(dllimport) __stdcall MP422E_EEPROM_CRD(HANDLE hDevice,long adr, long len , unsigned char *rdata);
