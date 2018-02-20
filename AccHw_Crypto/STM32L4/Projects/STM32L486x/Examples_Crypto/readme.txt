/**
  @page Examples_Crypto
  
  @verbatim
  ******************** (C) COPYRIGHT 2015 STMicroelectronics *******************
  * @file    Examples_Crypto/readme.txt 
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    30-October-2015
  * @brief   Description of the different algorithms implemented in STM32   
  *          Hardware Crypto Librar
  ******************************************************************************
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
  * limitations under the License
  * 
  ******************************************************************************
   @endverbatim


@par Example Description 

This project provides a set of examples wich describes how to use the different 
algorithms implemented in STM32 Hardware Crypto Library. 

This project supports the following examples:

1. AES:
   - AES128 CCM Encryption/Decryption        (for more details about this example pleaser refer to aes_128bits_ccm.txt)
   - AES128 CFB Encryption/Decryption        (for more details about this example pleaser refer to aes_128bits_cfb.txt)
   - AES128 KEYWRAP Encryption/Decryption    (for more details about this example pleaser refer to aes_128bits_keywrap.txt)
   - AES128 OFB Encryption/Decryption        (for more details about this example pleaser refer to aes_128bits_ofb.txt)
   - AES256 XTS Encryption/Decryption        (for more details about this example pleaser refer to aes_256bits_xts.txt)

2. ECC: 
   - Key Generation/Signature/Verification   (for more details about this example pleaser refer to ecc_keygen_sign_verify.txt)
   - Signature/Veridication                  (for more details about this example pleaser refer to ecc_sign_verify.txt)
   
3. POLY1305 Get MAC/Verification MAC         (for more details about this example pleaser refer to poly1305_getmac_verifymac.txt)

4. RSA Encryption/Decryption                 (for more details about this example pleaser refer to rsa_enc_dec.txt)

You can select one or many algorithms to be performed by uncommenting the corresponding 
define inside the main.h file.


@par Directory contents 

  - Examples_Crypto/Inc/STM32l4xx_hal_conf.h                 HAL configuration file        
  - Examples_Crypto/Inc/STM32l4xx_it.h                       Interrupt handlers header file
  - Examples_Crypto/Inc/main.h                               Header for main.c module      
  - Examples_Crypto/Src/example_aes128bits_ccm.h             AES_CCM example                   
  - Examples_Crypto/Src/example_aes128bits_cfb.h             AES_CFB example                   
  - Examples_Crypto/Src/example_aes128bits_cmac.h            AES_CMAC example                   
  - Examples_Crypto/Src/example_aes128bits_gcm.h             AES_GCM example                
  - Examples_Crypto/Src/example_aes128bits_keywrap.h         AES_KEYWRAP example             
  - Examples_Crypto/Src/example_aes128bits_ofb.h             AES_OFB example                 
  - Examples_Crypto/Src/example_aes256bits_xts.h             AES_XTS example          
  - Examples_Crypto/Src/example_ecc_keygen_sign_verify.h     ECC Key generation Signature and Verfication example                  
  - Examples_Crypto/Src/example_ecc_sign_verify.h            ECC Signature and Verfication example                    
  - Examples_Crypto/Src/example_poly1305_getmac_verifymac.h  Poly1305 examples 
  - Examples_Crypto/Src/example_rsa_encdec.h                 RSA Encryption/Decryption example       
  - Examples_Crypto/Src/STM32l4xx_it.c                       Interrupt handlers
  - Examples_Crypto/Src/main.c                               Main program
  - Examples_Crypto/Src/example_aes128bits_ccm.c             Header for AES_CCM example                                     
  - Examples_Crypto/Src/example_aes128bits_cfb.c             Header for AES_CFB example                                     
  - Examples_Crypto/Src/example_aes128bits_cmac.c            Header for AES_CMAC example                                    
  - Examples_Crypto/Src/example_aes128bits_gcm.c             Header for AES_GCM example                                     
  - Examples_Crypto/Src/example_aes128bits_keywrap.c         Header for AES_KEYWRAP example                                 
  - Examples_Crypto/Src/example_aes128bits_ofb.c             Header for AES_OFB example                                     
  - Examples_Crypto/Src/example_aes256bits_xts.c             Header for AES_XTS example                                     
  - Examples_Crypto/Src/example_ecc_keygen_sign_verify.c     Header for ECC Key generation Signature and Verfication example
  - Examples_Crypto/Src/example_ecc_sign_verify.c            Header for ECC Signature and Verfication example                 
  - Examples_Crypto/Src/example_poly1305_getmac_verifymac.c  Header for Poly1305 examples                                     
  - Examples_Crypto/Src/example_rsa_encdec.c                 Header for RSA Encryption/Decryption example                         
  - Examples_Crypto/Src/system_stm32l4xx.c                   STM32l4xx system source file


@par Hardware and Software environment  

  - This example runs on STM32L486ZGTx device
    
  - This example has been tested with STM32L486_EVAL RevB board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */