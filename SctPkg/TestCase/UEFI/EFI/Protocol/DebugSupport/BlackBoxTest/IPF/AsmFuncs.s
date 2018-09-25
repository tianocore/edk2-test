// @file
// 
//  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
//  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
// 
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at 
//  http://opensource.org/licenses/bsd-license.php
// 
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
// 
//
//
//
//  Name:
//      SoftwareBreak
//
//  Description:
//      C callable function to generate a software break
//

        .global         SoftwareBreak
        .proc           SoftwareBreak
SoftwareBreak::
        break        0;;
        {
            .mib
            nop.m   0
            nop.i   0
            nop.b   0
        }
        br.ret.sptk.many    b0

        .endp           SoftwareBreak

