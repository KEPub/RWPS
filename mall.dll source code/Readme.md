# File Hash

| File                | SHA256 Hash                                                           |
|---------------------|-----------------------------------------------------------------------|
|   dllmain.cpp   |   E47EE3B3EEA0124C661C8008CA3AC0E4F152DEDEF9CE607ACD955AA88F4BB6AC   |
|   framework.h   |   188C9E04096A0A539B82A8C61784D69FD7334DEA8066C181F31B429024974384   |
|   mal.cpp   |   813380734198BF688B67C0BFADF187661CA159B099996D6343CD4EAC790E5A01   |
|   mal.def   |   B342401D83C51571C81DBDC7D93BCB08601ECAF2D733A959C4BDEB04A9066E1C   |
|   mal.exp   |   D56103076A96CEDFDC9EC05B4C7FC6EE737BF48B6AF61F169BD8DEDAEA7C20E4   |
|   mal.h   |   0D918EEB77B6DE5012BDC744FD368312C75441EADCDBD80846A39F262F0E8311   |
|   mal.lib   |   D2F9BC4AAFB714587D2857B99661CBD082E0608FE5023272B514B6E15E50B9C6   |
|   mal.obj   |   4FEBD7AD3B7B39D17D194E6EE39F53671A0999D7A8FA9CBE5AA0A9902B1F3747   |
|   mal.sln   |   9F150A5309B47897B2BB1970CD2EC5A15B3B7099502BCF4A42FD829B0CC26721   |
|   mal.vcxproj           |   82241DCE27C5992DCB92AD928A66AE6DF143419BE064FE1F9882AD14E3D604F7   |
|   mal.vcxproj.filters   |   52496296C3AD9746BAE90A6DE9923FCDD53AA510A0E29CEFD08B9FDF2AFE38EB   |
|   mal.vcxproj.user      |   C06A75B13F855A94D46616796E024C52B499F8F92CF00CCB571DDBC6FF574676   |
|   pch.cpp               |   B1DFC417CE748FFEEC95311109DAE13142C638E58CFA86EB6E5A0865082428AA   |
|   pch.h                 |   C2D8C468B0DD828EAA49A609C5E54EBCA95EA4D2DE3CD390E968E01C5D7F79ED   |
|   pch.obj               |   E9064F48C58F0E575D769261E202C16EE9143FAAE22099044E44197A662348B5   |


# Compile and Test DLL Instructions

Used to test code execution,  the DLL will create a msgbox with an eicar signature, or call "Invoke-Mimikatz" as to show execution. Dynamic Library (.dll) was compiled using Visual Studio 2022.


## Steps to Compile and Test
1. **Open Developer Command Prompt for Visual Studio**
   - Download the sources code, and open the 'mal.sln' in Visual Studio.

2. **Open Developer Command Prompt for Visual Studio**
   - On the right in the Solution Explorer, right click on the project 'mal', and select "Open in Terminal".

   ![image](https://github.com/user-attachments/assets/0c26e9ed-9449-4410-b957-de015bc211cb)
   
3. **Compile the DLL**
   - Use the following command to compile the DLL:
     ```sh
     cl /LD /EHsc mal.cpp pch.cpp mal.def user32.lib
     ```
   ![image](https://github.com/user-attachments/assets/9ee1f7af-de30-4c41-a184-71223834b718)


4. **Verify the Export Table**
   - Use `dumpbin` to check the exported functions:
     ```sh
     dumpbin /exports mal.dll
     ```
   - Ensure both `eicar` and `mimi` are listed without decorations.

   ![image](https://github.com/user-attachments/assets/6da0faf4-eed9-49f9-8da4-1d680ef78962)

5. **Run the DLL**
   - Use `rundll32.exe` to run the functions:
     - **Run the `eicar` function:**
       ```sh
       rundll32.exe C:\Windows\System32\mal.dll,eicar
       ```
       ![image](https://github.com/user-attachments/assets/45daa001-d085-4891-83de-75c2036a8f61)

     - **Run the `mimi` function:**
       ```sh
       rundll32.exe C:\Windows\System32\mal.dll,mimi
       ```
      ![image](https://github.com/user-attachments/assets/7a9e86b5-2856-491c-ba6d-40a696ce3d39)

6. **<Optional> If Issues**
   - Open windows CLI with Admin privilages
   - copy the mal.dll to c:\windows\system32\ using hte following command;
   ```sh
   copy mal.dll C:\Windows\System32
    ```
   - Repeat Step 5, if furhter issues use the full path to the DLL. For example:
    ```sh
   rundll32.exe C:\Windows\System32\mal.dll,eicar
   ```
