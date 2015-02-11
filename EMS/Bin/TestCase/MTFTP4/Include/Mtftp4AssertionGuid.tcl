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
# Guid for CreateChild() interface
#
set Mtftp4CreateChildConfAssertionGuid001   F44C5295-599E-48bc-BB67-ED9A215BA9B1
set Mtftp4CreateChildConfAssertionGuid002   5E30AA7C-D5F6-4cac-B254-BFDF163B34FC

set Mtftp4CreateChildFuncAssertionGuid001   CA3FB64A-D149-4f76-9145-E4F6CCE65B27
set Mtftp4CreateChildFuncAssertionGuid002   B07AE013-0D83-49c3-9923-EF2767D548FE
set Mtftp4CreateChildFuncAssertionGuid003   D4D966C4-C05A-4995-BFFB-2C868B3C2C0B

#
# Guid for DestroyChild() interface
#
set Mtftp4DestroyChildConfAssertionGuid001  3C312328-313D-47f6-807C-5B1E10C2C04D
set Mtftp4DestroyChildConfAssertionGuid002  E1C0EE52-D5AF-4ec0-A3F6-31FBE0D4B704
set Mtftp4DestroyChildConfAssertionGuid003  28F8E30C-A5D9-4327-99FA-ACDAC95FA4FF

set Mtftp4DestroyChildFuncAssertionGuid001  CB939B7A-266A-44f5-A2E3-57EADE7F4408
set Mtftp4DestroyChildFuncAssertionGuid002  C9D38D67-ADC1-425d-A4A1-0418C64B630C

#
# Guid for GetModeData() interface
#
set Mtftp4GetModeDataConfAssertionGuid001   DC9AC841-8A0F-4214-9173-6065EE518C52

set Mtftp4GetModeDataFuncAssertionGuid001   40ECCFCD-EE1C-405f-B064-2DE5667BFBEE

#
# Guid for Configure() interface
#
set Mtftp4ConfigureConfAssertionGuid001     2C5B72D9-2C30-4249-A23A-9214FDEA7312
set Mtftp4ConfigureConfAssertionGuid002     01EF2CAC-1259-41c9-BD91-4968A9FDD642
set Mtftp4ConfigureConfAssertionGuid003     BE92BD2E-D085-4da2-AFBF-EC7B0DC7ECCA
set Mtftp4ConfigureConfAssertionGuid004     5891D15C-7F5D-4c0d-B090-88CD44E1EA68
set Mtftp4ConfigureConfAssertionGuid005     D01D26BE-35FB-4a08-B022-7BE253CF9902
set Mtftp4ConfigureConfAssertionGuid006     37CCAE28-4B81-4ba5-8DE6-79E7DAB90304

set Mtftp4ConfigureFuncAssertionGuid001     D31E47EA-5A76-49aa-BD40-6FD949885F84

#
# Guid for GetInfo() interface
#
set Mtftp4GetInfoConfAssertionGuid001       794B1AAE-92B4-40de-ADED-43B35537D8A3
set Mtftp4GetInfoConfAssertionGuid002       0733CDB5-4072-4129-A206-CE566EF6D861
set Mtftp4GetInfoConfAssertionGuid003       A04D3E7C-5E50-4472-A770-C1A948CBD91E
set Mtftp4GetInfoConfAssertionGuid004       10D2101C-0AA3-4713-B82B-E143EDF41126
set Mtftp4GetInfoConfAssertionGuid005       F85B07F6-9F89-41ad-8D53-475397AC981A
set Mtftp4GetInfoConfAssertionGuid006       B9CAEDCF-F071-421a-9FB9-7E249DF4E3B2
set Mtftp4GetInfoConfAssertionGuid007       5CB9E305-B4E2-4416-A735-E272B698F823
set Mtftp4GetInfoConfAssertionGuid008       30E6A222-2BBC-4ff6-A8F2-D68AC2919829
set Mtftp4GetInfoConfAssertionGuid009       C4C5CED1-30A5-4c54-A3C0-802B3583BF70
set Mtftp4GetInfoConfAssertionGuid010       32DB978C-9D9B-4144-979C-2714429FE347
set Mtftp4GetInfoConfAssertionGuid011       77DBE1E4-6219-4531-AEBE-58264B537ED1
set Mtftp4GetInfoConfAssertionGuid012       70E8D3E9-75A9-4652-8268-A40DDD1A815F
set Mtftp4GetInfoConfAssertionGuid013       FAA23D30-1D66-4d8e-BE21-2DA7BC1C9DFD
set Mtftp4GetInfoConfAssertionGuid014       D2C1E819-610B-4cfc-94F1-33CD13AF4BC9
set Mtftp4GetInfoConfAssertionGuid015       290076E3-DAF2-453d-B221-CD27CEE73DBE
set Mtftp4GetInfoConfAssertionGuid016       706BC816-6353-40ae-A947-9AF001A9828C
set Mtftp4GetInfoConfAssertionGuid017       A165BD19-951A-4486-884D-1D9430A7BE3C


