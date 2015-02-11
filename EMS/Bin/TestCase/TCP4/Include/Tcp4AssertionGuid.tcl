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
set Tcp4CreateChildConf1AssertionGuid001    94AD4201-7703-4e0b-9103-A04E2605AAAE
set Tcp4CreateChildFunc1AssertionGuid001    F72CB825-B850-45e1-92D6-E8973F5EED10

set Tcp4DestroyChildConf1AssertionGuid001   8641E51C-C44C-4ada-BFF3-021F28EF0531
set Tcp4DestroyChildConf2AssertionGuid001   53A0B383-71BF-47a9-8BA4-584D25C7289D
set Tcp4DestroyChildFunc1AssertionGuid001   2B0EDE0E-6113-47d0-A823-60D6FD76C433

set Tcp4GetModeDataConf1AssertionGuid001    F76D5A91-5EF5-4306-B147-C4B641D392C0
set Tcp4GetModeDataFunc1AssertionGuid001    F7C924B2-AAA6-4729-B1D0-71F8EDC8818F
set Tcp4GetModeDataFunc1AssertionGuid002    D39219B6-A262-4797-AC44-35E546C0E9C8
set Tcp4GetModeDataFunc1AssertionGuid003    7BE1DDB5-F3BF-4eb3-8752-9AF6916C51C5
set Tcp4GetModeDataFunc1AssertionGuid004    6255190B-3EB5-40e9-BD24-2685FC87AB29
set Tcp4GetModeDataFunc1AssertionGuid005    62F96356-53D3-4fdd-B136-1253C2B0148E
set Tcp4GetModeDataFunc1AssertionGuid006    F753264F-22D0-4e19-8181-F34DD9F6DB59
set Tcp4GetModeDataFunc1AssertionGuid007    0848D02D-3463-4f06-B16E-CED1323B53D2
set Tcp4GetModeDataFunc1AssertionGuid008    A92B1577-6D14-4d77-9F5B-85BA55F81D52
set Tcp4GetModeDataFunc1AssertionGuid009    31388819-2579-414e-890F-FEC9BE088C37
set Tcp4GetModeDataFunc1AssertionGuid010    EC2502C3-DF73-4bff-A4AC-AF5E773DBFA1
set Tcp4GetModeDataFunc1AssertionGuid011    32100AD2-BC14-426b-86EE-0EC18EB311B2
set Tcp4GetModeDataFunc1AssertionGuid012    3AE2F864-8963-48ca-BCA5-010DDF139EB1
set Tcp4GetModeDataFunc1AssertionGuid013    C72C71BF-781F-4a08-ACA1-B01FBC799160
set Tcp4GetModeDataFunc1AssertionGuid014    86FB248C-3238-411e-A6A5-411C214282C4
set Tcp4GetModeDataFunc1AssertionGuid015    DDDAF809-A972-4376-B2DB-1A3514CC880A
set Tcp4GetModeDataFunc1AssertionGuid016    F6873B19-BDEF-4bac-934D-55E08706672E
set Tcp4GetModeDataFunc1AssertionGuid017    8B5D7AA1-9838-4b5a-8837-A7D1935F8E46
set Tcp4GetModeDataFunc1AssertionGuid018    064D8786-876C-46a2-84A7-1A698A5965B0
set Tcp4GetModeDataFunc1AssertionGuid019    B98BB8A0-F8BD-405d-996C-52473C204338
set Tcp4GetModeDataFunc1AssertionGuid020    23FA07B0-CD96-490b-A6F6-E65D8D8928C6
set Tcp4GetModeDataFunc1AssertionGuid021    BFA282E9-6393-428f-8FE1-6DF2CAFC9B84
set Tcp4GetModeDataFunc1AssertionGuid022    245EA469-0422-45fa-974B-0B45C2F87027
set Tcp4GetModeDataFunc1AssertionGuid023    70445B77-59EC-4fd1-BA2B-9ACD7E0F7883
set Tcp4GetModeDataFunc1AssertionGuid024    FA72381D-5C30-4dd1-BAF4-FFCA300A2F15
set Tcp4GetModeDataFunc1AssertionGuid025    AD6D2B6F-8E2F-49ed-A1D8-3B3369042C2E
set Tcp4GetModeDataFunc1AssertionGuid026    7D6EF330-3522-434d-9FF7-3484E40D1FC5
set Tcp4GetModeDataFunc1AssertionGuid027    1F83096C-6342-4f1a-A122-E31ED5633653
set Tcp4GetModeDataFunc1AssertionGuid028    E7F67D55-5BB8-400c-99FC-530E5DC01F51
set Tcp4GetModeDataFunc1AssertionGuid029    A72E1AEC-5502-434c-B8ED-680B54B2A88E
set Tcp4GetModeDataFunc1AssertionGuid030    59E6CAF6-0DB0-45f9-9150-CADB1CAE9BC2
set Tcp4GetModeDataFunc1AssertionGuid031    3FD1EBB6-3EDD-4a61-988E-FC92BDEF8DF0
set Tcp4GetModeDataFunc1AssertionGuid032    53417686-CF3B-4dc5-9D7B-83AD7C963E0F

set Tcp4GetModeDataFunc2AssertionGuid001    05F9A5F1-445D-46d2-B882-F0E23472CA48
set Tcp4GetModeDataFunc2AssertionGuid002    529C2A7A-F533-4777-A37D-096F0C5299A7
set Tcp4GetModeDataFunc2AssertionGuid003    E6BC773D-F461-4f0f-97ED-78697F0B81CB
set Tcp4GetModeDataFunc2AssertionGuid004    42F51EBD-24D2-42af-B9AD-7EB2FE2A1865

set Tcp4ConfigureConf1AssertionGuid001      64729D75-1007-4b20-9B78-59C4C702EC9E
set Tcp4ConfigureConf2AssertionGuid001      E8CEF00F-0796-4b1c-BD09-2C86DB4DBA44
set Tcp4ConfigureConf2AssertionGuid002      6AAABBCA-B7D3-49a1-8F11-4A823F2ED900
set Tcp4ConfigureConf2AssertionGuid003      A176DE8A-D68D-4529-97B5-CF13A7E333C0
set Tcp4ConfigureConf2AssertionGuid004      F3F1B054-D497-4e1a-A467-9C23ABBB4308
set Tcp4ConfigureConf2AssertionGuid005      6FD9C85C-7CC5-480f-A914-8FBD0D30BA15
set Tcp4ConfigureConf2AssertionGuid006      0782F91F-5553-4854-92BE-B525790B4279
set Tcp4ConfigureConf3AssertionGuid001      21E9706F-F449-4c3c-956E-F428DD225AB9
set Tcp4ConfigureConf4AssertionGuid001      A1E6077C-035E-4684-81E2-99B2444E0B9D


set Tcp4RoutesConf1AssertionGuid001         F071D560-6489-4d6c-B4F3-D8E8358C0F81
set Tcp4RoutesConf3AssertionGuid001         84298587-88E5-42d9-9F2E-0098FB16EE79
set Tcp4RoutesConf3AssertionGuid002         3CA42E03-4E25-42c1-B595-1D3FDA3094B6
set Tcp4RoutesConf3AssertionGuid003         29320850-CC47-42ec-8F6A-F5FD84D16EB6
set Tcp4RoutesConf3AssertionGuid004         2B934E3E-992C-48f6-9941-FA0869E22C74
set Tcp4RoutesConf3AssertionGuid005         0BB49249-C0B5-467e-92F9-7181CF988546
set Tcp4RoutesConf3AssertionGuid006         D03447CE-089E-4f5b-B857-E3204F2725A4
set Tcp4RoutesConf5AssertionGuid001         41C55145-497A-4aca-A3AA-925560BE5F4A
set Tcp4RoutesConf6AssertionGuid001         EB8177AF-96FA-482c-8AF1-035ADFE4B2AE
set Tcp4RoutesFunc1AssertionGuid001         411E9053-7641-4c1b-9917-C23B5F6C003B
set Tcp4RoutesFunc2AssertionGuid001         659CF27E-5DC2-4b0b-A81D-BB2AC387D517


set Tcp4ConnectConf1AssertionGuid001        0DC45007-FF6E-41da-8105-552D88E80914
set Tcp4ConnectConf2AssertionGuid001        A00EFEF2-D596-4332-A19B-380AE0D723E0
set Tcp4ConnectConf2AssertionGuid002        E204E699-7941-4d65-8B2E-F2BED36CCF7E
set Tcp4ConnectConf2AssertionGuid003        672D8332-A9A0-4111-A295-10FE88178604
set Tcp4ConnectConf3AssertionGuid001        3011F8F5-6CCF-46f4-B99A-09D0F3DE3A12
set Tcp4ConnectConf3AssertionGuid002        513B33C4-4DF0-449e-B8F5-D64E30270EA4
         
