#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
#
# Tcp6 Service Binding : CreateChild and DestroyChild
#
set Tcp6CreateChildConf1AssertionGuid001    FCA64CBC-D99E-42f0-9123-0776D771829F
set Tcp6DestroyChildConf1AssertionGuid001   991825B0-D208-429b-98C9-4046E5400015
set Tcp6CreateDestroyChildFunc1AssertionGuid001   7BFD1B83-519B-4bb4-9A44-124ADC43DC56
set Tcp6CreateDestroyChildFunc1AssertionGuid002   2D22615B-8E8B-44d2-9525-CC5C7E8C8454
set Tcp6CreateDestroyChildFunc1AssertionGuid003   D681C6B2-A4D4-4725-ABE5-EA5B038076BF
set Tcp6CreateDestroyChildFunc1AssertionGuid004   363EAC60-183A-4b57-AE9E-91CCF19539FD

#
# Tcp6 : GetModeData
#
set Tcp6GetModeDataConf1AssertionGuid001  D957C9DE-716A-4f6e-BE7C-66C6E5A02E09
set Tcp6GetModeDataFunc1AssertionGuid001  88A3650B-3AA5-4417-9771-EFA4F6E59A79
set Tcp6GetModeDataFunc1AssertionGuid002  798259AD-BC64-4989-9D8B-8248011A0306
set Tcp6GetModeDataFunc1AssertionGuid003  CCB9B645-F133-4a2c-BC72-C1F1C81505E5
set Tcp6GetModeDataFunc1AssertionGuid004  A9389312-0007-48ec-AB83-26811D0FA797
set Tcp6GetModeDataFunc1AssertionGuid005  8AA7BF92-F01F-4de8-80AB-789F4CAA1649
set Tcp6GetModeDataFunc1AssertionGuid006  92FCC066-F41D-4aad-A602-F84EDE26156D
set Tcp6GetModeDataFunc1AssertionGuid007  B30B7510-3055-427d-854A-79CDB1BBD201


#
# Tcp6 : Configure
#
set Tcp6ConfigureConf1AssertionGuid001   BEBB71C0-E62E-400d-9EAF-3EBFB023B2D6
set Tcp6ConfigureConf2AssertionGuid001   ABFF27D2-86EF-4399-BD90-578E8E0837B4
set Tcp6ConfigureConf3AssertionGuid001   1F16D3CC-5CCF-4177-8BF2-56DE33E0D1F7
set Tcp6ConfigureConf3AssertionGuid002   AE7A2155-192E-4bbb-92C5-AD6D1757BCEB
set Tcp6ConfigureConf4AssertionGuid001   3FEA1F75-CE53-4c85-B8E5-8E5A7C42EB64
set Tcp6ConfigureConf5AssertionGuid001   D8BC8EDB-FE65-4457-B55A-EBD4FADE7B7D
set Tcp6ConfigureFunc1AssertionGuid001   AD816E3D-F3E6-443b-A154-0851A56463B4
set Tcp6ConfigureFunc1AssertionGuid002   85D67600-F53B-4363-9834-B921AAF88F08
set Tcp6ConfigureFunc1AssertionGuid003   51B04624-AA43-4424-A9B4-EE2F2624F52F
set Tcp6ConfigureFunc1AssertionGuid004   3D93A121-DE18-4496-87C2-B7830A92EE0E
set Tcp6ConfigureFunc1AssertionGuid005   9F6AD319-0B1C-40a0-91EE-F94E1AFF9E09
set Tcp6ConfigureFunc1AssertionGuid006   EA63C75A-839F-47b4-AD6C-6FCF5FFD97FC
set Tcp6ConfigureFunc1AssertionGuid007   0275B281-F70E-478d-A620-A328525AD807


