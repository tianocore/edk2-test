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
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
#
#
# Guid for CreateChild() interface
#
set Dhcp4CreateChildConf1AssertionGuid001   4b66733f-d324-4af9-9d92-914f5f772ef0
set Dhcp4CreateChildFunc1AssertionGuid001   1e0f5047-1be9-4db0-a571-fc82bc2d0a06

#
# Guid for DestroyChild() interface
#
set Dhcp4DestroyChildConf1AssertionGuid001  1f92470a-7aec-4fb4-a40d-5f0cd2401f08
set Dhcp4DestroyChildConf2AssertionGuid001  06b43e55-d8af-494f-8b93-78f8d07aa4c8
set Dhcp4DestroyChildFunc1AssertionGuid001  c44a4b68-1f16-4098-b26d-2c43cb274dae

#
# Guid for GetModeData() interface
#
set Dhcp4GetModeDataFunc1AssertionGuid001   52159e94-4a67-44f6-9b0b-83219341e1f3
set Dhcp4GetModeDataFunc2AssertionGuid001   969e5dac-2097-4a3f-aa15-b06dff2648ec
set Dhcp4GetModeDataFunc2AssertionGuid002   ca520116-5097-4cda-8079-4a9b8fdd8838

#
# Guid for Configure() interface
#
set Dhcp4ConfigureConf1AssertionGuid001     bd919c90-708b-4502-add7-d585304b840e
set Dhcp4ConfigureConf2AssertionGuid001     57b62321-14a8-4412-b420-ad495d6aabbb
set Dhcp4ConfigureConf3AssertionGuid001     5101b2b6-8021-4a04-9083-f66b9f4d101f
set Dhcp4ConfigureConf3AssertionGuid002     50f034a4-2aa4-4d1a-8a8c-9d7c0648c935
set Dhcp4ConfigureConf3AssertionGuid003     c199419b-62b1-4cda-b438-9dcded4d836d
set Dhcp4ConfigureConf3AssertionGuid004     ada01077-4869-4c21-8f6d-6e659341bca6
set Dhcp4ConfigureFunc1AssertionGuid001     de6079f0-4aa4-4665-808b-a0223c8bf640
set Dhcp4ConfigureFunc1AssertionGuid002     73401b2e-30aa-422d-a3ca-9f36781cfa94
set Dhcp4ConfigureFunc2AssertionGuid001     1a27208e-08a8-42a6-b93f-8b95942446b7

#
# Guid for Start() interface
#
set Dhcp4StartConf1AssertionGuid001         bac2be63-d705-4667-9d1b-04e05eebcb3a
set Dhcp4StartConf2AssertionGuid001         c67ae0d7-3401-4daf-a64c-b9a60eea1771
set Dhcp4StartConf3AssertionGuid001         d7cd1980-7509-4612-80c0-5c215b9e8e10
set Dhcp4StartConf4AssertionGuid001         580e7e81-506d-4339-b7c2-9f05538ff5de
set Dhcp4StartFunc1AssertionGuid001         8bd59e83-3f3a-4649-b861-3656235c8f7d
set Dhcp4StartFunc1AssertionGuid002         aca2403d-458b-4c8e-8f77-1f87853108ed
set Dhcp4StartFunc1AssertionGuid003         7344b984-306d-467b-a43d-3677f8c97978
set Dhcp4StartFunc1AssertionGuid004         f9a23299-eb65-472b-be96-e5ea772e03c0
set Dhcp4StartFunc1AssertionGuid005         723e3088-5f48-4b09-9b17-804586f99aad
set Dhcp4StartFunc1AssertionGuid006         a8fcde55-522b-49ea-bce8-6bea80579121
set Dhcp4StartFunc2AssertionGuid001         941de4e1-c289-417b-87eb-ef3e1ec0123d
set Dhcp4StartFunc2AssertionGuid002         ff3f4b6d-2b40-49b5-b9e0-7e118a73700a
set Dhcp4StartFunc2AssertionGuid003         35972f03-90dc-41ae-8e1e-2772473b06b6
set Dhcp4StartFunc2AssertionGuid004         90924db4-1237-4d59-88f3-118bed0180ae
set Dhcp4StartFunc2AssertionGuid005         434f1845-d940-4129-aaeb-7a1be7e13948
set Dhcp4StartFunc2AssertionGuid006         340ff4c6-7412-44d4-8f33-ebc26f221d0c