set Tcp4AcceptConf1AssertionGuid001         81D93128-FCDA-49fa-87EA-D48E831A6E8B
set Tcp4AcceptConf2AssertionGuid001         9F46E8F3-C4E0-4027-8809-6BC4C65DCAF5
set Tcp4AcceptConf2AssertionGuid002         D59B4F29-874C-4282-AC7D-3FF68D5254E8
set Tcp4AcceptConf2AssertionGuid003         85F6AB8A-9374-4afe-8576-5EA444578731
set Tcp4AcceptConf3AssertionGuid001         26F62B3C-B67A-4f2a-868F-6530F65EE31B
set Tcp4AcceptConf3AssertionGuid002         4FBD5006-0D81-40d0-B8FF-CA77038034B6
set Tcp4AcceptFunc1AssertionGuid001         0DF289CA-FC53-4fc2-92B3-B43ACF3C5034
set Tcp4AcceptFunc2AssertionGuid001         71F6D2E2-9D2A-435e-830E-639F1FE73195
set Tcp4AcceptFunc2AssertionGuid002         0B1D8B5C-C111-4548-AC9E-3CC285AA0DAB
set Tcp4AcceptFunc2AssertionGuid003         BEF6D443-BECE-4315-8457-90E4B1C4340A


set Tcp4TransmitConf1AssertionGuid001       E268C41A-3749-4e6c-95DC-116C4A579340
set Tcp4TransmitConf2AssertionGuid001       F05CB723-7194-45f9-AE3D-529BB363DE19 
set Tcp4TransmitConf2AssertionGuid002       AABA9E1F-DC0C-4320-8A01-51C00722FB73
set Tcp4TransmitConf2AssertionGuid003       96EB6C53-68BC-4a3b-A407-96BC97AC8E1E
set Tcp4TransmitConf2AssertionGuid004       C0BCE6B7-CD60-484a-B337-F5B4FE9930B2
set Tcp4TransmitConf2AssertionGuid005       C00B7871-A4AC-4bfd-81DA-7852C0C05465
set Tcp4TransmitConf3AssertionGuid001       7E824BB2-B6CD-49b6-9F1B-E360027DD75F
set Tcp4TransmitConf3AssertionGuid002       97D1F634-39AA-44a3-B4C8-22A4172B9A12
set Tcp4TransmitConf3AssertionGuid003       42145B1A-DD0C-40f8-8F9A-4CFCB6DE882E
set Tcp4TransmitConf3AssertionGuid004       B1618C99-C9C4-4b90-864A-8FA332FD13E6

set Tcp4TransmitFunc1AssertionGuid001       B5B0F9AB-04F3-4269-96A6-40F548A09B7E
set Tcp4TransmitFunc1AssertionGuid002       19052FCE-5744-470f-8FC0-C384CC88571D
set Tcp4TransmitFunc1AssertionGuid003       7740AC88-4CF3-4943-9BF9-ECC46A58CC90
set Tcp4TransmitFunc2AssertionGuid001       C6E11D01-485B-4585-9A2E-CF43AC942E1A
set Tcp4TransmitFunc2AssertionGuid002       A5F63716-D4A2-44dc-932A-D8DF33D2A165