set Mtftp4GetInfoFuncAssertionGuid001       BF72714A-113F-487e-AB10-08A798F34FC4

#
# Guid for ParseOptions() interface
#
set Mtftp4ParseOptionsConfAssertionGuid001  9BEA2F3F-9F02-4eb2-8B1F-99D5CFC35729
set Mtftp4ParseOptionsConfAssertionGuid002  0BC09196-B38A-4fa8-B038-4C4C8B3C69FA
set Mtftp4ParseOptionsConfAssertionGuid003  72723929-60BD-49c1-99BD-D14860337ADC
set Mtftp4ParseOptionsConfAssertionGuid004  B7ED01B9-7E1B-40ba-8B6A-5234DF1353F0
set Mtftp4ParseOptionsConfAssertionGuid005  350C473E-9901-4125-BCC9-65BFA9F31630
set Mtftp4ParseOptionsConfAssertionGuid006  CF909489-ACE2-4fec-8DC9-66A0D933A64A
set Mtftp4ParseOptionsConfAssertionGuid007  0131DA11-62A1-494f-B10A-AF5DE212E988
set Mtftp4ParseOptionsConfAssertionGuid008  5B7BBE95-DBA3-4e9c-89DE-37F1F6420424

set Mtftp4ParseOptionsFuncAssertionGuid001  973E370A-5936-4377-B06C-82E6114DDA6F

