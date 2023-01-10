/**
 * @file per_eth_f4.c
 *
 * This file contains the Ethernet peripheral interface (ETH)
 *
 * Copyright (c) 2023 admaunaloa admaunaloa@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "per_eth_f4.h"

static uint32_t Macpmtcsr; // Latch for wakeup flags
static uint32_t Dmamfc; // Latch for missed frame counter
static uint16_t Dmamfa; // Latch for Missed frames by the application
static bool Dmaomfc; // Latch for Overflow bit for missed frame counter
static bool Dmaofoc; // Latch for Overflow bit for FIFO overflow counter

/// ETH Macpmtcsr update
uint32_t per_eth_mac_macpmtcsr(const per_eth_t* const eth)
{
   uint32_t val = per_bit_rw32_reg(&eth->PerMac->Macpmtcsr); // Fetch
   val |= Macpmtcsr; // Add latched rc_r bits
   Macpmtcsr = val & PER_ETH_PMTCSR_RC_R_MASK; // Update latch

   return val;
}

/// ETH Magic packet received
bool per_eth_mac_wfr(const per_eth_t* const eth)
{
   bool val = (per_eth_mac_macpmtcsr(eth) & PER_ETH_PMTCSR_WFR) != 0;
   Macpmtcsr &= ~PER_ETH_PMTCSR_WFR; // Clear the latch

   return val;
}

/// ETH Magic Packet received
bool per_eth_mac_mpr(const per_eth_t* const eth)
{
   bool val = (per_eth_mac_macpmtcsr(eth) & PER_ETH_PMTCSR_MPR) != 0;
   Macpmtcsr &= ~PER_ETH_PMTCSR_MPR; // Clear the latch

   return val;
}

/// ETH Fetch and latch the MFBOCR
static void per_eth_dma_mfbocr_latch(const per_eth_t* const eth)
{
   uint32_t val = per_bit_r32_reg(&eth->PerDma->Mfbocr); // Fetch and clear

   Dmamfc += val & PER_ETH_DMA_MFBOCR_MFC_MASK;
   Dmaomfc |= (val & PER_ETH_DMA_MFBOCR_OMFC_MASK) != 0;
   Dmamfa += (uint16_t)((val >> PER_ETH_DMA_MFBOCR_MFA_SHIFT) & PER_ETH_DMA_MFBOCR_MFA_MASK);
   Dmaofoc |= (val & PER_ETH_DMA_MFBOCR_OFOC_MASK) != 0;
}

/// ETH Missed frames by the controller
uint32_t per_eth_dma_mfc(const per_eth_t* const eth)
{
   per_eth_dma_mfbocr_latch(eth);
   
   uint32_t val = Dmamfc;
   Dmamfc = 0; // clear
 
   return val;
}

/// ETH Overflow bit for missed frame counter
bool per_eth_dma_omfc(const per_eth_t* const eth)
{
   per_eth_dma_mfbocr_latch(eth);
   
   bool val = Dmaomfc;
   Dmaomfc = false;

   return val;
}

/// ETH Missed frames by the application
uint16_t per_eth_dma_mfa(const per_eth_t* const eth)
{
  per_eth_dma_mfbocr_latch(eth);
   
   uint16_t val = Dmamfa;
   Dmamfa = 0; // clear
 
   return val;
}

/// ETH Overflow bit for FIFO overflow counter
bool per_eth_dma_ofoc(const per_eth_t* const eth)
{
   per_eth_dma_mfbocr_latch(eth);
   
   bool val = Dmaofoc;
   Dmaofoc = false;

   return val;
}