set Tcp4ReceiveConf1AssertionGuid001        E28B3623-C8BA-431a-91CD-E2C56036AA80
set Tcp4ReceiveConf2AssertionGuid001        484C93A6-93BA-429f-9E63-0A7D5C19F5C7
set Tcp4ReceiveConf2AssertionGuid002        BE0FF6C1-26A0-4c3f-88C7-CCFC9FC8BE28
set Tcp4ReceiveConf2AssertionGuid003        D0D81B11-23DC-41ac-8CEC-DD3C0F9F25EF
set Tcp4ReceiveConf2AssertionGuid004        6D723765-1345-45ad-B357-F0BCA14C0C8F
set Tcp4ReceiveConf2AssertionGuid005        1AED8F61-F658-4abb-AC90-04742C468757
set Tcp4ReceiveConf3AssertionGuid001        2AC8BC18-6C65-4b0d-AFF1-4FB52E63C84F
set Tcp4ReceiveConf3AssertionGuid002        77F0240A-16A4-471a-9552-F658F9BB11B1
set Tcp4ReceiveConf3AssertionGuid003        276A8E6D-F79A-4cc5-BACB-99483859DEFB
set Tcp4ReceiveConf3AssertionGuid004        DDE96586-D067-4f04-A0D9-BD940E309790
set Tcp4ReceiveConf4AssertionGuid001        C527D95B-BF72-4c94-A8CC-608C47048507
set Tcp4ReceiveConf5AssertionGuid001        C9109F21-D490-4382-BB22-12FD816714EC
set Tcp4ReceiveFunc1AssertionGuid001        36F08E10-BF24-4a97-8342-993233FFBE18
set Tcp4ReceiveFunc2AssertionGuid001        DA1653B3-CF85-4152-8830-D4BF54176A22
set Tcp4ReceiveFunc2AssertionGuid002        D40FF5F0-CB1D-41cf-8EAB-3FCEA8933F4F
set Tcp4ReceiveFunc3AssertionGuid001        F1974D5D-5860-4519-8B8F-78CE0AADBBEC
set Tcp4ReceiveFunc3AssertionGuid002        C9D79086-5EB8-4c76-A4C4-F1FE786FC031
set Tcp4ReceiveFunc3AssertionGuid003        3C0CC77E-FB9B-4b24-85D0-AF3F39C8FDB7
set Tcp4ReceiveFunc3AssertionGuid004        5252CAE8-B23B-456e-97DF-1C01DDC4CD05
set Tcp4ReceiveFunc3AssertionGuid005        8A11BBCA-E267-4221-A550-33623388EB06
set Tcp4ReceiveFunc3AssertionGuid006        794EFF7B-B88F-4f67-9DA1-D50EA6BC5C37



set Tcp4CloseConf1AssertionGuid001          C92FAD2D-446D-43d7-AFBE-81CE03D4E812
set Tcp4CloseConf2AssertionGuid001          82827716-B622-4527-B89E-A53059CEC9EC
set Tcp4CloseConf2AssertionGuid002          9F19E873-71A5-4350-A6B5-A9968C64E6DE
set Tcp4CloseConf3AssertionGuid001          A9472AA1-FFF1-4130-90C9-F887698F8BC1
set Tcp4CloseConf3AssertionGuid002          09CAA34E-DF4F-4dcf-BE5B-7BE3F36890C0
set Tcp4CloseFunc1AssertionGuid001          3756329A-21C3-41c6-A103-159A57938E9F
set Tcp4CloseFunc2AssertionGuid001          499852F9-49C2-4168-8F90-AB970F06530B


set Tcp4CancelConf2AssertionGuid001         DD1A70FB-790B-4d60-9AA4-4375BD3BE86E
set Tcp4CancelConf4AssertionGuid001         82758908-0F15-4e71-BC6B-CC64EDC30D6B
set Tcp4CancelFunc1AssertionGuid001         75515E6F-A430-4b5d-ADE6-A77559AA044F
set Tcp4CancelFunc1AssertionGuid002         73CE1D38-5C5D-4618-9C2E-A924BF19F042
set Tcp4CancelFunc1AssertionGuid003         3202E449-F16E-4069-A5D1-004A2F41CDBF
set Tcp4CancelFunc1AssertionGuid004         C7CE8DDA-154E-40ce-B02B-8AE91F193193
set Tcp4CancelFunc1AssertionGuid005         5355D4C4-74CE-4cc2-997A-489DBDFA3945



set Tcp4CnntClosingFunc1AssertionGuid001    C9FA5B59-7A1C-4b2b-9BCE-6BAD38122B0D
set Tcp4CnntClosingFunc1AssertionGuid002    8AE1E58B-CD65-4fb0-BA12-4395EFAB9CD1
set Tcp4CnntClosingFunc1AssertionGuid003    8B1BCBD7-3DB6-46ec-8BF0-84B4B90FB895
set Tcp4CnntClosingFunc1AssertionGuid004    EBC0E165-3146-4fa1-9AD8-6D56DFB09FD6
set Tcp4CnntClosingFunc1AssertionGuid005    9530E11A-4D42-4c45-9EE9-3082FCC90F97
set Tcp4CnntClosingFunc1AssertionGuid006    8CB38A66-FB72-4dce-948B-3E8FAE666F98
set Tcp4CnntClosingFunc1AssertionGuid007    C9EF7A67-C2A7-40b4-A931-BA7A83165315
set Tcp4CnntClosingFunc1AssertionGuid008    C4E81C62-E709-4096-BBFB-599907AF8982
set Tcp4CnntClosingFunc2AssertionGuid001    37B8E036-3FF9-4401-8176-A570D916A94E
set Tcp4CnntClosingFunc2AssertionGuid002    2C9F0FFE-F355-4a2f-B6A2-BF846CE8332F
set Tcp4CnntClosingFunc3AssertionGuid001    AAF0C2AD-5433-46cf-A4D9-C3EA65E138FC
set Tcp4CnntClosingFunc3AssertionGuid002    7996049D-C63F-4bb4-96A2-B190E7358C3C
set Tcp4CnntClosingFunc3AssertionGuid003    A740C41C-A9B1-4194-8AF5-6C92D920C778
set Tcp4CnntClosingFunc3AssertionGuid004    D012D6BB-9DAC-4e3b-A554-F6E9F57722B4