#
# Guid for ReadFile() interface
#
set Mtftp4ReadFileConfAssertionGuid001      38728E11-6F6F-409a-8431-F51E600F7D6F
set Mtftp4ReadFileConfAssertionGuid002      CB0105AB-7F16-46a1-87F2-186B86746ABA
set Mtftp4ReadFileConfAssertionGuid003      95384167-A706-4f2c-828C-8E3F15EE820A
set Mtftp4ReadFileConfAssertionGuid004      F5AC75D7-A32E-4b1f-A819-2EFC7324CCBA
set Mtftp4ReadFileConfAssertionGuid005      49F424ED-FDBC-4c82-8DB8-D5A2A49B7EFF
set Mtftp4ReadFileConfAssertionGuid006      1392CEF9-74E0-4f89-A526-A7A7775633D4
set Mtftp4ReadFileConfAssertionGuid007      1F4FD053-9E4B-49c4-9AEA-587560F1EC7D
set Mtftp4ReadFileConfAssertionGuid008      9BBCC0BB-5386-4e5c-A3AC-65C762F693AA
set Mtftp4ReadFileConfAssertionGuid009      329AE187-6758-42b9-84AE-92324215A5EF
set Mtftp4ReadFileConfAssertionGuid010      E491FC10-0C0F-4d45-B5C3-3C2910DBE470
set Mtftp4ReadFileConfAssertionGuid011      CFF83E43-5D33-4cc0-80C4-55960E5F58AE
set Mtftp4ReadFileConfAssertionGuid012      28754983-AC7D-4e7f-9FAD-BF5559FFA762
set Mtftp4ReadFileConfAssertionGuid013      64FD965D-2ACC-4540-BC57-50E8AB02E88A
set Mtftp4ReadFileConfAssertionGuid014      D09C7076-316F-4245-AC31-958222A467D7
set Mtftp4ReadFileConfAssertionGuid015      1322CB38-8F90-4fa8-BEA9-5B318EB824AD
set Mtftp4ReadFileConfAssertionGuid016      FF2D0E80-DECD-4a1c-B67C-E4CD999D6909
set Mtftp4ReadFileConfAssertionGuid017      A7FCBFFF-8367-466e-9D25-5B80B84FB58F
set Mtftp4ReadFileConfAssertionGuid018      00450815-41F5-4da8-9066-7880940734EA
set Mtftp4ReadFileConfAssertionGuid019      9017244C-127A-486e-815B-20E8A655D46F
set Mtftp4ReadFileConfAssertionGuid020      84B13FAB-04F5-474b-894C-63EF9DCF7858
set Mtftp4ReadFileConfAssertionGuid021      D25FF5A4-71E7-4e38-B43E-4ACCE783FA77
set Mtftp4ReadFileConfAssertionGuid022      F370C329-E20B-45a0-9AB3-D41370980003
set Mtftp4ReadFileConfAssertionGuid023      2357C86F-F9BA-4f25-9C77-7510ABB5107E
set Mtftp4ReadFileConfAssertionGuid024      66019567-321D-41a8-AAFF-607F75A40842
set Mtftp4ReadFileConfAssertionGuid025      5F64495C-AD06-4185-8755-86D944F63981
set Mtftp4ReadFileConfAssertionGuid026      17FA0734-38F6-4fe5-9F6A-5DAE9EF2F3AC
set Mtftp4ReadFileConfAssertionGuid027      A5D93FC4-9B20-45cc-BE45-CC605E51AEF4
set Mtftp4ReadFileConfAssertionGuid028      40F05E07-3A7B-4244-974F-969A895CA483
set Mtftp4ReadFileConfAssertionGuid029      A8D5ABDF-3E19-462e-9F6D-9FA613D296D3
set Mtftp4ReadFileConfAssertionGuid030      AB02A8D2-2086-4372-B5C7-060E28651E8F
set Mtftp4ReadFileConfAssertionGuid031      F135F02B-51CA-47b9-ABF4-4BD9788668F8
set Mtftp4ReadFileConfAssertionGuid032      B8363DD2-EDCA-49a6-BE32-9087B9576A1F
set Mtftp4ReadFileConfAssertionGuid033      5AE24123-BB88-42a5-A1D0-B349FA20046F
set Mtftp4ReadFileConfAssertionGuid034      CFDAF47B-8A46-498c-920E-9615C123BE57
set Mtftp4ReadFileConfAssertionGuid035      731FB0EC-B6B1-4424-B061-1BAAB33FC088
set Mtftp4ReadFileConfAssertionGuid036      BD75E9F5-76B3-4e67-B9BF-CDFBED5C34A6
set Mtftp4ReadFileConfAssertionGuid037      C9F2CDC8-38EB-4446-9DC4-5C784A690BD1
set Mtftp4ReadFileConfAssertionGuid038      C911F1F0-385B-4de3-B386-E320EC3CA8C2
set Mtftp4ReadFileConfAssertionGuid039      FD55BE46-B941-4708-BE69-2482CA2C2934
set Mtftp4ReadFileConfAssertionGuid040      B441EE5B-BF7F-446f-A25C-777A0BDDDE78
set Mtftp4ReadFileConfAssertionGuid041      6EAABF78-3914-4d08-850C-BF636DE9F355
set Mtftp4ReadFileConfAssertionGuid042      D5E062FC-5C0F-470c-8B7A-44F7BCADC69C
set Mtftp4ReadFileConfAssertionGuid043      6D8A5555-E632-470e-98E5-61D22EC90D0D
set Mtftp4ReadFileConfAssertionGuid044      732738E8-1FF1-4f3a-A0C8-38811D159283
set Mtftp4ReadFileConfAssertionGuid045      D1C4E1E8-1099-4646-B7C9-647E65C38230

