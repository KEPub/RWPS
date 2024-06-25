# Compile and Test DLL Instructions

Used to test code execution,  the DLL will create a msgbox with the eicar signature, or call "Invoke-Mimikatz".  Goal is just to show execution.

## Steps to Compile and Test

1. **Open Developer Command Prompt for Visual Studio**
   - Ensure you are using the correct environment.

2. **Navigate to the Directory Containing Your Source Files**
   - Use `cd` to navigate to the directory where `mal.cpp` and `mal.def` are located.

3. **Compile the DLL**
   - Use the following command to compile the DLL:
     ```sh
     cl /LD /EHsc mal.cpp mal.def user32.lib
     ```

4. **Verify the Export Table**
   - Use `dumpbin` to check the exported functions:
     ```sh
     dumpbin /exports mal.dll
     ```
   - Ensure both `eicar` and `mimi` are listed without decorations.

5. **Place the DLL in the System Directory**
   - Copy the `mal.dll` file to `C:\Windows\System32`:
     ```sh
     copy mal.dll C:\Windows\System32
     ```

6. **Run the DLL**
   - Use `rundll32.exe` to run the exported functions:
     - **Run the `eicar` function:**
       ```sh
       rundll32.exe C:\Windows\System32\mal.dll,eicar
       ```
     - **Run the `mimi` function:**
       ```sh
       rundll32.exe C:\Windows\System32\mal.dll,mimi
       ```