set CongestionCtrlFunc1AssertionGuid001     B0CDF9B2-0CC0-4e99-9683-DEF396C1C6A7
set CongestionCtrlFunc1AssertionGuid002     05D19FAC-66E6-4f41-BA70-FF3E487F4D4A
set CongestionCtrlFunc1AssertionGuid003     C12B24DA-A3C5-4820-8198-6E34AD28FCAF
set CongestionCtrlFunc2AssertionGuid001     F5C35856-3C84-40ce-BAF4-91577EFA4498
set CongestionCtrlFunc2AssertionGuid002     0DF29AC1-5B58-49cc-9531-CECEB449B53A
set CongestionCtrlFunc2AssertionGuid003     3A4FB624-8B05-46ce-97D7-0FC91E5D376A
set CongestionCtrlFunc2AssertionGuid004     A4D6BD97-6D30-4fec-8B50-CFACB17E9E0A


set Tcp4CnntOpeningFunc1AssertionGuid001    156E08BB-21C4-48a0-BEC0-8D0C177B90F2
set Tcp4CnntOpeningFunc1AssertionGuid002    D7814EE7-2CC3-4cc6-B43C-547E1F73C312
set Tcp4CnntOpeningFunc1AssertionGuid003    EAC7FE49-5202-457f-9E77-49E577A14B4E
set Tcp4CnntOpeningFunc1AssertionGuid004    C5678E42-6D91-41c1-962D-B67BAA72F821
set Tcp4CnntOpeningFunc1AssertionGuid005    3131D110-7545-46c5-91D1-8701D3047FCF
set Tcp4CnntOpeningFunc1AssertionGuid006    165AD06C-F630-4516-95BA-903FD8A24DE4
set Tcp4CnntOpeningFunc1AssertionGuid007    2328ABEB-2DCA-4960-A093-4294C88C3D51
set Tcp4CnntOpeningFunc1AssertionGuid009    E39E864A-347D-4c08-A7EC-0E5534E8A020
set Tcp4CnntOpeningFunc1AssertionGuid010    697D126D-D496-448b-8508-606DC1C63F65
set Tcp4CnntOpeningFunc1AssertionGuid012    B22365C7-6DAA-48e9-A37A-1DE547F4044E
set Tcp4CnntOpeningFunc1AssertionGuid013    8E4D9BAC-42B6-408f-A244-D3FE9BDC0CC7
set Tcp4CnntOpeningFunc1AssertionGuid014    72D8A37D-312E-44ee-86CB-B5585C636D65
set Tcp4CnntOpeningFunc1AssertionGuid015    E0C87D8A-81D4-4634-A20A-EEBADC4496E6
set Tcp4CnntOpeningFunc2AssertionGuid001    13F5C5E1-D4DC-437d-ACA2-931A8D85E0D3
set Tcp4CnntOpeningFunc2AssertionGuid002    656575EC-018B-475a-80A0-FF32EF503174
set Tcp4CnntOpeningFunc2AssertionGuid003    CABA9876-C926-42b3-AF99-B57D71836220
set Tcp4CnntOpeningFunc3AssertionGuid001    CD97A722-C8FE-4584-B39C-659BBB2C5A6F


set Tcp4UrgHandlingFunc1AssertionGuid001    355D3648-8375-4b16-94C4-19E1BC87FC8B
set Tcp4UrgHandlingFunc1AssertionGuid002    03663FA9-0A34-43a5-845B-2C367F7EB6D8
set Tcp4UrgHandlingFunc1AssertionGuid003    FCE0E13A-35DF-4713-AFB8-4D1ECCA5829B
set Tcp4UrgHandlingFunc2AssertionGuid001    75F47641-2982-4d51-953B-4B6591735E76
set Tcp4UrgHandlingFunc2AssertionGuid002    D0F54967-AA9B-4017-8787-24FB349DE451
set Tcp4UrgHandlingFunc2AssertionGuid003    4CBB57E5-E348-4340-819E-ED615AC21A35
set Tcp4UrgHandlingFunc2AssertionGuid004    6145A7F3-BB3D-48e8-ABDF-90C98782DC25
set Tcp4UrgHandlingFunc3AssertionGuid001    73CF4C9A-8C1D-4b7f-947C-7F7406F5101D
set Tcp4UrgHandlingFunc3AssertionGuid002    6019F57B-D99F-47b4-944A-86803E556354