set Mtftp4ReadFileFuncAssertionGuid001      8AD083D8-9757-40ef-9986-21EE904AA02D
set Mtftp4ReadFileFuncAssertionGuid002      C3640C29-BFCD-4f0c-AE7E-CC448AC18E16
set Mtftp4ReadFileFuncAssertionGuid003      5E294D5A-F09E-4fdc-A22E-9DCBFA443D2B
set Mtftp4ReadFileFuncAssertionGuid004      162E4457-63D9-4402-ADAC-AADF3A61AFDC
set Mtftp4ReadFileFuncAssertionGuid005      E0D3922C-017D-44a2-9088-ADB6EB9F4CED
set Mtftp4ReadFileFuncAssertionGuid006      CC4F141C-9DF1-404e-9027-60EABDA808D8
set Mtftp4ReadFileFuncAssertionGuid007      2D4D9962-24AC-4f62-9B66-3CA5F367B3A0
set Mtftp4ReadFileFuncAssertionGuid008      9E9E85F5-669D-4de3-82A4-FF96B9697905
set Mtftp4ReadFileFuncAssertionGuid009      0BDC47FC-659E-497f-8D10-1052D3957D19
set Mtftp4ReadFileFuncAssertionGuid010      C965CBDF-1539-4507-B0D1-4FCD17C4BB54
set Mtftp4ReadFileFuncAssertionGuid011      CF00A8AE-8676-4ee3-B5CC-8222F9469403
set Mtftp4ReadFileFuncAssertionGuid012      21A80B34-73B3-47ba-820C-3734437ED5D4
set Mtftp4ReadFileFuncAssertionGuid013      9E8004A9-C28C-461b-84A1-31CAC6483128
set Mtftp4ReadFileFuncAssertionGuid014      9BD82567-6249-4635-B02D-F8060D2668A6
set Mtftp4ReadFileFuncAssertionGuid015      CF35445D-0AA1-4485-8EB6-5FD8B4655584
set Mtftp4ReadFileFuncAssertionGuid016      62908D19-C308-4f16-A170-B69ADF47B472
set Mtftp4ReadFileFuncAssertionGuid017      58C614FB-51D9-4043-B124-95A37CCD3D70
set Mtftp4ReadFileFuncAssertionGuid018      23A7AEBE-0117-44fc-9DCC-684CA6312A20
set Mtftp4ReadFileFuncAssertionGuid019      9DF88B27-0A20-4d91-982B-322641623944
set Mtftp4ReadFileFuncAssertionGuid020      AD60CB28-6451-400a-A574-F6359F0192D3
set Mtftp4ReadFileFuncAssertionGuid021      2309B8EA-5593-4835-B624-65DAC551045D
set Mtftp4ReadFileFuncAssertionGuid022      F6C81B41-8EDD-46df-8A82-4640D98BDAA5
set Mtftp4ReadFileFuncAssertionGuid023      7156D37F-D7EF-47ea-A2F3-643E7C449F65
set Mtftp4ReadFileFuncAssertionGuid024      34753378-B423-40b1-937C-4DAA5CA66343
set Mtftp4ReadFileFuncAssertionGuid025      D756BE67-D667-432f-BBD6-3AE1F5E661D1
set Mtftp4ReadFileFuncAssertionGuid026      C0FC889F-C91F-4a41-8059-0E2256790B53
set Mtftp4ReadFileFuncAssertionGuid027      5A4ED7D1-0E36-4f9c-A79C-F2352EF73B2D

