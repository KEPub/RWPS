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

