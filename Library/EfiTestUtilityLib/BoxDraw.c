/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  BoxDraw.c

Abstract:

  Lib functions to support Box Draw Unicode code pages.

--*/

#include "lib.h"

typedef struct {
    CHAR16  Unicode;
    CHAR8   PcAnsi;
    CHAR8   Ascii;
} UNICODE_TO_CHAR;


//
// This list is used to define the valid extend chars.
// It also provides a mapping from Unicode to PCANSI or
// ASCII. The ASCII mapping we just made up.
//
//

STATIC UNICODE_TO_CHAR UnicodeToPcAnsiOrAscii[] = {
    BOXDRAW_HORIZONTAL,                 0xc4, L'-',
    BOXDRAW_VERTICAL,                   0xb3, L'|',
    BOXDRAW_DOWN_RIGHT,                 0xda, L'/',
    BOXDRAW_DOWN_LEFT,                  0xbf, L'\\',
    BOXDRAW_UP_RIGHT,                   0xc0, L'\\',
    BOXDRAW_UP_LEFT,                    0xd9, L'/',
    BOXDRAW_VERTICAL_RIGHT,             0xc3, L'|',
    BOXDRAW_VERTICAL_LEFT,              0xb4, L'|',
    BOXDRAW_DOWN_HORIZONTAL,            0xc2, L'+',
    BOXDRAW_UP_HORIZONTAL,              0xc1, L'+',
    BOXDRAW_VERTICAL_HORIZONTAL,        0xc5, L'+',
    BOXDRAW_DOUBLE_HORIZONTAL,          0xcd, L'-',
    BOXDRAW_DOUBLE_VERTICAL,            0xba, L'|',
    BOXDRAW_DOWN_RIGHT_DOUBLE,          0xd5, L'/',
    BOXDRAW_DOWN_DOUBLE_RIGHT,          0xd6, L'/',
    BOXDRAW_DOUBLE_DOWN_RIGHT,          0xc9, L'/',
    BOXDRAW_DOWN_LEFT_DOUBLE,           0xb8, L'\\',
    BOXDRAW_DOWN_DOUBLE_LEFT,           0xb7, L'\\',
    BOXDRAW_DOUBLE_DOWN_LEFT,           0xbb, L'\\',
    BOXDRAW_UP_RIGHT_DOUBLE,            0xd4, L'\\',
    BOXDRAW_UP_DOUBLE_RIGHT,            0xd3, L'\\',
    BOXDRAW_DOUBLE_UP_RIGHT,            0xc8, L'\\',
    BOXDRAW_UP_LEFT_DOUBLE,             0xbe, L'/',
    BOXDRAW_UP_DOUBLE_LEFT,             0xbd, L'/',
    BOXDRAW_DOUBLE_UP_LEFT,             0xbc, L'/',
    BOXDRAW_VERTICAL_RIGHT_DOUBLE,      0xc6, L'|',
    BOXDRAW_VERTICAL_DOUBLE_RIGHT,      0xc7, L'|',
    BOXDRAW_DOUBLE_VERTICAL_RIGHT,      0xcc, L'|',
    BOXDRAW_VERTICAL_LEFT_DOUBLE,       0xb5, L'|',
    BOXDRAW_VERTICAL_DOUBLE_LEFT,       0xb6, L'|',
    BOXDRAW_DOUBLE_VERTICAL_LEFT,       0xb9, L'|',
    BOXDRAW_DOWN_HORIZONTAL_DOUBLE,     0xd1, L'+',
    BOXDRAW_DOWN_DOUBLE_HORIZONTAL,     0xd2, L'+',
    BOXDRAW_DOUBLE_DOWN_HORIZONTAL,     0xcb, L'+',
    BOXDRAW_UP_HORIZONTAL_DOUBLE,       0xcf, L'+',
    BOXDRAW_UP_DOUBLE_HORIZONTAL,       0xd0, L'+',
    BOXDRAW_DOUBLE_UP_HORIZONTAL,       0xca, L'+',
    BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE, 0xd8, L'+',
    BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL, 0xd7, L'+',
    BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL, 0xce, L'+',

    BLOCKELEMENT_FULL_BLOCK,            0xdb, L'*',
    BLOCKELEMENT_LIGHT_SHADE,           0xb0, L'+',

    GEOMETRICSHAPE_UP_TRIANGLE,         0x1e, L'^',
    GEOMETRICSHAPE_RIGHT_TRIANGLE,      0x10, L'>',
    GEOMETRICSHAPE_DOWN_TRIANGLE,       0x1f, L'v',
    GEOMETRICSHAPE_LEFT_TRIANGLE,       0x11, L'<',

    ARROW_LEFT,                         0x3c, L'<',

    ARROW_UP,                           0x18, L'^',

    ARROW_RIGHT,                        0x3e, L'>',

    ARROW_DOWN,                         0x19, L'v',

    0x0000, 0x00
};


BOOLEAN
LibIsValidTextGraphics (
    IN  CHAR16  Graphic,
    OUT CHAR8   *PcAnsi,    OPTIONAL
    OUT CHAR8   *Ascii      OPTIONAL
    )
/*++

Routine Description:

    Detects if a Unicode char is for Box Drawing text graphics.

Arguments:

    Grphic  - Unicode char to test.

    PcAnsi  - Optional pointer to return PCANSI equivalent of Graphic.

    Asci    - Optional pointer to return Ascii equivalent of Graphic.

Returns:

    TRUE if Gpaphic is a supported Unicode Box Drawing character.

--*/{
    UNICODE_TO_CHAR     *Table;

    if ((((Graphic & 0xff00) != 0x2500) && ((Graphic & 0xff00) != 0x2100))) {

        //
        // Unicode drawing code charts are all in the 0x25xx range,
        //  arrows are 0x21xx
        //
        return FALSE;
    }

    for (Table = UnicodeToPcAnsiOrAscii; Table->Unicode != 0x0000; Table++) {
        if (Graphic == Table->Unicode) {
            if (PcAnsi) {
                *PcAnsi = Table->PcAnsi;
            }
            if (Ascii) {
                *Ascii = Table->Ascii;
            }
            return TRUE;
        }
    }
    return FALSE;
}

BOOLEAN
IsValidAscii (
    IN  CHAR16  Ascii
    )
{
    if ((Ascii >= 0x20) && (Ascii <= 0x7f)) {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN
IsValidEfiCntlChar (
    IN  CHAR16  c
    )
{
    if (c == CHAR_NULL || c == CHAR_BACKSPACE || c == CHAR_LINEFEED || c == CHAR_CARRIAGE_RETURN) {
        return TRUE;
    }
    return FALSE;
}