#
# Tcp6 : Connect
#
set Tcp6ConnectConf1AssertionGuid001  A092E680-27E9-483b-B3DB-07B8691AB7FC
set Tcp6ConnectConf2AssertionGuid001  1E456F02-7477-4933-84F9-129A8F6480A5
set Tcp6ConnectConf3AssertionGuid001  3B5E2748-1549-465f-9837-67D948DF509F
set Tcp6ConnectConf4AssertionGuid001  73F9316D-BFCB-4c3a-BD75-56B7031D5830
set Tcp6ConnectConf5AssertionGuid001  D15151A5-F62B-4203-8E16-473B4A13D089
set Tcp6ConnectConf5AssertionGuid002  F9DE93E5-4D4D-45ab-950D-C1537551ECB5
set Tcp6ConnectConf6AssertionGuid001  FB14D45A-A20D-4c96-94C7-86C6C1099DA4
set Tcp6ConnectFunc1AssertionGuid001  3CAF2371-32E9-4e29-8764-441214CBA163
set Tcp6ConnectFunc1AssertionGuid002  CD1704C9-BABE-4447-AFDA-D208C69BD88F
set Tcp6ConnectFunc1AssertionGuid003  6E521181-2A24-4697-BB83-4BD9DE5B89C0
set Tcp6ConnectFunc1AssertionGuid004  1944BCF5-9123-469b-86C2-5C987A39FE59
set Tcp6ConnectFunc1AssertionGuid005  CDAE7179-F66E-4980-9C08-890AE2CC4D46

#
# Tcp6 : Accept
#
set Tcp6AcceptConf1AssertionGuid001  30EC775A-CEFA-4d56-8C88-A2DC7513569C
set Tcp6AcceptConf2AssertionGuid001  08809174-9447-4956-930D-A7B2A763809F
set Tcp6AcceptConf3AssertionGuid001  8F109AF6-55FE-4f5c-8B84-22A8424BC7F9
set Tcp6AcceptConf4AssertionGuid001  FC47EF2F-C11C-488c-8821-C8EF3E2F3E7E
set Tcp6AcceptConf5AssertionGuid001  F336471A-6809-4886-9537-2FF8B75E5E8D
set Tcp6AcceptFunc1AssertionGuid001  19464085-7CCC-42a8-BD81-8A210AF470CD
set Tcp6AcceptFunc1AssertionGuid002  2953F594-8F06-42f6-8E7B-C78FF5C24EA9
set Tcp6AcceptFunc1AssertionGuid003  04DF3E6D-599B-43df-B9B4-F4AFC83F4849
set Tcp6AcceptFunc1AssertionGuid004  727BB534-D41F-4132-88BB-8E02C6842CBF
set Tcp6AcceptFunc1AssertionGuid005  F88FF924-FB1C-4252-9AA9-18FF46AE7590
set Tcp6AcceptFunc1AssertionGuid006  1BFF0F74-465C-4e25-A680-8D2D4352284D
set Tcp6AcceptFunc1AssertionGuid007  06850748-C64F-4d44-BA43-4EFBDE2D2C7D
set Tcp6AcceptFunc1AssertionGuid008  7415D9D3-054F-4a18-B8BF-6F6AAEF4BC3F
set Tcp6AcceptFunc1AssertionGuid009  72834F64-41FE-46ab-8B39-64E39F286F71


#
# Tcp6 : Transmit
#
set Tcp6TransmitConf1AssertionGuid001  EF652675-3D29-4c9c-BE90-D3D653AC7B3C
set Tcp6TransmitConf2AssertionGuid001  31CBE783-DEA8-4d05-9B0B-F0875D3B0724
set Tcp6TransmitConf3AssertionGuid001  CBB9C387-96EF-4834-BAEB-E19ECA99AEC7
set Tcp6TransmitConf4AssertionGuid001  FDD4086F-EFFD-4e7a-93D2-73746D0F6318
set Tcp6TransmitConf5AssertionGuid001  B3528D10-D5AE-4960-B503-DD89D0F76A09
set Tcp6TransmitConf6AssertionGuid001  A8598EDC-469C-4803-BDF4-37BF068F4187
set Tcp6TransmitConf7AssertionGuid001  6231D7C6-F61C-4d6b-94C4-C6FC7359B6E2
set Tcp6TransmitConf8AssertionGuid001  5172270A-F411-4197-BD34-82C5C0E9A7CF
set Tcp6TransmitConf9AssertionGuid001  13FA7B6C-DC0F-4f9e-AE4A-9E3E1102E298
set Tcp6TransmitConf10AssertionGuid001  9192CADE-7B3D-44bf-8AE7-362889D87623
set Tcp6TransmitFunc1AssertionGuid001  8652C924-F3D0-43cc-8BDA-8CD716DCB3A0
set Tcp6TransmitFunc1AssertionGuid002  096D60C6-F036-46be-B0B2-9513CFF18081
set Tcp6TransmitFunc1AssertionGuid003  0D441C88-D3EB-4b97-9C3D-C9BEEC2DEBC5
set Tcp6TransmitFunc1AssertionGuid004  9B0D226F-4BC4-4e1c-B707-A18E3A7B30F6
set Tcp6TransmitFunc1AssertionGuid005  FACA42A2-A769-4af9-90CB-F0D05FF08E03


