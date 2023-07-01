# Process Killer

🚀 Welcome to the Process Killer script! This script is designed to automatically kill unwanted processes running on a system.

## Objective

🎯 The objective of this script is to provide a convenient way to terminate processes that are not whitelisted. It scans the running processes and kills any process that is not included in the predefined whitelist.

## Features

✨ Here are some features of the Process Killer script:

- Whitelist: The script maintains a whitelist of allowed processes that should not be terminated.
- Automatic Scanning: It periodically scans the running processes and terminates any process not present in the whitelist.
- Signal-based Termination: The script uses the `SIGKILL` signal to forcefully terminate processes.
- Flexibility: The whitelist can be customized by modifying the `whitelist` vector in the script.

## Usage

📘 Here's how you can use the Process Killer script:

1. Configure the Whitelist: Open the script and modify the `whitelist` vector to include the processes you want to keep alive.
2. Run the Script: Execute the script on your system using a C++ compiler that supports C++11 or later.
3. Enable Process Killing: The script will start scanning and killing processes not included in the whitelist. To enable or disable the process killing functionality, modify the `enableKiller` parameter in the `InitKiller` function call.
4. Monitor the Output: The script will display messages indicating whether processes were successfully killed or if any errors occurred.

⚠️ Caution: Be careful when modifying the whitelist to ensure essential processes are not terminated.

## Contributing

🤝 Contributions are welcome! If you would like to contribute to this project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch: `git checkout -b my-feature-branch`
3. Make your changes.
4. Commit your changes: `git commit -am 'Add some feature'`
5. Push to the branch: `git push origin my-feature-branch`
6. Submit a pull request.

👍 Thank you to all the contributors who help make this script better!

## License

📝 This project is licensed under the [MIT License](LICENSE).