set Tcp4RstHandlingFunc1AssertionGuid001    1DD96986-44C7-4981-BA01-1473FF82B2ED
set Tcp4RstHandlingFunc1AssertionGuid002    554F2D12-FA71-48eb-9602-FF5CFB8D45E6
set Tcp4RstHandlingFunc1AssertionGuid003    12DEA7E9-1773-4adb-9727-E8C3CFFBB97B
set Tcp4RstHandlingFunc1AssertionGuid004    EBF00938-B335-4a33-A27B-4D54F6427299
set Tcp4RstHandlingFunc1AssertionGuid005    21941C4E-B4E3-422b-8158-EFCD28B0EEEF
set Tcp4RstHandlingFunc1AssertionGuid006    EE1C295D-13E1-4bc3-944B-B52EAF48B25F
set Tcp4RstHandlingFunc1AssertionGuid007    4FAC9B90-F3C4-4779-AB3F-32E8D99B8B09
set Tcp4RstHandlingFunc1AssertionGuid008    FA9A7729-C10B-4233-B8E9-EB8AF6658575
set Tcp4RstHandlingFunc1AssertionGuid009    D6646A78-5508-4643-9D9B-0CCA22220AC6
set Tcp4RstHandlingFunc2AssertionGuid001    C0B6A498-1CBD-4df0-9771-D19514EC74F2
set Tcp4RstHandlingFunc2AssertionGuid002    E48E5518-AF29-4e2b-B9BA-FEFC0A371956
set Tcp4RstHandlingFunc2AssertionGuid003    386FC38F-8F4D-4c34-8568-6271510C35F5
set Tcp4RstHandlingFunc2AssertionGuid004    B886E8C2-F6E7-40e3-BFC8-78C391918DAE
set Tcp4RstHandlingFunc2AssertionGuid005    1A49BC31-AD75-4165-AFFF-AEF01D1A7B29
set Tcp4RstHandlingFunc2AssertionGuid006    E88FA39A-FBC5-4366-9C68-489978D40E23
set Tcp4RstHandlingFunc3AssertionGuid001    600A697D-6250-49a2-97AC-A3C728203F9D
set Tcp4RstHandlingFunc3AssertionGuid002    A9631841-2E5E-49cb-B9EB-9ABA04AFA35F
set Tcp4RstHandlingFunc3AssertionGuid003    4226EE2F-D8F2-46e2-8FAF-1A0042F67E29
set Tcp4RstHandlingFunc3AssertionGuid004    DF8DC924-A0A4-4520-9D07-59AE218BB453
set Tcp4RstHandlingFunc3AssertionGuid005    17F9536E-A472-4b33-9E2C-30B18D824944
set Tcp4RstHandlingFunc3AssertionGuid006    E99B76FC-1F57-4f68-8B16-4EF81AA7C601
set Tcp4RstHandlingFunc3AssertionGuid007    C7F281CF-5FF7-475e-AB0E-8E1376B446A6
set Tcp4RstHandlingFunc3AssertionGuid008    EEA6DD88-1DF4-438e-A52B-EE9FC5B2D6F7
set Tcp4RstHandlingFunc3AssertionGuid009    B316E0CC-260E-4d24-A5EE-F4AE3430A952
set Tcp4RstHandlingFunc3AssertionGuid010    9A8293C3-3D43-4cfd-B373-B1CA0DEF9166