#
# Tcp6 : Receive
#
set Tcp6ReceiveConf1AssertionGuid001     D54CF9ED-80E9-44c0-8125-A7852BBFEC83
set Tcp6ReceiveConf2AssertionGuid001     A682E94A-5D64-4646-988D-1E7AB1688DB1
set Tcp6ReceiveConf3AssertionGuid001     AD9F6B64-D0A0-4bef-BEDB-F0429B00FD76
set Tcp6ReceiveConf4AssertionGuid001     C9A6CAE7-6E5E-4c04-9B1E-27F36134838A
set Tcp6ReceiveConf5AssertionGuid001     0CB365FF-F855-4ef5-B8E5-EF2BC2D46A7D
set Tcp6ReceiveConf6AssertionGuid001     3AD62087-FAF8-4864-9BD9-ADB1166A5462
set Tcp6ReceiveConf7AssertionGuid001     4B325E98-9AE8-4a2b-9E3E-0ACF4A7E6953
set Tcp6ReceiveConf8AssertionGuid001     DDEF303A-3180-466f-8055-26A42F121B78
set Tcp6ReceiveConf9AssertionGuid001     59B5CC95-B0E9-4cd6-B11D-74CC26723367
set Tcp6ReceiveConf10AssertionGuid001     D985C3A0-B98C-4ad9-B99C-1C5CFC4BEAAD
set Tcp6ReceiveConf11AssertionGuid001     DCAE30DA-090C-441f-BDA9-02284D2EABCB
set Tcp6ReceiveFunc1AssertionGuid001  2003BB96-F32D-48ca-8E5A-2C716E9533F7
set Tcp6ReceiveFunc1AssertionGuid002  5DF1BF20-8C5D-4ef4-B370-FD7814F20A88
set Tcp6ReceiveFunc1AssertionGuid003  B65C6862-EBAD-4d51-A1AC-73C01924008D
set Tcp6ReceiveFunc1AssertionGuid004  FC18F3EC-E779-4730-8224-EADD9A4FD4F9


#
# Tcp6: Close
#
set Tcp6CloseConf1AssertionGuid001          97E34EDC-8B15-479c-9DA9-57265818722D
set Tcp6CloseConf2AssertionGuid001          49EA02D4-0022-49c6-AC02-3DE9968648B9
set Tcp6CloseConf3AssertionGuid001          43DD8F75-40D1-4f54-815C-813EED713789
set Tcp6CloseConf4AssertionGuid001          ED7C5CD6-0D5B-4951-AA37-96EAE8A27B89
set Tcp6CloseConf5AssertionGuid001          772E9C64-C345-4470-9D93-6171F8955271
set Tcp6CloseFunc1AssertionGuid001    45385C8F-A54A-481d-B264-3FC812D15039
set Tcp6CloseFunc1AssertionGuid002    764114C1-2BA3-4791-9633-35B20B8843F4
set Tcp6CloseFunc1AssertionGuid003    10E12A40-97C5-467d-9790-0F581184F121
set Tcp6CloseFunc1AssertionGuid004    333BDD81-801D-4aa1-8C71-311D0F158957
set Tcp6CloseFunc1AssertionGuid005    33FA7B0C-9E89-4138-A9AF-3EEE54A39004
set Tcp6CloseFunc1AssertionGuid006    1CDB5BE1-F8D0-4570-8E99-7C6B6BB97673
set Tcp6CloseFunc2AssertionGuid001    134177F3-458A-4088-8E29-84751D684143
set Tcp6CloseFunc2AssertionGuid002    B124B733-1F2E-4493-95F6-8EA3931A8D6F
set Tcp6CloseFunc2AssertionGuid003    EDE2639E-A23B-4ae5-A0B3-9D1C1B27903D
set Tcp6CloseFunc2AssertionGuid004    7C552532-55EA-46ac-86F8-0D1C273471ED
set Tcp6CloseFunc2AssertionGuid005    DFE82050-3325-4dcf-A0DC-B720A672E9F0
set Tcp6CloseFunc3AssertionGuid001    362144C2-D822-445a-8D8D-1A27CDF31740





