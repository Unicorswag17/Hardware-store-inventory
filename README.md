This program allows users to manage a hardware store inventory through a command-line interface. Developed in **C**, it provides functionalities to:

- Add new tools to the inventory.
- Update the quantity or price of an existing tool.
- Automatically remove tools with zero quantity.

The data is stored and updated in files, ensuring persistence. It includes file management for safe updates and backups.

### **Main Features**:
1. **Fill Inventory**: Add new tools with initial quantities and prices.
2. **Update Tool**: Search for a tool by name and modify its details.
3. **Automatic Backup**: Maintains a backup of the original file before each update.

### **Files Used**:
- `hardware.dat`: Stores the inventory data.
- `temp.dat`: Temporary file used for data updates.
- `backup.dat`: Backup of the `hardware.dat` file.

This project was developed by  Super17 and ChrisRedBeard.