#
# Guid for WriteFile() interface
#
set Mtftp4WriteFileConfAssertionGuid001     4B00DF17-C244-413d-8EBF-E87E109AA8D4
set Mtftp4WriteFileConfAssertionGuid002     DDC80D3B-448D-4ef9-AB74-8847A7C97CA8
set Mtftp4WriteFileConfAssertionGuid003     97304D43-1101-4b76-9070-6685629EB3A3
set Mtftp4WriteFileConfAssertionGuid004     F061683F-B39E-42af-9286-9F18CCC7C08D
set Mtftp4WriteFileConfAssertionGuid005     A2D02347-9410-49b3-A9D2-D71AF4C5A734
set Mtftp4WriteFileConfAssertionGuid006     E8F09C7B-2CF3-482e-93C6-4F45853A430C
set Mtftp4WriteFileConfAssertionGuid007     069921C9-8F37-45b6-A498-A32FC9B58D50
set Mtftp4WriteFileConfAssertionGuid008     B95D36A6-091E-444b-9DD7-304C9E59AB81
set Mtftp4WriteFileConfAssertionGuid009     67021DD5-F97D-4783-8DE2-936E6C5AE5EB
set Mtftp4WriteFileConfAssertionGuid010     4A445105-F332-4251-B15C-105C27EB6709
set Mtftp4WriteFileConfAssertionGuid011     00EE8108-B8CE-4428-9A58-3CF3333EF49A
set Mtftp4WriteFileConfAssertionGuid012     0B05148F-4F07-413d-8E47-99BEAC25C34D
set Mtftp4WriteFileConfAssertionGuid013     26AC0F66-2FA1-4e91-9314-FE0F8693474D
set Mtftp4WriteFileConfAssertionGuid014     105A5B0C-72CB-4854-95DD-86D7280DA612
set Mtftp4WriteFileConfAssertionGuid015     CAEEF509-3240-4675-A250-0BAFB55ACB16
set Mtftp4WriteFileConfAssertionGuid016     B76D5034-BEE6-468a-A1F2-C69F200DA6AE

set Mtftp4WriteFileFuncAssertionGuid001     CC7A5AAD-E6EC-4fa7-970A-AC30D6392016
set Mtftp4WriteFileFuncAssertionGuid002     2649936F-161C-40c2-A853-C0A4A32EF262
set Mtftp4WriteFileFuncAssertionGuid003     BCBEC9FD-00D8-494d-A4FF-8698C4B06A5A
set Mtftp4WriteFileFuncAssertionGuid004     741101E7-7888-4bd8-A2CB-1DECB1346631
set Mtftp4WriteFileFuncAssertionGuid005     A3C22B82-5F14-4419-8FC6-D78988A988E9
set Mtftp4WriteFileFuncAssertionGuid006     20787B06-8766-4ced-B025-65FAF1D36C7C
set Mtftp4WriteFileFuncAssertionGuid007     F549A91C-9D15-45c7-B2ED-A67EFF08C0F4
set Mtftp4WriteFileFuncAssertionGuid008     9EE2172F-B96E-4d13-9E6C-BD274495EEC6
set Mtftp4WriteFileFuncAssertionGuid009     434974C8-5F8C-46d8-8957-4E03FFFAA3C5

#
# Guid for ReadDirectory() interface
#
set Mtftp4ReadDirectoryConfAssertionGuid001 C9E02DED-0E98-4162-8D4C-1458D06AC7AB
set Mtftp4ReadDirectoryConfAssertionGuid002 120FA0F3-AD22-4d39-B900-E560DD8FE3B2
set Mtftp4ReadDirectoryConfAssertionGuid003 E6339187-07D0-467f-9B89-5BF56C2DF8E0
set Mtftp4ReadDirectoryConfAssertionGuid004 C39CB583-3FA4-4c7f-9A93-A5F930F0426C
set Mtftp4ReadDirectoryConfAssertionGuid005 AF58AAF5-3CD0-47aa-8B93-4F7B8BE84DF1
set Mtftp4ReadDirectoryConfAssertionGuid006 7044E68A-6CA9-4b23-9A50-918534A3CAFB
set Mtftp4ReadDirectoryConfAssertionGuid007 8BD21805-EC3C-4041-A4E4-75F1A4ECAE4D
set Mtftp4ReadDirectoryConfAssertionGuid008 7ECF38C4-4FC5-4663-A4C4-C04845FE596B
set Mtftp4ReadDirectoryConfAssertionGuid010 31599521-B38B-47c8-A639-AF50E330BE87
set Mtftp4ReadDirectoryConfAssertionGuid011 EFC6D249-179F-49a2-961C-0D90E7794CCB
set Mtftp4ReadDirectoryConfAssertionGuid012 AB9BACFB-79EE-41e5-B9E9-40317AF1CC64

set Mtftp4ReadDirectoryFuncAssertionGuid001 968731A3-01E8-44d7-ADBA-7088808C99E1

#
# Guid for Poll() interface
#
set Mtftp4PollConfAssertionGuid001          57E97972-A7A3-4647-959A-23295B812CFE
