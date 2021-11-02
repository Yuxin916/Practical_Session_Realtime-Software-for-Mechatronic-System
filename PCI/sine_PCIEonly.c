// 09September 2005
//******************************************************************************************************
// Performs basic I/O for the Omega PCI-DAS1602 
//
// Demonstration routine to demonstrate pci hardware programming
// Demonstrated the most basic DIO and ADC and DAC functions
// - excludes FIFO and strobed operations 
//
// Note :
//
//			22 Sept 2016 : Restructured to demonstrate Sine wave to DA
//
// G.Seet - 26 August 2005
//******************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <hw/pci.h>
#include <hw/inout.h>
#include <sys/neutrino.h>
#include <sys/mman.h>
#include <math.h>
																
#define 	INTERRUPT	iobase[1] + 4	// Badr1 + 4 - PCIe 32-bit

#define 	ADC_Data	iobase[2] + 0	// Badr2 + 0 - PCIe 16-bit w->srt
#define 	DAC0_Data	iobase[2] + 2	// Badr2 + 2 - PCIe 12-bit
#define 	DAC1_Data	iobase[2] + 4	// Badr2 + 4 - PCIe 12-bit
	
#define 	MUXCHAN		iobase[3] + 0	// Badr3 + 0 - Mux scan/upper lower
#define 	DIO_Data	iobase[3] + 1	// Badr3 + 1 - 8bit DI3 DI2 DI1 DI0
#define	ADC_Stat1		iobase[3] + 2 	// Badr3 + 2 - 1 : MSB
#define 	ADC_Stat2	iobase[3] + 3	// Badr3 + 3 - Alt EOC
#define	CLK_Pace		iobase[3] + 5	// Badr3 + 5 - S/W Pacer : XXXX XX0X
#define 	ADC_Enable	iobase[3] + 6	// Badr3 + 6 - Brst_off Conv_EN:0x01
#define 	ADC_Gain	iobase[3] + 7	// Badr3 + 7 - unipolar 5V : 0x01

#define	DEBUG		1


int badr[5];															// PCI 2.2 assigns 6 IO base addresses

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
int main() {
struct pci_dev_info info;
void *hdl;

uintptr_t iobase[6],dio_in;

uint16_t adc_in;
	
unsigned int i,count;
unsigned short chan;

unsigned int data[100];
float delta,dummy;

printf("\fDemonstration Routine for PCI-DAS 1602\n\n");

memset(&info,0,sizeof(info));
if(pci_attach(0)<0) {
  perror("pci_attach");
  exit(EXIT_FAILURE);
  }

																		/* Vendor and Device ID */
info.VendorId=0x1307;
info.DeviceId=0x01;

if ((hdl=pci_attach_device(0, PCI_SHARE|PCI_INIT_ALL, 0, &info))==0) {
  perror("pci_attach_device");
  exit(EXIT_FAILURE);
  }
  																		// Determine assigned BADRn IO addresses for PCI-DAS1602			

printf("\nDAS 1602 Base addresses:\n\n");
for(i=0;i<5;i++) {
  badr[i]=PCI_IO_ADDR(info.CpuBaseAddress[i]);
  printf("Badr[%d] : %x\n", i, badr[i]);
  }
 
printf("\nReconfirm Iobase:\n");  						// map I/O base address to user space						
for(i=0;i<5;i++) {												// expect CpuBaseAddress to be the same as iobase for PC
  iobase[i]=mmap_device_io(0x0f,badr[i]);	
  printf("Index %d : Address : %x ", i,badr[i]);
  printf("IOBASE  : %x \n",iobase[i]);
  }													
																		// Modify thread control privity
if(ThreadCtl(_NTO_TCTL_IO,0)==-1) {
  perror("Thread Control");
  exit(1);
  }																											
   		
//**********************************************************************************************
// Setup waveform array
//**********************************************************************************************
																

delta=(2.0*3.142)/50.0;					// increment
for(i=0;i<50;i++) {
  dummy= ((sinf((float)(i*delta))) + 1.0) * 0x8000 ;
  data[i]= (unsigned) dummy;			// add offset +  scale
 }

//*********************************************************************************************
// Output wave
//*********************************************************************************************

while(1) {
for(i=0;i<50;i++) {
	out16(DA_CTLREG,0x0a23);			// DA Enable, #0, #1, SW 5V unipolar		2/6
   	out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
   	out16(DA_Data,(short) data[i]);																																		
   	out16(DA_CTLREG,0x0a43);			// DA Enable, #1, #1, SW 5V unipolar		2/6
  	out16(DA_FIFOCLR, 0);					// Clear DA FIFO  buffer
	out16(DA_Data,(short) data[i]);																																		
  	}
}
  	
//**********************************************************************************************
// Reset DAC to default : 5v
//**********************************************************************************************

out16(DA_CTLREG,(short)0x0a23);	
out16(DA_FIFOCLR,(short) 0);			
out16(DA_Data, 0x8fff);						// Mid range - Unipolar																											
  
out16(DA_CTLREG,(short)0x0a43);	
out16(DA_FIFOCLR,(short) 0);			
out16(DA_Data, 0x8fff);				
																																						
printf("\n\nExit Demo Program\n");
pci_detach_device(hdl);

//**********************************************************************************************

return(0);
}