/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),
                             zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2010  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2010  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2010  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2010  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/


#include "snes9x.h"
#include "memmap.h"
#include "fxinst.h"
#include "fxemu.h"

void S9xInitSuperFX (void)
{
	memset((uint8 *) &GSU, 0, sizeof(struct FxRegs_s));
}

static void fx_readRegisterSpace (void)
{
	static uint32	avHeight[] = { 128, 160, 192, 256 };
	static uint32	avMult[]   = {  16,  32,  32,  64 };

	uint8	*p;
	int		n;

	GSU.vErrorCode = 0;

	// Update R0-R15
	p = GSU.pvRegisters;
	for (int i = 0; i < 16; i++)
	{
		GSU.avReg[i] = *p++;
		GSU.avReg[i] += ((uint32) (*p++)) << 8;
	}

	// Update other registers
	p = GSU.pvRegisters;
	GSU.vStatusReg     =  (uint32) p[GSU_SFR];
	GSU.vStatusReg    |= ((uint32) p[GSU_SFR + 1]) << 8;
	GSU.vPrgBankReg    =  (uint32) p[GSU_PBR];
	GSU.vRomBankReg    =  (uint32) p[GSU_ROMBR];
	GSU.vRamBankReg    = ((uint32) p[GSU_RAMBR]) & (FX_RAM_BANKS - 1);
	GSU.vCacheBaseReg  =  (uint32) p[GSU_CBR];
	GSU.vCacheBaseReg |= ((uint32) p[GSU_CBR + 1]) << 8;

	// Update status register variables
	GSU.vZero     = !(GSU.vStatusReg & FLG_Z);
	GSU.vSign     =  (GSU.vStatusReg & FLG_S)  << 12;
	GSU.vOverflow =  (GSU.vStatusReg & FLG_OV) << 16;
	GSU.vCarry    =  (GSU.vStatusReg & FLG_CY) >> 2;

	// Set bank pointers
	GSU.pvRamBank = GSU.apvRamBank[GSU.vRamBankReg & 0x3];
	GSU.pvRomBank = GSU.apvRomBank[GSU.vRomBankReg];
	GSU.pvPrgBank = GSU.apvRomBank[GSU.vPrgBankReg];

	// Set screen pointers
	GSU.pvScreenBase = &GSU.pvRam[USEX8(p[GSU_SCBR]) << 10];
	n  =  (int) (!!(p[GSU_SCMR] & 0x04));
	n |= ((int) (!!(p[GSU_SCMR] & 0x20))) << 1;
	GSU.vScreenHeight = GSU.vScreenRealHeight = avHeight[n];
	GSU.vMode = p[GSU_SCMR] & 0x03;

	if (n == 3)
		GSU.vScreenSize = (256 / 8) * (256 / 8) * 32;
	else
		GSU.vScreenSize = (GSU.vScreenHeight / 8) * (256 / 8) * avMult[GSU.vMode];

	if (GSU.vPlotOptionReg & 0x10) // OBJ Mode (for drawing into sprites)
		GSU.vScreenHeight = 256;

	if (GSU.pvScreenBase + GSU.vScreenSize > GSU.pvRam + (GSU.nRamBanks * 65536))
		GSU.pvScreenBase = GSU.pvRam + (GSU.nRamBanks * 65536) - GSU.vScreenSize;

	fx_OpcodeTable[0x04c] = fx_PlotTable[GSU.vMode];
	fx_OpcodeTable[0x14c] = fx_PlotTable[GSU.vMode + 5];
	fx_OpcodeTable[0x24c] = fx_PlotTable[GSU.vMode];
	fx_OpcodeTable[0x34c] = fx_PlotTable[GSU.vMode + 5];

	fx_computeScreenPointers();

	//fx_backupCache();
}

static void FxReset (struct FxInfo_s *psFxInfo)
{
	// Clear all internal variables
	memset((uint8 *) &GSU, 0, sizeof(struct FxRegs_s));

	// Set default registers
	GSU.pvSreg = GSU.pvDreg = &R0;

	// Set RAM and ROM pointers
	GSU.pvRegisters       = psFxInfo->pvRegisters;
	GSU.nRamBanks         = psFxInfo->nRamBanks;
	GSU.pvRam             = psFxInfo->pvRam;
	GSU.nRomBanks         = psFxInfo->nRomBanks;
	GSU.pvRom             = psFxInfo->pvRom;
	GSU.vPrevScreenHeight = ~0;
	GSU.vPrevMode         = ~0;

	// The GSU can't access more than 2mb (16mbits)
	if (GSU.nRomBanks > 0x20)
		GSU.nRomBanks = 0x20;

	// Clear FxChip register space
	memset(GSU.pvRegisters, 0, 0x300);

	// Set FxChip version Number
	GSU.pvRegisters[0x3b] = 0;

	// Make ROM bank table
	for (int i = 0; i < 256; i++)
	{
		uint32	b = i & 0x7f;

		if (b >= 0x40)
		{
			if (GSU.nRomBanks > 1)
				b %= GSU.nRomBanks;
			else
				b &= 1;

			GSU.apvRomBank[i] = &GSU.pvRom[b << 16];
		}
		else
		{
			b %= GSU.nRomBanks * 2;
			GSU.apvRomBank[i] = &GSU.pvRom[(b << 16) + 0x200000];
		}
	}

	// Make RAM bank table
	for (int i = 0; i < 4; i++)
	{
		GSU.apvRamBank[i] = &GSU.pvRam[(i % GSU.nRamBanks) << 16];
		GSU.apvRomBank[0x70 + i] = GSU.apvRamBank[i];
	}

	// Start with a nop in the pipe
	GSU.vPipe = 0x01;

	// Set pointer to GSU cache
	GSU.pvCache = &GSU.pvRegisters[0x100];

	fx_readRegisterSpace();
}

