# File Hash

| File                | SHA256 Hash                                                           |
|---------------------|-----------------------------------------------------------------------|
| 	mal.cpp	          | 	FE28C5CC1BC3F19E05692348B1563D7525CC070D1E31ECE6FF2F9FDB8A24B1C3	 | 
| 	mal.def	          | 	57F3D35D7FC17DF2C7BC412C8DE9757E724F7C580452EB39613AED677DD7966B	 | 
| 	mal.h	             | 	C3301B7147D4D0F04C1FE91A7AC3592D044A45891D740DED8C403956B4F48E9B   | 
| 	Readme.md	       | 	078163D5C16F64CAA5A14784323FD51451B8C831C73396B967B4E35E6879937B	 | 



# Compile and Test DLL Instructions

Used to test code execution,  the DLL will create a msgbox with an eicar signature, or call "Invoke-Mimikatz" as to show execution. Dynamic Library (.dll) was compiled using Visual Studio 2022.


## Steps to Compile and Test
1. **Open Developer Command Prompt for Visual Studio**
   - Download the provided sources code, and open the Dll1.sln file using Visual Studio Code.

2. **Open Developer Command Prompt for Visual Studio**
   - right click on "Solution Explorer", and go to "Open in Terminal".

![image](https://github.com/user-attachments/assets/acc7adf5-0552-4254-8d04-bd63f47edc4d)

3. **Navigate to the Directory Containing Your Source Files**
   - Use `cd` to navigate to the directory where `mal.cpp` and `mal.def` are located.

4. **Compile the DLL**
   - Use the following command to compile the DLL:
     ```sh
     cl /LD /EHsc mal.cpp mal.def user32.lib
     ```

5. **Verify the Export Table**
   - Use `dumpbin` to check the exported functions:
     ```sh
     dumpbin /exports mal.dll
     ```
   - Ensure both `eicar` and `mimi` are listed without decorations.

6. **Place the DLL in the System Directory**
   - Copy the `mal.dll` file to `C:\Windows\System32`:
     ```sh
     copy mal.dll C:\Windows\System32
     ```

7. **Run the DLL**
   - Use `rundll32.exe` to run the exported functions:
     - **Run the `eicar` function:**
       ```sh
       rundll32.exe C:\Windows\System32\mal.dll,eicar
       ```
     - **Run the `mimi` function:**
       ```sh
       rundll32.exe C:\Windows\System32\mal.dll,mimi
       ```