set Tcp4WinFlowCtrlFunc1AssertionGuid001    E107339E-ED3B-44fa-A918-83F0100E7014
set Tcp4WinFlowCtrlFunc1AssertionGuid002    823C66D7-2787-400d-8F62-69DD3B211F58
set Tcp4WinFlowCtrlFunc1AssertionGuid003    530D5E6D-928E-42c3-A46E-7493C0ACCABF
set Tcp4WinFlowCtrlFunc2AssertionGuid001    1A697687-3DEB-4b7b-896F-7835951B7AE9
set Tcp4WinFlowCtrlFunc3AssertionGuid001    BC12ABB0-F022-4705-9D12-3278AA8980B8
set Tcp4WinFlowCtrlFunc4AssertionGuid001    0541C800-7639-46f5-901A-207CC31144C9
set Tcp4WinFlowCtrlFunc4AssertionGuid002    613C599E-26E8-4d39-96E1-2D30D6BE20F7
set Tcp4WinFlowCtrlFunc4AssertionGuid003    BBB555FC-8A4D-41eb-AF1D-8CC987B44645
set Tcp4WinFlowCtrlFunc4AssertionGuid004    5B42C4D0-AF0C-4ae9-9FFC-B4F83FCD4D73
set Tcp4WinFlowCtrlFunc5AssertionGuid001    F3A8F990-0F1F-408f-AD66-2C981FC16534
set Tcp4WinFlowCtrlFunc5AssertionGuid002    CE6F5D62-0C72-412d-9AF4-C8CC968DE342
set Tcp4WinFlowCtrlFunc5AssertionGuid003    0165A4F8-5976-4051-A273-9EA162E5C9AC



set Tcp4NagleSWSAFunc1AssertionGuid001      CEEF47A7-F194-4200-9ABC-E29DFE80AA49
set Tcp4NagleSWSAFunc1AssertionGuid002      3906F7FA-BE7B-435a-B678-1D5BBAE5514A
set Tcp4NagleSWSAFunc2AssertionGuid001      A528B7A1-23CB-4601-B274-D70BCC175E42
set Tcp4NagleSWSAFunc2AssertionGuid002      0D5581C0-6903-4387-AFF7-E32CAC17EE33
set Tcp4NagleSWSAFunc3AssertionGuid001      ABF756AC-54A7-492c-AEA6-6D46D744B872
set Tcp4NagleSWSAFunc3AssertionGuid002      94C3EE05-142E-4f2e-8A9A-8F0525BBB483
set Tcp4NagleSWSAFunc3AssertionGuid003      81D74381-B0DF-4ef3-8A1C-DC7BE960C602
set Tcp4NagleSWSAFunc4AssertionGuid001      D7C7813E-4624-4f11-B365-456E003030E2
set Tcp4NagleSWSAFunc5AssertionGuid001      F853DEE2-A900-417b-B5CE-80865517AB57
set Tcp4NagleSWSAFunc5AssertionGuid002      93015811-2C00-4834-8317-7BBF7F1ACB52
set Tcp4NagleSWSAFunc5AssertionGuid003      FA149507-1607-44da-B2AE-5FD3517D82BA
set Tcp4NagleSWSAFunc5AssertionGuid004      CEB5C9E5-EBCE-4486-B5C5-06A60C365EA6



