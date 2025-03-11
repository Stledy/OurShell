### **What Does `myone` Do?**
The `myone` command in your *OurShell* project is designed to **help employees** by providing useful workplace-related information. It automates several tasks and presents them in a single execution.

---

## **🔹 Features of `myone`**
When you run `myone`, it performs the following tasks:

### **1️⃣ Fetches the Live Weather for Maseru**
   - Uses `curl` to fetch real-time weather data from `wttr.in` for Maseru.
   - Helps employees plan their commute and outdoor tasks.

   **Command Used:**  
   ```bash
   curl -s wttr.in/Maseru?format=3
   ```
   _(This returns a simple weather summary for Maseru.)_

---

### **2️⃣ Displays Company Announcements**
   - Reads and prints important company announcements from a text file.
   - Helps employees stay updated with news, policies, or events.

   **Command Used:**  
   ```bash
   cat /path/to/company/announcements.txt
   ```
   _(Replace `/path/to/...` with the actual file location.)_

---

### **3️⃣ Shows Today's Meeting Schedule**
   - Reads and displays a list of scheduled meetings from a text file.
   - Helps employees quickly check their agenda without needing to open emails or calendars.

   **Command Used:**  
   ```bash
   cat /path/to/meetings/today.txt
   ```
   _(Replace `/path/to/...` with the actual file location.)_

---

### **4️⃣ Performs a System Health Check**
   - Displays system resource usage (disk space & memory usage).
   - Helps employees monitor system performance, especially useful for those working with large files or applications.

   **Commands Used:**  
   ```bash
   df -h    # Disk usage
   free -h  # Memory usage
   ```

---

### **5️⃣ Takes a Screenshot of the Output**
   - Captures everything displayed in the terminal and saves it as an image.
   - Useful for documentation, sharing, or personal record-keeping.

   **Command Used:**  
   ```bash
   scrot ~/screenshot.png
   ```
   _(Saves the screenshot in the user's home directory as `screenshot.png`.)_

---

### **🔹 Summary: Why `myone` is Helpful**
✅ **Saves Time** – Employees don’t have to check multiple sources manually.  
✅ **Boosts Productivity** – Gives all key information in one place.  
✅ **Improves System Monitoring** – Helps prevent computer slowdowns.  
✅ **Records Information** – Automatically takes a screenshot for future reference.  

---

### **🚀 How to Run `myone`**
1. **Compile the program** (if not already compiled):
   ```bash
   gcc -o ourshell ourshell.c
   ```
2. **Run the shell:**
   ```bash
   ./ourshell
   ```
3. **Execute `myone`:**
   ```bash
   myone
   ```

Now, every time an employee runs `myone`, they get **live weather, announcements, meeting schedules, system status, and a screenshot**—all in one go! 🚀