#
# Guid for RenewRebind() interface
#
set Dhcp4RenewRebindConf1AssertionGuid001   15bdc212-bad5-4213-b238-50ac7618dc90
set Dhcp4RenewRebindConf2AssertionGuid001   2949dc87-dbcd-4d64-8f10-682fa227e088
set Dhcp4RenewRebindConf3AssertionGuid001   d7f4cb11-c3dc-421f-9880-5c2a2d730602
set Dhcp4RenewRebindFunc1AssertionGuid001   38bb70ba-b05c-4431-b4f9-8f4e9b10c754
set Dhcp4RenewRebindFunc1AssertionGuid002   432ccefe-8586-4358-b7ee-f136e38ad830
set Dhcp4RenewRebindFunc2AssertionGuid001   c0b17d39-32bb-41f8-bd44-6bb8530fa4af
set Dhcp4RenewRebindFunc2AssertionGuid002   819f530e-0d51-43ce-8373-0b27c6363b63
set Dhcp4RenewRebindFunc3AssertionGuid001   982b5d48-2d87-40ea-be60-446049fe0898
set Dhcp4RenewRebindFunc3AssertionGuid002   4cc9abee-d9e8-444b-b834-3ed4579625c9
set Dhcp4RenewRebindFunc4AssertionGuid001   061ca38f-5092-483b-a4d2-f31f533fe7ac
set Dhcp4RenewRebindFunc4AssertionGuid002   f9fa2078-6283-4510-ad21-bae1152156f9

#
# Guid for Release() interface
#
set Dhcp4ReleaseConf1AssertionGuid001       a80fa204-87dd-4e92-8a5d-ee556c83ac7c
set Dhcp4ReleaseConf1AssertionGuid002       70f9485c-4fef-4bf3-acd5-2ee0ba303dd9
set Dhcp4ReleaseFunc1AssertionGuid001       67c1be03-f9c4-4419-88f0-b9fc6c1ad267
set Dhcp4ReleaseFunc2AssertionGuid001       555d101b-f86a-4e6f-9570-1cfae7d2d68a

#
# Guid for Stop() interface
#
set Dhcp4StopFunc1AssertionGuid001          da8661a5-82d4-4b1b-a268-f34fe5ab0357
set Dhcp4StopFunc2AssertionGuid001          0f6193fc-21f7-4831-bf53-3928c0496b48

#
# Guid for Build() interface
#
set Dhcp4BuildConf1AssertionGuid001         c2aa2960-dd52-4e56-877e-8c446a5eea31
set Dhcp4BuildConf1AssertionGuid002         f19cc8c3-9a84-4d62-94ae-c34b063aea91
set Dhcp4BuildConf1AssertionGuid003         c650067b-4ab0-4170-9b4b-4f7aeb77c05e
set Dhcp4BuildConf1AssertionGuid004         1debfafe-dfbe-4ff5-8acd-8fe1118230e0
set Dhcp4BuildConf1AssertionGuid005         d0beca24-a8f3-4753-8cdb-96e600927847
set Dhcp4BuildConf1AssertionGuid006         7d05c782-ccf3-42d0-9a6e-0d6b5c8d9c20
set Dhcp4BuildFunc1AssertionGuid001         f52d8032-d5c6-48e1-86b0-ac47ae8293ed
set Dhcp4BuildFunc2AssertionGuid001         78dae7e2-579a-47a1-b245-8cad39c80727
set Dhcp4BuildFunc2AssertionGuid002         fc1f9cb7-ed3d-4e6d-932a-63b5cfb4b337

#
# Guid for TransmitReceive() interface
#
set Dhcp4TransmitReceiveConf1AssertionGuid001 6d1bb6a7-5d67-4982-9635-54eb4b0cfad5
set Dhcp4TransmitReceiveConf1AssertionGuid002 d2bec02f-8304-4713-8a95-4bd34c6989c0
set Dhcp4TransmitReceiveConf1AssertionGuid003 9dfd549b-59eb-4f5d-995f-b82ddd1802ba
set Dhcp4TransmitReceiveConf1AssertionGuid004 ce99ae23-910a-4818-a089-f3f45bc5eba8
set Dhcp4TransmitReceiveConf2AssertionGuid001 be6683bd-807a-4fb0-bc7b-f751070e0e66

#
# Guid for Parse() interface
#
set Dhcp4ParseConf1AssertionGuid001         7cca1a2c-4136-4ff0-bc22-ca80568dfdbf
set Dhcp4ParseConf1AssertionGuid002         225ddf1b-9fb9-4a9b-b3b6-ca25eb310dbb
set Dhcp4ParseConf1AssertionGuid003         ea1a95dd-db6c-4200-b7c7-19b0a381065d
set Dhcp4ParseConf1AssertionGuid004         91e4d243-4ed6-451a-b09c-0a356a061dda
set Dhcp4ParseConf1AssertionGuid005         d836cddd-6bb4-455e-9ec4-499fc327dd21
set Dhcp4ParseConf1AssertionGuid006         ed5c8f2b-0043-4f43-ae83-a6bfab5ba2ba
set Dhcp4ParseConf2AssertionGuid001         4bd82a66-cede-4132-a8ca-d995e8e79ab2
set Dhcp4ParseConf2AssertionGuid002         a73ac67a-e5c9-41e7-b6c0-80a26f277ec0
set Dhcp4ParseFunc1AssertionGuid001         c84a412c-702a-40e1-a39c-55a88cbe605a
set Dhcp4ParseFunc1AssertionGuid002         2ba25811-4069-45da-b39e-fa0514424a4c
set Dhcp4ParseFunc1AssertionGuid003         6ce744e5-9e5a-4fb5-a5f2-3be8f5b5ad42