set Tcp4OptionsFunc1AssertionGuid001        1F1C574B-D5B8-4111-9014-F650043C8A71
set Tcp4OptionsFunc2AssertionGuid001        5BE584CC-39E0-4bcf-AF69-DA64FFFA9A02 
set Tcp4OptionsFunc2AssertionGuid002        BFC4A76F-19AD-4f34-9751-07D3D5E4920A
set Tcp4OptionsFunc3AssertionGuid001        BC3C725E-8784-4559-8191-606693B09AD1
set Tcp4OptionsFunc3AssertionGuid002        957BD7EF-6A40-46e2-BD62-9BA23935E296
set Tcp4OptionsFunc3AssertionGuid003        D4F6AB22-5D0A-4f9e-A5CE-8094F242C2D0
set Tcp4OptionsFunc4AssertionGuid001        EE9C7EA4-3BEC-4de0-8465-CB18214E3B01
set Tcp4OptionsFunc4AssertionGuid002        D69ABE03-DBB5-473f-9159-F343E7F004E8
set Tcp4OptionsFunc4AssertionGuid003        98E61624-7C30-4d11-8BF0-454ED80B21C0
set Tcp4OptionsFunc4AssertionGuid004        50EFBCF2-ABE6-4cfa-94C7-7886E938D859
set Tcp4OptionsFunc4AssertionGuid005        AB7715EF-8D1F-4b68-B866-B38D84719871
set Tcp4OptionsFunc4AssertionGuid006        A0845AF3-382F-4ab9-8DE0-E6C30CCD95D0
set Tcp4OptionsFunc4AssertionGuid007        A7D40772-C53A-44f6-981E-BF9FA6CF565B
set Tcp4OptionsFunc4AssertionGuid008        1B50447F-868C-4ea4-93C0-CB00733152CF
set Tcp4OptionsFunc4AssertionGuid009        3973BBB2-E1C5-40ea-8E50-DB538EC142A9
set Tcp4OptionsFunc4AssertionGuid010        B74382C6-37DC-4151-9DE3-D4988E4CD8CD
set Tcp4OptionsFunc4AssertionGuid011        53CD1A49-AA07-4bf8-9545-A4D3836C4FB4
set Tcp4OptionsFunc5AssertionGuid001        454D5884-F7E1-43a8-97AB-48BBD222A65B
set Tcp4OptionsFunc5AssertionGuid002        C8D0492A-79E8-411c-9142-082E7A81BB86
set Tcp4OptionsFunc5AssertionGuid003        691E1119-E737-4560-9633-B757D62E22DE
set Tcp4OptionsFunc5AssertionGuid004        CA16DC5D-5720-45d0-A2E4-1998C2A85F5C
set Tcp4OptionsFunc5AssertionGuid005        ADE14E0F-A957-4489-83F8-DB9F691DFC18
set Tcp4OptionsFunc5AssertionGuid006        90CC4928-D470-491d-AFA8-9D8607B7F315
set Tcp4OptionsFunc5AssertionGuid007        5CD402E2-E9D1-40a7-8AAD-E1C78942526B
set Tcp4OptionsFunc5AssertionGuid008        E47378C6-77D8-4f08-BB52-E76B14D928D6
set Tcp4OptionsFunc6AssertionGuid001        82AACAA9-A48E-47c2-B8A8-88D318F1D4E1
set Tcp4OptionsFunc6AssertionGuid002        B0BF1171-5E75-42c4-96ED-9721C650E687
set Tcp4OptionsFunc6AssertionGuid003        6DB78216-1741-4d22-862B-1E376F9FBEC9
set Tcp4OptionsFunc6AssertionGuid004        688ADC05-942E-4150-A16F-ECCE9C3B6652
set Tcp4OptionsFunc6AssertionGuid005        98E5CF1F-72CE-4be6-9995-0543CD6C8293
set Tcp4OptionsFunc6AssertionGuid006        2F71233B-EEAF-4dc5-B3DD-359FD6A6A242


set Tcp4HrdFormatAckFunc1AssertionGuid001   B550F0A9-302A-445a-9BBF-DBD3939AEC79
set Tcp4HrdFormatAckFunc1AssertionGuid002   CED29CF0-BFA9-4b92-B9E9-DC3EC9EA6A53
set Tcp4HrdFormatCheckSumFunc1AssertionGuid001 EB8958D6-9FAC-4c35-A166-F2351F4361B7

set Tcp4KeepAliveTimerFunc1AssertionGuid001 ECE1FC13-84F5-413a-90CB-53FD453A8D07
set Tcp4KeepAliveTimerFunc1AssertionGuid002 54E62A42-25BB-45c6-9042-93968DABFC2C

set Tcp4OthersFunc1AssertionGuid001         E78B5EFA-B455-464e-A25F-DAF53A142C09
set Tcp4OthersFunc1AssertionGuid002         0C2A1607-DFF9-4794-B8CA-04286ADFA846
set Tcp4OthersFunc1AssertionGuid003         B8B111F9-B3B7-496b-825D-AA9AD8596C6E
set Tcp4OthersFunc2AssertionGuid001         111F5B8E-F762-4eaf-93B9-E097CB5BCD3F
set Tcp4OthersFunc2AssertionGuid002         8D7DD35A-05F1-495d-8EED-7E547020D767
set Tcp4OthersFunc3AssertionGuid001         EF277ABD-FE01-4bbb-910D-AABB9F6468F4
set Tcp4OthersFunc4AssertionGuid001         A1C11437-BE91-4857-9EBC-99FC3A3FBA98
set Tcp4OthersFunc4AssertionGuid002         EB18FB2D-2306-41bc-9D68-10878FF3E5EF
set Tcp4OthersFunc4AssertionGuid003         968F5B4D-4801-487f-81C1-A61691444772
set Tcp4OthersFunc5AssertionGuid001         127D1F26-9F39-435c-8034-6B1CC95E853B
set Tcp4OthersFunc5AssertionGuid002         2D2065EF-7E6A-419a-8430-2C1DBFF70CAC

set Tcp4PersistTimerFunc1AssertionGuid001   B498BBFE-D47E-4c9e-B980-8F83C733C626

set Tcp4RetransmissionTimerFunc1AssertionGuid001 64785C77-4352-4da5-B0E8-850DDC5F3248
set Tcp4RetransmissionTimerFunc1AssertionGuid002 F2474612-61E6-4bb9-857C-B700970500DF