void S9xResetSuperFX (void)
{
	// FIXME: Snes9x can't execute CPU and SuperFX at a time. Don't ask me what is 0.417 :P
	float frames_per_second = 60.0f;
	if (Settings.PAL)
		frames_per_second = 50.0f;

	SuperFX.speedPerLine = (uint32) (0.417 * 10.5e6 * ((1.0f / frames_per_second) / ((float) (Timings.V_Max))));
	SuperFX.oneLineDone = FALSE;
	SuperFX.vFlags = 0;
	FxReset(&SuperFX);
}

// Update RamBankReg and RAM Bank pointer
#define FX_UPDATE_RAM_BANK(byte) \
	/* Update BankReg and Bank pointer */ \
	GSU.vRamBankReg = (uint32) byte & (FX_RAM_BANKS - 1); \
	GSU.pvRamBank = GSU.apvRamBank[byte & 0x3];

// SCBR write seen. We need to update our cached screen pointers
#define fx_dirtySCBR() GSU.vSCBRDirty = TRUE;

// Write access to the cache
#define FX_CACHE_WRITE_ACCESS(vAddress) \
	if ((vAddress & 0x00f) == 0x00f) \
		GSU.vCacheFlags |= 1 << ((vAddress & 0x1f0) >> 4);

#define FX_FLUSH_CACHE() \
	GSU.vCacheFlags = 0; \
	GSU.vCacheBaseReg = 0; \
	GSU.bCacheActive = FALSE; \
	/* GSU.vPipe = 0x1; */

void S9xSetSuperFX (uint8 byte, uint16 address)
{
	switch (address)
	{
		case 0x3030:
			if ((Memory.FillRAM[0x3030] ^ byte) & FLG_G)
			{
				Memory.FillRAM[0x3030] = byte;
				if (byte & FLG_G)
				{
					if (!SuperFX.oneLineDone)
					{
						S9xSuperFXExec();
						SuperFX.oneLineDone = TRUE;
					}
				}
				else
				{
					FX_FLUSH_CACHE();
				}
			}
			else
				Memory.FillRAM[0x3030] = byte;

			break;

		case 0x3031:
			Memory.FillRAM[0x3031] = byte;
			break;

		case 0x3033:
			Memory.FillRAM[0x3033] = byte;
			break;

		case 0x3034:
			Memory.FillRAM[0x3034] = byte & 0x7f;
			break;

		case 0x3036:
			Memory.FillRAM[0x3036] = byte & 0x7f;
			break;

		case 0x3037:
			Memory.FillRAM[0x3037] = byte;
			break;

		case 0x3038:
			Memory.FillRAM[0x3038] = byte;
			fx_dirtySCBR();
			break;

		case 0x3039:
			Memory.FillRAM[0x3039] = byte;
			break;

		case 0x303a:
			Memory.FillRAM[0x303a] = byte;
			break;

		case 0x303b:
			break;

		case 0x303c:
			Memory.FillRAM[0x303c] = byte;
			FX_UPDATE_RAM_BANK(byte);
			break;

		case 0x303f:
			Memory.FillRAM[0x303f] = byte;
			break;

		case 0x301f:
			Memory.FillRAM[0x301f] = byte;
			Memory.FillRAM[0x3000 + GSU_SFR] |= FLG_G;
			if (!SuperFX.oneLineDone)
			{
				S9xSuperFXExec();
				SuperFX.oneLineDone = TRUE;
			}

			break;

		default:
			Memory.FillRAM[address] = byte;
			if (address >= 0x3100)
			{
				FX_CACHE_WRITE_ACCESS(address);
			}

			break;
	}
}

uint8 S9xGetSuperFX (uint16 address)
{
	uint8	byte;

	byte = Memory.FillRAM[address];
	if (address == 0x3031)
	{
		S9xClearIRQ(GSU_IRQ_SOURCE);
		Memory.FillRAM[0x3031] = byte & 0x7f;
	}

	return (byte);
}

static bool8 fx_checkStartAddress (void)
{
	// Check if we start inside the cache
	if (GSU.bCacheActive && R15 >= GSU.vCacheBaseReg && R15 < (GSU.vCacheBaseReg + 512))
		return (TRUE);

	// Check if we're in RAM and the RAN flag is not set
	bool condition1 = GSU.vPrgBankReg >= 0x60 && GSU.vPrgBankReg <= 0x6f;
	bool condition2 = GSU.vPrgBankReg >= 0x74;
	bool condition3 = GSU.vPrgBankReg >= 0x70 && GSU.vPrgBankReg <= 0x73 && !(SCMR & 8);
	bool condition4 = !(SCMR & 16);

	if (condition1 | condition2 | condition3 | condition4)
		return (FALSE);

	return (TRUE);
}

static void fx_writeRegisterSpace (void)
{
	uint8	*p;

	p = GSU.pvRegisters;
	for (int i = 0; i < 16; i++)
	{
		*p++ = (uint8)  GSU.avReg[i];
		*p++ = (uint8) (GSU.avReg[i] >> 8);
	}

	// Update status register
	if (USEX16(GSU.vZero) == 0)
		SF(Z);
	else
		CF(Z);

	if (GSU.vSign & 0x8000)
		SF(S);
	else
		CF(S);

	if (GSU.vOverflow >= 0x8000 || GSU.vOverflow < -0x8000)
		SF(OV);
	else
		CF(OV);

	if (GSU.vCarry)
		SF(CY);
	else
		CF(CY);

	p = GSU.pvRegisters;
	p[GSU_SFR]     = (uint8)  GSU.vStatusReg;
	p[GSU_SFR + 1] = (uint8) (GSU.vStatusReg >> 8);
	p[GSU_PBR]     = (uint8)  GSU.vPrgBankReg;
	p[GSU_ROMBR]   = (uint8)  GSU.vRomBankReg;
	p[GSU_RAMBR]   = (uint8)  GSU.vRamBankReg;
	p[GSU_CBR]     = (uint8)  GSU.vCacheBaseReg;
	p[GSU_CBR + 1] = (uint8) (GSU.vCacheBaseReg >> 8);
}

void S9xSuperFXExec (void)
{
	if ((Memory.FillRAM[0x3000 + GSU_SFR] & FLG_G) && (Memory.FillRAM[0x3000 + GSU_SCMR] & 0x18) == 0x18)
	{
		// EMULATE FX CHIP
		// Execute until the next stop instruction
		uint32 nInstructions = (Memory.FillRAM[0x3000 + GSU_CLSR] & 1) ? SuperFX.speedPerLine * 2 : SuperFX.speedPerLine;

		// Read registers and initialize GSU session
		fx_readRegisterSpace();

		// Check if the start address is valid
		if (fx_checkStartAddress())
		{
			// Execute GSU session
			CF(IRQ);

			fx_run(nInstructions);

			// Store GSU registers
			fx_writeRegisterSpace();
		}
		else
		{
			CF(G);
			fx_writeRegisterSpace();
		}
		// EOF EMULATE FX CHIP

		uint16 GSUStatus = Memory.FillRAM[0x3000 + GSU_SFR] | (Memory.FillRAM[0x3000 + GSU_SFR + 1] << 8);
		if ((GSUStatus & (FLG_G | FLG_IRQ)) == FLG_IRQ)
			S9xSetIRQ(GSU_IRQ_SOURCE);
	}
}

void fx_computeScreenPointers (void)
{
	if (GSU.vMode != GSU.vPrevMode || GSU.vPrevScreenHeight != GSU.vScreenHeight || GSU.vSCBRDirty)
	{
		GSU.vSCBRDirty = FALSE;

		// Make a list of pointers to the start of each screen column
		uint8* pvScreenBase = GSU.pvScreenBase;
		uint32 vmode = GSU.vMode;
		int32 condition = vmode - 2;
		int32 mask = (condition | -condition) >> 31;
		int32 result = (vmode & mask) | (3 & ~mask);
		uint32 screenheight = GSU.vScreenHeight;
		uint32 incrementvalue = screenheight+screenheight;
		vmode = result;
		vmode++;
		switch (screenheight)
		{
			case 128:
			case 160:
			case 192:
				uint32 vmode_mul = 0;
				for(uint32 i = 0; i < 32; i++)
				{
					GSU.x[i] = incrementvalue * i * vmode;
					GSU.apvScreen[i] = pvScreenBase + (vmode_mul * vmode);
					vmode_mul += 16;
				}
				break;
			case 256:
				const uint32 mul_8192 = vmode << 13;
				const uint32 mul_4096 = vmode << 12;
				uint32 apv_multiply = 0;
				uint32 gsu_x_multiply = 0;
				for(int i = 0; i < 16; i++)
				{
					GSU.apvScreen[i] = GSU.apvScreen[i+16] = pvScreenBase + (apv_multiply * vmode);
					GSU.x[i] = GSU.x[i+16] = (gsu_x_multiply * vmode);
					GSU.apvScreen[i+16] += mul_8192;
					GSU.x[i+16] += mul_4096;
					apv_multiply += 256;
					gsu_x_multiply += 16;
				}
				break;
		}

		GSU.vPrevMode = GSU.vMode;
		GSU.vPrevScreenHeight = GSU.vScreenHeight;
	}
}

void fx_flushCache (void)
{
	GSU.vCacheFlags = 0;
	GSU.bCacheActive = FALSE;
}
