# GSM-A5-1-Encrypt-Decrypt
Implementation of A5/1 algorithm used in GSM for voice and SMS encryption.  It is designed to encrypt/decrypt any local file or file stream.

## Download:
```
git clone https://github.com/can-yesilyurt/GSM-A5-1-Encrypt-Decrypt.git
```
## Install:

# [Pre-build binary](https://github.com/can-yesilyurt/GSM-A5-1-Encrypt-Decrypt/tree/main/prebuild_bin) for MacOS.

***

# From source:

```
cd GSM-A5-1-Encrypt-Decrypt

mkdir build

cd build

cmake ../

cmake --build .

sudo cmake --install .
```
and it will be installed in /usr/local/bin/encrypt_GSM_A5-1

## Usage:

encrypt_GSM_A5-1 [ key ] [ Input Path ] [ Output Path ]

key: 64 bit HexString

## Example: 

In GSM-A5-1-Encrypt-Decrypt/Test_Files/
```
encrypt_GSM_A5-1 "1122334455aabbcc" ./test_image_1.png ./test_image_1.png_enc
```
> ./test_image_1.png_enc

Same command with same key would decrypt the encrypted file
```
encrypt_GSM_A5-1 "1122334455aabbcc" ./test_image_1.png_enc ./test_image_1_dec.png
```
> ./test_image_1_dec.png


## Copyright

This software is Copyright 2024 Can Yesilyurt <can--yesilyurt@hotmail.com>

encrypt_GSM_A5-1 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

encrypt_GSM_A5-1 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<http://www.gnu.org/licenses/>.
