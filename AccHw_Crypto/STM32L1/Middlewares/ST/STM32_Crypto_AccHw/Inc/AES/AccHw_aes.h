/**
  ******************************************************************************
  * @file    AccHw_aes.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Container for the AES functionalities
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************/


#include "Common/AccHw_aes_low_level.h"
#include "Common/AccHw_aes_common.h"

#ifdef INCLUDE_AccHw_CFB
#include "CFB/AccHw_aes_cfb.h"
#endif

#ifdef INCLUDE_AccHw_OFB
#include "OFB/AccHw_aes_ofb.h"
#endif

#ifdef INCLUDE_AccHw_XTS
#include "XTS/AccHw_aes_xts.h"
#endif

#ifdef INCLUDE_AccHw_CCM
#include "CCM/AccHw_aes_ccm.h"
#endif

#ifdef INCLUDE_AccHw_GCM
#include "GCM/AccHw_aes_gcm.h"
#endif

#ifdef INCLUDE_AccHw_CMAC
#include "CMAC/AccHw_aes_cmac.h"
#endif

#ifdef INCLUDE_AccHw_KEY_WRAP
#include "KEYWRAP/AccHw_aes_keywrap.h"
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
