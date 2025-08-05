# ExeLaunchHandler

**ExeLaunchHandler** — это приложение-лаунчер, которое позволяет выполнять пользовательские действия перед запуском целевого приложения. Весь pre-run функционал настраивается через Python-скрипты, которые выполняются в пайплайне.

> 📖 **English version**: [README.md](README.md)

## 🚀 Основные возможности

- **Пайплайн Python-скриптов**: Выполнение последовательности задач перед запуском приложения
- **Графический интерфейс**: Удобная настройка конфигурации через Qt-интерфейс
- **Гибкая конфигурация**: Настройка через JSON с поддержкой различных параметров
- **Логирование**: Встроенная система логирования с настраиваемыми уровнями
- **Обработка результатов**: Система результатов с поддержкой различных статусов (OK, Warning, Error, Fatal)

## 📋 Требования

- Windows OS
- Python 3.x
- Qt5 (Core, Gui, Widgets)
- CMake 3.31+
- Visual Studio или совместимый компилятор C++17

## 🛠️ Установка и сборка

### Клонирование репозитория

```bash
git clone https://github.com/yellow1cucumber/ExeLaunchHandler.git
cd ExeLaunchHandler
```

### Сборка проекта

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## ⚙️ Конфигурация

Приложение настраивается через файл `config.json`:

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

### Секции конфигурации

#### `loggerConfig`

- `logLevel`: Уровень логирования (`Debug`, `Info`, `Warning`, `Error`, `Critical`)
- `logFile`: Путь к файлу логов
- `logFileMaxSizeMB`: Максимальный размер файла логов в МБ

#### `pipesConfig`

- `scriptsDir`: Директория с Python-скриптами
- `runSync`: Синхронное выполнение скриптов (`true`) или асинхронное (`false`)

#### `exeRunnerConfig`

- `exePath`: Путь к целевому приложению
- `exeArgs`: Аргументы командной строки для запуска
- `cancelOnFatalError`: Отменять запуск при фатальных ошибках

## 🐍 Создание Python-скриптов

### Базовая структура скрипта

Создайте Python-файл в директории `scripts/` со следующей структурой:

```python
import pipebridge

def my_pre_launch_action():
    """
    Ваша логика выполняется здесь
    """
    pipebridge.Logger.info("Выполняется предстартовая задача")
    
    # Ваш код здесь
    # ...
    
    # Возврат результата (опционально)
    return {
        "status": "ok",
        "message": "Задача выполнена успешно"
    }

# Регистрация pipe в пайплайне
pipebridge.register_pipe(
    name="MyPreLaunchAction",
    func=my_pre_launch_action,
    description="Описание того, что делает эта задача"
)
```

### Доступные статусы результатов

- `"ok"`: Успешное выполнение
- `"warning"`: Выполнено с предупреждениями
- `"error"`: Ошибка выполнения
- `"fatal"`: Критическая ошибка

### Логирование в скриптах

```python
import pipebridge

pipebridge.Logger.debug("Отладочное сообщение")
pipebridge.Logger.info("Информационное сообщение")
pipebridge.Logger.warning("Предупреждение")
pipebridge.Logger.error("Ошибка")
pipebridge.Logger.critical("Критическая ошибка")
```

### Примеры скриптов

#### Пример 1: Проверка файлов

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
            "message": f"Отсутствуют файлы: {', '.join(missing_files)}"
        }
    
    return {"status": "ok", "message": "Все файлы найдены"}

pipebridge.register_pipe(
    name="FileChecker",
    func=check_required_files,
    description="Проверка наличия необходимых файлов"
)
```

#### Пример 2: Очистка временных файлов

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
            return {"status": "ok", "message": "Временные файлы очищены"}
        except Exception as e:
            return {"status": "warning", "message": f"Не удалось очистить: {str(e)}"}
    
    return {"status": "ok", "message": "Временная директория не найдена"}

pipebridge.register_pipe(
    name="TempCleaner",
    func=cleanup_temp_files,
    description="Очистка временных файлов"
)
```

## 🖥️ Режимы запуска

### Консольный режим

```bash
ExeLaunchHandler.exe --config config.json
```

### Графический режим

```bash
ExeLaunchHandler.exe --config config.json --ui
```

### Параметры командной строки

- `--config <path>`: Путь к файлу конфигурации (обязательный)
- `--ui`: Запуск в режиме графического интерфейса
- `--help`: Показать справку

## 🔧 Архитектура проекта

```text
ExeLaunchHandler/
├── config/           # Модуль конфигурации
├── constants/        # Константы приложения
├── launch/           # Модуль запуска процессов
├── logging/          # Система логирования
├── pipes/            # Пайплайн и pipe-интерфейсы
├── python_bridge/    # Мост для Python-скриптов
├── results_api/      # API результатов выполнения
├── ui/               # Графический интерфейс (Qt)
├── third_party/      # Внешние библиотеки
└── scripts/          # Директория для Python-скриптов
```

### Ключевые компоненты

- **PipelineSync**: Синхронный исполнитель пайплайна
- **PyBridge::Adapter**: Адаптер для взаимодействия с Python
- **ConfigManager**: Менеджер конфигурации с поддержкой JSON
- **Logger**: Система логирования с различными уровнями
- **ProcessLauncher**: Запуск целевых процессов

## 📝 Примеры использования

## Обновление конфигурации из облака

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
        
        return {"status": "ok", "message": "Конфигурация обновлена"}
        
    except Exception as e:
        return {"status": "warning", "message": f"Не удалось обновить конфигурацию: {str(e)}"}

pipebridge.register_pipe("ConfigSync", sync_cloud_config, "Синхронизация конфигурации")
```

## 🤝 Contributing

1. Форкните репозиторий
2. Создайте ветку для новой функции (`git checkout -b feature/amazing-feature`)
3. Зафиксируйте изменения (`git commit -m 'Add amazing feature'`)
4. Отправьте ветку (`git push origin feature/amazing-feature`)
5. Откройте Pull Request

## 📄 Лицензия

Этот проект распространяется под лицензией MIT. См. файл `LICENSE` для получения дополнительной информации.

## 👨‍💻 Автор

Nikita Sadovskiy (yellow1cucumber)

- GitHub: [@yellow1cucumber](https://github.com/yellow1cucumber)

## 🐛 Отчеты об ошибках

Если вы нашли ошибку, пожалуйста, создайте issue в [GitHub Issues](https://github.com/yellow1cucumber/ExeLaunchHandler/issues).
