# ExeLaunchHandler

**ExeLaunchHandler** is a launcher application that allows you to perform custom actions before launching a target application. All pre-run functionality is configured through Python scripts that are executed in a pipeline.

> 📖 **Русская версия**: [README_RU.md](README_RU.md)

## 🚀 Key Features

- **Python Script Pipeline**: Execute a sequence of tasks before launching the application
- **Graphical Interface**: Convenient configuration setup through Qt interface
- **Flexible Configuration**: JSON-based configuration with support for various parameters
- **Logging**: Built-in logging system with configurable levels
- **Result Processing**: Result system with support for various statuses (OK, Warning, Error, Fatal)

## 📋 Requirements

- Windows OS
- Python 3.x
- Qt5 (Core, Gui, Widgets)
- CMake 3.31+
- Visual Studio or compatible C++17 compiler

## 🛠️ Installation and Build

### Cloning the Repository

```bash
git clone https://github.com/yellow1cucumber/ExeLaunchHandler.git
cd ExeLaunchHandler
```

### Building the Project

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## ⚙️ Configuration

The application is configured through a `config.json` file:

```json
{
  "loggerConfig": {
    "logLevel": "Debug",
    "logFile": "log.txt",
    "logFileMaxSizeMB": 10
  },
  "pipesConfig": {
    "scriptsDir": "scripts/",
    "runSync": true
  },
  "exeRunnerConfig": {
    "exePath": "app.exe",
    "exeArgs": "",
    "cancelOnFatalError": false
  }
}
```

### Configuration Sections

#### `loggerConfig`

- `logLevel`: Logging level (`Debug`, `Info`, `Warning`, `Error`, `Critical`)
- `logFile`: Path to the log file
- `logFileMaxSizeMB`: Maximum log file size in MB

#### `pipesConfig`

- `scriptsDir`: Directory containing Python scripts
- `runSync`: Synchronous script execution (`true`) or asynchronous (`false`)

#### `exeRunnerConfig`

- `exePath`: Path to the target application
- `exeArgs`: Command line arguments for launch
- `cancelOnFatalError`: Cancel launch on fatal errors

## 🐍 Creating Python Scripts

### Basic Script Structure

Create a Python file in the `scripts/` directory with the following structure:

```python
import pipebridge

def my_pre_launch_action():
    """
    Your logic is executed here
    """
    pipebridge.Logger.info("Executing pre-launch task")
    
    # Your code here
    # ...
    
    # Return result (optional)
    return {
        "status": "ok",
        "message": "Task completed successfully"
    }

# Register pipe in the pipeline
pipebridge.register_pipe(
    name="MyPreLaunchAction",
    func=my_pre_launch_action,
    description="Description of what this task does"
)
```

### Available Result Statuses

- `"ok"`: Successful execution
- `"warning"`: Executed with warnings
- `"error"`: Execution error
- `"fatal"`: Critical error

### Logging in Scripts

```python
import pipebridge

pipebridge.Logger.debug("Debug message")
pipebridge.Logger.info("Information message")
pipebridge.Logger.warning("Warning")
pipebridge.Logger.error("Error")
pipebridge.Logger.critical("Critical error")
```

### Script Examples

#### Example 1: File Checking

```python
import pipebridge
import os

def check_required_files():
    required_files = ["config.ini", "data.db"]
    missing_files = []
    
    for file in required_files:
        if not os.path.exists(file):
            missing_files.append(file)
    
    if missing_files:
        return {
            "status": "error",
            "message": f"Missing files: {', '.join(missing_files)}"
        }
    
    return {"status": "ok", "message": "All files found"}

pipebridge.register_pipe(
    name="FileChecker",
    func=check_required_files,
    description="Check for required files"
)
```

#### Example 2: Temporary File Cleanup

```python
import pipebridge
import shutil
import os

def cleanup_temp_files():
    temp_dir = "temp/"
    
    if os.path.exists(temp_dir):
        try:
            shutil.rmtree(temp_dir)
            os.makedirs(temp_dir)
            return {"status": "ok", "message": "Temporary files cleaned"}
        except Exception as e:
            return {"status": "warning", "message": f"Failed to clean: {str(e)}"}
    
    return {"status": "ok", "message": "Temporary directory not found"}

pipebridge.register_pipe(
    name="TempCleaner",
    func=cleanup_temp_files,
    description="Clean temporary files"
)
```

## 🖥️ Launch Modes

### Console Mode

```bash
ExeLaunchHandler.exe --config config.json
```

### GUI Mode

```bash
ExeLaunchHandler.exe --config config.json --ui
```

### Command Line Parameters

- `--config <path>`: Path to configuration file (required)
- `--ui`: Launch in GUI mode
- `--help`: Show help

## 🔧 Project Architecture

```text
ExeLaunchHandler/
├── config/           # Configuration module
├── constants/        # Application constants
├── launch/           # Process launch module
├── logging/          # Logging system
├── pipes/            # Pipeline and pipe interfaces
├── python_bridge/    # Python script bridge
├── results_api/      # Result execution API
├── ui/               # Graphical interface (Qt)
├── third_party/      # External libraries
└── scripts/          # Directory for Python scripts
```

### Key Components

- **PipelineSync**: Synchronous pipeline executor
- **PyBridge::Adapter**: Adapter for Python interaction
- **ConfigManager**: Configuration manager with JSON support
- **Logger**: Logging system with various levels
- **ProcessLauncher**: Target process launcher

## 📝 Usage Examples

### Scenario 1: License Validation Before Game Launch

```python
import pipebridge
import requests
from datetime import datetime

def validate_license():
    try:
        # Check license on server
        response = requests.get("https://api.company.com/validate-license")
        
        if response.status_code == 200:
            data = response.json()
            if data.get("valid"):
                pipebridge.Logger.info("License is valid")
                return {"status": "ok"}
            else:
                return {"status": "fatal", "message": "License is invalid"}
        else:
            return {"status": "error", "message": "Failed to validate license"}
            
    except Exception as e:
        return {"status": "warning", "message": f"Validation error: {str(e)}"}

pipebridge.register_pipe("LicenseValidator", validate_license, "License validation")
```

### Scenario 2: Cloud Configuration Update

```python
import pipebridge
import json
import urllib.request

def sync_cloud_config():
    try:
        with urllib.request.urlopen("https://config.company.com/app-config.json") as response:
            cloud_config = json.loads(response.read().decode())
        
        with open("local-config.json", "w") as f:
            json.dump(cloud_config, f, indent=2)
        
        return {"status": "ok", "message": "Configuration updated"}
        
    except Exception as e:
        return {"status": "warning", "message": f"Failed to update configuration: {str(e)}"}

pipebridge.register_pipe("ConfigSync", sync_cloud_config, "Configuration synchronization")
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is distributed under the MIT License. See the `LICENSE` file for more information.

## 👨‍💻 Author

Nikita Sadovskiy (yellow1cucumber)

- GitHub: [@yellow1cucumber](https://github.com/yellow1cucumber)

## 🐛 Bug Reports

If you find a bug, please create an issue in [GitHub Issues](https://github.com/yellow1cucumber/ExeLaunchHandler/issues).

## 📚 Additional Documentation

- [Pipeline Architecture](docs/pipeline-architecture.md)
- [API Reference](docs/api-reference.md)
- [Script Examples](docs/script-examples.md)
